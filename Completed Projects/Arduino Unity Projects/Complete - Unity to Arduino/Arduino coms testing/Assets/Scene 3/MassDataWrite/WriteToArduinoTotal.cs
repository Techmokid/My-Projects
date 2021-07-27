using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class WriteToArduinoTotal : MonoBehaviour {
	public Renderer D2;
	public Renderer D3;
	public Renderer D4;
	public Renderer D5;
	public Renderer D6;
	public Renderer D7;
	public Renderer D8;
	public Renderer D9;
	public Renderer D10;
	public Renderer D11;
	public Renderer D12;
	public Renderer D13;
	SerialPort sp = new SerialPort ("COM3",9600);

	void Start () {
		sp.Open ();
		sp.WriteTimeout = 20;

		//Set all boxes to red to start with
		D2.material.color = Color.red;
		D3.material.color = Color.red;
		D4.material.color = Color.red;
		D5.material.color = Color.red;
		D6.material.color = Color.red;
		D7.material.color = Color.red;
		D8.material.color = Color.red;
		D9.material.color = Color.red;
		D10.material.color = Color.red;
		D11.material.color = Color.red;
		D12.material.color = Color.red;
		D13.material.color = Color.red;
	}

	void Update () {
		//If the user is pressing one of these buttons, send a message to the Arduino to turn on or off the corresponding digital pin, then set the colour of the box onscreen
		if (Input.GetKeyDown (KeyCode.Q)) {		//D2
			sp.Write ("A");
			D2.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.Q)) {
			sp.Write ("a");
			D2.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.W)) {		//D3
			sp.Write ("B");
			D3.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.W)) {
			sp.Write ("b");
			D3.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.E)) {		//D4
			sp.Write ("C");
			D4.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.E)) {
			sp.Write ("c");
			D4.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.R)) {		//D5
			sp.Write ("D");
			D5.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.R)) {
			sp.Write ("d");
			D5.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.T)) {		//D6
			sp.Write ("E");
			D6.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.T)) {
			sp.Write ("e");
			D6.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.Y)) {		//D7
			sp.Write ("F");
			D7.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.Y)) {
			sp.Write ("f");
			D7.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.U)) {		//D8
			sp.Write ("G");
			D8.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.U)) {
			sp.Write ("g");
			D8.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.I)) {		//D9
			sp.Write ("H");
			D9.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.I)) {
			sp.Write ("h");
			D9.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.O)) {		//D10
			sp.Write ("I");
			D10.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.O)) {
			sp.Write ("i");
			D10.material.color = Color.red;
		}

		if (Input.GetKeyDown (KeyCode.P)) {		//D11
			sp.Write ("J");
			D11.material.color = Color.green;
		}
		if (Input.GetKeyUp (KeyCode.P)) {
			sp.Write ("j");
			D11.material.color = Color.red;
		}

		if (Input.GetKeyDown ("[")) {			//D12
			sp.Write ("K");
			D12.material.color = Color.green;
		}
		if (Input.GetKeyUp ("[")) {
			sp.Write ("k");
			D12.material.color = Color.red;
		}

		if (Input.GetKeyDown ("]")) {			//D13
			sp.Write ("L");
			D13.material.color = Color.green;
		}
		if (Input.GetKeyUp ("]")) {
			sp.Write ("l");
			D13.material.color = Color.red;
		}
	}
}
