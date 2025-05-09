/*********************************************************************************************************************************
  Modem_SIM800_Extra_Generic.h
  
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

#ifndef _MODEM_SIM800_EXTRA_INCLUDED_H
#define _MODEM_SIM800_EXTRA_INCLUDED_H

///////////////////////////////////////////////////////////////////////

//#define GSM_NL "\r\n"

class GPRS_ModemUrcHandler : public ModemUrcHandler 
{
  public:
  
    int ready()
    {
      int ready = MODEM.ready();

      if (ready == GSM_RESPONSE_IDLE)
      {
        return GSM_RESPONSE_IDLE;
      }

      switch (_state)
      {
        case GPRS_STATE_IDLE:
        default:
          {
            break;
          }

        case GPRS_STATE_ATTACH:
          {
            //MODEM.send("AT+CGATT=1");
            MODEM.send("AT++SAPBR=3,1,\"Contype\",\"GPRS\"");     // Set the connection type to GPRS
            
            _state = GPRS_STATE_WAIT_ATTACH_RESPONSE;
            ready = GSM_RESPONSE_IDLE;
            break;
          }

        case GPRS_STATE_WAIT_ATTACH_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_SET_APN;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
        case GPRS_STATE_SET_APN:
          {
            //MODEM.sendf("AT+UPSD=0,1,\"%s\"", _apn);
            MODEM.sendf("AT+SAPBR=3,1,\"APN\",\"%s\"", _apn);   // Set the APN
            
            _state = GPRS_STATE_WAIT_SET_APN_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_SET_APN_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_SET_AUTH_MODE;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }

#if 1

        case GPRS_STATE_SET_AUTH_MODE:
          {
            //MODEM.sendf("AT+UPSD=0,6,3");
            _state = GPRS_STATE_SET_USERNAME;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

#else

        case GPRS_STATE_SET_AUTH_MODE:
          {
            MODEM.sendf("AT+UPSD=0,6,3");
            _state = GPRS_STATE_WAIT_SET_AUTH_MODE_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }
#endif

        case GPRS_STATE_WAIT_SET_AUTH_MODE_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_SET_USERNAME;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }

        case GPRS_STATE_SET_USERNAME:
          {
            //MODEM.sendf("AT+UPSD=0,2,\"%s\"", _username);
            MODEM.sendf("AT+SAPBR=3,1,\"USER\",\"%s\"", _username);   // Set the user name
            
            _state = GPRS_STATE_WAIT_SET_USERNAME_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_SET_USERNAME_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_SET_PASSWORD;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }

        case GPRS_STATE_SET_PASSWORD:
          {
            //MODEM.sendf("AT+UPSD=0,3,\"%s\"", _password);
            MODEM.sendf("AT+SAPBR=3,1,\"PWD\",\"%s\"", _password);    // Set the password
            
            _state = GPRS_STATE_WAIT_SET_PASSWORD_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_SET_PASSWORD_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_SET_DYNAMIC_IP;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }

#if 1
        case GPRS_STATE_DEFINE_PDP_CONTEXT:
          {
            MODEM.sendf("AT+CGDCONT=1,\"IP\",\"%s\"", _apn);    // Define the PDP context
                
            _state = GPRS_STATE_WAIT_DEFINE_PDP_CONTEXT_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_DEFINE_PDP_CONTEXT_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_ACTIVATE_PDP_CONTEXT;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
          
        case GPRS_STATE_ACTIVATE_PDP_CONTEXT:
          {
            MODEM.send("AT+CGACT=1,1");   // Activate the PDP context
                
            _state = GPRS_STATE_WAIT_ACTIVATE_PDP_CONTEXT_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_ACTIVATE_PDP_CONTEXT_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_OPEN_GPRS_BEARER_CONTEXT;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
          
        case GPRS_STATE_OPEN_GPRS_BEARER_CONTEXT:
          {
            MODEM.send("AT+SAPBR=1,1");  // Open the defined GPRS bearer context
                
            _state = GPRS_STATE_WAIT_OPEN_GPRS_BEARER_CONTEXT_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_OPEN_GPRS_BEARER_CONTEXT_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_QUERY_GPRS_BEARER_CONTEXT;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }         
          
        case GPRS_STATE_QUERY_GPRS_BEARER_CONTEXT:
          {
            MODEM.send("AT+SAPBR=2,1");  // Query the GPRS bearer context status
                
            _state = GPRS_STATE_WAIT_QUERY_GPRS_BEARER_CONTEXT_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_QUERY_GPRS_BEARER_CONTEXT_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_ATTACH_GPRS;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
          
        case GPRS_STATE_ATTACH_GPRS:
          {
            MODEM.send("AT+CGATT=1");  // Attach to GPRS
                
            _state = GPRS_STATE_WAIT_ATTACH_GPRS_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_ATTACH_GPRS_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_SET_MULTI_IP;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
          
        case GPRS_STATE_SET_MULTI_IP:
          {
            MODEM.send("AT+CIPMUX=1");  // Set to multi-IP
                
            _state = GPRS_STATE_WAIT_SET_MULTI_IP_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_SET_MULTI_IP_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_START_TASK;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
          
        // Put in "quick send" mode (thus no extra "Send OK")
        // Set to get data manually
          
        case GPRS_STATE_START_TASK:
          {
            MODEM.sendf("AT+CSTT=\"%s\",\"%s\",\"%s\"", _apn, _username, _password);  // Start Task and Set APN, USER NAME, PASSWORD
                
            _state = GPRS_STATE_WAIT_START_TASK_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_START_TASK_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_WIRELESS_UP;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
          
          case GPRS_STATE_WIRELESS_UP:
          {
            MODEM.send("AT+CIICR");  // Bring Up Wireless Connection with GPRS or CSD
                
            _state = GPRS_STATE_WAIT_WIRELESS_UP_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_WIRELESS_UP_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_GET_IP;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
          
        case GPRS_STATE_GET_IP:
          {
            MODEM.send("AT+CIFSR;E0");
            _state = GPRS_STATE_WAIT_GET_IP_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_GET_IP_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_CONFIG_DNS;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }
          
        case GPRS_STATE_CONFIG_DNS:
          {
            MODEM.send("CDNSCFG=\"8.8.8.8\",\"8.8.4.4\"");
            _state = GPRS_STATE_WAIT_CONFIG_DNS_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_CONFIG_DNS_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_IDLE;
              _status = GPRS_READY;
            }

            break;
          }
          
                  

#else
        case GPRS_STATE_SET_DYNAMIC_IP:
          {
            MODEM.send("AT+UPSD=0,7,\"0.0.0.0\"");
            _state = GPRS_STATE_WAIT_SET_DYNAMIC_IP_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_SET_DYNAMIC_IP_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_ACTIVATE_IP;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }

        case GPRS_STATE_ACTIVATE_IP:
          {
            MODEM.send("AT+UPSDA=0,3");
            _state = GPRS_STATE_WAIT_ACTIVATE_IP_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_ACTIVATE_IP_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_IDLE;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }


        case GPRS_STATE_CHECK_PROFILE_STATUS:
          {
            MODEM.setResponseDataStorage(&_response);
            MODEM.send("AT+UPSND=0,8");
            _state = GPRS_STATE_WAIT_CHECK_PROFILE_STATUS_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_CHECK_PROFILE_STATUS_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK || !_response.endsWith(",1"))
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_IDLE;
              _status = GPRS_READY;
            }

            break;
          }
#endif

        case GPRS_STATE_DEACTIVATE_IP:
          {
            MODEM.send("AT+CIPSHUT");   // Shut the TCP/IP connection to close *all* open connections
            
            _state = GPRS_STATE_WAIT_DEACTIVATE_IP_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_DEACTIVATE_IP_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_DEATTACH;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }

        case GPRS_STATE_DEATTACH:
          {
            MODEM.send("AT+CGATT=0");
            _state = GPRS_STATE_WAIT_DEATTACH_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case GPRS_STATE_WAIT_DEATTACH_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_ERROR;
            }
            else
            {
              _state = GPRS_STATE_IDLE;
              _status = GSM_IDLE;
            }

            break;
          }         
      }

      return ready;
    }
    
    //////////////////////////////////////////////////////

    IPAddress getIPAddress()
    {
      String response;

      //MODEM.send("AT+UPSND=0,0");
      MODEM.send("AT+CIFSR;E0");

      if (MODEM.waitForResponse(100, &response) == GSM_RESPONSE_OK)
      {
#if 1
        response.replace(GSM_NL "OK" GSM_NL, "");
        response.replace(GSM_NL, "");
        response.trim();
        
        IPAddress ip;

        if (ip.fromString(response))
        {
          return ip;
        }
        
#else
        if (response.startsWith("+UPSND: 0,0,\"") && response.endsWith("\""))
        {
          response.remove(0, 13);
          response.remove(response.length() - 1);

          IPAddress ip;

          if (ip.fromString(response))
          {
            return ip;
          }
        }
#endif        
      }

      return IPAddress(0, 0, 0, 0);
    }
    
    //////////////////////////////////////////////////////

    int hostByName(const char* hostname, IPAddress& result)
    {
      String response;

      MODEM.sendf("AT+UDNSRN=0,\"%s\"", hostname);

      if (MODEM.waitForResponse(70000, &response) != GSM_RESPONSE_OK)
      {
        return 0;
      }

      if (!response.startsWith("+UDNSRN: \"") || !response.endsWith("\""))
      {
        return 0;
      }

      response.remove(0, 10);
      response.remove(response.length() - 1);

      if (result.fromString(response))
      {
        return 1;
      }

      return 0;
    }
    
    //////////////////////////////////////////////////////

    int ping(const char* hostname, uint8_t ttl)
    {
      String response;

      _pingResult = 0;

      MODEM.sendf("AT+UPING=\"%s\",1,32,5000,%d", hostname, ttl);

      if (MODEM.waitForResponse() != GSM_RESPONSE_OK)
      {
        return GPRS_PING_ERROR;
      };

      for (unsigned long start = millis(); (millis() - start) < 5000 && (_pingResult == 0);)
      {
        MODEM.poll();
      }

      if (_pingResult == 0)
      {
        _pingResult = GPRS_PING_TIMEOUT;
      }

      return _pingResult;
    }
    
    //////////////////////////////////////////////////////

    void handleUrc(const String& urc)
    {
      if (urc.startsWith("+UUPINGER: "))
      {
        if (urc.endsWith(",8"))
        {
          _pingResult = GPRS_PING_UNKNOWN_HOST;
        }
        else
        {
          _pingResult = GPRS_PING_ERROR;
        }
      }
      else if (urc.startsWith("+UUPING: "))
      {
        int lastCommaIndex = urc.lastIndexOf(',');

        if (lastCommaIndex == -1)
        {
          _pingResult = GPRS_PING_ERROR;
        }
        else
        {
          _pingResult = urc.substring(lastCommaIndex + 1).toInt();

          if (_pingResult == -1)
          {
            _pingResult = GPRS_PING_TIMEOUT;
          }
          else if (_pingResult <= 0)
          {
            _pingResult = GPRS_PING_ERROR;
          }
        }
      }
      else if (urc.startsWith("+UUPSDD: "))
      {
        int profileId = urc.charAt(urc.length() - 1) - '0';

        if (profileId == 0)
        {
          // disconnected
          _status = GSM_IDLE;
        }
      }
    }
    
    protected:
      // To be used in derived classes
      const char* _apn;
      const char* _username;
      const char* _password;
      int         _state;
      
      GSM3_NetworkStatus_t  _status;
      String                _response;
      int                   _pingResult;
};

///////////////////////////////////////////////////////////////////////

class GSMClient_ModemUrcHandler : public ModemUrcHandler 
{
  public:
  
    virtual int ready()
    {
      int ready = MODEM.ready();

      if (ready == GSM_RESPONSE_IDLE)
      {
        return GSM_RESPONSE_IDLE;
      }

      switch (_state)
      {
        case CLIENT_STATE_IDLE:
        default:
          {
            break;
          }

        case CLIENT_STATE_CREATE_SOCKET:
          {
            MODEM.setResponseDataStorage(&_response);
            //MODEM.send("AT+USOCR=6");

            //_state = CLIENT_STATE_WAIT_CREATE_SOCKET_RESPONSE;
            _state = CLIENT_STATE_CONNECT;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case CLIENT_STATE_WAIT_CREATE_SOCKET_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK || !_response.startsWith("+USOCR: "))
            {
              _state = CLIENT_STATE_IDLE;
            }
            else
            {
              _socket = _response.charAt(_response.length() - 1) - '0';

              if (_ssl)
              {
                _state = CLIENT_STATE_ENABLE_SSL;
              }
              else
              {
                _state = CLIENT_STATE_CONNECT;
              }

              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }

        // TO DO SSL
        case CLIENT_STATE_ENABLE_SSL:
          {
            //MODEM.sendf("AT+USOSEC=%d,1,0", _socket);

            _state = CLIENT_STATE_WAIT_ENABLE_SSL_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case CLIENT_STATE_WAIT_ENABLE_SSL_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = CLIENT_STATE_CLOSE_SOCKET;
            }
            else
            {
              _state = CLIENT_STATE_MANAGE_SSL_PROFILE;
            }

            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case CLIENT_STATE_MANAGE_SSL_PROFILE:
          {
            //MODEM.sendf("AT+USECPRF=0,0,%d", _sslprofile);

            _state = CLIENT_STATE_WAIT_MANAGE_SSL_PROFILE_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case CLIENT_STATE_WAIT_MANAGE_SSL_PROFILE_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = CLIENT_STATE_CLOSE_SOCKET;
            }
            else
            {
              _state = CLIENT_STATE_CONNECT;
            }

            ready = GSM_RESPONSE_IDLE;

            break;
          }
        //////////////////////////////////////////   

        case CLIENT_STATE_CONNECT:
          {
            if (_host != NULL)
            {
              //MODEM.sendf("AT+USOCO=%d,\"%s\",%d", _socket, _host, _port);
              MODEM.sendf("AT+CIPSTART=%d,\"TCP\",\"%s\",%d", _socket, _host, _port);
            }
            else
            {
              MODEM.sendf("AT+CIPSTART=%d,\"%d.%d.%d.%d\",%d", _socket, _ip[0], _ip[1], _ip[2], _ip[3], _port);
            }

            _state = CLIENT_STATE_WAIT_CONNECT_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case CLIENT_STATE_WAIT_CONNECT_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = CLIENT_STATE_CLOSE_SOCKET;

              ready = GSM_RESPONSE_IDLE;
            }
            else
            {
              _connected = true;
              _state = CLIENT_STATE_IDLE;
            }

            break;
          }

        case CLIENT_STATE_CLOSE_SOCKET:
          {
            MODEM.closeSocket(_socket);

            _state = CLIENT_STATE_WAIT_CLOSE_SOCKET;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case CLIENT_STATE_WAIT_CLOSE_SOCKET:
          {
            _state = CLIENT_STATE_IDLE;
            _socket = -1;

            break;
          }
      }

      return ready;
    }
    
    //////////////////////////////////////////////////////
    
    size_t write(const uint8_t* buf, size_t size)
    {
      if (_writeSync)
      {
        while (ready() == GSM_RESPONSE_IDLE);
      }
      else if (ready() == GSM_RESPONSE_IDLE)
      {
        return 0;
      }

      if (_socket == -1)
      {
        return 0;
      }

      size_t written = 0;
      String command;

      command.reserve(19 + (size > 256 ? 256 : size) * 2);

      while (size)
      {
        size_t chunkSize = size;

        if (chunkSize > 256)
        {
          chunkSize = 256;
        }

        //command = "AT+USOWR=";
        command = "AT+CIPSEND=";
        command += _socket;
        command += ",";
        command += chunkSize;
        command += ",\"";

        for (size_t i = 0; i < chunkSize; i++)
        {
          byte b = buf[i + written];

          byte n1 = (b >> 4) & 0x0f;
          byte n2 = (b & 0x0f);

          command += (char)(n1 > 9 ? 'A' + n1 - 10 : '0' + n1);
          command += (char)(n2 > 9 ? 'A' + n2 - 10 : '0' + n2);
        }

        command += "\"";

        MODEM.send(command);

        if (_writeSync)
        {
          if (MODEM.waitForResponse(10000) != GSM_RESPONSE_OK)
          {
            break;
          }
        }

        written += chunkSize;
        size -= chunkSize;
      }

      return written;
    }
    
    //////////////////////////////////////////////////////
   
    virtual void handleUrc(const String& urc)
    {
      GSM_LOGDEBUG1(F("GSMClient::handleUrc: usr = "), urc);
      
      if (urc.startsWith("+CIPRXGET: "))
      {
        int socket = urc.charAt(9) - '0';

        if (socket == _socket)
        {
          if (urc.endsWith(",4294967295"))
          {
            _connected = false;
          }
        }
      }
    }
    
    //////////////////////////////////////////////////////  
    
  protected:
    // To be used in derived classes
    int         _socket;
    int         _connected;

    int         _state;
    IPAddress   _ip;
    const char* _host;
    uint16_t    _port;
    bool        _ssl;

    int         _sslprofile;
    bool        _writeSync;
    String      _response;
};

///////////////////////////////////////////////////////////////////////

#include "GSMClient_Generic.h"

#define MAX_CHILD_SOCKETS 6

class GSMServer_ModemUrcHandler : public ModemUrcHandler 
{
  public:
  
    int ready()
    {
      int ready = MODEM.ready();

      if (ready == GSM_RESPONSE_IDLE)
      {
        return GSM_RESPONSE_IDLE;
      }

      switch (_state)
      {
        case SERVER_STATE_IDLE:
        default:
          {
            break;
          }

        case SERVER_STATE_CREATE_SOCKET:
          {
            MODEM.setResponseDataStorage(&_response);
            MODEM.send("AT+USOCR=6");

            _state = SERVER_STATE_WAIT_CREATE_SOCKET_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case SERVER_STATE_WAIT_CREATE_SOCKET_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK || !_response.startsWith("+USOCR: "))
            {
              _state = SERVER_STATE_IDLE;
            }
            else
            {
              _socket = _response.charAt(_response.length() - 1) - '0';

              _state = SERVER_STATE_LISTEN;
              ready = GSM_RESPONSE_IDLE;
            }

            break;
          }

        case SERVER_STATE_LISTEN:
          {
            MODEM.sendf("AT+USOLI=%d,%d", _socket, _port);

            _state = SERVER_STATE_WAIT_LISTEN_RESPONSE;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case SERVER_STATE_WAIT_LISTEN_RESPONSE:
          {
            if (ready > GSM_RESPONSE_OK)
            {
              _state = SERVER_STATE_CLOSE_SOCKET;
              ready = GSM_RESPONSE_IDLE;
            }
            else
            {
              _state = SERVER_STATE_IDLE;
            }

            break;
          }

        case SERVER_STATE_CLOSE_SOCKET:
          {
            MODEM.closeSocket(_socket);

            _state = SERVER_STATE_WAIT_CLOSE_SOCKET;
            ready = GSM_RESPONSE_IDLE;

            break;
          }

        case SERVER_STATE_WAIT_CLOSE_SOCKET:
          {
            _state = SERVER_STATE_IDLE;
            _socket = -1;
            break;
          }
      }

      return ready;
    }
    
    //////////////////////////////////////////////////////
    
    GSMClient available(bool synch = true)
    {
      MODEM.poll();

      int socket = -1;

      if (_socket != -1) 
      {
        // search for new accepted sockets first
        for (int i = 0; i < MAX_CHILD_SOCKETS; i++) 
        {
          if (_childSockets[i].socket != -1 && _childSockets[i].accepted) 
          {
            _childSockets[i].accepted = false;
            socket = _childSockets[i].socket;

            break;
          }
        }

        if (socket == -1) 
        {
          // no new accepted sockets, search for one with data to be read
          for (int i = 0; i < MAX_CHILD_SOCKETS; i++) 
          {
            if (_childSockets[i].socket != -1) 
            {
              // check if socket is still alive
              //MODEM.sendf("AT+USORD=%d,0", _childSockets[i].socket);
              MODEM.sendf("AT+CIPRXGET=2,%d,0", _childSockets[i].socket);
              
              if (MODEM.waitForResponse(10000) != GSM_RESPONSE_OK) 
              {
                // closed
                _childSockets[i].socket = -1;
                _childSockets[i].accepted = false;
                _childSockets[i].available = 0;

                continue;
              }

              if (_childSockets[i].available) 
              {
                _childSockets[i].available = 0;
                socket = _childSockets[i].socket;
                break;
              }
            }
          }
        }
      }

      return GSMClient(socket, synch);
    }
    
    ////////////////////////////////////////////////////// 
    
    void stop()
    {
      if (_socket < 0) 
      {
        return;
      }

      MODEM.closeSocket(_socket);
      
      MODEM.waitForResponse(10000);

      _socket = -1;
    }
    
    //////////////////////////////////////////////////////  
  
    virtual void handleUrc(const String& urc)
    {
      GSM_LOGDEBUG1(F("GSMServer::handleUrc: urc = "), urc);
      
      if (urc.startsWith("+UUSOLI: ")) 
      {
        int socket = urc.charAt(9) - '0';

        for (int i = 0; i < MAX_CHILD_SOCKETS; i++) 
        {
          if (_childSockets[i].socket == -1) 
          {
            _childSockets[i].socket = socket;
            _childSockets[i].accepted = true;
            _childSockets[i].available = 0;

            break;
          }
        }
      } 
      else if (urc.startsWith("+UUSOCL: ")) 
      {
        int socket = urc.charAt(urc.length() - 1) - '0';

        if (socket == _socket) 
        {
          _socket = -1;
        } 
        else 
        {
          for (int i = 0; i < MAX_CHILD_SOCKETS; i++) 
          {
            if (_childSockets[i].socket == socket) 
            {
              _childSockets[i].socket = -1;
              _childSockets[i].accepted = false;
              _childSockets[i].available = 0;

              break;
            }
          }
        }
      } 
      //else if (urc.startsWith("+UUSORD: ")) 
      else if (urc.startsWith("+CIPRXGET: "))
      {
        int socket = urc.charAt(9) - '0';

        for (int i = 0; i < MAX_CHILD_SOCKETS; i++) 
        {
          if (_childSockets[i].socket == socket) 
          {
            int commaIndex = urc.indexOf(',');
            
            if (commaIndex != -1) 
            {
              _childSockets[i].available = urc.substring(commaIndex + 1).toInt();
            }

            break;
          }
        }
      }
    }
    
    //////////////////////////////////////////////////////  
    
  protected:
    uint16_t  _port;
    bool      _synch;

    int       _socket;
    int       _state;
    String    _response;

    struct 
    {
      int socket;
      bool accepted;
      int available;
    } _childSockets[MAX_CHILD_SOCKETS];
};

///////////////////////////////////////////////////////////////////////

class GSMUDP_ModemUrcHandler : public ModemUrcHandler 
{
  public:
  
    uint8_t begin(uint16_t port)
    {
      String response;
      
      GSM_LOGDEBUG1(F("GSMUDP::begin: port = "), port);

      MODEM.send("AT+USOCR=17");

      if (MODEM.waitForResponse(100, &response) != GSM_RESPONSE_OK)
      {
        GSM_LOGDEBUG(F("GSMUDP::begin: Error no modem response"));
        
        return 0;
      }

      _socket = response.charAt(response.length() - 1) - '0';

      MODEM.sendf("AT+USOLI=%d,%d", _socket, port);

      if (MODEM.waitForResponse(10000) != GSM_RESPONSE_OK)
      {
        stop();
        return 0;
      }
      
      GSM_LOGDEBUG1(F("GSMUDP::begin: OK, _socket = "), _socket);

      return 1;
    }
    
    ////////////////////////////////////////////////////// 

    void stop()
    {
      if (_socket < 0)
      {
        return;
      }

      MODEM.closeSocket(_socket);
      
      MODEM.waitForResponse(10000);

      _socket = -1;
    }
    
    ////////////////////////////////////////////////////// 
    
    int endPacket()
    {
      String command;

      if (_txHost != NULL)
      {
        command.reserve(26 + strlen(_txHost) + _txSize * 2);
      }
      else
      {
        command.reserve(41 + _txSize * 2);
      }

      command += "AT+USOST=";
      command += _socket;
      command += ",\"";

      if (_txHost != NULL)
      {
        command += _txHost;
      }
      else
      {
        command += _txIp[0];
        command += '.';
        command += _txIp[1];
        command += '.';
        command += _txIp[2];
        command += '.';
        command += _txIp[3];
      }

      command += "\",";
      command += _txPort;
      command += ",";
      command += _txSize;
      command += ",\"";

      for (size_t i = 0; i < _txSize; i++)
      {
        byte b = _txBuffer[i];

        byte n1 = (b >> 4) & 0x0f;
        byte n2 = (b & 0x0f);

        command += (char)(n1 > 9 ? 'A' + n1 - 10 : '0' + n1);
        command += (char)(n2 > 9 ? 'A' + n2 - 10 : '0' + n2);
      }

      command += "\"";

      MODEM.send(command);

      if (MODEM.waitForResponse() == GSM_RESPONSE_OK) 
      {
        return 1;
      } 
      else 
      {
        return 0;
      }
    }
    
    ////////////////////////////////////////////////////// 
    
    int parsePacket()
    {
      MODEM.poll();

      if (_socket < 0) 
      {
        return 0;
      }

      if (!_packetReceived) 
      {
        return 0;
      }
      
      _packetReceived = false;

      String response;

      MODEM.sendf("AT+USORF=%d,%d", _socket, sizeof(_rxBuffer));
      
      if (MODEM.waitForResponse(10000, &response) != GSM_RESPONSE_OK) 
      {
        return 0;
      }

      if (!response.startsWith("+USORF: ")) 
      {
        return 0;
      }

      response.remove(0, 11);

      int firstQuoteIndex = response.indexOf('"');
      
      if (firstQuoteIndex == -1) 
      {
        return 0;
      }

      String ip = response.substring(0, firstQuoteIndex);
      _rxIp.fromString(ip);

      response.remove(0, firstQuoteIndex + 2);

      int firstCommaIndex = response.indexOf(',');
      
      if (firstCommaIndex == -1) 
      {
        return 0;
      }

      String port = response.substring(0, firstCommaIndex);
      
      _rxPort = port.toInt();
      firstQuoteIndex = response.indexOf("\"");

      response.remove(0, firstQuoteIndex + 1);
      response.remove(response.length() - 1);

      _rxIndex = 0;
      _rxSize = response.length() / 2;

      for (size_t i = 0; i < _rxSize; i++) 
      {
        byte n1 = response[i * 2];
        byte n2 = response[i * 2 + 1];
       
        n1 = charToInt(n1);
        n2 = charToInt(n2);

        _rxBuffer[i] = (n1 << 4) | n2;
      }

      MODEM.poll();

      return _rxSize;
    }
       
    ////////////////////////////////////////////////////// 
  
    virtual void handleUrc(const String& urc)
    {
      GSM_LOGDEBUG1(F("GSMUDP::handleUrc: urc = "), urc);
      
      if (urc.startsWith("+UUSORF: ")) 
      {
        int socket = urc.charAt(9) - '0';

        if (socket == _socket) 
        {
          _packetReceived = true;
        }
      } 
      else if (urc.startsWith("+UUSOCL: ")) 
      {
        int socket = urc.charAt(urc.length() - 1) - '0';

        if (socket == _socket) 
        {
          // this socket closed
          _socket = -1;
          _rxIndex = 0;
          _rxSize = 0;
        }
      }
    }
    
    ////////////////////////////////////////////////////// 
    
  protected:
    int         _socket;
    bool        _packetReceived;

    IPAddress   _txIp;
    const char* _txHost;
    uint16_t    _txPort;
    size_t      _txSize;
    uint8_t     _txBuffer[512];

    IPAddress   _rxIp;
    uint16_t    _rxPort;
    size_t      _rxSize;
    size_t      _rxIndex;
    uint8_t     _rxBuffer[512];
};

///////////////////////////////////////////////////////////////////////

class GSMLocation_ModemUrcHandler : public ModemUrcHandler 
{
  public:

    void handleUrc(const String& urc)
    {
      GSM_LOGDEBUG1(F("GSMLocation::handleUrc: urc = "), urc);
      
      if (urc.startsWith("+UULOC: ")) 
      {
        String temp = urc;
        int lastCommaIndex;

        _locationAvailable = true;

        lastCommaIndex = temp.lastIndexOf(',');
        _uncertainty = temp.substring(lastCommaIndex + 1).toInt();
        temp.remove(lastCommaIndex);

        lastCommaIndex = temp.lastIndexOf(',');
        _altitude = temp.substring(lastCommaIndex + 1).toInt();
        temp.remove(lastCommaIndex);

        lastCommaIndex = temp.lastIndexOf(',');
        _longitude = temp.substring(lastCommaIndex + 1).toFloat();
        temp.remove(lastCommaIndex);

        lastCommaIndex = temp.lastIndexOf(',');
        _latitude = temp.substring(lastCommaIndex + 1).toFloat();
        temp.remove(lastCommaIndex);
      }
    }
    
  protected:
  
    bool  _commandSent;
    bool  _locationAvailable;

    float _latitude;
    float _longitude;
    long  _altitude;
    long  _uncertainty;

};

///////////////////////////////////////////////////////////////////////


class GSMVoiceCall_ModemUrcHandler : public ModemUrcHandler 
{
  public:
    
    void handleUrc(const String& urc)
    {
      GSM_LOGDEBUG1(F("GSMVoiceCall::handleUrc: urc = "), urc);
      
      if (urc.startsWith("+UCALLSTAT: ")) 
      {
        int status = urc.charAt(urc.length() - 1) - '0';

        if (status == 0 || status == 1 || status == 7) 
        {
          _callStatus = TALKING;
          _dtmfBuffer = "";
          
          GSM_LOGDEBUG(F("GSMVoiceCall::handleUrc: TALKING"));
        } 
        else if (status == 2 || status == 3) 
        {
          _callStatus = CALLING;
          
          GSM_LOGDEBUG(F("GSMVoiceCall::handleUrc: CALLING"));
        } 
        else if (status == 4 || status == 5) 
        {
          _callStatus = RECEIVINGCALL;
          
          GSM_LOGDEBUG(F("GSMVoiceCall::handleUrc: RECEIVINGCALL"));
        } 
        else 
        {
          _callStatus = IDLE_CALL;
          
          GSM_LOGDEBUG(F("GSMVoiceCall::handleUrc: IDLE_CALL"));
        }
      } 
      else if (urc.startsWith("+UUDTMFD: ")) 
      {
        _dtmfBuffer += urc.charAt(10);
      }
    }
    
  protected:
    int               _synch;
    GSM3_voiceCall_st _callStatus;
    String            _dtmfBuffer; 
};


///////////////////////////////////////////////////////////////////////

#endif    // _MODEM_SIM800_EXTRA_INCLUDED_H
