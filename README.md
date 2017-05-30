# QC2Control
Set the voltage of a Quick Charge 2.0 source via the Arduino.  
By Timo Engelgeer (Septillion)

All credit goes to [Hugatry's HackVlog](https://www.youtube.com/channel/UCHgeChD442K0ah-KxEg0PHw) because he came up with the idea and first code. I just made a nicer wrapper :p

##What does it do?
Makes it possible to set the voltage (even on the fly) of a Quick Charge 2.0 source like a mains charger or power bank. Possible voltages are 5V (USB default), 9V or 12V. The source needs to support the [Quick Charge 2.0](https://www.qualcomm.com/products/features/quick-charge) technology form [Qualcomm](https://www.qualcomm.com/) in order to work.

###How to connect?
Diagram will come. For now, see video description of ["Set QuickCharge 2.0 PSU's Output Voltage With Arduino" (YouTube)](https://youtu.be/MldONoCgr20). It's the **new** two pin version.

##Download and install
###Library manager
Will come!

###GitHub
Latest release: **Release soon!**

1. Download the latest release.
2. Extract it to the `libraries` folder **inside** your Sketchbook. Default is `[user]\Arduino\libraries`. 
3. Rename the folder to `QC2Control` (remove version number).
4. Restart the Arduino IDE if you had it open.
5. Done!

###Update
You can update to the latest version of the library in the Library Manager as well. 

1.  Open the Arduino IDE (1.5 or above).
2.  In the tool-bar click Sketch -> Include Library -> Manage Libraries...
3.  Type in the search bar "QC2Control".
4.  The FadeLed library should show.
5.  Click on it and click Update.
6.  Done!

Alternatively you can download it from GitHub and simply unpack it over the current version (or remove the old version first).

##Usage
Just see this simple sketch
```C++
#include <QC2Control.h>

//Pin 4 for Data-
//Pin 5 for Data-
//See How to connect in the documentation for more details.
QC2Control quickCharge(4, 5);

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
  qickCharge.setVoltage(9);
  delay(1000);
  qickCharge.setVoltage(5);
  delay(1000);
  qickCharge.setVoltage(12);
}
```

**Please note**, delay() here is just used to demonstrate. Better not to stop the complete program with delay()'s.

## Full documentation
Full documentation of all the methods of this library can be found inside the library located in `QC2Control\doc`. Just open `QC2Control\doc\index.html` to see all methods of FadeLed. 

You can also view the documentation via [GitHub HTML Preview](https://htmlpreview.github.io/?https://github.com/septillion-git/QC2Control/blob/master/doc/index.html).

This documentation is powered by [Doxygen](http://www.doxygen.org/) and thus fully extracted from the source files. This README.md is also used as Main Page.

##FAQ

###Can I control more the one Quick Charge source with a single Arduino?
Yes you can! Just make multiple QC2Control objects connected to different pins. But be sure to connect GND of all power supplies (including QC2.0 sources) together but **not** the voltage rails.