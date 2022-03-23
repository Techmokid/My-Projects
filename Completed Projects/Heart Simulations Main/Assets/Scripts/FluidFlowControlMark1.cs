using UnityEngine;

public class FluidFlowControlMark1 : MonoBehaviour
{
    public Transform rotatingObj;
    public bool isInput;
    public bool _print;

    float startIn = 80;
    float endIn = 150;
    float startOut = 10;
    float endOut = 60;

    Renderer rend;

    void Start() {
        rend = transform.GetChild(0).GetComponent<Renderer>();
    }

    void Update()
    {
        Color c = rend.material.color;
        float rot = rotatingObj.rotation.eulerAngles.z;
        while (rot > 180)
            rot -= 180;
        if (_print)
            print(rot);

        float localStart = startOut;
        float localEnd = endOut;
        if (isInput) { localStart = startIn; localEnd = endIn; }
        if (_print) { print(localStart); }
        if ((rot > localStart) && (rot < localEnd)) {
            //Add fade effect here
            localEnd -= localStart;
            rot -= localStart;
            float perc = rot / localEnd;
            c.a = SmoothCurve(perc);
        } else {
            c.a = 0;
        }

        rend.material.color = c;
    }

    float SmoothCurve(float percentageThroughCurve) {
        return 1 - (Mathf.Cos(2 * Mathf.PI * percentageThroughCurve) + 1) / 2;
    }
}
