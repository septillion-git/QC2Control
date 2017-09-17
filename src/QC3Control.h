/**
 *  @file
 *  @brief A simple Arduino library to set the voltage on a Quick Charge 3.0 charger.
 */
#pragma once

#include "Arduino.h"

/* 
 *  Params and return value constants
 */
 
#define QC_ERROR_OK                     0  /// Return value when everything was OK
#define QC_ERROR_QC2_ONLY               -1 /// Return value when a QC3 operation was requested but lib is in QC2 mode

/* 
 *  QC specification constants
 */
 
#define QC3_MIN_VOLTAGE_MV              3600
#define QC3_MAX_VOLTAGE_MV              12000

// timing values for Portable Device are not available, indicative values for a HVDCP taken from uP7104 datasheet https://www.upi-semi.com/files/1889/1b8dae21-e91a-11e6-97d5-f1910565ec6d
#define QC_T_GLICH_V_CHANGE_MS          60
#define QC_T_ACTIVE_MS                  1
#define QC_T_INACTIVE_MS                1

/**
 *  @brief Main class of the QC3Control-library
 *  
 *  The QC3Control-class includes all the functions to easily set the voltage of a Quick Charge 3.0 source..
 *  
 *  @see setVoltage() 
 */
class QC3Control{
  public:
    /**
     *  @brief Makes an object to control a Quick Charge 3.0 source.
     *  
     *  @details Makes it possible to set the voltage of the QC3.0 
     *  source to any supported voltage (between 3.6V and 12V). See general description on how to wire it.
     *  
     *  @param [in] DpPin Data+ pin 
     *  @param [in] DmHiPin Data- "High" pin
     *  @param [in] DmLoPin Data- "Low" pin. If 0, the library starts in QC2 mode
     */
    QC3Control(byte DpPin, byte DmHiPin, byte DmLoPin);

    /**
     *  @brief Makes an object to control a Quick Charge 2.0 source (QC2 mode).
     *  
     *  @details Makes it possible to set the voltage of the QC2.0 
     *  source to either 5V, 9V or 12V. This is backwards compatible with QCControl2.
     *  
     *  @param [in] DpPin Data+ pin 
     *  @param [in] DmPin Data- "High" pin. The lower side of the divider must be connected to GND.
     */
    QC3Control(byte DpPin, byte DmPin);
    
    /**
     *  @brief Starts the handshake with the QC3.0 source.
     *  
     *  @details A handshake is needed to be able to set the voltage. 
     *  begin() may be left out, in which case the first method modifying the voltage will silently call begin().
     *
     *  begin() is **blocking code**. It waits for a fixed period counting from the start up of the Arduino to act because the handshake needs a minimum time (1,25s minimum). But this is most likely not a problem because if you need 9V or 12V in your application, there is no gain in proceeding when the voltage isn't there yet (because of the handshake). And by putting begin() (or a call to setVoltage()) at the end of setup() (or other initialization) you can even do stuff while waiting because it counts from Arduino startup.
     *  
     *  @return QC_ERROR_OK if everything is OK
     *  
     *  @see setVoltage(), set5V(), set9V(), set12V()
     */
    int begin();
    
    /**
     *  @brief Sets the desired voltage of the QC3.0 source.
     *  
     *  @details Will set the voltage using continuous (QC3) mode. Setting an unreachable voltage will result in the closest supported voltage.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to setVoltage() will result in a call to begin() to do the handshake.
     *  
     *  @param [in] volt The desired voltage (between 3.6V and 12V).
     *  
     *  @return QC_ERROR_OK if everything is OK, or QC_ERROR_QC2_ONLY if library is in QC2 mode and requested voltage cannot be set 
     */
    int setVoltage(double volt);

    /**
     *  @brief Sets the desired voltage of the QC3.0 source.
     *  
     *  @details Same as setVoltage, but takes an integer value in milliVolts
     *  
     *  @see setVoltage()
     *
     *  @param [in] milliVolt The desired voltage in mV (between 3600mV and 12000mV).
     *  
     *  @return QC_ERROR_OK if everything is OK, or QC_ERROR_QC2_ONLY if library is in QC2 mode and requested voltage cannot be set 
     *  
     */
    int setMilliVoltage(unsigned int milliVolt);
    
    
    /**
     *  @brief Return the last voltage that was requested.
     *  
     *  @details This will be a value between 3.6 and 12V.
     *  
     *  @note The library has no notion if the voltage is really set. It just tries to set it but if you just start it all of a QC3.0 source it should set the correct voltage.
     *  
     *  @return The last requested voltage
     */
    double getVoltage();
    
    /**
     *  @brief Return the last voltage that was requested.
     *  
     *  @details Same as getVoltage, but returns an integer value in milliVolts
     *  
     *  @note The library has no notion if the voltage is really set. It just tries to set it but if you just start it all of a QC3.0 source it should set the correct voltage.
     *  
     *  @return The last requested voltage
     */
    unsigned int getMilliVoltage();
    
    
    /**
     *  @brief Set voltage to 5V
     *  
     *  @return Sets the output of the QC source to 5V using discrete (QC2) mode.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to setVoltage() will result in a call to begin() to do the handshake.
     *  
     *  @return QC_ERROR_OK if everything is OK 
     */
    int set5V();
    
    /**
     *  @brief Set voltage to 9V
     *  
     *  @return Sets the output of the QC source to 9V using discrete (QC2) mode.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to setVoltage() will result in a call to begin() to do the handshake.
     *  
     *  @return QC_ERROR_OK if everything is OK 
     */
    int set9V();
    
    /**
     *  @brief Set voltage to 12V
     *  
     *  @return Sets the output of the QC source to 12V using discrete (QC2) mode.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to setVoltage() will result in a call to begin() to do the handshake.
     *  
     *  @return QC_ERROR_OK if everything is OK 
     */
    int set12V();

    /**
     *  @brief Increment the desired voltage of the QC3.0 source by 200mV.
     *  
     *  @details Will request an increment of the voltage by 200mV. Performing the increment request when the maximum value is already reached has no effect.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to incrementVoltage() will result in a call to begin() to do the handshake, then the voltage will be incremented starting from 5V
     *  
     *  @return QC_ERROR_OK if everything is OK, or QC_ERROR_QC2_ONLY if library is in QC2 mode 
     */
    int incrementVoltage();

    /**
     *  @brief Decrement the desired voltage of the QC3.0 source by 200mV.
     *  
     *  @details Will request a decrement of the voltage by 200mV. Performing the decrement request when the minimum value is already reached has no effect.
     *  
     *  @note If no handshake has been done (via begin()) with the QC source, the first call to decrementVoltage() will result in a call to begin() to do the handshake, then the voltage will be decremented starting from 5V
     *  
     *  @return QC_ERROR_OK if everything is OK, or QC_ERROR_QC2_ONLY if library is in QC2 mode 
     */
    int decrementVoltage();

  
  protected:
    const byte _DpPin; //!< Data+ pin
    const byte _DmHiPin; //!< Data- "high" pin
    const byte _DmLoPin; //!< Data- "low" pin. If set to 0, library is in QC2 mode
    
    bool _handshakeDone; //!< Is the handshake done?
    bool _continuousMode; //!< Are we in QC3 continuous adjustment mode?
  
    unsigned int _milliVoltNow; //!< Voltage currently set (in mV). Avoiding the term "current milliVolt" to prevent confusion between "current" and "voltage" :-)
    
    static const unsigned int _WaitTime; //!< Wait time in the handshake. Should be at least 1,25s

    int QC3Control::switchToContinuousMode();

    // Low level functions to obtain desired voltages    
    void dm0V();
    void dm600mV();
    void dm3300mV();
    void dp600mV();
    void dp3300mV();
};

