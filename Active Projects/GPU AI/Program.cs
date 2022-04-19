﻿using System;
using System.Threading;
using System.Collections.Generic;

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
			NI.PrintFormattedMsg("CryptoAI","LOG","Retrieving crypto data....");
			API.UpdateAllCoinsData(300);
			NI.PrintFormattedMsg("CryptoAI","SUCCESS","Retrieved all crypto data");
			
			AI_GPU AI = new AI_GPU();
			AI_GPU.saveDirectory = desktop + "Andrey AI/";
			
			AI.NewNetworkGPU(100,150,300,6,2);
			AI_GPU.trainingData = API.allCoinsData;
			List<double[]> results = AI.GetNetworkOutput(AI_GPU.trainingData[0]);
			for(int i = 0; i < results.Count; i++) {
			//	Console.WriteLine("Genome " + i + ": " + results[i][0] + "\t\t\t" + results[i][1]);
			}
			
			AI.SaveNetworkGPU();
			
			
			//for(int i = 0; i < AI_GPU.NGPU.nodes.Length; i++) {
			//	Console.WriteLine("ID: " + i + "\t\tnII: " + AI_GPU.NGPU.nodes[i].nII + "\t\tnIO: " + AI_GPU.NGPU.nodes[i].nIO);
			//	Thread.Sleep(100);
			//}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			//AI_GPU.trainingData = new List<double[]>();
			//for (int i = 0; i < 15; i++) {
			//	double[] tmp = new double[350];
			//	for(int x = 0; x < tmp.Length; x++) {
			//		tmp[x] = 1;
			//	}
			//	
			//	AI_GPU.trainingData.Add(tmp);
			//}
			
			
			//CryptoAlgorithm CA = new CryptoAlgorithm();
			//CA.analyzeData(API.allCoinsData);
			//for(int i = 0; i < 2; i++) {
			//	AI.CreateTrainingSavingLoop();
			//}
			
			//AI.GetNetworkOutput(AI_GPU.trainingData);
			//for(int i = 0; i < ; i++) {
			//	
			//}
			
			//AI.SaveNetworkGPU("F:/GPU Crypto AI");
			//AI.LoadNetworkGPU("F:/GPU Crypto AI");
			
			NI.PrintFormattedMsg("CryptoAI","SUCCESS","Completed network tests");
			while(true) {}
		}
	}
}