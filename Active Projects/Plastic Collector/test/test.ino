#include <sim800cmd.h>
//initialize the library instance
//fundebug is an application callback function,when someone is calling.
Sim800Cmd sim800demo(fundebug);

//the setup routine runs once when you press reset:
void setup() {
  //initialize SIM800H,return 1 when initialize success.
  while((sim800demo.sim800init()) == 0);
  Serial.println("Fixed");
}

//the loop routine runs over and over again forever:
void loop() {
  //Signal strength
  unsigned char csq = 0;
  //To obtain the signal strength, return 1 when obtain success.
  if( sim800demo.callReadCSQ(&csq) ) {
    Serial.println("Connecting");
    //Make Voice Call
    sim800demo.sendSMS("0030003400390038003500380030003200390032","0030003400390038003500380030003200390032");
    Serial.println("Connected!");
    while(1);
  }
  digitalWrite(13,HIGH);//turn the LED on by making the voltage HIGH
  delay(500);
  digitalWrite(13,LOW);//turn the LED off by making the voltage LOW
  delay(500);
}
 
//application callback function
void fundebug(void) { }
