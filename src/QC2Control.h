/**
 *  @file
 *  @brief A simple Arduino library to set the voltage on a Quick Charge 2.0 charger.
 */
#pragma once

#include "Arduino.h"

/**
 *  @brief Main class of the QC2Control-library
 *  
 *  The QC2Control-class includes all the functions to easily set the voltage of a Quick Charge 2.0 source..
 *  
 *  @see setVoltage() 
 */
class QC2Control{
  public:
    /**
     *  @brief Makes an object to control a Quick Charge 2.0 source.
     *  
     *  @details Makes it possible to set the voltage of the QC2.0 
     *  source to 5V, 9V or 12V.) See general description on how to wire it.
     *  
     *  @param [in] DpPin Data+ pin 
     *  @param [in] DmPin Data- pin
     */
    QC2Control(byte DpPin, byte DmPin);
    
    /**
     *  @brief Starts the handshake with the QC2.0 source.
     *  
     *  @details A handshake is needed to be able to set the voltage. begin() may
     *  be left out, a calling setVoltage() will call begin() if it's not already.
     *  
     *  @see setVoltage(), set5V(), set9V(), set12V()
     */
    void begin();
    
    /**
     *  @brief Sets the desired voltage of the QC2.0 source.
     *  
     *  @details Possible voltages are 5V, 9V and 12V. Any other number will result in 5V. 
     *  
     *  begin() is **blocking code**. It waits for a fixed period counting from the start up of the Arduino to act because the handshake needs a minimum time (1,25s minimum). But this is most likely not a problem because if you need 9V or 12V in your application, there is no gain in proceeding when the voltage isn't there yet (because of the handshake). And by putting begin() (or a call to setVoltage()) at the end of setup() (or other initialization) you can even do stuff while waiting because it counts from Arduino startup.
     *  
     *  @note If no handshake has been done (via begin()) with the QC2.0 source the first call to setVoltage() will result in a call to begin() to do the handshake.
     *  
     *  @param [in] volt The desired voltage, 5, 9 or 12.
     */
    void setVoltage(byte volt);
    
    /**
     *  @brief Return the current voltage set.
     *  
     *  @details This can be 5V, 9V or 12V
     *  
     *  @note The library has no notion if the voltage is really set. It just tries to set it but if you just start it all of a QC2.0 source it should set the correct voltage.
     *  
     *  @return The current set voltage
     */
    byte getVoltage();
    
    
    /**
     *  @brief Set voltage to 5V
     *  
     *  @return Sets the output of the QC2.0 source to 5V. Short for setVoltage(5).
     *  
     *  @see setVoltage()
     */
    void set5V();
    
    /**
     *  @brief Set voltage to 9V
     *  
     *  @return Sets the output of the QC2.0 source to 9V. Short for setVoltage(9).
     *  
     *  @see setVoltage()
     */
    void set9V();
    
    /**
     *  @brief Set voltage to 12V
     *  
     *  @return Sets the output of the QC2.0 source to 12V. Short for setVoltage(12).
     *  
     *  @see setVoltage()
     */
    void set12V();
  
  protected:
    const byte _DpPin; //!< Data+ pin
    const byte _DmPin; //!< Data- pin
    
    bool _handshakeDone; //!< Is the handshake done? 
    byte _setVoltage; //!< Current set voltage
    
    static const unsigned int _WaitTime; //!< Wait time in the handshake. Should be at least 1,25s
};

inline void QC2Control::set5V(){
  setVoltage(5);
}

inline void QC2Control::set9V(){
  setVoltage(9);
}

inline void QC2Control::set12V(){
  setVoltage(12);
}

inline byte QC2Control::getVoltage(){
  return _setVoltage;
}