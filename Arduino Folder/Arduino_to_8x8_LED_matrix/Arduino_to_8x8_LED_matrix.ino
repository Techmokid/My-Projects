/* code for max 7219 from maxim, 
reduced and optimised for useing more then one 7219 in a row,
______________________________________

Code History:
--------------

The orginal code was written for the Wiring board by:
* Nicholas Zambetti and Dave Mellis /Interaction Design Institute Ivrea /Dec 2004
* http://www.potemkin.org/uploads/Wiring/MAX7219.txt

First modification by:
* Marcus Hannerstig/  K3, malm? h?gskola /2006
* http://www.xlab.se | http://arduino.berlios.de

This version is by:
* tomek ness /FH-Potsdam / Feb 2007
* http://design.fh-potsdam.de/ 

* @acknowledgements: eric f. 

-----------------------------------

General notes: 


-if you are only using one max7219, then use the function maxSingle to control
the little guy ---maxSingle(register (1-8), collum (0-255))

-if you are using more then one max7219, and they all should work the same, 
then use the function maxAll ---maxAll(register (1-8), collum (0-255))

-if you are using more than one max7219 and just want to change something
at one little guy, then use the function maxOne
---maxOne(Max you wane controll (1== the first one), register (1-8), 
collum (0-255))

/* During initiation, be sure to send every part to every max7219 and then
upload it.
For example, if you have five max7219's, you have to send the scanLimit 5 times
before you load it-- other wise not every max7219 will get the data. the
function maxInUse  keeps track of this, just tell it how many max7219 you are
using.
*/

int dataIn = 11;
int load = 12;
int clock = 13;

int maxInUse = 4;    //change this variable to set how many MAX7219's you'll use

int e = 0;           // just a varialble

                     // define max7219 registers
byte max7219_reg_noop        = 0x00;
byte max7219_reg_digit0      = 0x01;
byte max7219_reg_digit1      = 0x02;
byte max7219_reg_digit2      = 0x03;
byte max7219_reg_digit3      = 0x04;
byte max7219_reg_digit4      = 0x05;
byte max7219_reg_digit5      = 0x06;
byte max7219_reg_digit6      = 0x07;
byte max7219_reg_digit7      = 0x08;
byte max7219_reg_decodeMode  = 0x09;
byte max7219_reg_intensity   = 0x0a;
byte max7219_reg_scanLimit   = 0x0b;
byte max7219_reg_shutdown    = 0x0c;
byte max7219_reg_displayTest = 0x0f;

void putByte(byte data) {
  byte i = 8;
  byte mask;
  while(i > 0) {
    mask = 0x01 << (i - 1);      // get bitmask
    digitalWrite( clock, LOW);   // tick
    if (data & mask){            // choose bit
      digitalWrite(dataIn, HIGH);// send 1
    }else{
      digitalWrite(dataIn, LOW); // send 0
    }
    digitalWrite(clock, HIGH);   // tock
    --i;                         // move to lesser bit
  }
}

void maxSingle( byte reg, byte col) {    
//maxSingle is the "easy"  function to use for a     //single max7219

  digitalWrite(load, LOW);       // begin     
  putByte(reg);                  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data   
// and load da shit
  digitalWrite(load,HIGH); 
}

void maxAll (byte reg, byte col) {    // initialize  all  MAX7219's in the system
  int c = 0;
  digitalWrite(load, LOW);  // begin     
  for ( c =1; c<= maxInUse; c++) {
  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data
    }
  digitalWrite(load,HIGH);
}

void maxOne(byte maxNr, byte reg, byte col) {    
//maxOne is for adressing different MAX7219's, 
//whilele having a couple of them cascaded

  int c = 0;
  digitalWrite(load, LOW);  // begin     

  for ( c = maxInUse; c > maxNr; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }

  putByte(reg);  // specify register
  putByte(col);//((data & 0x01) * 256) + data >> 1); // put data 

  for ( c =maxNr-1; c >= 1; c--) {
    putByte(0);    // means no operation
    putByte(0);    // means no operation
  }

// and load da shit
  digitalWrite(load,HIGH); 
}


void setup () {
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  Serial.begin(9600);

  pinMode(dataIn, OUTPUT);
  pinMode(clock,  OUTPUT);
  pinMode(load,   OUTPUT);

  Serial.begin(9600);
  digitalWrite(clock, HIGH);  

//initiation of the max 7219
  maxAll(max7219_reg_scanLimit, 0x07);      
  maxAll(max7219_reg_decodeMode, 0x00);  // using an led matrix (not digits)
  maxAll(max7219_reg_shutdown, 0x01);    // not in shutdown mode
  maxAll(max7219_reg_displayTest, 0x00); // no display test
   for (e=1; e<=8; e++) {    // empty registers, turn all LEDs off 
    maxAll(e,0);
  }
  maxAll(max7219_reg_intensity, 0x0f & 0x0f);    // the first 0x0f is the value you can set
                                                  // range: 0x00 to 0x0f
}  

void loop () {


  //if you use just one MAX7219 it should look like this
  /* 
   maxSingle(1,1);                       //  + - - - - - - -
   maxSingle(2,2);                       //  - + - - - - - -
   maxSingle(3,4);                       //  - - + - - - - -
   maxSingle(4,8);                       //  - - - + - - - -
   maxSingle(5,16);                      //  - - - - + - - -
   maxSingle(6,32);                      //  - - - - - + - -
   maxSingle(7,64);                      //  - - - - - - + -
   maxSingle(8,128);                     //  - - - - - - - +

  */
  //if you use more than one MAX7219, it should look like this

  /*
  maxAll(1,1);                       //  + - - - - - - -
  maxAll(2,3);                       //  + + - - - - - -
  maxAll(3,7);                       //  + + + - - - - -
  maxAll(4,15);                      //  + + + + - - - -
  maxAll(5,31);                      //  + + + + + - - -
  maxAll(6,63);                      //  + + + + + + - -
  maxAll(7,127);                     //  + + + + + + + -
  maxAll(8,255);                     //  + + + + + + + +
  */

  //

  //if you use more then one max7219 the second one should look like this

  /*
  maxOne(2,1,1);                       //  + - - - - - - -
  maxOne(2,2,2);                       //  - + - - - - - -
  maxOne(2,3,4);                       //  - - + - - - - -
  maxOne(2,4,8);                       //  - - - + - - - -
  maxOne(2,5,16);                      //  - - - - + - - -
  maxOne(2,6,32);                      //  - - - - - + - -
  maxOne(2,7,64);                      //  - - - - - - + -
  maxOne(2,8,128);                     //  - - - - - - - +
  */

  maxOne (1,8,126);
  maxOne (1,7,126);
  maxOne (1,6,102);
  maxOne (1,5,102);
  maxOne (1,4,126);
  maxOne (1,3,126);
  maxOne (1,2,6);
  maxOne (1,1,6);
  delay(100);

  maxOne (2,8,6);
  maxOne (2,7,6);
  maxOne (2,6,6);
  maxOne (2,5,6);
  maxOne (2,4,6);
  maxOne (2,3,6);
  maxOne (2,2,126);
  maxOne (2,1,126);
  delay(100);
  
  maxOne (3,8,0);
  maxOne (3,7,24);
  maxOne (3,6,36);
  maxOne (3,5,66);
  maxOne (3,4,126);
  maxOne (3,3,66);
  maxOne (3,2,66);
  maxOne (3,1,0);
  delay(100);
  
  maxOne (4,8,102);
  maxOne (4,7,102);
  maxOne (4,6,102);
  maxOne (4,5,60);
  maxOne (4,4,24);
  maxOne (4,3,24);
  maxOne (4,2,24);
  maxOne (4,1,24);
  delay(100);
  
  maxOne (1,1,0);
  maxOne (1,2,0);
  maxOne (1,3,0);
  maxOne (1,4,0);
  maxOne (1,5,0);
  maxOne (1,6,0);
  maxOne (1,7,0);
  maxOne (1,8,0);
  delay(100);

  maxOne (2,1,0);
  maxOne (2,2,0);
  maxOne (2,3,0);
  maxOne (2,4,0);
  maxOne (2,5,0);
  maxOne (2,6,0);
  maxOne (2,7,0);
  maxOne (2,8,0);
  delay(100);
  
  maxOne (3,1,0);
  maxOne (3,2,0);
  maxOne (3,3,0);
  maxOne (3,4,0);
  maxOne (3,5,0);
  maxOne (3,6,0);
  maxOne (3,7,0);
  maxOne (3,8,0);
  delay(100);
  
  maxOne (4,1,0);
  maxOne (4,2,0);
  maxOne (4,3,0);
  maxOne (4,4,0);
  maxOne (4,5,0);
  maxOne (4,6,0);
  maxOne (4,7,0);
  maxOne (4,8,0);
  delay(100);
}
