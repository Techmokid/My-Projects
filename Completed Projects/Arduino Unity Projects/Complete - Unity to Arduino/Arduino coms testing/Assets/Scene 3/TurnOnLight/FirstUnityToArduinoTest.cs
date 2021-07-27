using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class FirstUnityToArduinoTest : MonoBehaviour {
	SerialPort sp = new SerialPort ("COM3",9600);

	void Start () {
		sp.Open ();
		sp.WriteTimeout = 20;
		StartCoroutine(flash());
	}

	IEnumerator flash () {
		while (true) {
			sp.Write ("A");
			yield return new WaitForSeconds (1);
			sp.Write ("a");
			yield return new WaitForSeconds (1);
		}
	}
}
