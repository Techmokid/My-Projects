using System;
using System.IO;

using unirest_net.http;

namespace CryptoAI {
	class Program {
		static string filePath = "C:/Users/aj200/Desktop/";
		
		static void Main(string[] args) {
			Console.Clear();
			
			NetworkInterface.printTime = true;
			NetworkInterface.printModuleName = false;
			NetworkInterface.PrintFormattedMsg("CryptoAI","LOG","This is a logged message or generic output");
			NetworkInterface.PrintFormattedMsg("CryptoAI","DEBUG","This is debugging code output");
			NetworkInterface.PrintFormattedMsg("CryptoAI","WARNING","This is a warning that a function is having troubles");
			NetworkInterface.PrintFormattedMsg("CryptoAI","ERROR","This indicates something went very wrong");
			NetworkInterface.PrintFormattedMsg("CryptoAI","SUCCESS","This indicates that a function completed!");
			NetworkInterface.PrintFormattedMsg("CryptoAI","THING","This is a generic message that doesn't fit the other stuff");
			
			Console.WriteLine();
			Console.WriteLine();
			Console.WriteLine("---------------------------------------------------------------------");
			Console.WriteLine();
			Console.WriteLine();
			
			//DisplayManager.StartDisplay();
			NetworkInterface.PrintFormattedMsg("CryptoAI","LOG","Starting...");
			NetworkInterface.SetDirectory(filePath);
			
			//NetworkInterface.clearSave();
			Network N = NetworkInterface.LoadNetwork();
			
			//Network N = NetworkInterface.NewNetwork(50,150,400,10,4);
			//NetworkInterface.SaveNetwork(N);
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