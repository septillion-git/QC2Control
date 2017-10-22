#include "Arduino.h"
#include "QC3Control.h"

/* 
 *  QC specification constants
 *  Derived from http://www.upi-semi.com/files/1889/1b8dae21-e91a-11e6-97d5-f1910565ec6d
 */
const unsigned int QC3Control::MinMilliVoltage = 3600;
const unsigned int QC3Control::MaxMilliVoltageClassA = 12000;
const unsigned int QC3Control::MaxMilliVoltageClassB = 20000;
const unsigned int QC3Control::QCHandshakeTime = 1500;
const unsigned int QC3Control::QCModeChangeTime = 60;
const unsigned int QC3Control::QCActiveTime = 1;
const unsigned int QC3Control::QCInactiveTime = 1;

QC3Control::QC3Control(byte DpPin, byte DmPin, byte DmGndPin):
  _DpPin(DpPin),
  _DmPin(DmPin),
  _DmGndPin(DmGndPin),
  _handshakeDone(false),
  _continuousMode(false),
  _milliVoltNow(5000) {
    //nothing to do
  }

QC3Control::QC3Control(byte DpPin, byte DmPin):
  QC3Control(DpPin, DmPin, 255) {
    //nothing to do
  }

void QC3Control::begin() {
    begin(false);
}

void QC3Control::begin(bool classB) {
  
  _classB = classB;
  
  // The spec requires that D+ remains at 0.6V during _WaitTime.
  dp600mV(); // Setting D+ to 0.6V is done by default (Arduino pins are input on boot)
  if (_DmGndPin != 255) {
    // We're in "QC2 schema" + DmGndPin mode
    dmHiZ(); // Which is done by default

    //because the Arduino starts the right way we just wait till millis() passes
    //Has the advantage that if you call this last in setup, all other setup
    //stuff will be counted as "waiting" :)
    // After QCHandshakeTime, the QC source removes the short between D+ and D- and pulls D- down. 
    // We need to stay in this state for at least 2 more milliseconds before we can start requesting voltages.
    while(millis() < QCHandshakeTime + 2 ); 
  }
  else {
    // We're in "QC3 schema". There's no way to let D- "float", but setting it to 0.6V will prevent the D+/D- short from pulling D+/D- down
    dm600mV(); // Which is done by default

    //because the Arduino starts the right way we just wait till millis() passes
    //Has the advantage that if you call this last in setup, all other setup
    //stuff will be counted as "waiting" :)
    while(millis() < QCHandshakeTime); 

    // After QCHandshakeTime, the QC source removes the short between D+ and D- and pulls D- down. 
    // We need to stay in this state for at least 2 more milliseconds before we can start requesting voltages.
    dm0V(); // "Acknowledge" by simulating that we "follow" the internal pull down
    delay(2);
  }
    
  _handshakeDone = true;
  _continuousMode = false;
}

void QC3Control::set5V() {
  if(!_handshakeDone){
    begin();
  }
  
  dp600mV();
  dm0V();

  delay(QCModeChangeTime);

  _milliVoltNow = 5000;
  _continuousMode = false;
}

void QC3Control::set9V() {
  if(!_handshakeDone){
    begin();
  }

  if (_continuousMode) {
    // Transition from continous to discrete values requires first going to 5V
    set5V();
  }
  
  dp3300mV();
  dm600mV();
  
  delay(QCModeChangeTime);

  _milliVoltNow = 9000;
  _continuousMode = false;
}

void QC3Control::set12V() {
  if(!_handshakeDone){
    begin();
  }

  if (_continuousMode) {
    // Transition from continous to discrete values requires first going to 5V
    set5V();
  }

  dp600mV();
  dm600mV();

  delay(QCModeChangeTime);

  _milliVoltNow = 12000;
  _continuousMode = false;
}

void QC3Control::set20V() {
  if (_classB) {
    if(!_handshakeDone){
      begin();
    }

    if (_continuousMode) {
      // Transition from continous to discrete values requires first going to 5V
      set5V();
    }

    dp3300mV();
    dm3300mV();

    delay(QCModeChangeTime);

    _milliVoltNow = 20000;
    _continuousMode = false;
  }
}

void QC3Control::incrementVoltage() {
  if(!_handshakeDone){
    begin();
  }
  if (_milliVoltNow < (_classB ? MaxMilliVoltageClassB : MaxMilliVoltageClassA)) {
    if(!_continuousMode) {
      switchToContinuousMode();
    }
    // From http://www.onsemi.com/pub/Collateral/NCP4371-D.PDF :
    // "For the single request, an HVDCP recognizes a rising edge on D+ for an increment ..." 
    dp3300mV();
    delay(QCActiveTime);
    dp600mV();
    delay(QCInactiveTime);  
  } 

  _milliVoltNow += 200;
}

void QC3Control::decrementVoltage() {
  if(!_handshakeDone){
    begin();
  }
  if (_milliVoltNow > MinMilliVoltage) {
    if(!_continuousMode) {
      switchToContinuousMode();
    }

    // From http://www.onsemi.com/pub/Collateral/NCP4371-D.PDF :
    // "... and falling edge on D− for a decrement" 
    dm600mV();
    delay(QCActiveTime);
    dm3300mV();
    delay(QCInactiveTime);  
  }
  _milliVoltNow -= 200;
}


/* Returns the closest multiple of 200
 * e.g. passing 4901 or 4950 or 4999 or 5000 or 5001 or 5050 or 5100 returns 5000
 */
unsigned int getClosestValidMilliVolt(unsigned int mV){
  return 200 * ((mV + 99) / 200);
}

void QC3Control::setMilliVoltage(unsigned int milliVolt){
  if(!_handshakeDone){
    begin();
  }

  if (milliVolt <= MinMilliVoltage) {
    // below lower boundary: limit
    milliVolt = MinMilliVoltage;
  }
  else if (milliVolt >= (_classB ? MaxMilliVoltageClassB : MaxMilliVoltageClassA)) {
    // above upper boundary: limit
    milliVolt = (_classB ? MaxMilliVoltageClassB : MaxMilliVoltageClassA);
  }
  else {
    // within boundaries: round
    milliVolt = getClosestValidMilliVolt(milliVolt); // useful if an invalid value was passed
  }
  
  if(milliVolt == _milliVoltNow) return;

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
}

void QC3Control::setVoltage(double volt){
  unsigned int milliVolt = getClosestValidMilliVolt(volt * 1000); // useful if an invalid value was passed, but also for rounding errors from double arithmetics
  // For backwards compatibility with QC2Control, these specific values are always reached in discrete mode. Use setMilliVoltage if you want to avoid that
  switch(milliVolt) {
    case 5000:
      set5V();
      break;
    case 9000:
      set9V();
      break;
    case 12000:
      set12V();
      break;
    default:
      setMilliVoltage(milliVolt);
  }
}


inline double QC3Control::getVoltage(){
  return _milliVoltNow/1000.0;
}

inline unsigned int QC3Control::getMilliVoltage(){
  return _milliVoltNow;
}


// Non-public function

void QC3Control::switchToContinuousMode() {

  dp600mV();
  dm3300mV();

  delay(QCModeChangeTime);

  _continuousMode = true;
}


// Low level functions to obtain desired voltages

inline void QC3Control::dmHiZ() {
  if (_DmGndPin != 255) {
    // "disconnect" DM resistors : D- will be pulled down by QC source
    pinMode(_DmPin, INPUT); 
    pinMode(_DmGndPin, INPUT);
  }
  else {
    // Hi-Z is impossible with this hardware !
  }
}

inline void QC3Control::dm0V() {
  if (_DmGndPin != 255) {
    pinMode(_DmPin, INPUT); // "disconnect" DM top resistor
    digitalWrite(_DmGndPin, LOW);
    pinMode(_DmGndPin, OUTPUT); // and pull D- down
  }
  else {
    digitalWrite(_DmPin, LOW);
    pinMode(_DmPin, OUTPUT); // pull D- down
  }
}

inline void QC3Control::dm600mV() {
  if (_DmGndPin != 255) {  
    digitalWrite(_DmPin, HIGH); // Activate DM divider so it sets D- to about 0.6V
    pinMode(_DmPin, OUTPUT);
    digitalWrite(_DmGndPin, LOW);
    pinMode(_DmGndPin, OUTPUT);
  }
  else {
    pinMode(_DmPin, INPUT); // Let the DM divider set D- to about 0.6V
  }
}

inline void QC3Control::dm3300mV() {
  if (_DmGndPin != 255) {  
    digitalWrite(_DmPin, HIGH); // Pull D- up (3.3V minimum)
    pinMode(_DmPin, OUTPUT);  
    pinMode(_DmGndPin, INPUT);     // And leave DM bottom resistor "unconnected" 
  }
  else {
    digitalWrite(_DmPin, HIGH); // Pull D- up (3.3V minimum)
    pinMode(_DmPin, OUTPUT);
  }
}

inline void QC3Control::dp600mV() {
  pinMode(_DpPin, INPUT); // Let the DP divider set D+ to about 0.6V
}

inline void QC3Control::dp3300mV() {
  digitalWrite(_DpPin, HIGH); // Pull D+ up (3.3V minimum)
  pinMode(_DpPin, OUTPUT);
}

