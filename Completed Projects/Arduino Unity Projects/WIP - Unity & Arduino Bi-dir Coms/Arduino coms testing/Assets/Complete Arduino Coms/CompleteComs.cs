using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class CompleteComs : MonoBehaviour {
	//NOTE: If using this script, please do not spam the keys. It will still work, but it will also start to lag due to Serial Reading capabilities.
	//Start Communications Port
	SerialPort sp = new SerialPort ("COM3",9600);

	//Setup the variables so that we can change the color of the boxes so the user can see what is happening. Not needed, but I think it looks nice!
	public Renderer D2_UnityRead;
	public Renderer D2_UnityWrite;
	public Renderer D3_UnityRead;
	public Renderer D3_UnityWrite;
	public Renderer D4_UnityRead;
	public Renderer D4_UnityWrite;
	public Renderer D5_UnityRead;
	public Renderer D5_UnityWrite;
	public Renderer D6_UnityRead;
	public Renderer D6_UnityWrite;
	public Renderer D7_UnityRead;
	public Renderer D7_UnityWrite;
	public Renderer D8_UnityRead;
	public Renderer D8_UnityWrite;
	public Renderer D9_UnityRead;
	public Renderer D9_UnityWrite;
	public Renderer D10_UnityRead;
	public Renderer D10_UnityWrite;
	public Renderer D11_UnityRead;
	public Renderer D11_UnityWrite;
	public Renderer D12_UnityRead;
	public Renderer D12_UnityWrite;
	public Renderer D13_UnityRead;
	public Renderer D13_UnityWrite;

	public GameObject AnalogPin0;
	public GameObject AnalogPin1;
	public GameObject AnalogPin2;
	public GameObject AnalogPin3;
	public GameObject AnalogPin4;
	public GameObject AnalogPin5;

	void Start () {
		//Open and Initialise the Serialport. This is the only part other than starting the serial port (above)that REALLY matters when talking to the arduino
		sp.Open ();
		sp.WriteTimeout = 20;
		sp.ReadTimeout = 20;

		//Set all boxes to red on startup
		D2_UnityWrite.material.color = Color.red;
		D3_UnityWrite.material.color = Color.red;
		D4_UnityWrite.material.color = Color.red;
		D5_UnityWrite.material.color = Color.red;
		D6_UnityWrite.material.color = Color.red;
		D7_UnityWrite.material.color = Color.red;
		D8_UnityWrite.material.color = Color.red;
		D9_UnityWrite.material.color = Color.red;
		D10_UnityWrite.material.color = Color.red;
		D11_UnityWrite.material.color = Color.red;
		D12_UnityWrite.material.color = Color.red;
		D13_UnityWrite.material.color = Color.red;
	}

	void Update () {
		//Read From Arduino and Split the Data Into Easy-to-Remember Variables
		string UnSplitData = sp.ReadLine ();
		string[] SplitData = UnSplitData.Split ('_');

		//Analyze Data From Arduino
		if (SplitData [0] == "1") {
			D2_UnityRead.material.color = Color.green;
		} else {
			D2_UnityRead.material.color = Color.red;
		}
		if (SplitData [1] == "1") {
			D3_UnityRead.material.color = Color.green;
		} else {
			D3_UnityRead.material.color = Color.red;
		}
		if (SplitData [2] == "1") {
			D4_UnityRead.material.color = Color.green;
		} else {
			D4_UnityRead.material.color = Color.red;
		}
		if (SplitData [3] == "1") {
			D5_UnityRead.material.color = Color.green;
		} else {
			D5_UnityRead.material.color = Color.red;
		}
		if (SplitData [4] == "1") {
			D6_UnityRead.material.color = Color.green;
		} else {
			D6_UnityRead.material.color = Color.red;
		}
		if (SplitData [5] == "1") {
			D7_UnityRead.material.color = Color.green;
		} else {
			D7_UnityRead.material.color = Color.red;
		}
		if (SplitData [6] == "1") {
			D8_UnityRead.material.color = Color.green;
		} else {
			D8_UnityRead.material.color = Color.red;
		}
		if (SplitData [7] == "1") {
			D9_UnityRead.material.color = Color.green;
		} else {
			D9_UnityRead.material.color = Color.red;
		}
		if (SplitData [8] == "1") {
			D10_UnityRead.material.color = Color.green;
		} else {
			D10_UnityRead.material.color = Color.red;
		}
		if (SplitData [9] == "1") {
			D11_UnityRead.material.color = Color.green;
		} else {
			D11_UnityRead.material.color = Color.red;
		}
		if (SplitData [10] == "1") {
			D12_UnityRead.material.color = Color.green;
		} else {
			D12_UnityRead.material.color = Color.red;
		}
		if (SplitData [11] == "1") {
			D13_UnityRead.material.color = Color.green;
		} else {
			D13_UnityRead.material.color = Color.red;
		}

		//Analog Pins
		//If working with 3v3 power input, leave these values.
		//If working with 5v power input, change all of the 682's to 1023.
		float Value0 = int.Parse(SplitData[12]);
		Value0 = (Value0 / 682) - 0.5f;
		AnalogPin0.transform.localPosition = new Vector3(Value0,0,0);

		float Value1 = int.Parse(SplitData[13]);
		Value1 = (Value1 / 682) - 0.5f;
		AnalogPin1.transform.localPosition = new Vector3(Value1,0,0);

		float Value2 = int.Parse(SplitData[14]);
		Value2 = (Value2 / 682) - 0.5f;
		AnalogPin2.transform.localPosition = new Vector3(Value2,0,0);

		float Value3 = int.Parse(SplitData[15]);
		Value3 = (Value3 / 682) - 0.5f;
		AnalogPin3.transform.localPosition = new Vector3(Value3,0,0);

		float Value4 = int.Parse(SplitData[16]);
		Value4 = (Value4 / 682) - 0.5f;
		AnalogPin4.transform.localPosition = new Vector3(Value4,0,0);

		float Value5 = int.Parse(SplitData[17]);
		Value5 = (Value5 / 682) - 0.5f;
		AnalogPin5.transform.localPosition = new Vector3(Value5,0,0);

		//Writing To The Arduino
		//Write data relative to whether or not the user is pressing the button;
		if (Input.GetKeyDown (KeyCode.Q)) {				//Write To D2
			D2_UnityWrite.material.color = Color.green;
			sp.Write ("A");
		}
		if (Input.GetKeyUp (KeyCode.Q)) {
			D2_UnityWrite.material.color = Color.red;
			sp.Write ("a");
		}
		if (Input.GetKeyDown (KeyCode.W)) {				//Write To D3
			D3_UnityWrite.material.color = Color.green;
			sp.Write ("B");
		}
		if (Input.GetKeyUp (KeyCode.W)) {
			D3_UnityWrite.material.color = Color.red;
			sp.Write ("b");
		}
		if (Input.GetKeyDown (KeyCode.E)) {				//Write To D4
			D4_UnityWrite.material.color = Color.green;
			sp.Write ("C");
		}
		if (Input.GetKeyUp (KeyCode.E)) {
			D4_UnityWrite.material.color = Color.red;
			sp.Write ("c");
		}
		if (Input.GetKeyDown (KeyCode.R)) {				//Write To D5
			D5_UnityWrite.material.color = Color.green;
			sp.Write ("D");
		}
		if (Input.GetKeyUp (KeyCode.R)) {
			D5_UnityWrite.material.color = Color.red;
			sp.Write ("d");
		}
		if (Input.GetKeyDown (KeyCode.T)) {				//Write To D6
			D6_UnityWrite.material.color = Color.green;
			sp.Write ("E");
		}
		if (Input.GetKeyUp (KeyCode.T)) {
			D6_UnityWrite.material.color = Color.red;
			sp.Write ("e");
		}
		if (Input.GetKeyDown (KeyCode.Y)) {				//Write To D7
			D7_UnityWrite.material.color = Color.green;
			sp.Write ("F");
		}
		if (Input.GetKeyUp (KeyCode.Y)) {
			D7_UnityWrite.material.color = Color.red;
			sp.Write ("f");
		}
		if (Input.GetKeyDown (KeyCode.U)) {				//Write To D8
			D8_UnityWrite.material.color = Color.green;
			sp.Write ("G");
		}
		if (Input.GetKeyUp (KeyCode.U)) {
			D8_UnityWrite.material.color = Color.red;
			sp.Write ("g");
		}
		if (Input.GetKeyDown (KeyCode.I)) {				//Write To D9
			D9_UnityWrite.material.color = Color.green;
			sp.Write ("H");
		}
		if (Input.GetKeyUp (KeyCode.I)) {
			D9_UnityWrite.material.color = Color.red;
			sp.Write ("h");
		}
		if (Input.GetKeyDown (KeyCode.O)) {				//Write To D10
			D10_UnityWrite.material.color = Color.green;
			sp.Write ("I");
		}
		if (Input.GetKeyUp (KeyCode.O)) {
			D10_UnityWrite.material.color = Color.red;
			sp.Write ("i");
		}
		if (Input.GetKeyDown (KeyCode.P)) {				//Write To D11
			D11_UnityWrite.material.color = Color.green;
			sp.Write ("J");
		}
		if (Input.GetKeyUp (KeyCode.P)) {
			D11_UnityWrite.material.color = Color.red;
			sp.Write ("j");
		}
		if (Input.GetKeyDown ("[")) {				//Write To D12
			D12_UnityWrite.material.color = Color.green;
			sp.Write ("K");
		}
		if (Input.GetKeyUp ("[")) {
			D12_UnityWrite.material.color = Color.red;
			sp.Write ("k");
		}
		if (Input.GetKeyDown ("]")) {				//Write To D13
			D13_UnityWrite.material.color = Color.green;
			sp.Write ("L");
		}
		if (Input.GetKeyUp ("]")) {
			D13_UnityWrite.material.color = Color.red;
			sp.Write ("l");
		}

	}
}
