using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Rotate : MonoBehaviour
{
    Transform me;
    public float degreesPerSecondX = 0;
    public float degreesPerSecondY = 0;
    public float degreesPerSecondZ = 0;

    void Start() { me = transform; }
    void Update()
    {
        me.Rotate(Time.deltaTime * degreesPerSecondX, Time.deltaTime * degreesPerSecondY, Time.deltaTime * degreesPerSecondZ);
    }
}
