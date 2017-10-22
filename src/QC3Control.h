/**
 *  @file
 *  @brief A simple Arduino library to set the voltage on a Quick Charge 3.0 charger.
 */
#pragma once

#include "Arduino.h"

/* 
 *  QC specification constants
 */
 
#define QC3_MIN_VOLTAGE_MV              3600
#define QC3_CLASS_A_MAX_VOLTAGE_MV      12000
#define QC3_CLASS_B_MAX_VOLTAGE_MV      20000

// timing values for Portable Device are not available, indicative values for a HVDCP charger were taken from the uP7104 datasheet https://www.upi-semi.com/files/1889/1b8dae21-e91a-11e6-97d5-f1910565ec6d
#define QC_T_GLITCH_BC_DONE_MS          1500
#define QC_T_GLICH_V_CHANGE_MS          60
#define QC_T_ACTIVE_MS                  1
#define QC_T_INACTIVE_MS                1

/**
 *  @brief Main class of the QC3Control-library
 *  
 *  The QC3Control-class includes all the functions to easily set the voltage of a Quick Charge 3.0 source..
 *  
 *  @see setMilliVoltage(unsigned int) 
 */
class QC3Control{
  public:
    /**
     *  @brief Makes an object to control a Quick Charge source with a recommended "2-wire" circuit
     *  
     *  @details Makes it possible to set the voltage of the QC source to 5V, 9V or 12V (with a QC2.0 or later charger) 
     *  or to any supported voltage between 3.6V and 12V (with a QC3.0 or later charger).
     *  Call this constructor if you are using a recommended "2-wire" circuit. 
     *  See general description on how to wire it.
     *  
     *  @param [in] DpPin Data+ pin connected to the middle of the D+ 1K5-10K bridge via a 470R resistor 
     *  @param [in] DmPin Data- pin connected to the middle of the D- 1K5-10K bridge via a 470R resistor 
     */
    QC3Control(byte DpPin, byte DmPin);
    
    /**
     *  @brief Makes an object to control a Quick Charge 3.0 source with a legacy "3-wire" circuit
     *  
     *  @details Makes it possible to set the voltage of the QC source to 5V, 9V or 12V (with a QC2.0 or later charger) 
     *  or to any supported voltage between 3.6V and 12V (with a QC3.0 or later charger).
     *  Call this constructor if you are using a legacy "3-wire" circuit (try this if the "2-wire" circuit fails). 
     *  See general description on how to wire it.
     *  
     *  @param [in] DpPin Data+ pin connected to the middle of the D+ 1K5-10K bridge via a 470R resistor 
     *  @param [in] DmPin Data- pin connected to the top of the D- 1K5-10K bridge
     *  @param [in] DmGndPin pin connected to the bottom of the D- 1K5-10K bridge
     */
    QC3Control(byte DpPin, byte DmPin, byte DmGndPin);

    /**
     *  @brief Starts the handshake with the QC source in "class A" (up to 12V).
     *  
     *  @details A handshake is needed to be able to set the voltage. 
     *  begin() may be left out, in which case the first method modifying the voltage will silently call begin().
     *
     *  begin() is **blocking code**. It waits for a fixed period counting from the start up of the Arduino to act because the handshake needs a minimum time. But this is most likely not a problem because if you need 9V or 12V in your application, there is no gain in proceeding when the voltage isn't there yet (because of the handshake). And by putting begin() (or a call to one of the setXXX() functions) at the end of setup() (or other initialization) you can even do stuff while waiting because it counts from Arduino startup.
     *  
     *  @see begin(bool), setMilliVoltage(unsigned int), set5V(), set9V(), set12V()
     */
    void begin();

    /**
     *  @brief Starts the handshake with the QC source, specifying whether the source is "class B" compliant (up to 20V) or not.
     *  
     *  @details A handshake is needed to be able to set the voltage. 
     *  begin() may be left out, in which case the first method modifying the voltage will silently call begin(false).
     *
     *  begin() is **blocking code**. It waits for a fixed period counting from the start up of the Arduino to act because the handshake needs a minimum time. But this is most likely not a problem because if you need 9V or 12V in your application, there is no gain in proceeding when the voltage isn't there yet (because of the handshake). And by putting begin() (or a call to one of the setXXX() functions) at the end of setup() (or other initialization) you can even do stuff while waiting because it counts from Arduino startup.
     *  
     *  @see begin(), setMilliVoltage(unsigned int), set5V(), set9V(), set12V(), set20V()
     */
    void begin(bool classB);


    /**
     *  @brief (deprecated - use setMilliVoltage()) Sets the desired voltage of the QC source.
     *  
     *  @details Will set the passed voltage either using discrete (QC2) mode for 5V, 9V and 12V (for backwards compatibility with QC2Control API), or using continuous (QC3) mode for all other values. Please use setMilliVoltage() to avoid this behaviour.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to setVoltage() will result in a call to begin() to do the handshake.
     *  @note Setting an unreachable voltage will result in the closest supported voltage being set.
     *  @note Calling this method on a QC2 charger will only work for 5V, 9V or 12V.
     *  
     *  @param [in] volt The desired voltage (between 3.6V and 12V).
     *  
     *  @see setMilliVoltage(unsigned int), set5V(), set9V(), set12V()
     */
    void setVoltage(double volt);

    /**
     *  @brief Sets the desired voltage of the QC3.0 source.
     *  
     *  @details Will always set the passed voltage using continuous (QC3) mode (even for 5V, 9V, 12V and 20V). 
     *  To force usage of discrete (QC2) mode, please use set5V(), set9V(), set12V() or set20V();
     *
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to setMilliVoltage() will result in a call to begin() to do the handshake.
     *  @note Setting an unreachable voltage will result in the closest supported voltage being set.
     *  @note Calling this method on a QC2 charger will not work.
     *  
     *  @see set5V(), set9V(), set12V()
     *
     *  @param [in] milliVolt The desired voltage in mV (between 3600mV and 12000mV).
     *  
     */
    void setMilliVoltage(unsigned int milliVolt);
    
    
    /**
     *  @brief (deprecated - use getMilliVoltage()) Return the voltage that the charger is supposed to currently provide.
     *  
     *  @details This will be a value between 3.6 and 12V.
     *  
     *  @note The library has no feedback if that voltage is actually provided. It just takes note of the operations requested to the charger and computes the voltage that the charger is supposed to output now.
     *  
     *  @see getMilliVoltage()
     *  
     *  @return The voltage that the charger is supposed to currently provide, in Volt
     */
    double getVoltage();
    
    /**
     *  @brief Return the voltage that the charger is supposed to currently provide.
     *  
     *  @details Same as getVoltage, but returns an integer value in milliVolts
     *  
     *  @note The library has no notion if the voltage is really set. It just tries to set it but if you just start it all of a QC3.0 source it should set the correct voltage.
     *  
     *  @see getVoltage()
     *  
     *  @return The voltage that the charger is supposed to currently provide, in milliVolt
     */
    unsigned int getMilliVoltage();
    
    
    /**
     *  @brief Set voltage to 5V
     *  
     *  @details Sets the output of the QC source to 5V using discrete (QC2) mode.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to set5V() will result in a call to begin() to do the handshake.
     */
    void set5V();


    /**
     *  @brief Set voltage to 9V
     *  
     *  @details Sets the output of the QC source to 9V using discrete (QC2) mode.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to set9V() will result in a call to begin() to do the handshake.
     */
    void set9V();


    /**
     *  @brief Set voltage to 12V
     *  
     *  @details Sets the output of the QC source to 12V using discrete (QC2) mode.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to set12V() will result in a call to begin() to do the handshake.
     */
    void set12V();


    /**
     *  @brief Set voltage to 20V
     *  
     *  @details Sets the output of the QC Class B source to 20V using discrete mode.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to set20V() will result in a call to begin() to do the handshake.
     */
    void set20V();


    /**
     *  @brief Increment the desired voltage of the QC3.0 source by 200mV.
     *  
     *  @details Will request an increment of the voltage by 200mV. Performing the increment request when the maximum value is already reached has no effect.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to incrementVoltage() will result in a call to begin() to do the handshake, then the voltage will be incremented starting from 5V
     */
    void incrementVoltage();


    /**
     *  @brief Decrement the desired voltage of the QC3.0 source by 200mV.
     *  
     *  @details Will request a decrement of the voltage by 200mV. Performing the decrement request when the minimum value is already reached has no effect.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to decrementVoltage() will result in a call to begin() to do the handshake, then the voltage will be decremented starting from 5V
     */
    void decrementVoltage();

  
  protected:
    const byte _DpPin; //!< Data+ pin connected to the middle of the D+ 1K5-10K bridge via a 470R resistor 
    const byte _DmPin; //!< Data- pin connected either to the middle of the D- 1K5-10K bridge via a 470R resistor (in recommended "2-wire" circuit), or to the top of the D- 1K5-10K bridge (in legacy "3-wire" circuit)
    const byte _DmGndPin; //!< Pin pin connected to the bottom of the D- 1K5-10K bridge in legacy "3-wire" circuit. Must be 0 if using a recommended "2-wire" circuit
    
    bool _handshakeDone; //!< Is the handshake done?
    bool _continuousMode; //!< Are we in continuous adjustment (QC3) mode?
    bool _classB; //!< Do we have a class B QC source (up to 20V) ?
  
    unsigned int _milliVoltNow; //!< Voltage currently set (in mV). Using the word "now" instead of "current" to prevent confusion between "current" and "voltage" :-)
    
    void QC3Control::switchToContinuousMode(); //!< Switches to continues mode

    // Low level functions to obtain desired voltages    
    void dmHiZ(); //!< Sets Data- pin to floating
    void dm0V(); //!< Sets Data- pin to 0V
    void dm600mV(); //!< Sets Data- pin to 600mV
    void dm3300mV(); //!< Sets Data- pin to 3,3V
    void dp600mV(); //!<Sets Data+ pin to 600mV
    void dp3300mV(); //!< Sets Data+ pin to 3,3V
};

