using UnityEngine;

public class DynamicGateController : MonoBehaviour
{
    public Transform rotatingObject, pivot, internalPivot, endPoint;
    public bool invertAngle;
    public float startAngle, closedAngle, percOpen;
    public float rotationalOffset;
    public bool printBool;

    void Update()
    {
        float rot = Mathf.Abs(rotatingObject.eulerAngles.z) + rotationalOffset;
        while (rot > 180)
            rot -= 180;
        
        SetOpenPercentage(ElipticalCurve(rot)); //ChangeAngle(percOpen);
    }

    float SmoothCurve(float percentageThroughCurve) {
        return 1 - (Mathf.Cos(2 * Mathf.PI * percentageThroughCurve) + 1) / 2;
    }

    float ElipticalCurve(float angle) {
        angle *= Mathf.PI/180;
        angle += Mathf.PI / 2;

        float longerEclipseLength = 5.5f;
        float shorterEclipseLength = 3.5f;

        // Distance = Sqrt(a^2 * cos2(angle) + b^2 * cos2(angle))
        // Distance = a^2 * cos2(angle) + b^2 * cos2(angle)
        // Distance = partA + partB
        float partA = Mathf.Pow(longerEclipseLength, 2) * Mathf.Pow(Mathf.Cos(angle), 2);
        float partB = Mathf.Pow(shorterEclipseLength, 2) * Mathf.Pow(Mathf.Sin(angle), 2);
        float distToCenter = Mathf.Sqrt(partA + partB);

        distToCenter -= shorterEclipseLength;
        longerEclipseLength -= shorterEclipseLength;
        return distToCenter / longerEclipseLength;
    }

    void ChangeAngle(float rot)
    {
        if (invertAngle) { rot *= -1; }
        transform.rotation = Quaternion.Euler(0, 0, rot + rotatingObject.eulerAngles.z);
        Vector3 offset = pivot.position - internalPivot.position;
        transform.position += offset;
    }

    void SetOpen() { SetOpenPercentage(1); }
    void SetClosed() { SetOpenPercentage(0); }
    void SetOpenPercentage(float perc)
    {
        ChangeAngle((closedAngle - startAngle) * Mathf.Clamp01(perc) + startAngle);
    }
}
