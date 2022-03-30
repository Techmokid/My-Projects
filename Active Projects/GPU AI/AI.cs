using System;
using System.IO;
using System.Threading;
using System.Diagnostics;
using System.Collections.Generic;

namespace CryptoAI {
	public static class AI_Internal_Core {
		public static bool initialized = false;
        public static System.Random rand;
		
		public static Network n = null;
		
        public static void SetupRandom() { rand = new System.Random(); }
		public static float getRandomFloat() {
			if (!initialized)
				SetupRandom();
			initialized = true;
			
			return (float)rand.NextDouble();
		}
    }
	
	public struct NodeConnection {
		public Node n;
		public float w;
		public NodeConnection(Node x, float y) {n=x;w=y;}
	}
	
	public class Node {
		public int ID = 0;												// The ID of this node
		public NodeConnection[] connected_nodes = new NodeConnection[0];// All of the connected nodes downstream (Rolling end to start)
		public float triggerThreshold = 0;								// Minimum amount of input before triggering
		public float transmitionStrength = 0;
		
		public bool nodeIsInput = false; 								// Is the node is an input or not
		public float node_input = 0;									// If the node is an input, what have we entered
		public float precalculatedOutput = -99999;						// This variable just allows for quicker genome output computing
		
		public Node(int _ID, NodeConnection[] _connected_nodes) {
			ID = _ID;
			connected_nodes = _connected_nodes;
		}
		
		public float getNodeOutput() {
			if (nodeIsInput)
				return node_input;
			
			float inVals = 0;
			for (int i = 0; i < connected_nodes.Length; i++) {
				inVals += connected_nodes[i].n.getNodeOutput() * connected_nodes[i].w;
			}
			
			if (triggerThreshold < (inVals/((float)connected_nodes.Length))) {
				//Enough of the inputs have triggered
				return transmitionStrength;
			}
			return 0;
		}			
	}
	
	public class Genome {
		public Node[] nodes = new Node[0];
		public float fitness;
		public int ID = 0;
	}
	
	public class Network {
		public Genome[] genomes = new Genome[0];
		public int inputNodesCount;
		public int outputNodesCount;
		public int hiddenLayerCount;
		public int hiddenLayerWidth;
	}
	
	public static class SaveLoadNetwork {
		static string saveDirectory = "";
		
		public static void SetDirectory(string dir) {
			dir = dir.Replace('\\','/');
			if (dir[dir.Length-1] != '/')
				dir += '/';
			
			saveDirectory = dir;
			saveDirectory += "CryptoAI/";
		}
		
		public static Network LoadNetwork(string dir) { SetDirectory(dir); return LoadNetwork(); }
		public static Network LoadNetwork() {
			if (saveDirectory == "") {
				Console.ForegroundColor = ConsoleColor.Red;
				PrintFormattedMsg("CryptoAI","ERROR","Could not load network. LoadNetwork was called without setting save directory");
				quit();
			}
			
			string netSaveDir = saveDirectory + "Network Save Orig/";
			string netBackupDir = saveDirectory + "Network Save Backup/";
			string netStatusFile = saveDirectory + "saveStatus.txt";
			
			string loadDirectory = "";
			if (File.Exists(netStatusFile)) {
				//0 	Means it's completely safe to read from either.							Read from the first one
				//1 	Means it was in the middle of writing to the first copy. 				Read from the second
				//2 	Means it was in the middle of writing to the backup copy. 				Read from the first one
				//null  Means it was in the middle of writing to the save status directory.		Read from the first one
				try {
					int result = int.Parse(File.ReadAllText(netStatusFile));
					if (result == 0) {
						PrintFormattedMsg("AI Config","LOG","Loading AI network from primary save file");
						loadDirectory = netSaveDir;
					} else if (result == 1) {
						PrintFormattedMsg("AI Config","WARNING","Primary save file corrupted. Loading AI network from backup save file");
						loadDirectory = netBackupDir;
					} else if (result == 2) {
						PrintFormattedMsg("AI Config","WARNING","Backup save file corrupted. Attempting file repair");
						saveFileRepair();
						PrintFormattedMsg("AI Config","Log","Loading AI network from primary save file");
						loadDirectory = netSaveDir;
					} else {
						PrintFormattedMsg("AI Config","ERROR","Invalid save status detected in save directory");
						quit();
					}
				} catch {
					//null
					PrintFormattedMsg("AI Config","WARNING","No save status detected. Loading AI network from primary save file");
					loadDirectory = netSaveDir;
				}
			} else {
				PrintFormattedMsg("CryptoAI","WARNING","Could not find save status file. Using default option");
				if (Directory.Exists(netSaveDir)) {
					PrintFormattedMsg("AI Config","LOG","Loading AI network from primary save file");
					loadDirectory = netSaveDir;
				} else if (Directory.Exists(netBackupDir)) {
					PrintFormattedMsg("AI Config","LOG","Loading AI network from backup save file");
					loadDirectory = netBackupDir;
				} else {
					PrintFormattedMsg("CryptoAI","ERROR","Could not load network. No save file detected in directory");
					quit();
				}
			}
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			
			PrintFormattedMsg("CryptoAI","ERROR","This section of code is incomplete and hence still a W.I.P");
			quit();
			
			Network N = null;
			PrintFormattedMsg("CryptoAI","SUCCESS","Loaded AI network");
			return N;
		}
		
		private static void saveFileRepair() {
			PrintFormattedMsg("File Repair","ERROR","Could not repair save data. Function is W.I.P and therefore incomplete");
			quit();
		}
		
		public static void SaveNetwork(Network N) {
			//We cannot save the AI if we don't have a directory to save it to
			if (saveDirectory == "") {
				PrintFormattedMsg("CryptoAI","ERROR","Could not save network. SaveNetwork was called without setting save directory");
				quit();
			}
			
			string netSaveDir = saveDirectory + "Network Save Orig/";
			string netBackupDir = saveDirectory + "Network Save Backup/";
			string netStatusFile = saveDirectory + "saveStatus.txt";
			
			PrintFormattedMsg("CryptoAI","","Saving AI network....");
			if (!Directory.Exists(saveDirectory))
				Directory.CreateDirectory(saveDirectory);
			
			//Save the original copy
			File.WriteAllText(netStatusFile,"1");
			if (Directory.Exists(netSaveDir)) {
				PrintFormattedMsg("CryptoAI","","Clearing old primary save");
				Directory.Delete(netSaveDir,true);
				PrintFormattedMsg("CryptoAI","SUCCESS","Cleared old primary save");
			}
			
			PrintFormattedMsg("CryptoAI","","Saving AI network - primary copy");
			Directory.CreateDirectory(netSaveDir);
			SaveNetworkInternal(N,netSaveDir);
			PrintFormattedMsg("CryptoAI","SUCCESS","Saved AI network - primary copy");
			
			//Save the backup copy
			
			File.WriteAllText(netStatusFile,"2");
			if (Directory.Exists(netBackupDir)) {
				PrintFormattedMsg("CryptoAI","","Clearing old backup save");
				Directory.Delete(netBackupDir,true);
				PrintFormattedMsg("CryptoAI","SUCCESS","Cleared old backup save");
			}
			PrintFormattedMsg("CryptoAI","","Saving AI network - backup copy");
			Directory.CreateDirectory(netBackupDir);
			SaveNetworkInternal(N,netBackupDir);
			PrintFormattedMsg("CryptoAI","SUCCESS","Saved AI network - backup copy");
			
			//Now finish up
			File.WriteAllText(netStatusFile,"0");
			PrintFormattedMsg("CryptoAI","SUCCESS","Saved AI network!");
		}
		
		public static void SaveNetworkInternal(Network N, string dir) {
			//Here, all of the other stuff regarding backup copies and user interfaces is done and dealt with
			//All that's left is the raw save object code. Go nuts!
			if (N == null) {
				PrintFormattedMsg("CryptoAI","ERROR","Could not save network. Null AI network cannot be saved");
				quit();
			}
			
			//Get the best performing genome's ID
			int bestGenomeID = 0;
			for(int i = 0; i < N.genomes.Length; i++) {
				if (N.genomes[i].fitness > N.genomes[bestGenomeID].fitness)
					bestGenomeID = N.genomes[i].ID;
			}
			File.WriteAllText(dir + "Best Genome.txt",bestGenomeID.ToString());
			
			
			Stopwatch stopwatch = new Stopwatch();
			stopwatch.Start();
			
			List<ThreadDataContainer2> TDC_List = new List<ThreadDataContainer2>();
			bool run = true;
			int genomeIndex = 0;
			int maxThreadCount = 8;
			int currentThreadCount = 0;
			while(run) {
				while (currentThreadCount < maxThreadCount) {
					if(genomeIndex == N.genomes.Length) { run = false; break; }
				
					//HERE WE WANT TO ACTUALLY START THE THREAD PROCESS
					ThreadClass p = new ThreadClass();
					ThreadDataContainer2 TDC = new ThreadDataContainer2();
					
					TDC.g = N.genomes[genomeIndex];
					TDC.ID = genomeIndex;
					TDC.dir = dir;
					TDC_List.Add(TDC);
					Thread workerThread = new Thread(p.SaveGenome_CPUMultithreaded);  
					workerThread.Start(TDC);
						
					currentThreadCount++;
					genomeIndex++;
				}
				
				if (run) {
					for (int x = 0; x < TDC_List.Count; x++) {
						if (TDC_List[x].threadCompletionStatus) {
							TDC_List.RemoveAt(x);
							currentThreadCount--;
							x--;
						}
					}
				}
			}
			while(TDC_List.Count > 0) {
				for (int x = 0; x < TDC_List.Count; x++) {
					if (TDC_List[x].threadCompletionStatus) {
						TDC_List.RemoveAt(x);
						currentThreadCount--;
						x--;
					}
				}
			}
		}
		
		public static void saveNode(Node n, string saveLocation) {
			if (n == null) {
				PrintFormattedMsg("AI Save","ERROR","Could not save node. Null node detected");
				quit();
			}
			
			FileInfo fi = new FileInfo(saveLocation); 
			using (StreamWriter sw = fi.CreateText()) {
				sw.WriteLine("{");
				sw.WriteLine("\t\"ID\":" + n.ID.ToString() + ",");
				sw.WriteLine("\t\"tT\":" + n.triggerThreshold.ToString() + ",");
				sw.WriteLine("\t\"tS\":" + n.transmitionStrength.ToString() + ",");
				
				if (n.nodeIsInput == false && (n.connected_nodes != null || n.connected_nodes.Length > 0)) {
					sw.WriteLine("\t\"in\":\"" + n.nodeIsInput.ToString() + "\",");
					
					string temp = "\n\t\"CN\":[{\n";
					for(int i = 0; i < n.connected_nodes.Length; i++) {
						//if (i == 0)
						//	temp += "\n\t\t{";
						
						temp += "\t\t\t\"ID\":" + n.connected_nodes[i].n.ID.ToString() + ",";
						temp += "\t\"w\":" + n.connected_nodes[i].w.ToString() + "\t\t}";
						if (i + 1 != n.connected_nodes.Length)
							temp += ",{";
						
						temp += "\n";
					}
					sw.WriteLine(temp + "\t]");
				} else { sw.WriteLine("\t\"in\":\"" + n.nodeIsInput.ToString() + "\""); }
				
				sw.WriteLine("}");
			}
		}
		
		public static void quit() { exit(); }
		public static void exit() {
			Console.ForegroundColor = ConsoleColor.Magenta;
			Console.WriteLine();
			Console.WriteLine();
			Console.WriteLine();
			Console.WriteLine("--------------------------------------");
			Console.WriteLine("Please press Enter to quit the program");
			Console.ReadLine();
			System.Environment.Exit(1);
		}
		
		public static bool printTime = false;
		public static bool centerText = true;
		public static bool printModuleName = true;
		public static void PrintFormattedMsg(string moduleName, string msgType, string msg) {
			ConsoleColor startingColor = ConsoleColor.White;
			if (msgType.ToLower()=="log")
				msgType="";
			int digits = 0;
			
			//Setting up the colours
			ConsoleColor moduleBracketsColor = ConsoleColor.White;
			ConsoleColor moduleNameColor = ConsoleColor.Cyan;
			ConsoleColor timeBrackets = ConsoleColor.White;
			ConsoleColor time = ConsoleColor.White;
			ConsoleColor msgTypeBracketsColor = ConsoleColor.White;
			ConsoleColor msgTypeColor = ConsoleColor.Gray;
			msgTypeColor = msgType.ToLower()=="warning"	? ConsoleColor.Yellow 	: msgTypeColor;
			msgTypeColor = msgType.ToLower()=="success"	? ConsoleColor.Green 	: msgTypeColor;
			msgTypeColor = msgType.ToLower()=="error"	? ConsoleColor.Red 		: msgTypeColor;
			msgTypeColor = msgType.ToLower()=="debug"	? ConsoleColor.Magenta 	: msgTypeColor;
			msgTypeColor = msgType.ToLower()=="log"		? ConsoleColor.White 	: msgTypeColor;
			ConsoleColor msgColor = ConsoleColor.White;
			
			//Actually print the message
			if (printTime) {
				Console.ForegroundColor = timeBrackets;
				Console.Write("[");
				Console.ForegroundColor = time;
				String s = DateTime.Now.TimeOfDay.ToString();
				for(int i = 0; i < 7 - digits; i++) { s = s.Remove(s.Length-1); }
				if (digits == 0)
					s = s.Remove(s.Length-1);
				Console.Write(s);
				Console.ForegroundColor = timeBrackets;
				Console.Write("]");
			}
			
			if (printModuleName) {
				Console.ForegroundColor = moduleBracketsColor;
				Console.Write("[");
				Console.ForegroundColor = moduleNameColor;
				Console.Write(moduleName);
				Console.ForegroundColor = moduleBracketsColor;
				Console.Write("]");
			}
			
			Console.ForegroundColor = msgTypeBracketsColor;
			Console.Write("[");
			Console.ForegroundColor = msgTypeColor;
			
			if (centerText) {
				for(int i = 0; i < 3 - msgType.Length/2; i++) { Console.Write(" "); }
			}
			Console.Write(msgType);
			if (centerText) {
				for(int i = 0; i < 3 - msgType.Length/2; i++) { Console.Write(" "); }
				if (msgType.Length % 2 == 0)
					Console.Write(" ");
			}
			Console.ForegroundColor = msgTypeBracketsColor;
			Console.Write("] ");
			if (!centerText) {
				for(int i = 0; i < 7 - msgType.Length; i++) { Console.Write(" "); }
			}
			Console.ForegroundColor = msgColor;
			Console.WriteLine(msg);
			Console.ForegroundColor = startingColor;
		}
		
		public static Network NewNetwork(int genomeCount, int inputNodes, int nodesPerHiddenLayer, int hiddenLayerCount, int outputNodes) {
			PrintFormattedMsg("AI Config","WARNING","Generating new AI Network. This may take awhile...");
			
			Network N = new Network();
			N.inputNodesCount = inputNodes;
			N.outputNodesCount = outputNodes;
			N.hiddenLayerCount = hiddenLayerCount;
			N.hiddenLayerWidth = nodesPerHiddenLayer;
			
			N.genomes = new Genome[genomeCount];
			
			List<ThreadDataContainer> TDC_List = new List<ThreadDataContainer>();
			bool run = true;
			int genomeIndex = 0;
			int maxThreadCount = 8;
			int currentThreadCount = 0;
			while(run) {
				while (currentThreadCount < maxThreadCount) {
					if(genomeIndex == genomeCount) { run = false; break; }
				
					//HERE WE WANT TO ACTUALLY START THE THREAD PROCESS
					ThreadClass p = new ThreadClass();
					ThreadDataContainer TDC = new ThreadDataContainer();
					TDC.CPU_Thread_ID = genomeIndex;
					TDC.inputNodes = inputNodes;
					TDC.outputNodes = outputNodes;
					TDC.nodesPerHiddenLayer = nodesPerHiddenLayer;
					TDC.hiddenLayerCount = hiddenLayerCount;
					TDC_List.Add(TDC);
					Thread workerThread = new Thread(p.CreateNewRandomGenome_CPUMultithreaded);  
					workerThread.Start(TDC);
						
					currentThreadCount++;
					genomeIndex++;
				}
				
				if (run) {
					for (int x = 0; x < TDC_List.Count; x++) {
						if (TDC_List[x].threadCompletionStatus) {
							N.genomes[TDC_List[x].CPU_Thread_ID] = TDC_List[x].threadOutput;
							TDC_List.RemoveAt(x);
							currentThreadCount--;
							x--;
						}
					}
				}
			}
			while(TDC_List.Count > 0) {
				for (int x = 0; x < TDC_List.Count; x++) {
					if (TDC_List[x].threadCompletionStatus) {
						N.genomes[TDC_List[x].CPU_Thread_ID] = TDC_List[x].threadOutput;
						TDC_List.RemoveAt(x);
						currentThreadCount--;
						x--;
					}
				}
			}
			
			PrintFormattedMsg("AI Config","SUCCESS","Created new AI network");
			return N;
		}
		
		public static int CheckNetworkIntegrity(Network N) {
			int nullDetected = 0;
			for(int i = 0; i < N.genomes.Length; i++) {
				if (N.genomes[i] == null) {
					Console.WriteLine("Genome " + (i+1).ToString() + "/" + N.genomes.Length.ToString() + ":\t\tStatus - Null");
					nullDetected++;
				} else {
					Console.WriteLine("Genome " + (i+1).ToString() + "/" + N.genomes.Length.ToString() + ":\t\tStatus - Functional\t\tID: " + N.genomes[i].ID);
				}
			}
			return nullDetected;
		}
	}
		
	public class ThreadClass {
		public void CreateNewRandomGenome_CPUMultithreaded(object data) {
			ThreadDataContainer TDC = (ThreadDataContainer)data;
			
			Genome g = new Genome();
			g.ID = TDC.CPU_Thread_ID;
			g.nodes = new Node[TDC.inputNodes + TDC.outputNodes + TDC.nodesPerHiddenLayer*TDC.hiddenLayerCount];
			
			Node[] previousLayer = new Node[TDC.inputNodes];
			for (int i = 0; i < TDC.inputNodes; i++) {
				Node n = new Node(i,null);
				n.nodeIsInput = true;
				g.nodes[i] = n;
				previousLayer[i] = n;
			}
			
			int startingIndex = TDC.inputNodes;
			for(int layer = 0; layer < TDC.hiddenLayerCount; layer++) {
				for(int i = 0; i < TDC.nodesPerHiddenLayer; i++) {
					NodeConnection[] nc = new NodeConnection[previousLayer.Length];
					for (int connection = 0; connection < nc.Length; connection++) {
						nc[connection] = new NodeConnection(previousLayer[connection],AI_Internal_Core.getRandomFloat());
					}
					
					Node n = new Node(startingIndex + i + layer*TDC.nodesPerHiddenLayer,nc);
					n.triggerThreshold = AI_Internal_Core.getRandomFloat();
					n.transmitionStrength = AI_Internal_Core.getRandomFloat();
					g.nodes[startingIndex + i + layer*TDC.nodesPerHiddenLayer] = n;
				}
			}
			
			startingIndex += TDC.nodesPerHiddenLayer*TDC.hiddenLayerCount;
			for (int i = 0; i < TDC.outputNodes; i++) {
				NodeConnection[] nc = new NodeConnection[previousLayer.Length];
				for (int connection = 0; connection < nc.Length; connection++) {
					nc[connection] = new NodeConnection(previousLayer[connection],AI_Internal_Core.getRandomFloat());
				}
					
				Node n = new Node(startingIndex + i,nc);
				n.triggerThreshold = AI_Internal_Core.getRandomFloat();
				n.transmitionStrength = AI_Internal_Core.getRandomFloat();
				g.nodes[i + startingIndex] = n;
			}
			
			TDC.threadOutput = g;
			TDC.threadCompletionStatus = true;
		}
		
		public void SaveGenome_CPUMultithreaded(object data) {
			ThreadDataContainer2 TDC = (ThreadDataContainer2)data;
			
			Genome g = TDC.g;
			string newDir = TDC.dir + "Genome " + g.ID + "/";
			Directory.CreateDirectory(newDir);
			for(int x = 0; x < g.nodes.Length; x++) {
				SaveLoadNetwork.saveNode(g.nodes[x],newDir + "Node " + g.nodes[x].ID + ".json");
			}
			
			TDC.threadCompletionStatus = true;
		}
	}
		
	public class ThreadDataContainer {
		public bool threadCompletionStatus = false;
		public int CPU_Thread_ID;
		public int inputNodes;
		public int outputNodes;
		public int nodesPerHiddenLayer;
		public int hiddenLayerCount;
		public Genome threadOutput;
	}
	
	public class ThreadDataContainer2 {
		public bool threadCompletionStatus = false;
		public Genome g;
		public int ID;
		public string dir;
	}
}



















