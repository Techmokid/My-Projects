#include <Wire.h>
#include "RTClib.h"
RTC_DS1307 rtc;

const int dispPins[] = {
  10, 11, 19, 18, 17, 16, 15, 14,
  2,  3,  4,  5,  6,  7,  8,  9,
  38, 40, 42, 44, 46, 48, 50, 52,
  39, 41, 43, 45, 47, 49, 51, 53,
  22, 24, 26, 28, 30, 32, 34, 36,
  23, 25, 27, 29, 31, 33, 35, 37
};

int hours = 12;
int minutes = 00;
int seconds = 00;
bool militaryTime = false;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  
  //displayTest();
  identifyDisplays();
  delay(3000);

  if (!rtc.begin()) {
    Serial.println("Could not start RTC");
    setDisplay(0,'r');
    setDisplay(1,'t');
    setDisplay(2,'c');
    setDisplay(3,'e');
    setDisplay(4,'r');
    setDisplay(5,'r');
    while(1);
  } else {
    setDisplay(0,'r');
    setDisplay(1,'t');
    setDisplay(2,'c');
    setDisplay(0,'1');
    setDisplay(1,'/');
    setDisplay(2,'2');
  }

  delay(1000);
  if (!rtc.isrunning()) {
    //rtc.adjust(DateTime(2022, 4, 17, 12, 0, 0));
    rtc.set(RTC_HOUR,12);
    rtc.set(RTC_MINUTE,0);
    rtc.set(RTC_SECOND,0);
    Serial.println("RTC is not running");
    delay(1000);
    if (rtc.isrunning()) {
      Serial.println("Started RTC by setting");
    }
    setDisplay(0,'r');
    setDisplay(1,'t');
    setDisplay(2,'c');
    setDisplay(3,'e');
    setDisplay(4,'r');
    setDisplay(5,'r');
    while(1);
  } else {
    setDisplay(0,'r');
    setDisplay(1,'t');
    setDisplay(2,'c');
    setDisplay(0,'2');
    setDisplay(1,'/');
    setDisplay(2,'2');
  }
  
  delay(1000);
}

void loop() {
  if (Serial.available()) {
    delay(100);

    String msg = String(char(Serial.read()));
    while(Serial.available()) { msg += String(char(Serial.read())); }
    
    String hrs = msg.substring(0,msg.indexOf(':'));
    msg = msg.substring(hrs.length() + 1);
    String mins = "";
    String secs = "0";
    if (msg.indexOf(':') > -1) {
      mins = msg.substring(0,msg.indexOf(':'));
      secs = msg.substring(mins.length() + 1);
    } else {
      mins = msg.substring(mins.length() + 1);
    }

    hrs = getNumsOnly(hrs);
    mins = getNumsOnly(mins);
    secs = getNumsOnly(secs);

    //rtc.adjust(DateTime(2022, 4, 17, hrs.toInt(), mins.toInt(), secs.toInt()));
    rtc.set(RTC_HOUR,hrs.toInt());
    rtc.set(RTC_MINUTE,mins.toInt());
    rtc.set(RTC_SECOND,secs.toInt());
  }
  
  DateTime now = rtc.now();
  hours = now.hour();
  minutes = now.minute();
  seconds = now.second();
  
  displayTime(hours, minutes, seconds);
}

String getNumsOnly(String x) {
  String res = "";
  for(int i = 0; i < x.length(); i++) {
    if (x[i] > 47 && x[i] < 58) {
      res += x[i];
    }
  }
  return res;
}
