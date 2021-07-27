using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System;

public class TalkTest : MonoBehaviour {
	SerialPort stream = new SerialPort("COM3",9600);
	public bool fiveVolt;
	public bool DrivingStance;
	private string X_Axis;
	private Rigidbody rb;
	private ArduinoComms ac;

	void Start () {
		ac = GetComponent<ArduinoComms> ();
		stream.Open ();
		stream.ReadTimeout = 20;
		rb = GetComponent<Rigidbody> ();
	}

	void Update () {
		string value = stream.ReadLine ();
		string[] splitData = value.Split('_');

		//Digital Pins 2,3,4,5,6,7 and 8 are the Respective Buttons A, B, C, D, E, F, and K (Joystick Button)
		//Digital Pins 9, 10, 11, 12, and 13 are All Spare Pins
		string digitalPin2 = splitData[0];
		string digitalPin3 = splitData[1];
		string digitalPin4 = splitData[2];
		string digitalPin5 = splitData[3];
		string digitalPin6 = splitData[4];
		string digitalPin7 = splitData[5];
		string digitalPin8 = splitData[6];
		string digitalPin9 = splitData[7];
		string digitalPin10 = splitData[8];
		string digitalPin11 = splitData[9];
		string digitalPin12 = splitData[10];
		string digitalPin13 = splitData[11];

		//Analog Pins A0 and A1 are the Joystick Position Pins X and Y Respectively
		//Analog Pins A2, A3, A4, and A5 are all spares (A2, A3, and A4 Being Used Experimentally By the Magnetometer)
		string analogPinA0 = splitData [12];
		string analogPinA1 = splitData [13];
		string analogPinA2 = splitData [14];
		string analogPinA3 = splitData [15];
		string analogPinA4 = splitData [16];
		string analogPinA5 = splitData [17];

		//This is the Experimental Magnetometer Section of the Script
		X_Axis = ((int.Parse(analogPinA2)-329)/10).ToString();

		if (digitalPin4 == "0") {
			rb.velocity = new Vector3(rb.velocity.x,5,rb.velocity.z);
			Physics.gravity = new Vector3(0,-9.81f,0);
		} else {
			Physics.gravity = new Vector3(0,-35,0);
		}

		if (!DrivingStance) {
			if (fiveVolt) {
				analogPinA0 = Mathf.RoundToInt ((int.Parse (analogPinA0) - 512) / 50).ToString ();
				analogPinA1 = Mathf.RoundToInt ((int.Parse (analogPinA1) - 512) / 50).ToString ();
			} else {
				analogPinA0 = Mathf.RoundToInt ((int.Parse (analogPinA0) - 326) / 50).ToString ();
				analogPinA1 = Mathf.RoundToInt ((int.Parse (analogPinA1) - 326) / 50).ToString ();
			}

			rb.AddForce(new Vector3(float.Parse(analogPinA0),rb.velocity.y,float.Parse(analogPinA1)));
		} else {
			float pos = 0.00f;
			pos = -(int.Parse (analogPinA2) - 329);
			pos = pos / 10;
			print (pos);

			transform.position = new Vector3 (pos,0.5f,0);
		}
	}
}
