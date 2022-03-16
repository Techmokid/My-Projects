using UnityEngine;

public class TimedStaticGateController : MonoBehaviour
{
    public Transform rotatingObject, pivot, internalPivot, endPoint;
    public bool invertAngle;
    public float startAngle, closedAngle, percOpen;

    public float openingStatus;
    public bool isOpening,isClosing;


    void Update() {
        float rot = Mathf.Abs(rotatingObject.eulerAngles.z);
        if (rot > 180)
            rot -= 180;
        
        if ((rot < 45) || (rot > 120)) {
            if (rot > 120) { rot -= 120; } else { rot += 60; }
            float openPerc = SmoothCurve(rot / 105);
            SetOpenPercentage(openPerc);
            isOpening = openPerc > openingStatus;
            isClosing = openPerc < openingStatus;
            openingStatus = openPerc;
        } else {
            SetClosed();
            isOpening = false;
            isClosing = false;
        }
    }

    float SmoothCurve(float percentageThroughCurve) {
        return 1 - (Mathf.Cos(2*Mathf.PI*percentageThroughCurve) + 1)/2;
    }

    void ChangeAngle(float rot) {
        if (invertAngle) { rot *= -1; }
        transform.rotation = Quaternion.Euler(0, 0, rot);
        Vector3 offset = pivot.position - internalPivot.position;
        transform.position += offset;
    }

    void SetOpen() { SetOpenPercentage(1); }
    void SetClosed() { SetOpenPercentage(0); }
    void SetOpenPercentage(float perc) {
        ChangeAngle((closedAngle - startAngle) * Mathf.Clamp01(perc) + startAngle);
    }
}
