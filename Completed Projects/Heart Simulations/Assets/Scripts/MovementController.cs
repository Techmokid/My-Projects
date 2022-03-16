using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementController : MonoBehaviour {
    public Transform HeightPin;
    
    void Update() {
        transform.localPosition = new Vector3(0, HeightPin.position.y, -1.75f);
    }
}
