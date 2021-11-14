using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class SecondTest : MonoBehaviour {
	SerialPort sp = new SerialPort ("COM3",9600);

	void Start () {
		sp.Open ();
		sp.WriteTimeout = 20;
	}

	void Update () {
		//If the user is pressing one of these buttons, send a message to the Arduino to turn on or off the corresponding digital pin
		if (Input.GetKeyDown (KeyCode.Q)) {	//D2
			sp.Write ("A");
		}
		if (Input.GetKeyUp (KeyCode.Q)) {
			sp.Write ("a");
		}

		if (Input.GetKeyDown (KeyCode.W)) {	//D3
			sp.Write ("B");
		}
		if (Input.GetKeyUp (KeyCode.W)) {
			sp.Write ("b");
		}

		if (Input.GetKeyDown (KeyCode.E)) {	//D4
			sp.Write ("C");
		}
		if (Input.GetKeyUp (KeyCode.E)) {
			sp.Write ("c");
		}

		if (Input.GetKeyDown (KeyCode.R)) {	//D5
			sp.Write ("D");
		}
		if (Input.GetKeyUp (KeyCode.R)) {
			sp.Write ("d");
		}

		if (Input.GetKeyUp (KeyCode.T)) {	//D6
			sp.Write ("E");
		}
		if (Input.GetKeyUp (KeyCode.T)) {
			sp.Write ("e");
		}

		if (Input.GetKeyUp (KeyCode.Y)) {	//D7
			sp.Write ("F");
		}
		if (Input.GetKeyUp (KeyCode.Y)) {
			sp.Write ("f");
		}

		if (Input.GetKeyUp (KeyCode.U)) {	//D8
			sp.Write ("G");
		}
		if (Input.GetKeyUp (KeyCode.U)) {
			sp.Write ("g");
		}

		if (Input.GetKeyUp (KeyCode.I)) {	//D9
			sp.Write ("H");
		}
		if (Input.GetKeyUp (KeyCode.I)) {
			sp.Write ("h");
		}

		if (Input.GetKeyUp (KeyCode.O)) {	//D10
			sp.Write ("I");
		}
		if (Input.GetKeyUp (KeyCode.O)) {
			sp.Write ("i");
		}

		if (Input.GetKeyUp (KeyCode.P)) {	//D11
			sp.Write ("J");
		}
		if (Input.GetKeyUp (KeyCode.P)) {
			sp.Write ("j");
		}

		if (Input.GetKeyUp ("[")) {			//D12
			sp.Write ("K");
		}
		if (Input.GetKeyUp ("[")) {
			sp.Write ("k");
		}

		if (Input.GetKeyUp ("]")) {			//D13
			sp.Write ("L");
		}
		if (Input.GetKeyUp ("]")) {
			sp.Write ("l");
		}
	}
}
