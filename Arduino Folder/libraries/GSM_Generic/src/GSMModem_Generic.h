/*********************************************************************************************************************************
  GSMModem_Generic.h
  
  For ESP8266, ESP32, SAMD21/SAMD51, nRF52, SAM DUE, Teensy and STM32 with GSM modules
  
  GSM_Generic is a library for the ESP8266, ESP32, SAMD21/SAMD51, nRF52, SAM DUE, Teensy and STM32 with GSM modules
  
  Based on and modified from MKRGSM Library (https://github.com/arduino-libraries/MKRGSM)
  
  Built by Khoi Hoang https://github.com/khoih-prog/GSM_Generic
  Licensed under GNU Lesser General Public License
  
  Copyright (C) 2017  Arduino AG (http://www.arduino.cc/)
  This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License 
  as published by the Free Software Foundation, either version 2.1 of the License, or (at your option) any later version.
  This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty 
  of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
  You should have received a copy of the GNU General Public License along with this program.
  If not, see <https://www.gnu.org/licenses/>.  
 
  Version: 1.4.0
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.2.4    K Hoang     11/03/2021 Initial public release to add support to many boards / modules besides MKRGSM 1400 / SARA U201
  1.3.0    K Hoang     31/03/2021 Add ThingStream MQTTS support. Fix SMS receive bug.
  1.3.1    K Hoang     25/04/2021 Fix bug making ESP32 reset repeatedly.
  1.4.0    K Hoang     28/06/2021 Add support to RP2040-based boards using Arduino mbed or Arduino-pico core
 **********************************************************************************************************************************/

#pragma once

#ifndef _GSM_MODEM_H_INCLUDED
#define _GSM_MODEM_H_INCLUDED

#include <Arduino.h>

#include "GSM_Generic_Debug.h"

class GSMModem 
{
  public:

    /** Constructor */
    GSMModem();

    /** Check modem response and restart it
    */
    int begin(unsigned long baud = 115200);

    /** Obtain modem IMEI (command AT)
        @return modem IMEI number
    */
    String getIMEI();

    /** Obtain SIM card ICCID (command AT)
        @return SIM ICCID number
    */
    String getICCID();
    
    /** Enab;e AT-command and responses to be printed out
        @return no
    */
    void debug(Print& p = Serial)
    {
      MODEM.debug(p);
    }
    
    /** Enab;e AT-command and responses to be printed out
        @return no
    */
    void noDebug()
    {
      MODEM.noDebug();
    }
};

#include "GSMModem_Generic_Impl.hpp"

#endif    // _GSM_MODEM_H_INCLUDED
