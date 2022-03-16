using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovementController : MonoBehaviour {
    public Transform HeightPin;
    
    void Update() {
        transform.position = new Vector3(transform.position.x, HeightPin.position.y, transform.position.z);
    }
}
