#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
#include <URTouch.h>

MCUFRIEND_kbv tft;

#define t_SCK 13              
#define t_CS A3                
#define t_MOSI A1            
#define t_MISO A0              
#define t_IRQ A4     

URTouch ts(t_SCK, t_CS, t_MOSI, t_MISO, t_IRQ);

void setup() {
  Serial.begin(115200);
  tft.reset();
  tft.begin(tft.readID());
  tft.setRotation(1);
  
  tft.fillScreen(0x0000);
  
  ts.InitTouch();
  ts.setPrecision(PREC_EXTREME);
}

void loop() {
  if (ts.dataAvailable()) {
    ts.read();
    Serial.println(String(ts.getX()) + " " + String(ts.getY()));
  }
  
  //Serial.println(String(ts.TP_X) + " " + String(ts.TP_Y));
  
  delay(50);
}
