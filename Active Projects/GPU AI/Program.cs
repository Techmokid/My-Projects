using System;
using System.IO;
using System.Diagnostics;
using System.Runtime.InteropServices;

using ComputeSharp;
using Newtonsoft.Json;
using NI = CryptoAI.NetworkInterface;

namespace CryptoAI {
	public class Program {
		static string desktop = "C:/Users/aj200/Desktop/";
		
		static void Main(string[] args) {
			Console.Clear();
			
			NI.printTime = true;
			NI.printModuleName = false;
			NI.PrintFormattedMsg("CryptoAI","LOG","This is a logged message or generic output");
			NI.PrintFormattedMsg("CryptoAI","DEBUG","This is debugging code output");
			NI.PrintFormattedMsg("CryptoAI","WARNING","This is a warning that a function is having troubles");
			NI.PrintFormattedMsg("CryptoAI","ERROR","This indicates something went very wrong");
			NI.PrintFormattedMsg("CryptoAI","SUCCESS","This indicates that a function completed!");
			NI.PrintFormattedMsg("CryptoAI","THING","This is a generic message that doesn't fit the other stuff");
			
			Console.WriteLine();
			Console.WriteLine();
			Console.WriteLine("---------------------------------------------------------------------");
			Console.WriteLine();
			Console.WriteLine();
			
			//DisplayManager.StartDisplay();
			NI.PrintFormattedMsg("CryptoAI","LOG","Starting...");
			
			AI_GPU AI = new AI_GPU();
			AI_GPU.saveDirectory = desktop + "Andrey AI/";
			AI_GPU.trainingData = new double[1000];
			for (int i = 0; i < AI_GPU.trainingData.Length; i++) { AI_GPU.trainingData[i] = AI_Internal_Core.getRandomFloat(); }
			
			AI.NewNetworkGPU(50,150,200,8,2);
			AI.CreateTrainingSavingLoop();
			//AI.SaveNetworkGPU("F:/GPU Crypto AI");
			//AI.LoadNetworkGPU("F:/GPU Crypto AI");
			
			NI.PrintFormattedMsg("CryptoAI","SUCCESS","Completed network tests");
			while(true) {}
		}
	}
}