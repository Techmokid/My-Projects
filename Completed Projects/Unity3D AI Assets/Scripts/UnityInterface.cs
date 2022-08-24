using System.Threading;
using UnityEngine;
using CryptoAI;

public class UnityInterface : MonoBehaviour {
    public ComputeShader cs;
    public Program AI;

    void Start() {
        AI = new Program();

        Thread t = new Thread(AI.Main);
        t.Start();
    }
}
