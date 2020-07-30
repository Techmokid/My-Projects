//This should handle all the file/folder demands of this project

bool createDir(String directory) { if (SD.exists(directory)) { return false; } SD.mkdir(directory); return true; }

String readall(String file) {
  File f = SD.open(file,FILE_READ);
  
  String result = "";
  while (f.available()) { result += char(f.read()); }
  f.close();
  return result;
}

void writeall(String file) { writeall(file,""); }
void writeall(String file, String data) {
  if (SD.exists(file)) { SD.remove(file); }
  
  File f = SD.open(file,FILE_WRITE);
  if (f == false) { serPrintln(F("Error Opening File!")); SYSTEM_errorBlink(5,F("SLOW")); }
  if (data != "") { f.print(data); }
  f.close();
}

void deldir(String dir) { deldir(SD.open(dir),""); }
void deldir(File dir) { deldir(dir,""); }
void deldir(File dir,String pointer) {
  while (true) {
    //Loop until nothing left
    File entry = dir.openNextFile();
    if (! entry) { break; }
    
    //If it is a directory, then print it out and loop again
    if (entry.isDirectory()) {
      deldir(entry,pointer + "/" + entry.name());
      SD.rmdir(pointer + "/" + entry.name());
    } else {
      SD.remove(pointer + "/" + entry.name());
    }
    entry.close();
  }
}
