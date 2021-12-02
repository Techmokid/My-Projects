#define MULTIPLEXER_PIN_1 52
#define MULTIPLEXER_PIN_2 53
#define MULTIPLEXER_PIN_3 54
#define ClkPulseLen 10

#define FASTADC 1

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setupSensors() {
#if FASTADC
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;
#endif
  pinMode(A0,INPUT_PULLUP);
  pinMode(A1,INPUT_PULLUP);
  pinMode(A2,INPUT_PULLUP);
  pinMode(A3,INPUT_PULLUP);
  pinMode(A4,INPUT_PULLUP);
  
  pinMode(MULTIPLEXER_PIN_1,OUTPUT);
  pinMode(MULTIPLEXER_PIN_2,OUTPUT);
  pinMode(MULTIPLEXER_PIN_3,OUTPUT);
}

void updateSensors() {
  //Using 4051 8 input multiplexer
  for (int i = 0; i < 8; i++) {
    //We wanna set the 1,2,3 pins of the analog multiplexers
    digitalWrite(MULTIPLEXER_PIN_1,bitRead(i,0));
    digitalWrite(MULTIPLEXER_PIN_2,bitRead(i,1));
    digitalWrite(MULTIPLEXER_PIN_3,bitRead(i,2));
    delayMicroseconds(ClkPulseLen);
    
    sensorDataArr[0 + 5*i] = analogRead(A0);
    sensorDataArr[1 + 5*i] = analogRead(A1);
    sensorDataArr[2 + 5*i] = analogRead(A2);
    sensorDataArr[3 + 5*i] = analogRead(A3);
    sensorDataArr[4 + 5*i] = analogRead(A4);
  }
}

int getSensorOutput(int ID) { return sensorDataArr[ID]; }

bool sensorDisconnected() {
  for (int i = 0; i < sizeof(sensorDataArr)/sizeof(sensorDataArr[0]); i++) {
    if ((sensorDataArr[i] == 0) || (sensorDataArr[i] == 1023)) {
      return true;
    }
  }
  return false;
}
