#ifndef File_Manager_h
#define File_Manager_h

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

class File_Manager {
public:
	struct file_struct {
		int currentLine = 0;
		int lineCount = 0;
		String filepath = "";

		void updateLineCount() {
			lineCount = 0;
			fs::File temp = SD.open(filepath);
			while (temp.available()) { char i = temp.read(); if (i == '\n') { lineCount++; } }
			temp.close();
		}

		String readline() {
			currentLine++;
			int x = 0;
			fs::File temp = SD.open(filepath);
			while (x < currentLine) { char i = temp.read(); if (i == '\n') { x++; } }

			char i = temp.read();
			String result = "";
			while (i != '\n') { result += i; i = temp.read(); }
			temp.close();
			return result;
		};

		void writeline() { writeline(""); }
		void writeline(String data) {
			fs::File temp = SD.open(filepath);
			for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) { temp.write(data[i]); }
			temp.write('\n');
			temp.close();

			updateLineCount();
		}

		void skipline() { currentLine++; }
		void skiplines(int numberOfLinesToSkip) { currentLine += numberOfLinesToSkip; }

		void softFileCreate() { fs::File temp = SD.open(filepath, FILE_WRITE); temp.close(); }
	};
	
	file_struct bufferFile;

	File_Manager();

	fs::File toFile(file_struct temp);
	
	void addLine(file_struct fileToEdit, String dataToAdd);
	void addLine(file_struct fileToEdit, int index, String dataToAdd);
	void editLine(file_struct fileToEdit, int index, String dataToEdit);
	void clearLine(file_struct fileToEdit, int index);
	void removeLine(file_struct fileToEdit, int index);
};

#endif
