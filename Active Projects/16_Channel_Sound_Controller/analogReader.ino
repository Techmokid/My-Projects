//This isn't needed. It just makes reading it easier
bool isBetween(float in, float min, float max) {
  return ((in <= max) && (in >= min));
}

//This is the complicated bit. We need to get data in from 32 analog inputs, but we only have 8 inputs per 4051 chip
//The answer is to use 4 chips, and switch between them as we want to read them.

//For example, if I want to read from input 23, I need to ask chip 3 what the input on pin 7 is
// (In binary, pin 7 is ID 6 (Due to zero indexing, long story), which is "011")

float getAnalogInput(int pin) {
  switch (pin) {
    //We are using the first chip, which for input selection uses pins 13, 12, 11
    case 1:
      digitalWrite(13,false);
      digitalWrite(12,false);
      digitalWrite(11,false);
      return analogRead(A0);
    case 2:
      digitalWrite(13,true);
      digitalWrite(12,false);
      digitalWrite(11,false);
      return analogRead(A0);
    case 3:
      digitalWrite(13,false);
      digitalWrite(12,true);
      digitalWrite(11,false);
      return analogRead(A0);
    case 4:
      digitalWrite(13,true);
      digitalWrite(12,true);
      digitalWrite(11,false);
      return analogRead(A0);
    case 5:
      digitalWrite(13,false);
      digitalWrite(12,false);
      digitalWrite(11,true);
      return analogRead(A0);
    case 6:
      digitalWrite(13,true);
      digitalWrite(12,false);
      digitalWrite(11,true);
      return analogRead(A0);
    case 7:
      digitalWrite(13,false);
      digitalWrite(12,true);
      digitalWrite(11,true);
      return analogRead(A0);
    case 8:
      digitalWrite(13,true);
      digitalWrite(12,true);
      digitalWrite(11,true);
      return analogRead(A0);

    //We are using the second chip, which for input selection uses pins 10, 9, 8
    case 9:
      digitalWrite(10,false);
      digitalWrite(9,false);
      digitalWrite(8,false);
      return analogRead(A1);
    case 10:
      digitalWrite(10,true);
      digitalWrite(9,false);
      digitalWrite(8,false);
      return analogRead(A1);
    case 11:
      digitalWrite(10,false);
      digitalWrite(9,true);
      digitalWrite(8,false);
      return analogRead(A1);
    case 12:
      digitalWrite(10,true);
      digitalWrite(9,true);
      digitalWrite(8,false);
      return analogRead(A1);
    case 13:
      digitalWrite(10,false);
      digitalWrite(9,false);
      digitalWrite(8,true);
      return analogRead(A1);
    case 14:
      digitalWrite(10,true);
      digitalWrite(9,false);
      digitalWrite(8,true);
      return analogRead(A1);
    case 15:
      digitalWrite(10,false);
      digitalWrite(9,true);
      digitalWrite(8,true);
      return analogRead(A1);
    case 16:
      digitalWrite(10,true);
      digitalWrite(9,true);
      digitalWrite(8,true);
      return analogRead(A1);

    //We are using the third chip, which for input selection uses pins 7, 6, 5
    case 17:
      digitalWrite(7,false);
      digitalWrite(6,false);
      digitalWrite(5,false);
      return analogRead(A2);
    case 18:
      digitalWrite(7,true);
      digitalWrite(6,false);
      digitalWrite(5,false);
      return analogRead(A2);
    case 19:
      digitalWrite(7,false);
      digitalWrite(6,true);
      digitalWrite(5,false);
      return analogRead(A2);
    case 20:
      digitalWrite(7,true);
      digitalWrite(6,true);
      digitalWrite(5,false);
      return analogRead(A2);
    case 21:
      digitalWrite(7,false);
      digitalWrite(6,false);
      digitalWrite(5,true);
      return analogRead(A2);
    case 22:
      digitalWrite(7,true);
      digitalWrite(6,false);
      digitalWrite(5,true);
      return analogRead(A2);
    case 23:
      digitalWrite(7,false);
      digitalWrite(6,true);
      digitalWrite(5,true);
      return analogRead(A2);
    case 24:
      digitalWrite(7,true);
      digitalWrite(6,true);
      digitalWrite(5,true);
      return analogRead(A2);

    //We are using the fourth chip, which for input selection uses pins 4, 3, 2
    case 25:
      digitalWrite(4,false);
      digitalWrite(3,false);
      digitalWrite(2,false);
      return analogRead(A3);
    case 26:
      digitalWrite(4,true);
      digitalWrite(3,false);
      digitalWrite(2,false);
      return analogRead(A3);
    case 27:
      digitalWrite(4,false);
      digitalWrite(3,true);
      digitalWrite(2,false);
      return analogRead(A3);
    case 28:
      digitalWrite(4,true);
      digitalWrite(3,true);
      digitalWrite(2,false);
      return analogRead(A3);
    case 29:
      digitalWrite(4,false);
      digitalWrite(3,false);
      digitalWrite(2,true);
      return analogRead(A3);
    case 30:
      digitalWrite(4,true);
      digitalWrite(3,false);
      digitalWrite(2,true);
      return analogRead(A3);
    case 31:
      digitalWrite(4,false);
      digitalWrite(3,true);
      digitalWrite(2,true);
      return analogRead(A3);
    case 32:
      digitalWrite(4,true);
      digitalWrite(3,true);
      digitalWrite(2,true);
      return analogRead(A3);
  }
  
  return 0.00;
}
