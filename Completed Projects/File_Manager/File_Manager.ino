#include <SPI.h>
#include <SD.h>

struct file {
  int currentLine = 0;
  int lineCount = 0;
  String filepath = "";
  
  void updateLineCount() {
    lineCount = 0;
    File temp = SD.open(filepath);
    while (temp.available()) { char i = temp.read(); if (i == '\n') { lineCount++; } }
    temp.close();
  }
  
  String readline() {
    currentLine++;
    int x = 0;
    File temp = SD.open(filepath);
    while (x < currentLine) { char i = temp.read(); if (i == '\n') { x++; } }
    
    char i = temp.read();
    String result = "";
    while (i != '\n') { result += i; i = temp.read(); }
    temp.close();
    return result;
  };
  
  void writeline() { writeline(""); }
  void writeline(String data) {
    File temp = SD.open(filepath);
    for (int i = 0; i < sizeof(data)/sizeof(data[0]); i++) { temp.write(data[i]); }
    temp.write('\n');
    temp.close();
    
    updateLineCount();
  }
  
  void skipline() { currentLine++; }
  void skiplines(int temp) { currentLine += temp; }
  
  void softFileCreate() { File temp = SD.open(filepath, FILE_WRITE); temp.close(); }
};

file bufferFile;

void loop() {}
void setup() {
  bufferFile.filepath = "SYSBUFF.txt";
  bufferFile.softFileCreate();
}

File toFile(file temp) { return SD.open(temp.filepath); }

void addLine(file fileToEdit, String dataToAdd) { addLine(fileToEdit, fileToEdit.lineCount - 1, dataToAdd); }
void addLine(file fileToEdit, int index, String dataToAdd) {
  //First copy all data from the file to the buffer
  fileToEdit.updateLineCount();
  for (int i = 0; i < fileToEdit.lineCount; i++) { bufferFile.writeline(fileToEdit.readline()); }
  
  //Now go ahead and make the edit while copying it back
  for (int i = 0; i < bufferFile.lineCount; i++) {
    if (i == index) { fileToEdit.writeline(dataToAdd); }
    fileToEdit.writeline(bufferFile.readline());
  }
}

void editLine(file fileToEdit, int index, String dataToEdit) {
  //First copy all data from the file to the buffer
  fileToEdit.updateLineCount();
  for (int i = 0; i < fileToEdit.lineCount; i++) { bufferFile.writeline(fileToEdit.readline()); }
  
  //Now go ahead and make the edit while copying it back
  for (int i = 0; i < bufferFile.lineCount; i++) {
    if (i == index) { fileToEdit.writeline(dataToEdit); bufferFile.skipline();
    } else { fileToEdit.writeline(bufferFile.readline()); }
  }
}

void clearLine(file fileToEdit, int index) {
  //First copy all data from the file to the buffer
  fileToEdit.updateLineCount();
  for (int i = 0; i < fileToEdit.lineCount; i++) { bufferFile.writeline(fileToEdit.readline()); }
  
  //Now go ahead and make the edit while copying it back
  for (int i = 0; i < bufferFile.lineCount; i++) {
    if (i == index) { fileToEdit.writeline(); bufferFile.skipline();
    } else { fileToEdit.writeline(bufferFile.readline()); }
  }
}

void removeLine(file fileToEdit, int index) {
  //First copy all data from the file to the buffer
  fileToEdit.updateLineCount();
  for (int i = 0; i < fileToEdit.lineCount; i++) { bufferFile.writeline(fileToEdit.readline()); }
  
  //Now go ahead and make the edit while copying it back
  for (int i = 0; i < bufferFile.lineCount; i++) {
    if (i == index) { bufferFile.skipline(); } else { fileToEdit.writeline(bufferFile.readline()); }
  }
}
