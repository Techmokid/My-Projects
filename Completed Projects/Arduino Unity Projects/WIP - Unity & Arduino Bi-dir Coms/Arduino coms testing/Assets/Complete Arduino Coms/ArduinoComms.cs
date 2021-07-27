using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class ArduinoComms : MonoBehaviour {
	/*	
	 * This script is designed to be used easily for Arduino communications
	 * To use the script, type: "private ArduinoComms ac;" at the start
	 * Then, in your start method, type "ac = GetComponent<ArduinoComms> ();"
	 * To use a function, type something like, "ac.OpenArduinoComms ("COM3", 9600);"
	 */

	SerialPort sp;

	public void OpenArduinoComms(string CommPort, int BaudRate) {
		if (!sp.IsOpen) {
			sp = new SerialPort (CommPort, BaudRate);
			sp.Open ();
			sp.ReadTimeout = 20;
			sp.WriteTimeout = 20;
		} else {
			Debug.LogError ("Could Not Open COM Port - Arduino Link Is Already Open!");
		}
	}

	public void CloseArduinoComms () {
		if (!sp.IsOpen) {
			Debug.LogError ("Could Not Close COM Port - Arduino Link Is Already Closed!");
		} else {
			sp.Close ();
		}
	}

	public void WriteToArduino (string sentence) {
		if (!sp.IsOpen) {
			Debug.LogError ("Could Not Find Arduino - Arduino Link Is Not Open! Did Not Write To Arduino");
		} else {
			sp.Write (sentence);
		}
	}

	public string[] ReadFromArduino () {
		//D0 is not defined as it is needed for Serial Communications
		//D1 is not defined as it is needed for Serial Communications
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

		//A0 = splitData [12];
		//A1 = splitData [13];
		//A2 = splitData [14];
		//A3 = splitData [15];
		//A4 = splitData [16];
		//A5 = splitData [17];

		if (!sp.IsOpen) {
			Debug.LogError ("Could Not Read From Arduino - Arduino Link Is Not Open! Did Not Attempt To Read From Arduino");
			return null;
		} else {
			string value = sp.ReadLine ();
			string[] splitData = value.Split ('_');

			return splitData;
		}
	}

	public string RawReadFromArduino () {
		if (!sp.IsOpen) {
			Debug.LogError ("Could Not Read From Arduino - Arduino Link Is Not Open! Did Not Attempt To Read From Arduino");
			return null;
		} else {
			string data = sp.ReadLine ();
			return data;
		}
	}

	public void ChangeArduinoTimeout (int Timeout) {
		sp.ReadTimeout = Timeout;
		sp.WriteTimeout = Timeout;
	}
}
