float x = 0;
float y = 0;
float z = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("");
  x = analogRead(A0);
  y = analogRead(A1);
  z = analogRead(A2);
  x = ((x/(394)*1023-843)/2)-1;
  y = ((y/(390)*1023-843)/2);
  z = (z/(401)*1023-843)/2;
  x = x * 1.15;
  y = y * 1.15;
  x = x * 0.9;
  y = y * 0.9;
  Serial.print("x = ");
  if (x < 100) {
    if (x > 0) {
    Serial.print("0");
    }
  }
  if (x < 10) {
    if (x > -10) {
    Serial.print("0");
    }
  }
  Serial.print(x);
  Serial.print(" Degrees ");
  Serial.print("  Y = ");
  if (y < 100) {
    if (y > 0) {
    Serial.print("0");
  }
  }
  if (y < 10) {
    if (y > -10) {
    Serial.print("0");
    }
  }
  Serial.print(y);
  Serial.print(" Degrees ");
  Serial.print("  Z = ");
  if (z < 100) {
    if (z > 0) {
    Serial.print("0");
    }
  }
  if (z < 10) {
    if (z > -10) {
    Serial.print("0");
    }
  }
  Serial.print(z);
  Serial.print(" Degrees ");
  delay(10);
  ledInterfacerProgram();
}

void ledInterfacerProgram() {
    Serial.print("   Degrees (");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.print(")");
    x = x/(225-75)*75+125;
    Serial.print("   Servo x = ");
    Serial.print(x);
    y = y/(225-75)*75+125;
    Serial.print("   Servo Y = ");
    Serial.print(y);
    z = z/(225-75)*75+125;
    Serial.print("  Servo z = ");
    Serial.print(z);
    Serial.print("   Servo (");
    Serial.print(x);
    Serial.print(",");
    Serial.print(y);
    Serial.print(",");
    Serial.print(z);
    Serial.print(")");
}
