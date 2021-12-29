#include "Arduino.h"
#include <File_Manager.h>

//void loop() {}
//void setup() {
//	bufferFile.filepath = "SYSBUFF.txt";
//	bufferFile.softFileCreate();
//}

fs::File File_Manager::toFile(file_struct temp) { return SD.open(temp.filepath); }

void File_Manager::addLine(file_struct fileToEdit, String dataToAdd) { addLine(fileToEdit, fileToEdit.lineCount - 1, dataToAdd); }
void File_Manager::addLine(file_struct fileToEdit, int index, String dataToAdd) {
	//First copy all data from the file to the buffer
	fileToEdit.updateLineCount();
	for (int i = 0; i < fileToEdit.lineCount; i++) { bufferFile.writeline(fileToEdit.readline()); }

	//Now go ahead and make the edit while copying it back
	for (int i = 0; i < bufferFile.lineCount; i++) {
		if (i == index) { fileToEdit.writeline(dataToAdd); }
		fileToEdit.writeline(bufferFile.readline());
	}
}

void File_Manager::editLine(file_struct fileToEdit, int index, String dataToEdit) {
	//First copy all data from the file to the buffer
	fileToEdit.updateLineCount();
	for (int i = 0; i < fileToEdit.lineCount; i++) { bufferFile.writeline(fileToEdit.readline()); }

	//Now go ahead and make the edit while copying it back
	for (int i = 0; i < bufferFile.lineCount; i++) {
		if (i == index) {
			fileToEdit.writeline(dataToEdit); bufferFile.skipline();
		}
		else { fileToEdit.writeline(bufferFile.readline()); }
	}
}

void File_Manager::clearLine(file_struct fileToEdit, int index) {
	//First copy all data from the file to the buffer
	fileToEdit.updateLineCount();
	for (int i = 0; i < fileToEdit.lineCount; i++) { bufferFile.writeline(fileToEdit.readline()); }

	//Now go ahead and make the edit while copying it back
	for (int i = 0; i < bufferFile.lineCount; i++) {
		if (i == index) {
			fileToEdit.writeline(); bufferFile.skipline();
		}
		else { fileToEdit.writeline(bufferFile.readline()); }
	}
}

void File_Manager::removeLine(file_struct fileToEdit, int index) {
	//First copy all data from the file to the buffer
	fileToEdit.updateLineCount();
	for (int i = 0; i < fileToEdit.lineCount; i++) { bufferFile.writeline(fileToEdit.readline()); }

	//Now go ahead and make the edit while copying it back
	for (int i = 0; i < bufferFile.lineCount; i++) {
		if (i == index) { bufferFile.skipline(); }
		else { fileToEdit.writeline(bufferFile.readline()); }
	}
}
