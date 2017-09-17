#include "Arduino.h"
#include "QC3Control.h"

const unsigned int QC3Control::_WaitTime = 1500;

QC3Control::QC3Control(byte DpPin, byte DmHiPin, byte DmLoPin):
  _DpPin(DpPin),
  _DmHiPin(DmHiPin),
  _DmLoPin(DmLoPin),
  _handshakeDone(false),
  _continuousMode(false),
  _milliVoltNow(5000) {
    //nothing to do
  }

QC3Control::QC3Control(byte DpPin, byte DmPin):
  _DpPin(DpPin),
  _DmHiPin(DmPin),
  _DmLoPin(0),
  _handshakeDone(false),
  _continuousMode(false),
  _milliVoltNow(5000) {
    //nothing to do
  }

int QC3Control::begin() {
  //not really needed if just booted, just to make it clear
  dp600mV();
  dm0V();
    
  //because the Arduino starts the right way we just wait till millis() passes
  //Has the advantage that if you call this last in setup, all other setup
  //stuff will be counted as "waiting" :)
  while(millis() < _WaitTime + 2 );
 
  // After _WaitTime, the QC3.0 source removes the short between D+ and D- and pulls D- down. 
  // We need to stay in this state for at least 2ms before we can start requesting voltages.
  
  _handshakeDone = true;
  _continuousMode = false;
  
  return QC_ERROR_OK;
}

int QC3Control::set5V() {
  if(!_handshakeDone){
    begin();
  }
  
  dp600mV();
  dm0V();

  delay(QC_T_GLICH_V_CHANGE_MS);

  _milliVoltNow = 5000;
  _continuousMode = false;
  
  return QC_ERROR_OK;
}

int QC3Control::set9V() {
  if(!_handshakeDone){
    begin();
  }

  if (_continuousMode) {
    // Transition from continous to discrete values requires first going to 5V
    set5V();
  }
  
  dp3300mV();
  dm600mV();
  
  delay(QC_T_GLICH_V_CHANGE_MS);

  _milliVoltNow = 9000;
  _continuousMode = false;
  
  return QC_ERROR_OK;
}

int QC3Control::set12V() {
  if(!_handshakeDone){
    begin();
  }

  if (_continuousMode) {
    // Transition from continous to discrete values requires first going to 5V
    set5V();
  }

  dp600mV();
  dm600mV();

  delay(QC_T_GLICH_V_CHANGE_MS);

  _milliVoltNow = 12000;
  _continuousMode = false;
  
  return QC_ERROR_OK;
}

int QC3Control::incrementVoltage() {
  if (_DmLoPin == 0) return QC_ERROR_QC2_ONLY;
  
  if(!_handshakeDone){
    begin();
  }
  if (_milliVoltNow < QC3_MAX_VOLTAGE_MV) {
    if(!_continuousMode) {
      switchToContinuousMode();
    }
    // From http://www.onsemi.com/pub/Collateral/NCP4371-D.PDF :
    // "For the single request, an HVDCP recognizes a rising edge on D+ for an increment ..." 
    dp3300mV();
    delay(QC_T_ACTIVE_MS);
    dp600mV();
    delay(QC_T_INACTIVE_MS);  
  } 

  _milliVoltNow += 200;
  
  return QC_ERROR_OK;
}

int QC3Control::decrementVoltage() {
  if (_DmLoPin == 0) return QC_ERROR_QC2_ONLY;

  if(!_handshakeDone){
    begin();
  }
  if (_milliVoltNow > QC3_MIN_VOLTAGE_MV) {
    if(!_continuousMode) {
      switchToContinuousMode();
    }

    // From http://www.onsemi.com/pub/Collateral/NCP4371-D.PDF :
    // "... and falling edge on D− for a decrement" 
    dm600mV();
    delay(QC_T_ACTIVE_MS);
    dm3300mV();
    delay(QC_T_INACTIVE_MS);  
  }
  _milliVoltNow -= 200;
  
  return QC_ERROR_OK;
}


/* Returns the closest multiple of 200
 * e.g. passing 4901 or 4950 or 4999 or 5000 or 5001 or 5050 or 5100 returns 5000
 */
unsigned int getClosestValidMilliVolt(unsigned int mV){
  return 200* ((mV + 99) / 200);
}

int QC3Control::setMilliVoltage(unsigned int milliVolt){
  if(!_handshakeDone){
    begin();
  }

  if (milliVolt <= QC3_MIN_VOLTAGE_MV) milliVolt = QC3_MIN_VOLTAGE_MV;
  else if (milliVolt >= QC3_MAX_VOLTAGE_MV) milliVolt = QC3_MAX_VOLTAGE_MV;
  else milliVolt = getClosestValidMilliVolt(milliVolt); // useful if an invalid value was passed, but also for rounding errors from double arithmetics  
  
  if(milliVolt == _milliVoltNow) return;

  if (_DmLoPin == 0) return QC_ERROR_QC2_ONLY;
  
  if (milliVolt > _milliVoltNow) {
    while (_milliVoltNow < milliVolt) {
      incrementVoltage();
    }
  }
  else {
    while (_milliVoltNow > milliVolt) {
      decrementVoltage();
    }
  }
  
  return QC_ERROR_OK;
}

int QC3Control::setVoltage(double volt){
  return setMilliVoltage((unsigned int)(volt*1000)); // possible rounding errors will be taken care of later
}


inline double QC3Control::getVoltage(){
  return _milliVoltNow/1000.0;
}

inline unsigned int QC3Control::getMilliVoltage(){
  return _milliVoltNow;
}


// Non-public function

int QC3Control::switchToContinuousMode() {
  if (_DmLoPin == 0) return QC_ERROR_QC2_ONLY;

  dp600mV();
  dm3300mV();

  delay(QC_T_GLICH_V_CHANGE_MS);

  _continuousMode = true;
  
  return QC_ERROR_OK;
}


// Low level functions to obtain desired voltages

inline void QC3Control::dm0V() {
//  pinMode(_DmHiPin, INPUT); // "disconnect" DM resistors : D- will be pulled down by QC source
//  if (_DmLoPin != 0) {pinMode(_DmLoPin, INPUT); // "disconnect" DM resistors : D- will be pulled down by QC source

  pinMode(_DmHiPin, INPUT); // "disconnect" DM top resistor
  if (_DmLoPin != 0) {      // and pull D- down (if not already to GND)
    digitalWrite(_DmLoPin, LOW);
    pinMode(_DmLoPin, OUTPUT);
  }
}

inline void QC3Control::dm600mV() {
  digitalWrite(_DmHiPin, HIGH); // Activate DM divider so it sets D- to about 0.6V
  pinMode(_DmHiPin, OUTPUT);
  if (_DmLoPin !=0) {  
    digitalWrite(_DmLoPin, LOW);
    pinMode(_DmLoPin, OUTPUT);
  }
}

inline void QC3Control::dm3300mV() {
  digitalWrite(_DmHiPin, HIGH); // Pull D- up (3.3V minimum)
  pinMode(_DmHiPin, OUTPUT);  
  if (_DmLoPin !=0) {  
    pinMode(_DmLoPin, INPUT);     // And leave DM bottom resistor "unconnected" 
  }
}

inline void QC3Control::dp600mV() {
  pinMode(_DpPin, INPUT); // Let the DP divider set D+ to about 0.6V
}

inline void QC3Control::dp3300mV() {
  digitalWrite(_DpPin, HIGH); // Pull D+ up (3.3V minimum)
  pinMode(_DpPin, OUTPUT);
}

