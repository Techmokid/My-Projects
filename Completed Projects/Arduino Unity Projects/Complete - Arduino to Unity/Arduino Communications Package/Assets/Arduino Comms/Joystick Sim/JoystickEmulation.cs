using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class JoystickEmulation : MonoBehaviour {
	public GameObject JoystickPosition;
	public Renderer LeftButton;
	public Renderer RightButton;
	public Renderer UpButton;
	public Renderer DownButton;
	public Renderer E;
	public Renderer F;
	public Renderer K;

	private Color Pressed = Color.green;
	private Color NotPressed = Color.red;
	private ArduinoComms ac;

	void Start () {
		ac = GetComponent<ArduinoComms> ();
		ac.OpenArduinoComms ("COM3", 9600);
	}

	void Update () {
		string[] data = ac.ReadFromArduino ();

		//Set Colour of Buttons Depending On Whether They Are Pressed Or Not
		if (data [0] == "0") {
			UpButton.material.color = Pressed;
		} else {
			UpButton.material.color = NotPressed;
		}
		if (data [1] == "0") {
			RightButton.material.color = Pressed;
		} else {
			RightButton.material.color = NotPressed;
		}
		if (data [2] == "0") {
			DownButton.material.color = Pressed;
		} else {
			DownButton.material.color = NotPressed;
		}
		if (data [3] == "0") {
			LeftButton.material.color = Pressed;
		} else {
			LeftButton.material.color = NotPressed;
		}
		if (data [4] == "0") {
			E.material.color = Pressed;
		} else {
			E.material.color = NotPressed;
		}
		if (data [5] == "0") {
			F.material.color = Pressed;
		} else {
			F.material.color = NotPressed;
		}
		if (data [6] == "0") {
			K.material.color = Pressed;
		} else {
			K.material.color = NotPressed;
		}

		//Set Position of Slider
		float X_Pos = (float.Parse(data[12])-326) / 175;
		float Y_Pos = (float.Parse(data [13])-326) / 175;
		JoystickPosition.transform.localPosition = new Vector3(X_Pos,Y_Pos,0);
	}
}
