// include the GSM library
#include <GSM.h>

// initialize the library instances
GSM gsmAccess;
GSM_SMS sms;

void setup() {
  Serial.begin(115200);
  Serial.println("SMS Messages Handler");

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  boolean notConnected = true;
  while (notConnected) {
    if (gsmAccess.begin() == GSM_READY) {
      notConnected = false;
    } else {
      Serial.println("Not connected. Trying again...");
      delay(1000);
    }
  }
  
  Serial.println("GSM initialized");
  Serial.println("Waiting for messages");
  
  String msg = "Plastic Collection Controller Online!\n\n";
  msg += "Controller now connecting to the mainframe...";
  
  sendSMS("","0498580292");
}

void loop() {
  delay(250);
  digitalWrite(13,HIGH);
  
  getSMS();
  delay(250);
  digitalWrite(13,LOW);
}
