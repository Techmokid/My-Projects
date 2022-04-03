using System;
using System.IO;
using System.Linq;
using System.Threading;
using System.Diagnostics;
using System.Collections.Generic;

using Newtonsoft.Json;
using Newtonsoft.Json.Linq;

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
	
	public struct Node {
		public string NodeActivationType = "";
		public int ID = -1;									// The ID of this node
		public NodeConnection[] cN = new NodeConnection[0];	// All of the connected nodes downstream (Rolling end to start)
		public float[] previousWeights = new float[0];
		
		public float tT = 0;								// Minimum amount of input before triggering
		public float prev_tT = 0;
		public float tS = 0;								// Strength of the output transmition
		public float prev_tS = 0;
		
		public bool nII = false; 							// Is the node is an input or not
		public bool nIO = false; 							// Is the node is an output or not
		public float nIV = 0;								// If the node is an input, what have we entered
		public float pO = -99999;							// This variable just allows for quicker genome output computing
		
		public Node(int _ID, NodeConnection[] _connected_nodes) {
			ID = _ID;
			cN = _connected_nodes;
		}
		
		public float getNodeOutput() {
			if (pO != -99999)
				return pO;
			
			if (nII)
				return nIV;
			
			float inVals = 0;
			for (int i = 0; i < cN.Length; i++) {
				inVals += cN[i].n.getNodeOutput() * cN[i].w;
			}
			
			switch (NodeActivationType.ToLower()) {
				case "neural":
					if (tT < (inVals/((float)cN.Length))) {
						//Enough of the inputs have triggered
						pO = tS;
						return tS;
					}
					pO = 0;
					return 0;
				case "classic":
					return inVals/((float)cN.Length);
				default:
					return 0;
			}
		}
		
		public void resetNodeToPreviousState() {
			pO = -99999;
			tT = prev_tT;
			tS = prev_tS;
			
			for(int i = 0; i < cN.Length; i++) {
				cN[i].w = previousWeights[i];
			}
		}
	}
	
	public class Genome {
		public Node[] inputNodes = new Node[0];
		public Node[] outputNodes = new Node[0];
		public Node[] nodes = new Node[0];
		
		// Classic is the way I built my first AI
		// Neural is the all-or-nothing-response
		public string GenomeType = "";
		
		public float fitness;
		public int ID = 0;
		
		public void resetGenomeToPreviousState() {
			for(int i = 0; i < nodes.Length; i++) {
				nodes[i].resetNodeToPreviousState();
				nodes[i].NodeActivationType = GenomeType;
			}
		}
		
		public void resetPrecalculations() {
			for(int i = 0; i < nodes.Count(); i++) {
				nodes[i].pO = -99999;
				nodes[i].NodeActivationType = GenomeType;
			}
		}
		
		public void SetGenomeType(string type) {
			GenomeType = type;
			for(int i = 0; i < nodes.Count(); i++) {
				nodes[i].NodeActivationType = type;
			}
		}
		
		public void GetGenomeOutput(float[] inputValues, ref float[] outputValues) {
			if (inputNodes.Length != inputValues.Count()) {
				NetworkInterface.PrintFormattedMsg("CryptoAI","ERROR","Incorrect size of input array upon GetGenomeOutput()");
				NetworkInterface.PrintFormattedMsg("CryptoAI","ERROR","Received " + inputValues.Count().ToString() +
								  " values, but was expecting " + inputNodes.Count().ToString());
				NetworkInterface.quit();
			}
			
			for (int i = 0; i < inputNodes.Count(); i++) {
				inputNodes[i].nIV = inputValues[i];
			}
			
			for (int i = 0; i < outputValues.Count(); i++) {
				outputValues[i] = outputNodes[i].getNodeOutput();
			}
			
			return;
		}
	}
	
	public class Network {
		public Genome[] genomes = new Genome[0];
		public int inputNodesCount;
		public int outputNodesCount;
		public int hiddenLayerCount;
		public int hiddenLayerWidth;
	}
	
	public static class NetworkInterface {
		public static string saveDirectory = "";
		public static bool dumpAndPump = false;
		public static bool once = true;
		public static bool once2 = true;
		
		public static void SetDirectory(string dir) {
			dir = dir.Replace('\\','/');
			if (dir[dir.Length-1] != '/')
				dir += '/';
			
			saveDirectory = dir;
			saveDirectory += "CryptoAI/";
		}
		
		public static Genome LoadBestGenome(string dir) { SetDirectory(dir); return LoadBestGenome(); }
		public static Genome LoadBestGenome() {
			if (saveDirectory == "") {
				Console.ForegroundColor = ConsoleColor.Red;
				PrintFormattedMsg("CryptoAI","ERROR","Could not load best genome. LoadBestGenome was called without setting save directory");
				quit();
			}
			
			if (saveDirectory == "") {
				Console.ForegroundColor = ConsoleColor.Red;
				PrintFormattedMsg("CryptoAI","ERROR","Could not load best genome. LoadBestGenome was called without setting save directory");
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
						PrintFormattedMsg("AI Config","LOG","Loading best genome from primary save file");
						loadDirectory = netSaveDir;
					} else if (result == 1) {
						PrintFormattedMsg("AI Config","WARNING","Primary save file corrupted. Loading best genome from backup save file");
						loadDirectory = netBackupDir;
					} else if (result == 2) {
						PrintFormattedMsg("AI Config","WARNING","Backup save file corrupted. Attempting file repair");
						saveFileRepair();
						PrintFormattedMsg("AI Config","Log","Loading best genome from primary save file");
						loadDirectory = netSaveDir;
					} else {
						PrintFormattedMsg("AI Config","ERROR","Invalid save status detected in save directory");
						quit();
					}
				} catch {
					//null
					PrintFormattedMsg("AI Config","WARNING","No save status detected. Loading best genome from primary save file");
					loadDirectory = netSaveDir;
				}
			} else {
				PrintFormattedMsg("CryptoAI","WARNING","Could not find save status file. Using default option");
				if (Directory.Exists(netSaveDir)) {
					PrintFormattedMsg("AI Config","LOG","Loading best genome from primary save file");
					loadDirectory = netSaveDir;
				} else if (Directory.Exists(netBackupDir)) {
					PrintFormattedMsg("AI Config","LOG","Loading best genome from backup save file");
					loadDirectory = netBackupDir;
				} else {
					PrintFormattedMsg("CryptoAI","ERROR","Could not load best genome. No save file detected in directory");
					quit();
				}
			}
			
			//Read from the text file to find which ID was best
			string bestIDDirectory = loadDirectory + "Best Genome.txt";
			if (!File.Exists(bestIDDirectory)) {
				PrintFormattedMsg("CryptoAI","ERROR","Could not load best genome. Could not locate best genome ID file at position: ");
				PrintFormattedMsg("CryptoAI","ERROR"," - " + bestIDDirectory);
				quit();
			}
			
			int bestID = int.Parse(File.ReadAllText(bestIDDirectory));
			return LoadGenome(loadDirectory + "Genome " + bestID.ToString() + ".json");
		}
		
		public static Genome LoadGenome(string dir) {
			Genome g = new Genome();
			
			if (!dumpAndPump) {
				g.GenomeType = File.ReadAllText(dir + "/Genome Activation Type.txt").Replace("\t","").Replace("\n","").Replace(" ","");
				
				string[] allNodeDirs = Directory.GetFiles(dir,"Node*.json");
				g.nodes = new Node[allNodeDirs.Length];
				for(int i = 0; i < g.nodes.Length; i++) {
					g.nodes[i].ID = i;
				}
				
				//Just sort the node directories in ascending order
				for (int i = 0; i < allNodeDirs.Length; i++) {
					allNodeDirs[i] = dir + "/Node " + i.ToString() + ".json";
				}
				
				foreach (string nodeDir in allNodeDirs) {
					JObject nodeJSON = JObject.Parse(File.ReadAllText(nodeDir));
					int ID = (int)nodeJSON["ID"];
					
					Node n = new Node(ID,new NodeConnection[0]);
					//Does this node already exist in g.nodes? If so, overwrite "n"
					for(int i = 0; i < g.nodes.Length; i++) {
						if (g.nodes[i].ID == ID)
							n = g.nodes[i];
					}
					
					n.NodeActivationType = g.GenomeType;
					//n.NodeActivationType = (string)nodeJSON["nAT"];
					
					n.tT = (float)nodeJSON["tT"];
					n.tS = (float)nodeJSON["tS"];
					n.nII = (bool)nodeJSON["nII"];
					n.nIO = (bool)nodeJSON["nIO"];
					n.nIV = (float)nodeJSON["nIV"];
					n.pO = (float)nodeJSON["pO"];
					
					if (!n.nII) {
						List<NodeConnection> nC_List = new List<NodeConnection>();
						
						//Now that we have all the other required data, just figure out the node connections
						JArray cN_JSON = JArray.Parse(nodeJSON["cN"].ToString());
						foreach(JObject tempNode in cN_JSON) {
							nC_List.Add(
								new NodeConnection(
									g.nodes[(int)tempNode["ID"]],
									(int)tempNode["W"]
								)
							);
						}
						
						n.cN = new NodeConnection[nC_List.Count()];
						for(int i = 0; i < nC_List.Count(); i++) { n.cN[i] = nC_List[i]; }
					}
					
					g.nodes[ID] = n;
					if (n.nII) { for (int i = 0; i < g.inputNodes.Length;  i++) { g.inputNodes[i]  = n; } }
					if (n.nIO) { for (int i = 0; i < g.outputNodes.Length; i++) { g.outputNodes[i] = n; } }
				}
			} else {
				JObject rawGenomeData = (JObject)JsonConvert.DeserializeObject(File.ReadAllText(dir));
				g.nodes = new Node[rawGenomeData.Count];
				
				PrintFormattedMsg("CryptoAI","ERROR","Could not complete loading network in dumpAndPump mode. W.I.P");
				quit();
			}
			
			return g;
		}
		
		public static Network LoadNetwork(string dir) { SetDirectory(dir); return LoadNetwork(); }
		public static Network LoadNetwork() {
			if (saveDirectory == "") {
				Console.ForegroundColor = ConsoleColor.Red;
				PrintFormattedMsg("CryptoAI","ERROR","Could not load network. LoadNetwork was called without setting save directory");
				quit();
			}
			
			PrintFormattedMsg("AI Config","WARNING","Loading AI network can take several minutes...");
			
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
						PrintFormattedMsg("AI Config","LOG","Loading AI network from primary save");
						loadDirectory = netSaveDir;
					} else if (result == 1) {
						PrintFormattedMsg("AI Config","WARNING","Primary save corrupted. Loading AI network from backup save");
						loadDirectory = netBackupDir;
					} else if (result == 2) {
						PrintFormattedMsg("AI Config","WARNING","Backup save corrupted. Attempting file repair");
						saveFileRepair();
						PrintFormattedMsg("AI Config","Log","Loading AI network from primary save");
						loadDirectory = netSaveDir;
					} else {
						PrintFormattedMsg("AI Config","ERROR","Invalid save status detected in save directory. Defaulting to primary save");
						quit();
					}
				} catch {
					//null
					PrintFormattedMsg("AI Config","WARNING","Error reading from save status file. Defaulting to primary save");
					loadDirectory = netSaveDir;
					File.WriteAllText(netStatusFile,"0");
					PrintFormattedMsg("AI Config","SUCCESS","Overwrote corrupt data in save file");
				}
			} else {
				PrintFormattedMsg("CryptoAI","WARNING","Could not find save status file. Using default option");
				if (Directory.Exists(netSaveDir)) {
					PrintFormattedMsg("AI Config","LOG","Loading AI network from primary save");
					loadDirectory = netSaveDir;
				} else if (Directory.Exists(netBackupDir)) {
					PrintFormattedMsg("AI Config","LOG","Loading AI network from backup save");
					loadDirectory = netBackupDir;
				} else {
					PrintFormattedMsg("CryptoAI","ERROR","Could not load network. No save folder detected in directory");
					quit();
				}
			}
			
			string[] allGenomeDirectories = null;
			Network N = new Network();
			if (dumpAndPump) {
				allGenomeDirectories = Directory.GetFiles(loadDirectory,"*.json");
			} else {
				allGenomeDirectories = Directory.GetDirectories(loadDirectory,"*",SearchOption.TopDirectoryOnly);
			}
			
			N.genomes = new Genome[allGenomeDirectories.Length];
			
			Stopwatch stopwatch = new Stopwatch();
			stopwatch.Start();
			
			List<ThreadDataContainer3> TDC_List = new List<ThreadDataContainer3>();
			bool run = true;
			int genomeIndex = 0;
			int maxThreadCount = 32;
			int currentThreadCount = 0;
			while(run) {
				while (currentThreadCount < maxThreadCount) {
					if(genomeIndex == N.genomes.Length) { run = false; break; }
				
					//HERE WE WANT TO ACTUALLY START THE THREAD PROCESS
					ThreadClass p = new ThreadClass();
					ThreadDataContainer3 TDC = new ThreadDataContainer3();
					
					TDC.g = new Genome();
					TDC.dir = allGenomeDirectories[genomeIndex];
					TDC.ID = genomeIndex;
					TDC_List.Add(TDC);
					Thread workerThread = new Thread(p.LoadGenome_CPUMultithreaded);  
					workerThread.Start(TDC);
						
					currentThreadCount++;
					genomeIndex++;
				}
				
				if (run) {
					for (int x = 0; x < TDC_List.Count; x++) {
						if (TDC_List[x].threadCompletionStatus) {
							N.genomes[TDC_List[x].ID] = TDC_List[x].g;
							TDC_List.RemoveAt(x);
							currentThreadCount--;
							x--;
							if (once2) {
								once2 = false;
								float predictedTime = stopwatch.Elapsed.Milliseconds * (float)N.genomes.Length/(float)maxThreadCount;
								//PrintFormattedMsg("AI Config","DEBUG","Predicted time for this process: " + predictedTime);
								stopwatch.Stop();
							}
						}
					}
				}
			}
			while(TDC_List.Count > 0) {
				for (int x = 0; x < TDC_List.Count; x++) {
					if (TDC_List[x].threadCompletionStatus) {
						N.genomes[TDC_List[x].ID] = TDC_List[x].g;
						TDC_List.RemoveAt(x);
						currentThreadCount--;
						x--;
						if (once2) {
							once2 = false;
							float predictedTime = stopwatch.Elapsed.Milliseconds * (float)N.genomes.Length/(float)maxThreadCount;
							//PrintFormattedMsg("AI Config","DEBUG","Predicted time for this process: " + predictedTime);
							stopwatch.Stop();
						}
					}
				}
			}
			
			PrintFormattedMsg("CryptoAI","SUCCESS","Loaded AI network");
			return N;
		}
		
		public static void saveFileRepair() {
			
			PrintFormattedMsg("File Repair","ERROR","Could not repair save data. Function is W.I.P and therefore incomplete");
			quit();
		}
		
		public static bool clearSave() { return clearSave(true); }
		public static bool clearSave(bool askUser) {
			//Delete the save directory from the disk. Completely wipe it
			if (askUser) {
				PrintFormattedMsg("CryptoAI","WARNING","Are you absolutely certain you want to clear the saved AI network? (Y/N)");
				char userInput = Console.ReadKey(true).KeyChar;
				while (userInput != 'y' && userInput != 'n') { userInput = Console.ReadKey(true).KeyChar; }
				if (userInput == 'n') {
					PrintFormattedMsg("CryptoAI","LOG","User cancelled save data deletion");
					return false;
				}
			}
			
			PrintFormattedMsg("CryptoAI","PROCESS","Deleting AI Network save data from disk permanently");
			Directory.Delete(saveDirectory,true);
			PrintFormattedMsg("CryptoAI","SUCCESS","Deleted AI save data");
			Directory.CreateDirectory(saveDirectory);
			return true;
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
			
			float sizeOfSingleGenome = JsonConvert.SerializeObject(N.genomes[0]).Length;
			float genomeCount = N.inputNodesCount + N.outputNodesCount + N.hiddenLayerCount*N.hiddenLayerWidth;
			float sizeOnDisk = genomeCount*2*sizeOfSingleGenome/1000000000;
			Console.WriteLine(N.genomes[0].nodes.Length);
			PrintFormattedMsg("CryptoAI","DEBUG","Saving AI network. This process using the JSON serializer would be estimated to take up: " + sizeOnDisk.ToString() + " GB of disk space");
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
					TDC.GenomeCount = N.genomes.Length;
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
			
			string[] genomeActivationTypes = new string[] { "classic","neural" };
			AI_Internal_Core.getRandomFloat();
			
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
					
					int randomIndex = AI_Internal_Core.rand.Next(genomeActivationTypes.Length);
					TDC.NodeActivationType = genomeActivationTypes[randomIndex];
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
					PrintFormattedMsg("AI Config","ERROR","Genome " + (i+1).ToString() + "/" + N.genomes.Length.ToString() + ":\t\tStatus - Null");
					nullDetected++;
				} else {
					PrintFormattedMsg("AI Config","SUCCESS","Genome " + (i+1).ToString() + "/" + N.genomes.Length.ToString() + ":\t\tStatus - Functional\t\tID: " + N.genomes[i].ID);
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
			g.inputNodes = new Node[TDC.inputNodes];
			g.outputNodes = new Node[TDC.outputNodes];
			g.GenomeType = TDC.NodeActivationType;
			
			//Create Input Nodes
			Node[] previousLayer = new Node[TDC.inputNodes];
			for (int i = 0; i < TDC.inputNodes; i++) {
				Node n = new Node(i,null);
				n.nII = true;
				n.NodeActivationType = TDC.NodeActivationType;
				g.inputNodes[i] = n;
				g.nodes[i] = n;
				previousLayer[i] = n;
			}
			
			//Create Hidden Layers
			int startingIndex = TDC.inputNodes;
			for(int layer = 0; layer < TDC.hiddenLayerCount; layer++) {
				for(int i = 0; i < TDC.nodesPerHiddenLayer; i++) {
					NodeConnection[] nc = new NodeConnection[previousLayer.Length];
					for (int connection = 0; connection < nc.Length; connection++) {
						nc[connection] = new NodeConnection(previousLayer[connection],AI_Internal_Core.getRandomFloat());
					}
					
					Node n = new Node(startingIndex + i + layer*TDC.nodesPerHiddenLayer,nc);
					n.NodeActivationType = TDC.NodeActivationType;
					n.tT = AI_Internal_Core.getRandomFloat();
					n.tS = AI_Internal_Core.getRandomFloat();
					g.nodes[startingIndex + i + layer*TDC.nodesPerHiddenLayer] = n;	//------------------------------------------------------------
				}
			}
			
			//Create output layers
			startingIndex += TDC.nodesPerHiddenLayer*TDC.hiddenLayerCount;
			for (int i = 0; i < TDC.outputNodes; i++) {
				NodeConnection[] nc = new NodeConnection[previousLayer.Length];
				for (int connection = 0; connection < nc.Length; connection++) {
					nc[connection] = new NodeConnection(previousLayer[connection],AI_Internal_Core.getRandomFloat());
				}
					
				Node n = new Node(startingIndex + i,nc);
				n.NodeActivationType = TDC.NodeActivationType;
				n.tT = AI_Internal_Core.getRandomFloat();
				n.tS = AI_Internal_Core.getRandomFloat();
				n.nIO = true;
				g.nodes[i + startingIndex] = n;
				g.outputNodes[i] = n;
			}
			
			TDC.threadOutput = g;
			TDC.threadCompletionStatus = true;
		}
		
		public void SaveGenome_CPUMultithreaded(object data) {
			ThreadDataContainer2 TDC = (ThreadDataContainer2)data;
			
			string genomeDirectory = TDC.dir;
			
			float bytesTakenByGenome = 0;
			
			if (NetworkInterface.dumpAndPump) {
				//Console.WriteLine(genomeDirectory + "Genome " + TDC.g.ID + ".json");
				
				string nodeFileData = "[\n\t";
				for(int i = 0; i < TDC.g.nodes.Length; i++) {
					Node n = TDC.g.nodes[i];
					nodeFileData += "{\n";
					nodeFileData += "\t\t\"ID\":" + n.ID.ToString() + ",\n";
					nodeFileData += "\t\t\"tT\":" + n.tT.ToString() + ",\n";
					nodeFileData += "\t\t\"tS\":" + n.tS.ToString() + ",\n";
					nodeFileData += "\t\t\"nII\":\"" + n.nII.ToString() + "\",\n";
					nodeFileData += "\t\t\"nIO\":\"" + n.nIO.ToString() + "\",\n";
					nodeFileData += "\t\t\"nIV\":" + n.nIV.ToString() + ",\n";
					nodeFileData += "\t\t\"nAT\":\"" + n.NodeActivationType + "\",\n";
					nodeFileData += "\t\t\"pO\":" + n.pO.ToString();
					
					if (n.cN == null) {
						//There are no connected nodes
						nodeFileData += "\n\t}";
					} else if (n.cN.Length == 0) {
						//There are no connected nodes
						nodeFileData += "\n\t}";
					} else {
						//There are connected nodes
						nodeFileData += ",\n";
						nodeFileData += "\t\t\"cN\":[\n";
						
						for(int x = 0; x < n.cN.Length; x++) {
							nodeFileData += "\t\t\t{\"ID\":" + n.cN[x].n.ID.ToString() + ",\"W\":" + n.cN[x].w + "}";
							if (x + 1 != n.cN.Length)
								nodeFileData += ",";
							nodeFileData += "\n";
						}
						
						nodeFileData += "\t\t]";
						nodeFileData += "\n\t}";
					}
					
					if (i + 1 != TDC.g.nodes.Length)
						nodeFileData += ",";
				}
				nodeFileData += "]";
				
				File.WriteAllText(genomeDirectory + "Genome " + TDC.g.ID + ".json",nodeFileData);
			} else {
				//Console.WriteLine(genomeDirectory + "Genome " + TDC.g.ID + "/");
				Directory.CreateDirectory(genomeDirectory + "Genome " + TDC.g.ID + "/");
				File.WriteAllText(genomeDirectory + "Genome " + TDC.g.ID + "/Genome Activation Type.txt",TDC.g.GenomeType);
				for(int i = 0; i < TDC.g.nodes.Length; i++) {
					Node n = TDC.g.nodes[i];
					string nodeFileData = "{\n";
					nodeFileData += "\t\"ID\":" + n.ID.ToString() + ",\n";
					nodeFileData += "\t\"tT\":" + n.tT.ToString() + ",\n";
					nodeFileData += "\t\"tS\":" + n.tS.ToString() + ",\n";
					nodeFileData += "\t\"nII\":\"" + n.nII.ToString() + "\",\n";
					nodeFileData += "\t\"nIO\":\"" + n.nIO.ToString() + "\",\n";
					nodeFileData += "\t\"nIV\":" + n.nIV.ToString() + ",\n";
					nodeFileData += "\t\"nAT\":\"" + n.NodeActivationType + "\",\n";
					nodeFileData += "\t\"pO\":" + n.pO.ToString();
					if (n.cN == null) {
						//There are no connected nodes
						nodeFileData += "\n}";
					} else if (n.cN.Length == 0) {
						//There are no connected nodes
						nodeFileData += "\n}";
					} else {
						//There are connected nodes
						nodeFileData += ",\n";
						nodeFileData += "\t\"cN\":[\n";
						
						for(int x = 0; x < n.cN.Length; x++) {
							nodeFileData += "\t\t{\"ID\":" + n.cN[x].n.ID.ToString() + ",\"W\":" + n.cN[x].w + "}";
							if (x + 1 != n.cN.Length)
								nodeFileData += ",";
							nodeFileData += "\n";
						}
						
						nodeFileData += "\t]\n}";
					}
					
					File.WriteAllText(genomeDirectory + "Genome " + TDC.g.ID + "/Node " + n.ID.ToString() + ".json",nodeFileData);
					bytesTakenByGenome += nodeFileData.Length;
				}
				
				if (NetworkInterface.once) {
					NetworkInterface.once = false;
					bytesTakenByGenome/=10000000;
					NetworkInterface.PrintFormattedMsg("AI Config","DEBUG","Total AI network predicted size on disk: " + bytesTakenByGenome.ToString() + " GB");
				}
			}
			
			TDC.threadCompletionStatus = true;
		}
		
		public void LoadGenome_CPUMultithreaded(object data) {
			ThreadDataContainer3 TDC = (ThreadDataContainer3)data;
			Genome g = TDC.g;
			
			if (!NetworkInterface.dumpAndPump) {
				g.GenomeType = File.ReadAllText(TDC.dir + "/Genome Activation Type.txt").Replace("\t","").Replace("\n","").Replace(" ","");
				
				string[] allNodeDirs = Directory.GetFiles(TDC.dir,"Node*.json");
				g.nodes = new Node[allNodeDirs.Length];
				for(int i = 0; i < g.nodes.Length; i++) {
					g.nodes[i].ID = i;
				}
				
				//Just sort the node directories in ascending order
				for (int i = 0; i < allNodeDirs.Length; i++) {
					allNodeDirs[i] = TDC.dir + "/Node " + i.ToString() + ".json";
				}
				
				foreach (string nodeDir in allNodeDirs) {
					JObject nodeJSON = JObject.Parse(File.ReadAllText(nodeDir));
					int ID = (int)nodeJSON["ID"];
					
					Node n = new Node(ID,new NodeConnection[0]);
					//Does this node already exist in g.nodes? If so, overwrite "n"
					for(int i = 0; i < g.nodes.Length; i++) {
						if (g.nodes[i].ID == ID)
							n = g.nodes[i];
					}
					
					n.NodeActivationType = g.GenomeType;
					//n.NodeActivationType = (string)nodeJSON["nAT"];
					
					n.tT = (float)nodeJSON["tT"];
					n.tS = (float)nodeJSON["tS"];
					n.nII = (bool)nodeJSON["nII"];
					n.nIO = (bool)nodeJSON["nIO"];
					n.nIV = (float)nodeJSON["nIV"];
					n.pO = (float)nodeJSON["pO"];
					
					if (!n.nII) {
						List<NodeConnection> nC_List = new List<NodeConnection>();
						
						//Now that we have all the other required data, just figure out the node connections
						JArray cN_JSON = JArray.Parse(nodeJSON["cN"].ToString());
						foreach(JObject tempNode in cN_JSON) {
							nC_List.Add(
								new NodeConnection(
									g.nodes[(int)tempNode["ID"]],
									(int)tempNode["W"]
								)
							);
						}
						
						n.cN = new NodeConnection[nC_List.Count()];
						for(int i = 0; i < nC_List.Count(); i++) { n.cN[i] = nC_List[i]; }
					}
					
					g.nodes[ID] = n;
					if (n.nII) { for (int i = 0; i < g.inputNodes.Length;  i++) { g.inputNodes[i]  = n; } }
					if (n.nIO) { for (int i = 0; i < g.outputNodes.Length; i++) { g.outputNodes[i] = n; } }
				}
			} else {
				JObject rawGenomeData = (JObject)JsonConvert.DeserializeObject(File.ReadAllText(TDC.dir));
				g.nodes = new Node[rawGenomeData.Count];
				
				NetworkInterface.PrintFormattedMsg("CryptoAI","ERROR","Could not complete loading network in dumpAndPump mode. W.I.P");
				NetworkInterface.quit();
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
		public string NodeActivationType;
		public Genome threadOutput;
	}
	
	public class ThreadDataContainer2 {
		public bool threadCompletionStatus = false;
		public Genome g;
		public int ID;
		public string dir;
		public int GenomeCount;
	}
	
	public class ThreadDataContainer3 {
		public bool threadCompletionStatus = false;
		public Genome g;
		public string dir;
		public int ID;
	}
}



















