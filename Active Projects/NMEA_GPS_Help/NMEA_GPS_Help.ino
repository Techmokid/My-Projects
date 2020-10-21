//At the moment, this particular script just relays the message
//If this functions as a straight bypass, then the hard part is complete
//To test this, put an arduino mega with this code on it in the way of the signal.
//The signal comes in from "Serial3", and gets pinged over to "Serial2"

//If you are only using an arduino uno, there is a way to use that, although it is alot messier to handle
//We can use 2 digital pins as serial communication pins, but I hope not to resort to that if possible

void setup() {
  Serial3.begin(4800);    //Start the channel in from the GPS receiver
  Serial.begin(4800);     //Send all received NMEA data to the terminal

  //Serial2.begin(4800);  //Start the channel out to the receiving device
}

void loop() {
  String currentSentence = getNMEASentence();
  if (currentSentence != "") {
    Serial.println(currentSentence);
    
    //Serial2.print(currentSentence);
  }
}

String getNMEASentence() {
  //If we have anything recieved on the serial buffer, read it until the next command is received
  String sentence = "";
  bool sentenceComplete = (Serial3.available() > 0);
  while (sentenceComplete) {
    if (Serial3.available() > 0) {
      if (Serial3.peek() == '$') {
        sentenceComplete = false;
      } else { sentence += Serial3.read(); }
    }
  }
  
  return sentence;
}
