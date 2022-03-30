using System;
using System.IO;

using unirest_net.http;

namespace CryptoAI {
	class Program {
		static string filePath = "C:/Users/aj200/Desktop/";
		
		static void Main(string[] args) {
			Console.Clear();
			
			SaveLoadNetwork.printTime = true;
			SaveLoadNetwork.printModuleName = false;
			SaveLoadNetwork.PrintFormattedMsg("CryptoAI","LOG","This is a logged message or generic output");
			SaveLoadNetwork.PrintFormattedMsg("CryptoAI","DEBUG","This is debugging code output");
			SaveLoadNetwork.PrintFormattedMsg("CryptoAI","WARNING","This is a warning that a function is having troubles");
			SaveLoadNetwork.PrintFormattedMsg("CryptoAI","ERROR","This indicates something went very wrong");
			SaveLoadNetwork.PrintFormattedMsg("CryptoAI","SUCCESS","This indicates that a function completed!");
			SaveLoadNetwork.PrintFormattedMsg("CryptoAI","THING","This is a generic message that doesn't fit the other stuff");
			
			Console.WriteLine();
			Console.WriteLine();
			Console.WriteLine("---------------------------------------------------------------------");
			Console.WriteLine();
			Console.WriteLine();
			
			//DisplayManager.StartDisplay();
			SaveLoadNetwork.PrintFormattedMsg("CryptoAI","LOG","Starting...");
			SaveLoadNetwork.SetDirectory(filePath);
			
			//Genome Count
			//Input Node Count
			//Node count per hidden layer
			//Hidden layer count
			//Output nodes count
			
			
			Network N = SaveLoadNetwork.LoadNetwork();
			
			//Network N = SaveLoadNetwork.NewNetwork(1000,150,400,10,4);
			//SaveLoadNetwork.SaveNetwork(N);
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