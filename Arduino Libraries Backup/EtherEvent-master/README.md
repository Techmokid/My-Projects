EtherEvent
==========

Easy to use [Arduino](http://arduino.cc) library for password authenticated network communication via Ethernet between Arduinos and [EventGhost](http://eventghost.com), or any other program compatible with the EventGhost Network Event Sender and Receiver plugins. Compatible with Arduino Ethernet, Ethernet Shield, and other devices using the W5100/W5200/W5500 Ethernet controller.


#### Compatible Software
- Free
  - Tested to work with this library:
    - EventGhost: http://eventghost.com - Free open source automation tool for Windows. The Network Event Sender and Receiver plugins are compatible with EtherEvent.
    - TCPEvents EventGhost plugin: https://github.com/per1234/TCPEvents - Improved network event sender/receiver allows sending events to multiple IP addresses.
    - EgiGeoZone Geofence: https://play.google.com/store/apps/details?id=de.egi.geofence.geozone with the Arduino EtherEvent plugin: https://play.google.com/store/apps/details?id=de.egi.geofence.geozone.plugin.arduinoetherevent
    - EventGhost automation with LabVIEW: http://decibel.ni.com/content/docs/DOC-13135 - LabVIEW network event sender and receiver VI. The receiver requires a large timeout value.
  - Untested:
    - eventghost-android: http://github.com/timhoeck/eventghost-android - Android network event app
    - EGRemote Lite: http://play.google.com/store/apps/details?id=eu.rml.lab.egremote_lite - Android network event app
    - RemoteGhost: http://forum.xda-developers.com/showthread.php?t=2076716 - Windows Phone network event app
    - ProntoScript Library: http://remotecentral.com/cgi-bin/mboard/prontopro/thread.cgi?3646 - Philips Pronto Home Control Panel communication
    - Android/Eventghost Communication Suite: http://ip-symcon.de/forum/threads/19614-Android-Eventghost-Communication-Suite - IP-Symcon(pay software) automation system communication
- Pay
  - Untested:
    - terRemote - Android network event app
    - EGRemote - Android network event app
    - RemoteGhostPro - Windows Phone network event app


#### Related Programs
- EtherEventQueue outgoing event queue library: http://github.com/per1234/EtherEventQueue
- Modified Ethernet library - allows the use of `EtherEvent.senderIP()`: http://github.com/per1234/EthernetMod - make sure to choose the correct branch for your Arduino IDE version. The [W5x00 branch](https://github.com/per1234/EthernetMod/tree/W5x00) supports W5100, W5200 and W5500 Ethernet controllers.
- Wiznet Ethernet library provides another option for use with W5200 or W5500 Ethernet controllers: https://github.com/embeddist/WIZ_Ethernet_Library-IDE1.5.x


<a id="installation"></a>
#### Installation
- 32kB is the minimum recommended flash memory capacity for use of this library.
- Download the most recent version of EtherEvent here: https://github.com/per1234/EtherEvent/archive/master.zip
- Using Arduino IDE 1.0.x:
  - **Sketch > Import Library... > Add Library... >** select the downloaded file **> Open**
- Using Arduino IDE 1.5+:
  - **Sketch > Include Library > Add ZIP Library... >** select the downloaded file **> Open**
- Repeat this process with any other required libraries.
  - ArduinoMD5 http://github.com/tzikis/ArduinoMD5 - Not required if you disable event authentication.
  - If you want to use `EtherEvent.senderIP()` then you must install the modified Ethernet library: http://github.com/per1234/EthernetMod
- Running the example sketch:
  - File > Examples > EtherEvent > BasicUsage
  - Enable DHCP or set the device IP address, this can be any available IP address on your network.
  - Set the device MAC address. This can be any address not already used on your network
  - Set the EtherEvent password. The password must be the same on all connected devices.
  - Upload to device
  - Repeat with other connected devices.
  - Details of the test communications will be printed to the serial monitor.


#### About Events and Payloads
Events are used to trigger an action. The payload is information that accompanies the event. An example is an event code that triggers the display of the payload. Some events don't require a payload and in this case the payload may be left blank.


<a id="usage"></a>
#### Usage
See the example sketches at **File > Examples > EtherEvent** and the EventGhost tree files in the **examples/EventGhost-example-trees** folder for demonstration of library usage.

##### `#include <EtherEvent.h>`
Allow access to the functions of the EtherEvent library.

##### `#define ETHEREVENT_NO_AUTHENTICATION`
Add this line above the `#include <EtherEvent.h>` line in your sketch to disable password authentication. Requires [my version of the TCPEvents plugin](https://github.com/per1234/TCPEvents) with the password fields left blank in the configurations for communication with EventGhost. With authentication disabled the ArduinoMD5 library is not required, no need to set the password, memory usage is decreased significantly, and event transmission speed is increased. See the NoAuthentication example for a demonstration.

##### `#define ETHEREVENT_FAST_SEND`
Increase sending speed at the expense of increased memory use. Add this line above the `#include <EtherEvent.h>` line in your sketch. This significantly increases the speed of sending __FlashStringHelper(`F()` macro) events/payloads but also increases the sketch size and SRAM usage during the send process. ETHEREVENT_FAST_SEND also increases the speed of sending some other event/payload types.

##### `EtherEvent.begin([eventLengthMax, payloadLengthMax])`
Initialize EtherEvent.
- Parameter(optional): **eventLengthMax** - The maximum length of event that can be received. Longer events will be truncated to this length. EtherEvent reserves SRAM to buffer the received event so this value affects the amount of memory used. The default value is 15.
  - Type: byte
- Parameter(optional): **payloadLengthMax** - The maximum length of payload that can be received. Longer payloads will be truncated to this length. EtherEvent reserves SRAM to buffer the received payload so this value affects the amount of memory used. The default value is 100.
  - Type: unsigned int
- Returns: `true` = success, `false` = memory allocation failed
  - Type: boolean

##### `EtherEvent.setPassword(password)`
Set the password. This is not required if authentication is disabled.
- Parameter: **password** - Password used to authenticate event transmission.
  - Type: char array or __FlashStringHelper(`F()` macro)
- Returns: `true` = success, `false` = memory allocation failed
  - Type: boolean

##### `EtherEvent.availableEvent(ethernetServer[, cookie[, password]])`
Receives new event if an event is not already buffered.
- Parameter: **ethernetServer** - The EthernetServer object created in the Ethernet setup of the user's sketch.
  - Type: EthernetServer
- Parameter(optional): **cookie** - Cookie value to use in the authentication process. This can be used to provide a truly random cookie for enhanced security. If this parameter is not specified then a pseudorandom cookie will be generated using `random()`.
  - Type: long
- Parameter(optional): **password** - Password to use for the current event send. If the password parameter is used then the cookie parameter must be specified(If you want EtherEvent to generate your cookie then use `false` for the cookie parameter).
  - Type: char array, __FlashStringHelper(`F()` macro)
- Returns: Buffer size required to receive the event. This is the length of the received event and the null terminator minus the amount of the event already read.
  - Type: byte

##### `EtherEvent.availableEvent()`
- Returns: Length of the received event and the null terminator minus the amount of the event already read.
  - Type: byte
  
##### `EtherEvent.availablePayload()`
`EtherEvent.availableEvent()` must be called first.
- Returns: Buffer size required to receive the payload. This is the length of the received payload and the null terminator minus the amount of the payload already read.
  - Type: unsigned int

##### `EtherEvent.readEvent(eventBuffer)`
Puts the event in the passed array. `EtherEvent.availableEvent()` must be called first, size a char array according to the result and pass it to `EtherEvent.readEvent()`. After that it will contain the event.
- Parameter: **eventBuffer** - Buffer to hold the received event.
  - Type: char array
- Returns: none

##### `EtherEvent.readEvent()`
- Returns: The next character of the event.
  - Type: char
  
##### `EtherEvent.readPayload(payloadBuffer)`
Puts the payload string in the passed array. `EtherEvent.availableEvent()` must be called first, size a char array according to the result and pass it to `EtherEvent.readPayload()`. After that it will contain the payload.
- Parameter: **payloadBuffer** - Buffer to hold the received payload.
  - Type: char array
- Returns: none

##### `EtherEvent.readPayload()`
- Returns: The next character of the payload.
  - Type: char
  
##### `EtherEvent.senderIP()`
Returns the IP address of the sender of the most recent event. Must have the [modified Ethernet library](http://github.com/per1234/EthernetMod) installed for this function to be available.
- Returns: IP address of the sender.
  - Type: IPAddress

##### `EtherEvent.flushReceiver()`
Clear any buffered event and payload data so a new event can be received.
- Returns: none

##### `EtherEvent.send(ethernetClient, target, port, event[, payload[, password]])`
Send an event and payload.
- Parameter: **ethernetClient** - The EthernetClient object created in the Ethernet setup of the user's sketch.
  - Type: EthernetClient
- Parameter: **target** - IP address to send the event to.
  - Type: IPAddress or byte(4 byte array)
- Parameter: **port** - Port to send the event to.
  - Type: unsigned int
- Parameter: **event**
  - Type: char array, int8_t, byte, int, unsigned int, long, unsigned long, __FlashStringHelper(`F()` macro), String, IPAddress, float, double, Printable
- Parameter(optional): **payload** - Payload to send with the event.
  - Type: char array, int8_t, byte, int, unsigned int, long, unsigned long, __FlashStringHelper(`F()` macro), String, IPAddress, float, double, Printable
- Parameter(optional): **password** - Password to use for the current event send. If the password parameter is used then the payload parameter must be specified(If there is no payload use `""`).
  - Type: char array, __FlashStringHelper(`F()` macro)
- Returns: `true` = success, `false` = failure
  - Type: boolean

##### `EtherEvent.setSendDoubleDecimalPlaces(decimalPlaces)`
Set the number of decimal places when sending double or float type events and payloads. This function is only available if `ETHEREVENT_FAST_SEND` is defined. In normal mode only two decimal places are supported.
- Parameter: **decimalPlaces** - The initial value is 3.
  - Type: byte
- Returns: none

##### `EtherEvent.getTimeout()`
Returns the current timeout duration setting.
- Returns: The current timeout duration setting.
  - Type: unsigned int

##### `EtherEvent.setTimeout(timeout)`
Set the timeout duration(Stream functions).
- Parameter: **timeout** - The maximum time to wait for Ethernet communication in milliseconds.
  - Type: unsigned int
- Returns: none


<a id="troubleshooting"></a>
#### Troubleshooting
- Network configuration:
  - The MAC address you choose for the device must be unique on your network.
  - If using a static IP address it must be unique on your network.
  -  If using EventGhost, the firewall on the computer must allow it to communicate via the network.
- Timeouts: When using the **BasicUsage.ino** example sketch you may notice sending or receiving an event sometimes will hang for a long time before failing. This is caused by the conservative default timeout values. **AdvancedUsage.ino** demonstrates setting the EtherEvent timeout via `EtherEvent.setTimeout()` and the W5x00 Ethernet controller timeout and retry count via `W5100.setRetransmissionTime()` and `W5100.setRetransmissionCount()`. `EtherEvent.setTimeout()` controls the amount of time that EtherEvent will wait for the authentication process communications. `W5100.setRetransmissionTime()` controls the amount of time that the W5x00 will wait after a connection attempt before retrying. `W5100.setRetransmissionCount()` controls the number of attempts the W5x00 will make before failing the connection attempt. By reducing the timeout values you can shorten the amount of time that the system will hang during a failed event transmission. If the timeout values are too small then you will see frequent transmission failures. By experimenting with different values you can find appropriate timeouts for your system. Be aware that the timeout requirements for Arduino to EventGhost event transmission may be different than Arduino to Arduino transmission.
- Debug output: By turning debug output on you can get details of the authentication process in the serial monitor. Set `#define ETHEREVENT_DEBUG true` in EtherEvent.h, this will slow down communication and increase memory usage so only enable when needed. The default speed of the debug serial output is 9600 but this can be changed in the line `const unsigned long debugSerialBaud = 9600;` in **EtherEvent.h**
- If EventGhost recieves an event that contain '.' the standard event prefix will disappear from that event. This is a limitation of EventGhost, not EtherEvent.


<a id="security"></a>
#### Security Considerations
- If security is not necessary for your application you can disable authentication(see the NoAuthentication example).
- EtherEvent only encrypts the authentication password. The event is sent in plaintext. This prevents the receipt of unauthorized events but does not protect the information contained in the event from being seen.
- Use of EventGhost Network Event Receiver plugin in EventGhost versions previous to 4.0.1.r1710 is not recommended due to a bug that causes it to send the same cookie for every event. My [modified TCPEvents EventGhost plugin](https://github.com/per1234/TCPEvents) has this security vulnerability patched.
- Cookie Randomization: an important factor in the authentication security is the randomness of the cookie supplied by the event receiver. There is a trade-off between security and memory usage/speed so the ideal level of cookie randomization depends on your application.
  - Default operation: If a cookie is not supplied then EtherEvent uses the value of `micros()` for a seed and produces the cookie using `random()`.
  - User supplied cookie: You can generate your own random cookie and pass the value to `EtherEvent.availableEvent()`.
    - Entropy library: A truly random number can be generated by the Entropy library and used for every cookie. This will cause greater flash memory usage and slower authentication. See the example sketch **Entropy.ino** for demonstration of use of the Entropy library with EtherEvent.


<a id="process"></a>
#### Authentication Process
EventGhost uses MD5 encrypted APOP style authentication to avoid sending passwords in plaintext.
- sender: Connect to receiver. Send `quintessence\n\r`.
- receiver: Send cookie.
- sender: The password is appended to the cookie and the MD5 digest is calculated and sent back to the receiver.
- receiver: If the received MD5 digest is correct then it sends `accept`.
- sender: Send `payload {payload string}\n{event}\nclose\n` to the receiver.
- receiver: Close the connection to the sender.

