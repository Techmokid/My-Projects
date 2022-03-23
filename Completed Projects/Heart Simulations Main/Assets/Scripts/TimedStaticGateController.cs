using UnityEngine;

public class TimedStaticGateController : MonoBehaviour
{
    public Transform rotatingObject, pivot, internalPivot, endPoint;
    public bool invertAngle;
    public float startAngle, closedAngle, numberOfGaps,startingRotationalOffset;

    public float startOpeningRotation = 45;
    public float finishClosingRotation = 120;

    public float openingStatus;
    public bool isOpening,isClosing;
    public bool _print;

    void Update() {
        float degreesPerPulse = 360 / numberOfGaps;
        float rot = Mathf.Abs(rotatingObject.eulerAngles.z) + startingRotationalOffset;
        while (rot > degreesPerPulse)
            rot -= degreesPerPulse;
        if (_print)
            print(rot);

        if ((rot < startOpeningRotation) || (rot > finishClosingRotation)) {
            if (rot > finishClosingRotation) {
                rot -= finishClosingRotation;
            } else {
                rot += degreesPerPulse - finishClosingRotation;
            }

            float openPerc = SmoothCurve(rot / (startOpeningRotation + degreesPerPulse - finishClosingRotation));
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
