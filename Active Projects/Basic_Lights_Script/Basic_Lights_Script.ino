#include <Adafruit_NeoPixel.h>

#define PIN_LEDS              2 // The data pin you connect the LED strips to.
#define PIN_MODE_SWITCH       3 // Just connect your "Mode" switch between this pin and ground. No switch connection means it defaults to driving mode if something goes wrong

#define PIN_BRAKE             4 // Remember to use a resistor bridge to decrease voltage to 5 volts or less
#define PIN_FOGLIGHTS         5 // Remember to use a resistor bridge to decrease voltage to 5 volts or less
#define PIN_REVERSE           6 // Remember to use a resistor bridge to decrease voltage to 5 volts or less
#define PIN_LEFT_INDICATOR    7 // Remember to use a resistor bridge to decrease voltage to 5 volts or less
#define PIN_RIGHT_INDICATOR   8 // Remember to use a resistor bridge to decrease voltage to 5 volts or less

#define SOFTWARE_CONTROLLED_INDICATOR_BLINK true
#define BLANK_INDICATORS_WHILE_FLASHING true

#define LEDS_PER_CIRCLE 24
#define INDICATOR_FLASHRATE 75




#define INDICATOR_DELAY_TIME int(60000/INDICATOR_FLASHRATE)

Adafruit_NeoPixel strip(LEDS_PER_CIRCLE * 4, PIN_LEDS, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(PIN_MODE_SWITCH,INPUT_PULLUP);
  pinMode(PIN_BRAKE,INPUT);
  pinMode(PIN_FOGLIGHTS,INPUT);
  pinMode(PIN_REVERSE,INPUT);
  pinMode(PIN_LEFT_INDICATOR,INPUT);
  pinMode(PIN_RIGHT_INDICATOR,INPUT);

  strip.begin();
  strip.setBrightness(255);
}

void loop(){if(digitalRead(PIN_MODE_SWITCH)){DemoMode();}else{DrivingMode();}}

void SetAllCirclesColor(int R, int G, int B) {
  for (int i = 0; i < LEDS_PER_CIRCLE * 4; i++) {
    strip.setPixelColor(i,R,G,B);
  }
}

void SetCircleColor(int circleIndex, int R, int G, int B) {
  for (int i = 0; i < LEDS_PER_CIRCLE; i++) {
    strip.setPixelColor(circleIndex*LEDS_PER_CIRCLE + i,R,G,B);
  }
}

// Function to create the rainbow colors
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}






// The two modes, demo mode and regular driving mode
int colorWheelRotation = 0;
void DemoMode() {
  // Here is the fancy demo mode you make look pretty and stuff. I've precoded it with a basic rotating color wheel
  for (int circleIndex = 0; circleIndex < 4; circleIndex++) {
    for (int i = 0; i < LEDS_PER_CIRCLE; i++) {
      strip.setPixelColor(i + circleIndex*LEDS_PER_CIRCLE, Wheel(((i * 256 / LEDS_PER_CIRCLE) + colorWheelRotation) & 255));
    }
  }
  strip.show();

  // Decrease this pause to make the circle spin faster
  // Increase this pause to make the circle spin slower
  delay(20); // Pause 20ms between each iteration.
}

void DrivingMode() {
  // Regular driving mode. This is the default mode if the switch gets disconnected for safety reasons
  if (digitalRead(PIN_BRAKE)) {             // Braking
    SetAllCirclesColor(255,0,0);
  } else if (digitalRead(PIN_FOGLIGHTS)) {  // Headlights are on
    SetAllCirclesColor(100,0,0);
  } else if (digitalRead(PIN_REVERSE)) {    // Reversing
    SetAllCirclesColor(255,255,255);
  }

  HandleIndicators();
  strip.show();

  delay(100);
}

int lastFlashTime = 0;
bool flashState = false;
void HandleIndicators() {
  if (!SOFTWARE_CONTROLLED_INDICATOR_BLINK) {
    if (digitalRead(PIN_LEFT_INDICATOR)) {
      SetCircleColor(0,255,210,0);          // Assuming wheel 0 is left and wheel 3 is right
    }

    if (digitalRead(PIN_RIGHT_INDICATOR)) {
      SetCircleColor(3,255,210,0);          // Assuming wheel 0 is left and wheel 3 is right
    }
  } else {
    // We are bypassing the ECU's flasher control and just directly handling the indicators blinking
    if (millis() - lastFlashTime > INDICATOR_DELAY_TIME) {
      lastFlashTime = millis();
      flashState = !flashState;
    }

    if (digitalRead(PIN_LEFT_INDICATOR)) {
      if (flashState && SOFTWARE_CONTROLLED_INDICATOR_BLINK) {
        SetCircleColor(0,0,0,0);          // Assuming wheel 0 is left and wheel 3 is right
      } else {
        SetCircleColor(0,255,210,0);
      }
    }

    if (digitalRead(PIN_RIGHT_INDICATOR)) {
      if (flashState && SOFTWARE_CONTROLLED_INDICATOR_BLINK) {
        SetCircleColor(3,0,0,0);          // Assuming wheel 0 is left and wheel 3 is right
      } else {
        SetCircleColor(3,255,210,0);
      }
    }
  }
}