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

  delay(1000);
}

void loop() {
  //And you can change it on the fly
  delay(1000);
  quickCharge.set9V();
  delay(1000);
  quickCharge.set5V();
  delay(1000);
  quickCharge.setMilliVoltage(6000);
  delay(1000);
  for (int i = 0; i < 10; i++) quickCharge.decrementVoltage();
  delay(1000);
  quickCharge.set12V();
}
