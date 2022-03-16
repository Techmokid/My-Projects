using UnityEngine;

public class FluidFlowControlMark2 : MonoBehaviour {
    public Rotate rotationController;
    public TimedStaticGateController controller;
    public bool isInput;
    public bool _print;

    Renderer rend;

    void Start() {
        rend = transform.GetChild(0).GetComponent<Renderer>();
    }
    
    void Update() {
        Color c = rend.material.color;
        if (!controller.isOpening && isInput) {
            c.a = 0;
        } else if(!controller.isClosing && !isInput) {
            c.a = 0;
        } else {
            c.a = SmoothCurve(controller.openingStatus);
        }

        rend.material.color = c;
    }

    float SmoothCurve(float percentageThroughCurve) {
        return 1 - (Mathf.Cos(2 * Mathf.PI * percentageThroughCurve) + 1) / 2;
    }
}
