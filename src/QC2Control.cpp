#include "Arduino.h"
#include "QC2Control.h"

const unsigned int QC2Control::_WaitTime = 1500;

QC2Control::QC2Control(byte DpPin, byte DmPin):
    _DpPin(DpPin),
    _DmPin(DmPin),
    _handshakeDone(false),
    _setVoltage(5){
  //nothing to do
}

void QC2Control::begin(){
  //no real need to, just to make it clear
  pinMode(_DpPin, INPUT);
  pinMode(_DmPin, INPUT);
  
  //because the Arduino starts the right way we just wait till millis() passes
  //Has the advantage that if you call this last in setup, all other setup
  //stuff will be done while "waiting" :)
  while(millis() < _WaitTime  );
  
  digitalWrite(_DmPin, LOW);
  pinMode(_DmPin, OUTPUT);
  delay(2);
  
  _handshakeDone = true;
}

void QC2Control::setVoltage(byte volt){
  if(!_handshakeDone){
    begin();
  }
  
  _setVoltage = volt;
  
  switch(volt) {
    case 9:
      //this order, otherwise Dp is shortly low
      digitalWrite(_DpPin, HIGH);
      pinMode(_DpPin, OUTPUT);
      
      digitalWrite(_DmPin, HIGH);
      pinMode(_DmPin, OUTPUT);      
      break;
    case 12:
      pinMode(_DpPin, INPUT);
      
      digitalWrite(_DmPin, HIGH);
      pinMode(_DmPin, OUTPUT); 
      break;
    //in all other cases, save 5V
    default:
      pinMode(_DpPin, INPUT);
      pinMode(_DmPin, INPUT);
      
      //fix for invallid voltage
      _setVoltage = 5;
  }
}