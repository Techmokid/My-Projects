using System;
using System.IO;
using System.Diagnostics;
using System.Collections.Generic;
using System.Runtime.InteropServices;

using BasicAlgorithm;
using Binance_API;
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
			//AI_GPU.trainingData = new List<double[]>();
			
			AI.NewNetworkGPU(100,150,300,6,2);
			NI.PrintFormattedMsg("CryptoAI","LOG","Retrieving crypto data....");
			API.UpdateAllCoinsData(300);
			AI_GPU.trainingData = API.allCoinsData;
			NI.PrintFormattedMsg("CryptoAI","SUCCESS","Retrieved all crypto data");
			
			//CryptoAlgorithm CA = new CryptoAlgorithm();
			//CA.analyzeData(API.allCoinsData);
			for(int i = 0; i < 3; i++) {
				AI.CreateTrainingSavingLoop();
			}
			//AI.SaveNetworkGPU("F:/GPU Crypto AI");
			//AI.LoadNetworkGPU("F:/GPU Crypto AI");
			
			NI.PrintFormattedMsg("CryptoAI","SUCCESS","Completed network tests");
			while(true) {}
		}
	}
}