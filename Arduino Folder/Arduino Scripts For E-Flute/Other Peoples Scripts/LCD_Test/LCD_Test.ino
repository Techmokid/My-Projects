

//***************************************************
//***************************************************
//Property of: www.microcontroller-project.com     **
//Date       : 10-September-2015                   **
//By         : Usman Ali Butt                      **
//***************************************************
//***************************************************

void ReadDriver();//Reading Lcd Driver
void Command(char Com);//Writing Commands to Lcd

int Lcd_RD=A0;
int Lcd_WR=A1;
int Lcd_RS=A2;    //TFT Controlling Pins
int Lcd_CS=A3;
int Lcd_RST=A4;
int Lcd_D0=8;
int Lcd_D1=9;

void setup(){
  pinMode(Lcd_RD,OUTPUT);
  pinMode(Lcd_WR,OUTPUT);
  pinMode(Lcd_RS,OUTPUT);
  pinMode(Lcd_CS,OUTPUT);
  pinMode(Lcd_RST,OUTPUT);

  Serial.begin(9600);
  digitalWrite(Lcd_CS,LOW);//Select Lcd
  digitalWrite(Lcd_RST,HIGH);//No Reset For reset Lcd make LOW
  digitalWrite(Lcd_CS,LOW);//Select Lcd
}

void Command(char Com){
  DDRD=B11111111;//Port-D as Output
  DDRB=B11111111;//Port-B as Output
  PORTD=Com;
  PORTB=Com;
  delay(5);
  digitalWrite(Lcd_RD,HIGH);//In Write Mode
  digitalWrite(Lcd_RS,LOW);//Data on Bus is Command
  digitalWrite(Lcd_WR,HIGH);
  delay(10);
  digitalWrite(Lcd_WR,LOW);//Enable High for some time
  delay(10);
  digitalWrite(Lcd_WR,HIGH);
}

void ReadDriver() {
  int H=0,HH=0,i=0;
  Command(0x00);//Specifing Register Index
  DDRD=B00000000;//Port-D as Input
  DDRB=B00000000;//Port-B as Input
  Serial.print("LCD Driver Found = ");
  pinMode(Lcd_D0,INPUT);
  pinMode(Lcd_D1,INPUT);
  delay(5);

  for(i=0;i<2;i++){
    digitalWrite(Lcd_RD,HIGH);//In Read Mode
    digitalWrite(Lcd_RS,HIGH);//Data on Bus is Data
    digitalWrite(Lcd_WR,HIGH);//Enable High for some time
    delay(10);
    digitalWrite(Lcd_RD,LOW);
    delay(10);
    H=PIND>>2;
    H=H<<1;
    HH=H|digitalRead(Lcd_D1);
    HH=HH<<1;
    HH=HH|digitalRead(Lcd_D0);
    digitalWrite(Lcd_RD,HIGH);
    Serial.print(HH,HEX);
  }
  Serial.println();
}


void loop(){
  int value=0;  
  int i=0;
  digitalWrite(Lcd_CS,LOW);//Select TFT Lcd
  ReadDriver();
  while(1); 
}
