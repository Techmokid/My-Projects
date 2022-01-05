// EtherEvent - Easy to use password authenticated network communication between Arduinos and EventGhost Network Event Sender/Receiver and TCPEvents plugins: http://github.com/per1234/EtherEvent
#ifndef EtherEvent_h
#define EtherEvent_h

#include <Arduino.h>

#if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)
#include <avr/dtostrf.h>
#endif  //defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)

#include <Ethernet.h>

#ifndef ETHEREVENT_NO_AUTHENTICATION
#include <MD5.h>
#endif  //ETHEREVENT_NO_AUTHENTICATION


#define ETHEREVENT_DEBUG false  //(false == serial debug output off, true == serial debug output on)The serial debug output will increase memory usage and communication latency so only enable when needed.
#define ETHEREVENT_SERIAL if(ETHEREVENT_DEBUG)Serial  //I have to use a different name for Serial in this file otherwise the debug statement control also affects any other file that includes this file.
#if ETHEREVENT_DEBUG == true
#pragma message "EtherEvent debug output enabled"
#endif  //ETHEREVENT_DEBUG == true

#define ETHEREVENT_MAGIC_WORD "quintessence\n\r"  //word used to trigger the cookie send from the receiver. I had to #define this instead of const because find() didn't like the const
#define ETHEREVENT_ACCEPT_MESSAGE "accept\n"  //authentication success message. I had to #define this instead of const because find() didn't like the const


namespace EtherEventNamespace {
const unsigned long debugSerialBaud = 9600;
const char payloadSeparator[] = "payload ";  //indicates payload
const byte payloadSeparatorLength = strlen(EtherEventNamespace::payloadSeparator);  //includes space at the end
const char payloadWithoutRelease[] = "payload withoutRelease";  //eg sends this every time and EtherEvent filters it out
const byte payloadWithoutReleaseLength = strlen(EtherEventNamespace::payloadWithoutRelease);
const char closeMessage[] = "close\n";  //sender sends this message to the receiver to close the connection
const byte closeMessageLength = strlen(EtherEventNamespace::closeMessage);
}


class EtherEventClass {
  public:
    EtherEventClass();
    boolean begin(const byte eventLengthMaxInput = 15, const unsigned int payloadLengthMaxInput = 100);  //these are the default max length values


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //availableEvent - checks for senders, connects, authenticates, reads the event and payload into the buffer and returns the number of bytes of the most recently received event are left in the buffer
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    byte availableEvent() {
      return receivedEventLength - readEventLength;
    }

#ifndef ETHEREVENT_NO_AUTHENTICATION
    byte availableEvent(EthernetServer &ethernetServer, const __FlashStringHelper* passwordInput) {
      return availableEvent(ethernetServer, false, passwordInput);
    }

    byte availableEvent(EthernetServer &ethernetServer, const long cookieInput, const __FlashStringHelper* passwordInput) {
      const byte passwordInputLength = FSHlength(passwordInput);
      char passwordChar[passwordInputLength + 1];
      memcpy_P(passwordChar, passwordInput, passwordInputLength + 1);  //+1 for the null terminator
      return availableEvent(ethernetServer, cookieInput, passwordChar);
    }

    byte availableEvent(EthernetServer &ethernetServer, const char passwordInput[]) {
      return availableEvent(ethernetServer, false, passwordInput);
    }

    byte availableEvent(EthernetServer &ethernetServer, const long cookieInput = false, const char passwordInput[] = "") {
#else  //ETHEREVENT_NO_AUTHENTICATION
    byte availableEvent(EthernetServer &ethernetServer) {
#endif  //ETHEREVENT_NO_AUTHENTICATION
      if (receivedEventLength <= readEventLength) {  ///no event buffered
        flushPayload();
        if (EthernetClient ethernetClient = ethernetServer.available() ) {  //connect to the client
          ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: connected"));
          ethernetClient.setTimeout(timeout);  //timeout on Stream fumctions. This needs to be called every time in availableEvent() or it resets to the default of 1000ms because a new EthernetClient object is created every call.

#ifndef ETHEREVENT_NO_AUTHENTICATION
          if (ethernetClient.find((char*)ETHEREVENT_MAGIC_WORD) == true) {  //magic word correct - the (char*) is to get rid of "warning: deprecated conversion from string constant to char*" compile error
            ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: magic word received"));

            //create and send cookie
            long cookie;
            if (cookieInput != false) {  //use user-defined cookie
              ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: user defined cookie: "));
              cookie = cookieInput;
            }
            else {
              ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: automatically generated cookie: "));
              randomSeed(micros());
              cookie = random((((unsigned long) - 1) / 2));  //make random number to use as cookie
            }
            byte currentPasswordLength = passwordLength;
            if (passwordInput[0] != 0) {
              currentPasswordLength = strlen(passwordInput);
            }
            char cookiePassword[8 + 1 + currentPasswordLength + 1];  //create buffer of length sufficient for: cookie(8 hexadecimal digits max)  +  password separator  +  Password  +  null terminator
            ltoa(cookie, cookiePassword, HEX);
            ETHEREVENT_SERIAL.println(cookiePassword);
            ethernetClient.print(cookiePassword);  //send the cookie

            //calculate the hashword
            strcat(cookiePassword, ":");  //create the hashword to compare to the received one
            if (passwordInput[0] == 0) {
              strcat(cookiePassword, password);
            }
            else {
              strcat(cookiePassword, passwordInput);
            }
            ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: cookiePassword: "));
            ETHEREVENT_SERIAL.println(cookiePassword);
            unsigned char* cookiePasswordHash = MD5::make_hash(cookiePassword);
            char* cookiePasswordMD5 = MD5::make_digest(cookiePasswordHash, 16);
            free(cookiePasswordHash);
            ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: cookiePasswordMD5: "));
            ETHEREVENT_SERIAL.println(cookiePasswordMD5);

            //verify the received hashword
            if (ethernetClient.find(cookiePasswordMD5) == true) {  //authentication successful
              ethernetClient.flush();  //clear the \n or it will cause a null message in the payload/event message read
              ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: authentication successful"));
              ethernetClient.print(" " ETHEREVENT_ACCEPT_MESSAGE);  //The space indicates the server type is TCPEvents. For some reason I can't use F() on this one.
              free(cookiePasswordMD5);
#endif  //ETHEREVENT_NO_AUTHENTICATION
              //Read and process the message
              for (byte count = 0; count < 7; count++) {  //Read and process the count stuff is just to make sure it will never go into an infinite loop. It should never need more than five iterations of the for loop to get event and payload
                ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: payload/event for loop"));
                char receivedMessage[availableEventSubmessageLengthMax + 1];  //initialize the buffer to read into
                unsigned int bytesRead = ethernetClient.readBytesUntil(10, receivedMessage, availableEventSubmessageLengthMax + 1);  //put the incoming data up to the newline into receivedMessage
                if (bytesRead > availableEventSubmessageLengthMax) {  //event or payload exceeds max length
                  ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: event/payload > max length"));
                  char findString[] = "\n";  //I had to do this instead of just ethernetClient.find(10) or ethernetClient.find("\n") because that causes a compile error under Arduino IDE 1.6.0 which also doesn't allow const char
                  ethernetClient.find(findString);  //Flush up to the newline. I had to do the "\n" instead of just ethernetClient.find(10) because that causes a compile error under Arduino IDE 1.6.0
                  bytesRead--;  //so the null terminator will not be written past the end of the array
                }
                ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: bytesRead: "));
                ETHEREVENT_SERIAL.println(bytesRead);
                if (bytesRead == 0) {  //with Arduino 1.5 there is a leading char(10) for some reason(maybe flush() doesn't work and it's still left over from the last message?). This will handle null messages
                  continue;
                }
                receivedMessage[bytesRead] = 0;  //add a null terminator

                if (strncmp(receivedMessage, EtherEventNamespace::payloadSeparator, EtherEventNamespace::payloadSeparatorLength) == 0) {  //received message is a payload
                  ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: payload separator received"));
                  if (bytesRead > EtherEventNamespace::payloadSeparatorLength) {  //there is a payload

                    if (strncmp(receivedMessage, EtherEventNamespace::payloadWithoutRelease, EtherEventNamespace::payloadWithoutReleaseLength) == 0) {  //"withoutRelease" received
                      ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: payloadWithoutRelease"));
                      continue;
                    }

                    ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: payload length: "));
                    ETHEREVENT_SERIAL.println(bytesRead - EtherEventNamespace::payloadSeparatorLength);
                    receivedPayloadLength = min(bytesRead - EtherEventNamespace::payloadSeparatorLength, payloadLengthMax + TCPEventsPayloadFormattingLength);  //make sure the payload will never be longer than the max length

                    //Strip TCPEvents payload formatting. TCPEvents wraps the payload in [''] if the payload field is used in the Send an Event configuration.
                    byte payloadOffset = 0;
                    if (receivedMessage[EtherEventNamespace::payloadSeparatorLength] == '[' && receivedMessage[EtherEventNamespace::payloadSeparatorLength + 1] == 39) {  //39 is apostrophe
                      payloadOffset = TCPEventsPayloadFormattingLength;  //skip the first 2 characters of the payload
                      if (receivedMessage[receivedPayloadLength + EtherEventNamespace::payloadSeparatorLength - 1] == ']') {
                        receivedPayloadLength--;
                      }
                      if (receivedMessage[receivedPayloadLength + EtherEventNamespace::payloadSeparatorLength - 1] == 39) {
                        receivedPayloadLength--;
                      }
                      receivedPayloadLength -= payloadOffset;
                    }
                    else {  //no TCPEvents payload formatting is present
                      receivedPayloadLength = min(receivedPayloadLength, payloadLengthMax);
                    }

                    //put the payload into the buffer
                    for (unsigned int payloadCounter = 0; payloadCounter < receivedPayloadLength; payloadCounter++) {
                      receivedPayload[payloadCounter] = receivedMessage[payloadCounter + payloadOffset + EtherEventNamespace::payloadSeparatorLength];
                    }
                    receivedPayload[receivedPayloadLength] = 0;  //null terminator
                    receivedPayloadLength++;  //receivedEventLength and receivedPayloadLength include the null terminator, this way if the user makes a mistake in the buffer length it will be one byte longer than it needs to be instead of one byte shorter
                    ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: payload: "));
                    ETHEREVENT_SERIAL.println(receivedPayload);
                  }
                  continue;
                }

                else {  //received message is event
                  ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: event length: "));
                  ETHEREVENT_SERIAL.println(bytesRead);
                  if (strncmp(receivedMessage, EtherEventNamespace::closeMessage, EtherEventNamespace::closeMessageLength) == 0) {
                    ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: close received, no event"));
                    break;
                  }
                  strncpy(receivedEvent, receivedMessage, eventLengthMax);
                  receivedEventLength = min(bytesRead, eventLengthMax) + 1;  //length including null terminator
                  receivedEvent[receivedEventLength - 1] = 0;  //-1 because it is zero indexed and the receivedEventLength includes the null terminator
                  ETHEREVENT_SERIAL.print(F("EtherEvent.availableEvent: event received: "));
                  ETHEREVENT_SERIAL.println(receivedEvent);

                  //save the sender IP address
#ifdef ethernetclientwithremoteIP_h  //the include guard from the modified EthernetClient.h
                  fromIP = ethernetClient.remoteIP();  //Save the IP address of the sender. Requires modified ethernet library
#endif  //ethernetclientwithremoteIP_h

                  break;  //exit the payload/event message handler loop
                }
              }
#ifndef ETHEREVENT_NO_AUTHENTICATION
            }

            //authentication failed
            else {
              free(cookiePasswordMD5);
              ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: authentication failed"));
            }
          }
#endif  //ETHEREVENT_NO_AUTHENTICATION      
          ethernetClient.print(EtherEventNamespace::closeMessage);  //tell the receiver to close
          ethernetClient.stop();
          ETHEREVENT_SERIAL.println(F("EtherEvent.availableEvent: connection closed"));
        }
      }
      return availableEvent();
    }


    unsigned int availablePayload();
    void readEvent(char eventBuffer[]);
    char readEvent();
    void readPayload(char payloadBuffer[]);
    char readPayload();
#ifdef ethernetclientwithremoteIP_h  //the include guard from the modified EthernetClient.h
    IPAddress senderIP();
#endif  //ethernetclientwithremoteIP_h
    void flushReceiver();


    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //send
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    template <typename target_t, typename event_t>
    boolean send(EthernetClient &ethernetClient, const target_t target, const unsigned int port, const event_t event) {  //payload must be specified with password even if it's blank
      Serial.println(F("EtherEvent.send(no payload)"));
      noPayload = true;  //set the flag to indicate there is no payload
      return send(ethernetClient, target, port, event, false);
    }

    template <typename event_t, typename payload_t>
    boolean send(EthernetClient &ethernetClient, const byte target[], const unsigned int port, const event_t event, const payload_t payload) {
      IPAddress targetIP = IPAddress(target[0], target[1], target[2], target[3]);
      return send(ethernetClient, targetIP, port, event, payload);
    }

#ifndef ETHEREVENT_NO_AUTHENTICATION
    template <typename event_t, typename payload_t, typename password_t>
    boolean send(EthernetClient &ethernetClient, const byte target[], const unsigned int port, const event_t event, const payload_t payload, const password_t passwordInput) {
      IPAddress targetIP = IPAddress(target[0], target[1], target[2], target[3]);
      return send(ethernetClient, targetIP, port, event, payload, passwordInput);
    }

    template <typename event_t, typename payload_t>
    boolean send(EthernetClient &ethernetClient, const IPAddress &target, const unsigned int port, const event_t event, const payload_t payload, const __FlashStringHelper* passwordInput) {
      const byte passwordInputLength = FSHlength(passwordInput);
      char passwordChar[passwordInputLength + 1];
      memcpy_P(passwordChar, passwordInput, passwordInputLength + 1);  //+1 for the null terminator
      return send(ethernetClient, target, port, event, payload, passwordChar);
    }
#endif  //ETHEREVENT_NO_AUTHENTICATION
#ifndef ETHEREVENT_FAST_SEND
#ifndef ETHEREVENT_NO_AUTHENTICATION
    template <typename event_t, typename payload_t>
    boolean send(EthernetClient &ethernetClient, const IPAddress &target, const unsigned int port, const event_t event, const payload_t payload, const char passwordInput[] = "") {
#else //ETHEREVENT_NO_AUTHENTICATION
    template <typename event_t, typename payload_t>
    boolean send(EthernetClient &ethernetClient, const IPAddress &target, const unsigned int port, const event_t event, const payload_t payload) {
#endif  //ETHEREVENT_NO_AUTHENTICATION
#else //ETHEREVENT_FAST_SEND
#ifndef ETHEREVENT_NO_AUTHENTICATION
    boolean send(EthernetClient &ethernetClient, const IPAddress &target, const unsigned int port, const char event[], const char payload[] = "", const char passwordInput[] = "") {
#else //ETHEREVENT_NO_AUTHENTICATION
    boolean send(EthernetClient &ethernetClient, const IPAddress &target, const unsigned int port, const char event[], const char payload[] = "") {
#endif  //ETHEREVENT_NO_AUTHENTICATION
#endif  //ETHEREVENT_FAST_SEND

      ETHEREVENT_SERIAL.println(F("EtherEvent.send: attempting connection"));
      ETHEREVENT_SERIAL.print(F("EtherEvent.send: target: "));
      ETHEREVENT_SERIAL.println(target);
      ETHEREVENT_SERIAL.print(F("EtherEvent.send: port: "));
      ETHEREVENT_SERIAL.println(port);
      ETHEREVENT_SERIAL.print(F("EtherEvent.send: event: "));
      ETHEREVENT_SERIAL.println(event);
      ETHEREVENT_SERIAL.print(F("EtherEvent.send: payload: "));
      ETHEREVENT_SERIAL.println(payload);

      byte eventSuccess = false;
      if (ethernetClient.connect(target, port)) {  //connected to receiver

#ifndef ETHEREVENT_NO_AUTHENTICATION
        ethernetClient.setTimeout(timeout);  //Timeout on Stream functions. I only have to set it once here for the send() timeout but I can't set it in begin() because ethernetClient isn't passed to that function there so it's most efficient to just set it here every time
        ETHEREVENT_SERIAL.println(F("EtherEvent.send: connected, sending magic word"));
        ethernetClient.print(F(ETHEREVENT_MAGIC_WORD));  //send the magic word to the receiver so it will send the cookie

        byte currentPasswordLength = passwordLength;
        if (passwordInput[0] != 0) {
          currentPasswordLength = strlen(passwordInput);
        }
        char cookiePassword[cookieLengthMax + 1 + currentPasswordLength + 1];  //cookie, password separator(:), password, null terminator
        if (byte bytesRead = ethernetClient.readBytesUntil(10, cookiePassword, cookieLengthMax)) {  //get the cookie
          cookiePassword[bytesRead] = 0;
          strcat(cookiePassword, ":");  //add the password separator to the cookie
          if (passwordInput[0] != 0) {
            strcat(cookiePassword, passwordInput);  //add password to the cookie
          }
          else {
            strcat(cookiePassword, password);  //add password to the cookie
          }
          ETHEREVENT_SERIAL.print(F("EtherEvent.send: cookiePassword: "));
          ETHEREVENT_SERIAL.println(cookiePassword);
          unsigned char* cookiePasswordHash = MD5::make_hash(cookiePassword);
          char* cookiePasswordMD5 = MD5::make_digest(cookiePasswordHash, 16);
          free(cookiePasswordHash);
          ETHEREVENT_SERIAL.print(F("EtherEvent.send: hashWordMD5: "));
          ETHEREVENT_SERIAL.println(cookiePasswordMD5);
          ethernetClient.print(cookiePasswordMD5);  //send the MD5 of the hashword
          ethernetClient.write(10);  //newline
          free(cookiePasswordMD5);

          if (ethernetClient.find((char*)ETHEREVENT_ACCEPT_MESSAGE) == true) {  //authentication successful - the (char*) thing is to get rid of the "warning: deprecated conversion from string constant to ‘char*’" compiler warning
#endif  //ETHEREVENT_NO_AUTHENTICATION

#ifndef ETHEREVENT_FAST_SEND
            if (noPayload == false) {  //check if there is a payload
#else  //ETHEREVENT_FAST_SEND
            if (payload[0] != 0) {  //check if there is a payload
#endif  //ETHEREVENT_FAST_SEND
              ethernetClient.print(EtherEventNamespace::payloadSeparator);
#ifdef ETHEREVENT_NO_AUTHENTICATION
              //adds [''] to the payload in unauthenticated mode otherwise TCPEvents attempts to evaluate the payload as a python expression because the servertype is assumed to be TCPEvents in unauthenticated mode, EtherEvent.availableEvent() will strip these characters from the payload
              ethernetClient.print('[');
              ethernetClient.write(39);
#endif  //ETHEREVENT_NO_AUTHENTICATION
              ethernetClient.print(payload);
#ifdef ETHEREVENT_NO_AUTHENTICATION
              ethernetClient.write(39);
              ethernetClient.print(']');
#endif  //ETHEREVENT_NO_AUTHENTICATION
              ethernetClient.write(10);  //newline
            }
            ethernetClient.print(event);  //transmit event
            ethernetClient.write(10);  //newline
            eventSuccess = true;
#ifndef ETHEREVENT_NO_AUTHENTICATION
          }
        }
#endif  //ETHEREVENT_NO_AUTHENTICATION    
        ethernetClient.print(EtherEventNamespace::closeMessage);  //tell the receiver to close
        ethernetClient.stop();
        ETHEREVENT_SERIAL.println(F("EtherEvent.send: connection closed"));
      }
      else {
        ETHEREVENT_SERIAL.println(F("EtherEvent.send: connection failed"));
      }
      return eventSuccess;  //send finished
    }

#ifdef ETHEREVENT_FAST_SEND
    //send() is faster with non-char event/payload when the conversions are done this way but the buffering of the converted string causes the SRAM usage to be multiplied and F() event/payload causes flash usage to go up by 150 or 90 bytes depending on whether __FlashStringHelper ocnversion is already being done in another function
    //convert event
#ifdef ETHEREVENT_NO_AUTHENTICATION
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, char event[], const char payload[]) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(char event)"));
      return send(ethernetClient, target, port, (const char*)event, payload);  //Convert char to const char. Needed to fix ambiguous overload warning.
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const int8_t event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(int8_t event)"));
      return send(ethernetClient, target, port, (const int)event, payload);  //Convert event to int. Needed to fix ambiguous overload warning.
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const byte event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(byte event)"));
      return send(ethernetClient, target, port, (const int)event, payload);  //Convert event to int. Needed to fix ambiguous overload warning.
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const int16_t event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(int event)"));
      char eventChar[int16_tLengthMax + 1];
      itoa(event, eventChar, 10);
      return send(ethernetClient, target, port, (const char*)eventChar, payload);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const uint16_t event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(unsigned int event)"));
      char eventChar[uint16_tLengthMax + 1];
      utoa(event, eventChar, 10);
      return send(ethernetClient, target, port, (const char*)eventChar, payload);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const int32_t event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(long event)"));
      char eventChar[int32_tLengthMax + 1];
      ltoa(event, eventChar, 10);
      return send(ethernetClient, target, port, (const char*)eventChar, payload);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const uint32_t event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(unsigned long event)"));
      char eventChar[uint32_tLengthMax + 1];
      ultoa(event, eventChar, 10);
      return send(ethernetClient, target, port, (const char*)eventChar, payload);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const __FlashStringHelper* event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(F() event)"));
      const byte eventLength = FSHlength(event);
      char eventChar[eventLength + 1];
      memcpy_P(eventChar, event, eventLength + 1);  //+1 for the null terminator
      return send(ethernetClient, target, port, (const char*)eventChar, payload);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const String &event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(String event)"));
      const byte stringLength = event.length();
      char eventChar[stringLength + 1];
      for (byte counter = 0; counter < stringLength; counter++) {
        eventChar[counter] = event[counter];  //I could probably just use c_str() instead but then I have to deal with the pointer
      }
      eventChar[stringLength] = 0;
      return send(ethernetClient, target, port, (const char*)eventChar, payload);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const IPAddress &event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(IPAddress event)"));
      char eventChar[IPAddressLengthMax + 1];
      IPtoa(event, eventChar);
      return send(ethernetClient, target, port, (const char*)eventChar, payload);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const double event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(double event)"));
      char eventChar[doubleIntegerLengthMax + 1 + sendDoubleDecimalPlaces + 1];  //max integer length + decimal point + decimal places setting + null terminator
      dtostrf(event, sendDoubleDecimalPlaces + 2, sendDoubleDecimalPlaces, eventChar);
      return send(ethernetClient, target, port, (const char*)eventChar, payload);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const float event, const char payload[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(float event)"));
      return send(ethernetClient, target, port, (double)event, payload);  //needed to fix ambiguous compiler warning
    }

    //convert payload
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const char event[], char payload[]) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(char payload)"));
      return send(ethernetClient, target, port, event, (const char*)payload);  //Convert char to const char. Needed to fix ambiguous overload warning.
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const int16_t payload) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(int payload)"));
      char payloadChar[int16_tLengthMax + 1];
      itoa(payload, payloadChar, 10);
      return send(ethernetClient, target, port, event, payloadChar);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const uint16_t payload) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(unsigned int payload)"));
      char payloadChar[uint16_tLengthMax + 1];
      utoa(payload, payloadChar, 10);
      return send(ethernetClient, target, port, event, payloadChar);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const int32_t payload) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(long payload)"));
      char payloadChar[int32_tLengthMax + 1];
      ltoa(payload, payloadChar, 10);
      return send(ethernetClient, target, port, event, payloadChar);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const uint32_t payload) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(unsigned long payload)"));
      char payloadChar[uint32_tLengthMax + 1];
      ultoa(payload, payloadChar, 10);
      return send(ethernetClient, target, port, event, payloadChar);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const __FlashStringHelper* payload) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(F() payload)"));
      const unsigned int payloadLength = FSHlength(payload);
      char payloadChar[payloadLength + 1];
      memcpy_P(payloadChar, payload, payloadLength + 1);  //+1 for the null terminator
      return send(ethernetClient, target, port, event, payloadChar);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const String &payload) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(String payload)"));
      const byte stringLength = payload.length();
      char payloadChar[stringLength + 1];
      for (byte counter = 0; counter < stringLength; counter++) {
        payloadChar[counter] = payload[counter];  //I could probably just use c_str() instead but then I have to deal with the pointer
      }
      payloadChar[stringLength] = 0;
      return send(ethernetClient, target, port, event, payloadChar);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const IPAddress &payload) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(IPAddress payload)"));
      char payloadChar[IPAddressLengthMax + 1];
      IPtoa(payload, payloadChar);
      return send(ethernetClient, target, port, event, payloadChar);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const double payload) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(double payload)"));
      char payloadChar[doubleIntegerLengthMax + 1 + sendDoubleDecimalPlaces + 1];  //max integer length + decimal point + decimal places setting + null terminator
      dtostrf(payload, sendDoubleDecimalPlaces + 2, sendDoubleDecimalPlaces, payloadChar);
      return send(ethernetClient, target, port, event, payloadChar);
    }

    //convert event and payload
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, char event[], char payload[]) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(char event, char payload)"));
      return send(ethernetClient, target, port, (const char*)event, (const char*)payload);  //Convert char to const char. Needed to fix ambiguous overload warning.
    }


#else  //ETHEREVENT_NO_AUTHENTICATION
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, char event[], const char payload[], const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(char event)"));
      return send(ethernetClient, target, port, (const char*)event, payload, passwordInput);  //Convert char to const char. Needed to fix ambiguous overload warning.
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const int8_t event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(int8_t event)"));
      return send(ethernetClient, target, port, (const int)event, payload, passwordInput);  //Convert event to int. Needed to fix ambiguous overload warning.
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const byte event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(byte event)"));
      return send(ethernetClient, target, port, (const int)event, payload, passwordInput);  //Convert event to int. Needed to fix ambiguous overload warning.
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const int16_t event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(int event)"));
      char eventChar[int16_tLengthMax + 1];
      itoa(event, eventChar, 10);
      return send(ethernetClient, target, port, (const char*)eventChar, payload, passwordInput);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const uint16_t event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(unsigned int event)"));
      char eventChar[uint16_tLengthMax + 1];
      utoa(event, eventChar, 10);
      return send(ethernetClient, target, port, (const char*)eventChar, payload, passwordInput);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const int32_t event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(long event)"));
      char eventChar[int32_tLengthMax + 1];
      ltoa(event, eventChar, 10);
      return send(ethernetClient, target, port, (const char*)eventChar, payload, passwordInput);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const uint32_t event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(unsigned long event)"));
      char eventChar[uint32_tLengthMax + 1];
      ultoa(event, eventChar, 10);
      return send(ethernetClient, target, port, (const char*)eventChar, payload, passwordInput);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const __FlashStringHelper* event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(F() event)"));
      const byte eventLength = FSHlength(event);
      char eventChar[eventLength + 1];
      memcpy_P(eventChar, event, eventLength + 1);  //+1 for the null terminator
      return send(ethernetClient, target, port, (const char*)eventChar, payload, passwordInput);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const String &event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(String event)"));
      const byte stringLength = event.length();
      char eventChar[stringLength + 1];
      for (byte counter = 0; counter < stringLength; counter++) {
        eventChar[counter] = event[counter];  //I could probably just use c_str() instead but then I have to deal with the pointer
      }
      eventChar[stringLength] = 0;
      return send(ethernetClient, target, port, (const char*)eventChar, payload, passwordInput);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const IPAddress &event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(IPAddress event)"));
      char eventChar[IPAddressLengthMax + 1];
      IPtoa(event, eventChar);
      return send(ethernetClient, target, port, (const char*)eventChar, payload, passwordInput);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const double event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(double event)"));
      char eventChar[doubleIntegerLengthMax + 1 + sendDoubleDecimalPlaces + 1];  //max integer length + decimal point + decimal places setting + null terminator
      dtostrf(event, sendDoubleDecimalPlaces + 2, sendDoubleDecimalPlaces, eventChar);
      return send(ethernetClient, target, port, (const char*)eventChar, payload, passwordInput);
    }
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const float event, const char payload[] = "", const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(float event)"));
      return send(ethernetClient, target, port, (double)event, payload, passwordInput);  //needed to fix ambiguous compiler warning
    }

    //convert payload
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const char event[], char payload[], const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(char payload)"));
      return send(ethernetClient, target, port, event, (const char*)payload, passwordInput);  //Convert char to const char. Needed to fix ambiguous overload warning.
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const int16_t payload, const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(int payload)"));
      char payloadChar[int16_tLengthMax + 1];
      itoa(payload, payloadChar, 10);
      return send(ethernetClient, target, port, event, payloadChar, passwordInput);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const uint16_t payload, const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(unsigned int payload)"));
      char payloadChar[uint16_tLengthMax + 1];
      utoa(payload, payloadChar, 10);
      return send(ethernetClient, target, port, event, payloadChar, passwordInput);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const int32_t payload, const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(long payload)"));
      char payloadChar[int32_tLengthMax + 1];
      ltoa(payload, payloadChar, 10);
      return send(ethernetClient, target, port, event, payloadChar, passwordInput);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const uint32_t payload, const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(unsigned long payload)"));
      char payloadChar[uint32_tLengthMax + 1];
      ultoa(payload, payloadChar, 10);
      return send(ethernetClient, target, port, event, payloadChar, passwordInput);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const __FlashStringHelper* payload, const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(F() payload)"));
      const unsigned int payloadLength = FSHlength(payload);
      char payloadChar[payloadLength + 1];
      memcpy_P(payloadChar, payload, payloadLength + 1);  //+1 for the null terminator
      return send(ethernetClient, target, port, event, payloadChar, passwordInput);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const String &payload, const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(String payload)"));
      const byte stringLength = payload.length();
      char payloadChar[stringLength + 1];
      for (byte counter = 0; counter < stringLength; counter++) {
        payloadChar[counter] = payload[counter];  //I could probably just use c_str() instead but then I have to deal with the pointer
      }
      payloadChar[stringLength] = 0;
      return send(ethernetClient, target, port, event, payloadChar, passwordInput);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const IPAddress &payload, const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(IPAddress payload)"));
      char payloadChar[IPAddressLengthMax + 1];
      IPtoa(payload, payloadChar);
      return send(ethernetClient, target, port, event, payloadChar, passwordInput);
    }
    template <typename targetType, typename eventType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, const eventType event, const double payload, const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(double payload)"));
      char payloadChar[doubleIntegerLengthMax + 1 + sendDoubleDecimalPlaces + 1];  //max integer length + decimal point + decimal places setting + null terminator
      dtostrf(payload, sendDoubleDecimalPlaces + 2, sendDoubleDecimalPlaces, payloadChar);
      return send(ethernetClient, target, port, event, payloadChar, passwordInput);
    }

    //convert event and payload
    template <typename targetType>
    boolean send(EthernetClient &ethernetClient, const targetType &target, const unsigned int port, char event[], char payload[], const char passwordInput[] = "") {
      ETHEREVENT_SERIAL.println(F("EtherEvent.send(char event, char payload)"));
      return send(ethernetClient, target, port, (const char*)event, (const char*)payload, passwordInput);  //Convert char to const char. Needed to fix ambiguous overload warning.
    }
#endif  //ETHEREVENT_NO_AUTHENTICATION
#endif  //ETHEREVENT_FAST_SEND

    void setTimeout(const unsigned int timeoutInput);
    unsigned int getTimeout();
    boolean setPassword(const char passwordInput[]);
    boolean setPassword(const __FlashStringHelper* passwordInput);

#ifdef ETHEREVENT_FAST_SEND
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //setSendDoubleDecimalPlaces
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void setSendDoubleDecimalPlaces(const byte decimalPlaces) {
      ETHEREVENT_SERIAL.println(F("EtherEvent.setSendDoubleDecimalPlaces"));
      sendDoubleDecimalPlaces = decimalPlaces;
    }
#endif  //ETHEREVENT_FAST_SEND

    void IPtoa(const IPAddress &IP, char IPcharBuffer[]);
    unsigned int FSHlength(const __FlashStringHelper* FSHinput);


  private:
    //used for the FASTSEND char array conversions
    static const byte uint16_tLengthMax = 5;  //5 digits
    static const byte int16_tLengthMax = 1 + uint16_tLengthMax;  //sign + 5 digits
    static const byte uint32_tLengthMax = 10;  //10 digits
    static const byte int32_tLengthMax = 1 + uint32_tLengthMax;  //sign + 10 digits
    static const byte IPAddressLengthMax = 3 + 1 + 3 + 1 + 3 + 1 + 3;  //4 x octet + 3 x dot
    static const byte doubleIntegerLengthMax = 40;  //sign + 39 digits max (-1000000000000000000000000000000000000000 gives me "floating constant exceeds range of 'double'" warning)

    static const byte cookieLengthMax = 8;

    static const byte TCPEventsPayloadFormattingLength = 2;  //the length of one side of the formatting characters added to payloads entered in the payload field of TCPEvent's "Send an Event" action configuration([''])

    static const unsigned int timeoutDefault = 1000;  //(ms)Timeout duration for ethernet stream functions.
    static const byte sendDoubleDecimalPlacesDefault = 3;  //default number of decimal places when sending event/payload of double/float type



    unsigned int timeout;  //default is set in begin() and the user can change the timeout via setTimeout()
    unsigned int availableEventSubmessageLengthMax;  //value set in begin()

    char* password;
    byte passwordLength;

    boolean noPayload;

    IPAddress fromIP;  //IP address of the last event sender
    byte eventLengthMax;
    char* receivedEvent;  //event buffer
    byte receivedEventLength;  //save the length so I don't have to do strlen everytime availableEvent() is called
    byte readEventLength;  //number of characters of the event that have been read
    unsigned int payloadLengthMax;
    char* receivedPayload;  //payload buffer
    unsigned int receivedPayloadLength;
    unsigned int readPayloadLength;  //number of characters of the payload that have been read
    byte sendDoubleDecimalPlaces;

    void flushEvent();
    void flushPayload();
};

extern EtherEventClass EtherEvent;  //declare the class so it doesn't have to be done in the sketch
#endif

