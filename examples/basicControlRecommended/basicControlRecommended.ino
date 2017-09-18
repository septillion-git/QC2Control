#include <QC3Control.h>

//Pin 4 for Data+
//Pin 5 for DataHi-
//Pin 6 for DataLo-
//See How to connect in the documentation for more details.
QC3Control quickCharge(4, 5, 6);

void setup() {
  //Optional
  //quickCharge.begin();

  //set voltage to 12V
  quickCharge.set12V();
  //Same as
  //quickCharge.setVoltage(12);

  delay(1000);
}

void loop() {
  //And you can change it on the fly
  delay(1000);
  quickCharge.setVoltage(9);
  delay(1000);
  quickCharge.setVoltage(5);
  delay(1000);
  quickCharge.setVoltage(12);
  delay(1000);
  quickCharge.setVoltage(7.6);
  delay(1000);
  quickCharge.incrementVoltage();
}
