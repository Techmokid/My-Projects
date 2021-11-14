using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class CompleteArduinoCommsDebug : MonoBehaviour {
	//Digital Pins 0 and 1 Are Both Used For Serial Communications With Unity3D, and Hence Cannot Be Used
	public Renderer DigitalButton2;
	public Renderer DigitalButton3;
	public Renderer DigitalButton4;
	public Renderer DigitalButton5;
	public Renderer DigitalButton6;
	public Renderer DigitalButton7;
	public Renderer DigitalButton8;
	public Renderer DigitalButton9;
	public Renderer DigitalButton10;
	public Renderer DigitalButton11;
	public Renderer DigitalButton12;
	public Renderer DigitalButton13;

	public GameObject AnalogPin0;
	public GameObject AnalogPin1;
	public GameObject AnalogPin2;
	public GameObject AnalogPin3;
	public GameObject AnalogPin4;
	public GameObject AnalogPin5;

	private Color active = Color.green;
	private Color notActive = Color.red;
	SerialPort sp = new SerialPort("COM3",9600);

	void Start () {
		sp.Open ();
		sp.ReadTimeout = 20;
	}

	void Update () {
		string UnSplitData = sp.ReadLine ();
		string[] SplitData = UnSplitData.Split('_');

		//Digital Pins
		if (SplitData [0] == "1") {
			DigitalButton2.material.color = active;
		} else {
			DigitalButton2.material.color = notActive;
		}
		if (SplitData [1] == "1") {
			DigitalButton3.material.color = active;
		} else {
			DigitalButton3.material.color = notActive;
		}
		if (SplitData [2] == "1") {
			DigitalButton4.material.color = active;
		} else {
			DigitalButton4.material.color = notActive;
		}
		if (SplitData [3] == "1") {
			DigitalButton5.material.color = active;
		} else {
			DigitalButton5.material.color = notActive;
		}
		if (SplitData [4] == "1") {
			DigitalButton6.material.color = active;
		} else {
			DigitalButton6.material.color = notActive;
		}
		if (SplitData [5] == "1") {
			DigitalButton7.material.color = active;
		} else {
			DigitalButton7.material.color = notActive;
		}
		if (SplitData [6] == "1") {
			DigitalButton8.material.color = active;
		} else {
			DigitalButton8.material.color = notActive;
		}
		if (SplitData [7] == "1") {
			DigitalButton9.material.color = active;
		} else {
			DigitalButton9.material.color = notActive;
		}
		if (SplitData [8] == "1") {
			DigitalButton10.material.color = active;
		} else {
			DigitalButton10.material.color = notActive;
		}
		if (SplitData [9] == "1") {
			DigitalButton11.material.color = active;
		} else {
			DigitalButton11.material.color = notActive;
		}
		if (SplitData [10] == "1") {
			DigitalButton12.material.color = active;
		} else {
			DigitalButton12.material.color = notActive;
		}
		if (SplitData [11] == "1") {
			DigitalButton13.material.color = active;
		} else {
			DigitalButton13.material.color = notActive;
		}

		//Analog Pins
		//Complete Range of Joystick In 3v3 Mode Is Between 0 And 682
		//Slider Goes Between -0.5 and 0.5
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
	}
}
