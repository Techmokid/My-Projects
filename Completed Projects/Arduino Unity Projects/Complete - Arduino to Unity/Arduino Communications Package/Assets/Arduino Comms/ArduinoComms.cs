using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class ArduinoComms : MonoBehaviour {
	//Digital Pins 2,3,4,5,6,7 and 8 are the Respective Buttons A, B, C, D, E, F, and K (Joystick Button)
	//Digital Pins 9, 10, 11, 12, and 13 are All Spare Pins
	//D2 = splitData[0];
	//D3 = splitData[1];
	//D4 = splitData[2];
	//D5 = splitData[3];
	//D6 = splitData[4];
	//D7 = splitData[5];
	//D8 = splitData[6];
	//D9 = splitData[7];
	//D10 = splitData[8];
	//D11 = splitData[9];
	//D12 = splitData[10];
	//D13 = splitData[11];

	//Analog Pins A0 and A1 are the Joystick Position Pins X and Y Respectively
	//Analog Pins A2, A3, A4, and A5 are all spares (A2, A3, and A4 Being Used Experimentally By the Magnetometer)
	//A0 = splitData [12];
	//A1 = splitData [13];
	//A2 = splitData [14];
	//A3 = splitData [15];
	//A4 = splitData [16];
	//A5 = splitData [17];

	private string comAddress;
	private bool isSupposedToBeOpen = false;

	SerialPort sp;

	public void OpenArduinoComms(string CommPort, int BaudRate) {
		sp = new SerialPort(CommPort,BaudRate);
		sp.Open ();
		sp.ReadTimeout = 20;
		sp.WriteTimeout = 20;
		isSupposedToBeOpen = true;
	}

	public void CloseArduinoComms () {
		sp.Close ();
		isSupposedToBeOpen = false;
	}

	public void WriteToArduino (string sentence) {
		sp.Write(sentence);
	}

	public string[] ReadFromArduino () {
		string value = sp.ReadLine ();
		string[] splitData = value.Split('_');

		return splitData;
	}

	public string RawReadFromArduino () {
		string data = sp.ReadLine ();
		return data;
	}

	public void ChangeArduinoTimeout (int Timeout) {
		sp.ReadTimeout = Timeout;
		sp.WriteTimeout = Timeout;
	}

	void Update () {
		if (isSupposedToBeOpen) {
			if (!sp.IsOpen) {
				sp.Open ();
			}
		}
	}
}
