#include <File_Manager.h>

File_Manager::file_struct myFileStruct;

bool validPartCode(String code) {
  if (code.length() != 6) { return false; }
  if (isAlpha(code[0]) && isAlpha(code[1]) && isDigit(code[2]) && isDigit(code[3]) && isDigit(code[4]) && isDigit(code[5])) { return true; }
  return false;
}

void sdInit() {
  myFileStruct.filepath = "TEMP.TXT";
  myFileStruct.softFileCreate();
  
  Serial.begin(74880);
  while (!Serial) { SysCall::yield(); } delay(100);
  
  Serial.print("\n\nInitialising SD...");
  //if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) { sd.initErrorHalt(); }
  if (!sd.begin(chipSelect, SD_SCK_MHZ(50))) {
    Serial.println("ERROR: Could not initialise SD!");
    while(true) {
      digitalWrite(LED_BUILTIN,HIGH); SysCall::yield(); delay(500);
      digitalWrite(LED_BUILTIN,LOW);  SysCall::yield(); delay(500);
    };
  }
  
  Serial.println("Initialised SD!");
}

void getItem(String itemID) {
  Item_Position_X = -1;
  Item_Position_Y = -1;
  
  itemID.toUpperCase();
  
  sdfat::File f = sd.open("ITEMID~1.TXT",FILE_READ);
  if (!f) { Serial.println(F("Could not read file!")); while(true) {} }
  
  //The file exists. Now read from it
  String result = "";
  while (f.available()) {
    SysCall::yield();
    
    //Read from it and iterate over every line
    char nextVal = f.read();
    if (nextVal == '\n') {
      result.toUpperCase();
      
      //Here we have a complete sentence to work with without a newline at the end. We can decode it now
      String positionData = result.substring(0,result.indexOf(':'));
      String item = result.substring(result.indexOf(':') + 1,result.length() - 1);
      
      if (item == itemID) {
        Item_Position_X = positionData.substring(0,result.indexOf(',')).toInt();
        Item_Position_Y = positionData.substring(result.indexOf(',')+1,result.indexOf(':')).toInt();
        return;
      }
      
      result = "";
    } else { result += nextVal; }
  }
  
  //Here we have a complete sentence to work with without a newline at the end. We can decode it now
  String positionData = result.substring(0,result.indexOf(':'));
  String item = result.substring(result.indexOf(':') + 1,result.length());
  item.toUpperCase();
  
  if (item == itemID) {
    Item_Position_X = positionData.substring(0,result.indexOf(',')).toInt();
    Item_Position_Y = positionData.substring(result.indexOf(',')+1,result.indexOf(':')).toInt();
    return;
  }
  
  f.close();
}

void AddPartCode(String in) {
  String partCode = getValue(in,':',1);
  String x = getValue(in,':',2);
  String y = getValue(in,':',3);
  
  getItem(partCode); if (Item_Position_X != -1) { RemovePartCode(in); }
  
  sdfat::File f = sd.open("ITEMID~1.TXT",FILE_WRITE);
  f.println(x + "," + y + ":" + partCode);
  f.close();
  
  Serial.println("Part code " + partCode + " at position (" + x + "," + y + ") added to SD");
  client.println("Part code " + partCode + " at position (" + x + "," + y + ") added to SD");
}

void EditPartCode(String in) {
  RemovePartCode(in,false);
  AddPartCode(in);
}

void RemovePartCode(String in) { RemovePartCode(in,true); }
void RemovePartCode(String in,bool printData) {
  String partCode = getValue(in,':',1);
  getItem(partCode);
  if (Item_Position_X == -1) {
    if (printData) {
      Serial.println("Part code not found");
      client.println("Part code not found");
    }
    return;
  }
  
  client.println("ERROR: THIS PROCESS IT INCOMPLETE AND NONFUNCTIONAL");
  
  //Here we wanna copy across everything to a temporary file
  
  //myFileStruct.updateLineCount();
  //myFileStruct.readline();
  //myFileStruct.writeline();
  //myFileStruct.writeline(String data);
  //myFileStruct.skipline();
  //myFileStruct.skipline(int numberOfLines);
  //myFileStruct.softFileCreate();
  //
  
  if (printData) {
    Serial.println("Part code " + partCode + " at position (" + Item_Position_X + "," + Item_Position_Y + ") removed from SD");
    client.println("Part code " + partCode + " at position (" + Item_Position_X + "," + Item_Position_Y + ") removed from SD");
  }
}
