using System;
using System.IO;
using System.Diagnostics;
using ComputeSharp;

using NI = CryptoAI.NetworkInterface;

namespace CryptoAI {
	public partial class Program {
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
			NI.SetDirectory("Z:/");
			
			Network N = NI.NewNetwork_CPU_MT(1000,150,200,5,2);
			//Network N = NI.LoadNetwork_MT();
			
			NI.RegenerateAllGenomes_CPU(ref N);
			NI.CalculateNextNetworkIteration_CPU_MT(ref N);
			
			NI.PrintFormattedMsg("CryptoAI","LOG","Getting Genome output");
			
			//NI.SaveNetwork(N);
			
			NI.PrintFormattedMsg("CryptoAI","SUCCESS","Completed network tests");
			Console.ReadKey();
		}
		
		//dataScreen AIStatusText1 =   DisplayManager.addScreen(40,2,"Left","Top"," Algorithm  Status ");
		//dataScreen AIStatusText2 =   DisplayManager.addScreen(40,3,"Left","Top","      Offline    ");
		//dataScreen AIStatusText3 =   DisplayManager.addScreen(40,4,"Left","Top","");
		//dataScreen AIStatusText4 =   DisplayManager.addScreen(40,5,"Left","Top","");
		//DisplayManager.createGroup(new List<dataScreen> {AIStatusText1,AIStatusText2,AIStatusText3,AIStatusText4});
			
		//AIStatusText2.data =   "    Loading Genome";
		//DisplayManager.updateDisplays();
	}
}