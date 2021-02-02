//We require 16 channels of sound. That means:
// - 16 PWM outputs (Easy)
// - 32 analog inputs (Hard)

//This is a simple little structure of code that handles the output of a pin
struct pinController {
  //These are the important variables we want to take note of
  int pin = 2;
  float frequency = 0;
  float dutyCycle = 0;

  //These are timing variables
  unsigned long _timer = 0;
  bool state = false;

  //We call this to set up the pin as an output and default it to being off
  void setPin(int _pin) {
    pin = _pin;
    pinMode(pin,OUTPUT);
    digitalWrite(pin,false);
  }
  
  void updatePin() {
    if (frequency == 0) { return; }
    
    //Little bit of maths. Nothing too severe.
    //Just calculating how long to keep the pin on or off for to get the correct dutycycle and frequency
    float OnTime  = (1,000,000 / frequency) * dutyCycle;
    float OffTime = (1,000,000 / frequency) * (1 - dutyCycle);
    float timeSinceLastTrigger = micros() - _timer;

    //Now we just ask if the pin should change state from off to on or back again using the timing variable
    //Simply reset the timing variable, write the value we want out, then flip the pin state
    if ((state == true) && (timeSinceLastTrigger >= OnTime)) {
      timeSinceLastTrigger = micros();
      digitalWrite(pin,state);
      state = false;
    } else if ((state == false) && (timeSinceLastTrigger >= OffTime)) {
      timeSinceLastTrigger = micros();
      digitalWrite(pin,state);
      state = true;
    }
  }
};

//Here we want to define each channel using the structure we just wrote
pinController channel_1;
pinController channel_2;
pinController channel_3;
pinController channel_4;
pinController channel_5;
pinController channel_6;
pinController channel_7;
pinController channel_8;
pinController channel_9;
pinController channel_10;
pinController channel_11;
pinController channel_12;
pinController channel_13;
pinController channel_14;
pinController channel_15;
pinController channel_16;

//Now here we just designate each channel to an output pin
void setup() {
  channel_1.setPin(53);
  channel_2.setPin(52);
  channel_3.setPin(51);
  channel_4.setPin(50);
  channel_5.setPin(49);
  channel_6.setPin(48);
  channel_7.setPin(47);
  channel_8.setPin(46);
  channel_9.setPin(45);
  channel_10.setPin(44);
  channel_11.setPin(43);
  channel_12.setPin(42);
  channel_13.setPin(41);
  channel_14.setPin(40);
  channel_15.setPin(39);
  channel_16.setPin(38);
}

//For every single channel, we want to set it's frequency, dutyCycle, and then update the pin
void loop() {
  channel_1.frequency = getAnalogInput(1);
  channel_1.dutyCycle = map(getAnalogInput(2),0,1023,55,1760);
  channel_1.updatePin();

  channel_2.frequency = getAnalogInput(3);
  channel_2.dutyCycle = map(getAnalogInput(4),0,1023,55,1760);
  channel_2.updatePin();

  channel_3.frequency = getAnalogInput(5);
  channel_3.dutyCycle = map(getAnalogInput(6),0,1023,55,1760);
  channel_3.updatePin();

  channel_4.frequency = getAnalogInput(7);
  channel_4.dutyCycle = map(getAnalogInput(8),0,1023,55,1760);
  channel_4.updatePin();

  channel_5.frequency = getAnalogInput(9);
  channel_5.dutyCycle = map(getAnalogInput(10),0,1023,55,1760);
  channel_5.updatePin();

  channel_6.frequency = getAnalogInput(11);
  channel_6.dutyCycle = map(getAnalogInput(12),0,1023,55,1760);
  channel_6.updatePin();

  channel_7.frequency = getAnalogInput(13);
  channel_7.dutyCycle = map(getAnalogInput(14),0,1023,55,1760);
  channel_7.updatePin();

  channel_8.frequency = getAnalogInput(15);
  channel_8.dutyCycle = map(getAnalogInput(16),0,1023,55,1760);
  channel_8.updatePin();
  
  channel_9.frequency = getAnalogInput(17);
  channel_9.dutyCycle = map(getAnalogInput(18),0,1023,55,1760);
  channel_9.updatePin();

  channel_10.frequency = getAnalogInput(19);
  channel_10.dutyCycle = map(getAnalogInput(20),0,1023,55,1760);
  channel_10.updatePin();

  channel_11.frequency = getAnalogInput(21);
  channel_11.dutyCycle = map(getAnalogInput(22),0,1023,55,1760);
  channel_11.updatePin();

  channel_12.frequency = getAnalogInput(23);
  channel_12.dutyCycle = map(getAnalogInput(24),0,1023,55,1760);
  channel_12.updatePin();

  channel_13.frequency = getAnalogInput(25);
  channel_13.dutyCycle = map(getAnalogInput(26),0,1023,55,1760);
  channel_13.updatePin();

  channel_14.frequency = getAnalogInput(27);
  channel_14.dutyCycle = map(getAnalogInput(28),0,1023,55,1760);
  channel_14.updatePin();

  channel_15.frequency = getAnalogInput(29);
  channel_15.dutyCycle = map(getAnalogInput(30),0,1023,55,1760);
  channel_15.updatePin();

  channel_16.frequency = getAnalogInput(31);
  channel_16.dutyCycle = map(getAnalogInput(32),0,1023,55,1760);
  channel_16.updatePin();
}
