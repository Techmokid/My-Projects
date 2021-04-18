using System;
using System.IO;
using System.Threading;
using System.Collections.Generic;
using System.Text.Json;
using System.Text.Json.Serialization;

using Display;

namespace NEAT_AI {
    public static class Random
    {
        public static System.Random rand;
		public static ulong currentNodeIndex;
		public static ulong currentGeneIndex;
		
        public static void SetupRandom()
        {
            rand = new System.Random();
        }
		
		public static ulong getNextNodeID() {
			currentNodeIndex++;
			return currentNodeIndex;
		}
		
		public static ulong getNextGeneID() {
			currentGeneIndex++;
			return currentGeneIndex;
		}
    }
	
	[Serializable]
    public class Node
    {
		public ulong ID   { get; set; }
        public string node_type  { get; set; }
		//public string algorithm_type  { get; set; }
        public List<Node> connected_nodes  { get; set; }
        public List<float> connection_weights  { get; set; }
        public float node_input  { get; set; }
        public float upperTriggerThreshold  { get; set; }
        public float lowerTriggerThreshold  { get; set; }
		public float precalculatedOutput = -99999;
		
        public Node(string nodeType)
        {
            node_type = nodeType;
			ID = Random.getNextNodeID();
			connected_nodes = new List<Node>();
			connection_weights = new List<float>();
			node_input = -1000;
			upperTriggerThreshold = 100000000;
			lowerTriggerThreshold = -100000000;
			
			//List<string> node_algorithm_types = new List<string>{ "add","sub","mult","div","sin"};;
			//algorithm_type = node_algorithm_types[Random.rand.Next(node_algorithm_types.Count)];
        }
		
		public void saveNode(string saveLocation) {
			FileInfo fi = new FileInfo(saveLocation); 
			using (StreamWriter sw = fi.CreateText()) {
				sw.WriteLine("ID:" + ID.ToString());
				sw.WriteLine("node_type:" + node_type.ToString());
				//sw.WriteLine("algorithm_type:" + algorithm_type.ToString());
				sw.WriteLine("upperTriggerThreshold:" + upperTriggerThreshold.ToString());
				sw.WriteLine("lowerTriggerThreshold:" + lowerTriggerThreshold.ToString());
				
				sw.WriteLine("Connected Nodes:{");
			
				for(int i = 0; i < connected_nodes.Count; i++) {
					string temp = "\tID:" + connected_nodes[i].ID.ToString() + "|";
					temp += "\tWeight:" + connection_weights[i].ToString();
					
					if (i != connected_nodes.Count - 1) { sw.WriteLine(temp + ","); } else { sw.WriteLine(temp); }
				}
				
				sw.WriteLine("}");
			}
		}
		
        public float GetNodeOutput() { return GetNodeOutput(new List<Node>()); }
        public float GetNodeOutput(List<Node> nodeManager)
        {
			if (precalculatedOutput != -99999) { return precalculatedOutput; }
            if (nodeManager.Contains(this)) { return -1000; }
            nodeManager.Add(this);

            if (node_type == "input") { return node_input; }

            float result = 0;
            int loops = 0;
            foreach (Node i in connected_nodes)
            {
                float temp = connected_nodes[loops].GetNodeOutput(nodeManager) * connection_weights[loops];
                //if ((temp < upperTriggerThreshold) && (temp > lowerTriggerThreshold)) { result += temp; }
				result += temp;
                loops += 1;
            }

            //return (float)Math.Tanh(result);
			precalculatedOutput = -result;
			return precalculatedOutput;
        }

        public void SetNodeInput(float x) { node_input = x; }
    }
	
	[Serializable]
    public class Genome
    {
		public ulong ID  { get; set; }
        public float fitness  { get; set; }
        public int generationsSurvived  { get; set; }
        public List<Node> genome  { get; set; }
        public Genome orig  { get; set; }

        public Genome() {
			genome = new List<Node>();
			generationsSurvived = 0;
			fitness = 0;
			ID = Random.getNextGeneID();
			orig = this;
		}
		
        public Genome(Genome _orig) {
			orig = _orig;
			ID = Random.getNextGeneID();
			fitness = _orig.fitness;
			generationsSurvived = _orig.generationsSurvived;
			genome = _orig.genome;
		}
		
		public void saveGenome(string saveLocation) {
			FileInfo fi = new FileInfo(saveLocation + "/Genome Readout.txt"); 
			using (StreamWriter sw = fi.CreateText()) {
				sw.WriteLine("ID:" + ID.ToString());
				sw.WriteLine("fitness:" + fitness.ToString());
				sw.WriteLine("generationsSurvived:" + generationsSurvived.ToString());
			}
			
			foreach(Node n in genome) {
				if (File.Exists(saveLocation + "/Node ID " + n.ID + ".txt")) {
					throw new Exception("NODE ID CONFLICT");
				}
				
				n.saveNode(saveLocation + "/Node ID " + n.ID + ".txt");
			}
		}
		
        public void ClearGenomeData() { genome = new List<Node>(); }
		
		public void GenerateNewPrepopulatedGenome(int num_inputs, int num_outputs, int numberOfLayers, int nodesPerLayer) {
			ClearGenomeData();
			
			//Set the first input nodes
			for (int i = 0; i < num_inputs; i++) { this.genome.Add(new Node("input")); }
			
			//Set the internal nodes
			List<Node> previousNodes = this.genome;
			List<Node> currentNodes = new List<Node>();
			for (int node_layer = 0; node_layer < numberOfLayers; node_layer++) {
				//Iterate over each layer we require
				for (int node_index = 0; node_index < nodesPerLayer; node_index++) {
					//For each node in the layer, create it, then connect it to all nodes in the previous layer
					Node tempNode = new Node("hidden");
					currentNodes.Add(tempNode);
					
					//Console.WriteLine(previousNodes.Count);
					foreach (Node previousNode in previousNodes) {
						tempNode.connected_nodes.Add(previousNode);
						tempNode.connection_weights.Add((float)Random.rand.NextDouble() * 2 - 1);
					}
					
					//this.genome.Add(tempNode);
				}
				
				//Simply move all values from currentNodes to previousNodes, then clear currentNodes2
				previousNodes = new List<Node>();
				foreach (Node i in currentNodes) {
					previousNodes.Add(i);
					this.genome.Add(i);
				}
				
				currentNodes = new List<Node>();
			}
			
            for (int i = 0; i < num_outputs; i++) {
				Node tempNode = new Node("output");
				
				foreach (Node previousNode in previousNodes) {
					tempNode.connected_nodes.Add(previousNode);
					tempNode.connection_weights.Add((float)Random.rand.NextDouble() * 2 - 1);
				}
				
				this.genome.Add(tempNode);
			}
		}
		
        public void GenerateNewRandomGenome(int inputs, int outputs, int hidden, int connections)
        {
            ClearGenomeData();

            for (int i = 0; i < inputs; i++) { this.genome.Add(new Node("input")); }
            for (int i = 0; i < outputs; i++) { this.genome.Add(new Node("output")); }
            for (int i = 0; i < hidden; i++) { this.genome.Add(new Node("hidden")); }
            for (int i = 0; i < connections; i++)
            {
                bool runAgain = true;
                while (runAgain)
                {
                    int index_1 = Random.rand.Next(0, this.genome.Count);
                    int index_2 = Random.rand.Next(0, this.genome.Count);

                    while (index_1 == index_2) { index_2 = Random.rand.Next(0, this.genome.Count); }

                    Node test_node_1 = this.genome[index_1];
                    Node test_node_2 = this.genome[index_2];
                    test_node_1.connected_nodes.Add(test_node_2);
                    test_node_1.connection_weights.Add((float)Random.rand.NextDouble() * 2 - 1);
                    if (!IsGenomeStable())
                    {
                        int newPosition = test_node_1.connected_nodes.Count - 1;
                        test_node_1.connected_nodes.RemoveAt(newPosition);
                        test_node_1.connection_weights.RemoveAt(newPosition);

                        test_node_2.connected_nodes.Add(test_node_1);
                        test_node_2.connection_weights.Add((float)Random.rand.NextDouble() * 2 - 1);
                        if (!IsGenomeStable())
                        {
                            int newPos = test_node_2.connected_nodes.Count - 1;
                            test_node_2.connected_nodes.RemoveAt(newPos);
                            test_node_2.connection_weights.RemoveAt(newPos);
                        }
                        else { runAgain = false; }
                    }
                    else { runAgain = false; }
                }
            }
        }

        public List<Node> GetInputNodes()
        {
            List<Node> result = new List<Node>();
            foreach (Node i in genome)
            {
                if (i.node_type == "input") { result.Add(i); }
            }
            return result;
        }

        public List<Node> GetOutputNodes()
        {
            List<Node> result = new List<Node>();
            foreach (Node i in genome)
            {
                if (i.node_type == "output") { result.Add(i); }
            }
            return result;
        }

        public List<Node> GetHiddenNodes()
        {
            List<Node> result = new List<Node>();
            foreach (Node i in genome)
            {
                if (i.node_type == "hidden") { result.Add(i); }
            }
            return result;
        }

        public bool IsGenomeStable()
        {
            foreach (Node i in GetOutputNodes())
            {
                if (i.GetNodeOutput() == -1000) { return false; }
            }

            return true;
        }

        public List<float> GetOutput(Network nn, List<float> inputValues)
        {
			foreach (Node n in genome) { n.precalculatedOutput = -99999; }
		
			if (GetInputNodes().Count == 0) {
				List<float> result2 = new List<float>();
				for(int i = 0; i < nn.num_inputs; i++) { result2.Add(0.00f); }
				return result2;
			}
			
            if (inputValues.Count != GetInputNodes().Count)
            {
				string val = "Number Of Supplied Inputs Does Not Match AI Configuration! \nExpected: ";
				val += GetInputNodes().Count.ToString();
				val += " but got ";
				val += inputValues.Count.ToString();
                throw new System.InvalidOperationException(val);
            }

            int index = 0;
            foreach (Node node_object in GetInputNodes())
            {
                node_object.SetNodeInput(inputValues[index]);
                index++;
            }

            index = 0;
            List<float> result = new List<float>();
            foreach (Node node_object in GetOutputNodes())
            {
                result.Add(node_object.GetNodeOutput());
                index++;
            }

            return result;
        }
    }
	
	[Serializable]
    public class Network
    {
		public string trainingDataPath  { get; set; }
        public bool printTrainingTimes  { get; set; }
        public List<Genome> genomes  { get; set; }
        List<Genome> previousValidGenomes  { get; set; }
		bool silenceOutput;

        //NEAT Variables
        public string fitness_criterion  { get; set; }
        public int pop_size  { get; set; }
        public float bias_max_value  { get; set; }
        public float bias_min_value  { get; set; }
        public float bias_mutate_rate  { get; set; }
        public float conn_add_prob  { get; set; }
        public float conn_delete_prob  { get; set; }
        public float node_add_prob  { get; set; }
        public float node_delete_prob  { get; set; }
        public int num_inputs  { get; set; }
        public int num_outputs  { get; set; }
        public int num_hidden  { get; set; }
        public int num_connections  { get; set; }
        public float weight_mutate_prob  { get; set; }
        public float weight_replace_prob  { get; set; }
        public float survival_threshold  { get; set; }
        public int minimum_network_size  { get; set; }
		public int numberOfLayers  { get; set; }
		public int nodesPerLayer  { get; set; }
		public bool prepopulated  { get; set; }
		
        public Network(string folderPath, bool _printTrainingTimes, bool prepopulate, bool _silenceOutput)
        {
			genomes = new List<Genome>();
			previousValidGenomes = new List<Genome>();
			printTrainingTimes = _printTrainingTimes;
			trainingDataPath = folderPath;
			using (FileStream fs = File.Create(trainingDataPath + "/SaveData/override training values.txt")) {}
			
            Random.SetupRandom();
			
			if (!_silenceOutput) {
				Console.WriteLine("[NEAT AI][Info]: Setting up Variables. Please be aware this can take quite some time depending on config");
			}
			
            LiveConfigUpdate(folderPath + "/SaveData/config.txt");
			
			if (prepopulate) {
				prepopulated = true;
				GenerateNewPrepopulatedNetwork();
			} else {
				GenerateNewRandomNetwork();
			}
			
			if (!_silenceOutput) {
				Console.WriteLine("[NEAT AI][Info]: Population size set to " + pop_size.ToString());
				Console.WriteLine("[NEAT AI][Info]: Input count " + num_inputs.ToString());
				Console.WriteLine("[NEAT AI][Info]: Output count " + num_outputs.ToString());
			}
			
			silenceOutput = _silenceOutput;
		}
		
		public Genome loadBestGenome() {
			while (File.Exists(trainingDataPath + "/SaveData/saveLock.loc")) { Thread.Sleep(1000); }
			
			//if (genomes.Count != 0) { throw new Exception("Attempting to load network into pre-existing populated AI"); }
			genomes = new List<Genome>();
			
			string networkDataPath = trainingDataPath + "/SaveData/Saved AI Network 1";
			StreamReader file = new StreamReader(trainingDataPath + "/SaveData/saveStatus.txt");
            int saveStatus = int.Parse(file.ReadLine());
			if ((saveStatus == 0) || (saveStatus == 2)) {} else if (saveStatus == 1) {
				networkDataPath = trainingDataPath + "/SaveData/Saved AI Network 2";
			} else {
				throw new Exception("Error reading from NEAT AI save status file!");
			} //Code-Marker
			
			StreamReader networkReadout = new StreamReader(networkDataPath + "/Network Readout.txt");
			pop_size = (int)forcedStringToFloat(networkReadout.ReadLine());
			num_inputs = (int)forcedStringToFloat(networkReadout.ReadLine());
			num_outputs = (int)forcedStringToFloat(networkReadout.ReadLine());
			
			string genomePath = networkDataPath + "/Best Genome";
			StreamReader genomeReadout = new StreamReader(genomePath + "/Genome Readout.txt");
				
			Genome tempGenome = new Genome();
			tempGenome.ID = (ulong)forcedStringToFloat(genomeReadout.ReadLine());
			tempGenome.fitness = forcedStringToFloat(genomeReadout.ReadLine());
			tempGenome.generationsSurvived = (int)forcedStringToFloat(genomeReadout.ReadLine());
				
			//Iterate over all nodes
			string[] nodesPath = Directory.GetFiles(genomePath);
			foreach(string nodePath in nodesPath) {
				if (nodePath.Replace("\\","/") != genomePath.Replace("\\","/") + "/Genome Readout.txt") {
					StreamReader nodeData = new StreamReader(nodePath);
						
					//Find node with that matching ID. If it does not exist, create it
					int ID = (int)forcedStringToFloat(nodeData.ReadLine());
					Node tempNode = null;
					for (int index = 0; index < tempGenome.genome.Count; index++) {
						if (tempGenome.genome[index].ID == (ulong)ID) {
							tempNode = tempGenome.genome[index];
							index = tempGenome.genome.Count;
						}
					}
					
					if (tempNode == null) {
						tempNode = new Node("hidden");
						tempNode.ID = (ulong)ID;
						tempGenome.genome.Add(tempNode);
					}
					
					// Set the node type, and threshold values
					string tempStr = nodeData.ReadLine();
					tempNode.node_type = tempStr.Substring(tempStr.LastIndexOf(":") + 1,tempStr.Length - tempStr.LastIndexOf(":") - 1);
					
					tempNode.upperTriggerThreshold = (int)forcedStringToFloat(nodeData.ReadLine());
					tempNode.lowerTriggerThreshold = (int)forcedStringToFloat(nodeData.ReadLine());
						
					if (tempNode.node_type != "input") {
						nodeData.ReadLine();
						
						//Loop over all connected nodes in memory
						while(true) {
							tempStr = nodeData.ReadLine();
							if (tempStr.LastIndexOf("|") < 1) { break; }
							
							int tempNodeID = (int)forcedStringToFloat(tempStr.Split("|")[0]);
							float tempNodeWeight = forcedStringToFloat(tempStr.Split("|")[1]);
							
							//Does that node ID exist? If not, create it
							Node connectedNode = null;
							for (int index = 0; index < tempGenome.genome.Count; index++) {
								if (tempGenome.genome[index].ID == (ulong)tempNodeID) {
									connectedNode = tempGenome.genome[index];
									index = tempGenome.genome.Count;
								}
							}
							
							if (connectedNode == null) {
								Node tempNode2 = new Node("hidden");
								tempNode2.ID = (ulong)tempNodeID;
								tempGenome.genome.Add(tempNode2);
								connectedNode = tempNode2;
							}
							
							//Now that we have the node, simply apply the values
							tempNode.connected_nodes.Add(connectedNode);
							tempNode.connection_weights.Add(tempNodeWeight);
						}
					}
				}
			}
			
			return tempGenome;	//Code-Marker
		}
		
		public void saveNetwork() {
			using (FileStream fs = File.Create(trainingDataPath + "/SaveData/saveLock.loc")) {}
			
			if (!File.Exists(trainingDataPath + "/SaveData/saveStatus.txt")) {
				FileInfo saveStatusFileTemp = new FileInfo(trainingDataPath + "/SaveData/saveStatus.txt"); 
				using (StreamWriter sw = saveStatusFileTemp.CreateText()) { sw.WriteLine("0"); }
			}
			
			//First Pass for corruption detection
			FileInfo saveStatusFile = new FileInfo(trainingDataPath + "/SaveData/saveStatus.txt"); 
			using (StreamWriter sw = saveStatusFile.CreateText()) { sw.WriteLine("1"); }
			
			string saveLocation = trainingDataPath + "/SaveData/Saved AI Network 1";
			if (Directory.Exists(saveLocation)) { Directory.Delete(saveLocation,true); }
			Directory.CreateDirectory(saveLocation);
			
			FileInfo fi = new FileInfo(saveLocation + "/Network Readout.txt"); 
			using (StreamWriter sw = fi.CreateText()) {
				sw.WriteLine("pop_size:" + pop_size.ToString());
				sw.WriteLine("num_inputs:" + num_inputs.ToString());
				sw.WriteLine("num_outputs:" + num_outputs.ToString());
			}
			
			Genome bestFitnessGen = genomes[0];
			foreach (Genome g in genomes) {
				Directory.CreateDirectory(saveLocation + "/Active Genomes/Genome " + g.ID.ToString());
				g.saveGenome(saveLocation + "/Active Genomes/Genome " + g.ID.ToString());
				if (g.fitness > bestFitnessGen.fitness) {
					bestFitnessGen = g;
				}
			}
			bestFitnessGen.saveGenome(saveLocation + "/Best Genome");
			while (true) {
				try {
					File.Delete(trainingDataPath + "/SaveData/saveLock.loc");
					break;
				} catch { Thread.Sleep(500); }
			}
			foreach (Genome g in previousValidGenomes) {
				Directory.CreateDirectory(saveLocation + "/Previous Genomes/Genome " + g.ID.ToString());
				g.saveGenome(saveLocation + "/Previous Genomes/Genome " + g.ID.ToString());
			}
			
			//Second pass 
			using (StreamWriter sw = saveStatusFile.CreateText()) { sw.WriteLine("2"); }
			
			saveLocation = trainingDataPath + "/SaveData/Saved AI Network 2";
			if (Directory.Exists(saveLocation)) { Directory.Delete(saveLocation,true); }
			Directory.CreateDirectory(saveLocation);
			
			fi = new FileInfo(saveLocation + "/Network Readout.txt"); 
			using (StreamWriter sw = fi.CreateText()) {
				sw.WriteLine("pop_size:" + pop_size.ToString());
				sw.WriteLine("num_inputs:" + num_inputs.ToString());
				sw.WriteLine("num_outputs:" + num_outputs.ToString());
			}
			
			bestFitnessGen = genomes[0];
			foreach (Genome g in genomes) {
				Directory.CreateDirectory(saveLocation + "/Active Genomes/Genome " + g.ID.ToString());
				g.saveGenome(saveLocation + "/Active Genomes/Genome " + g.ID.ToString());
				if (g.fitness > bestFitnessGen.fitness) {
					bestFitnessGen = g;
				}
			}
			bestFitnessGen.saveGenome(saveLocation + "/Best Genome");
			
			foreach (Genome g in previousValidGenomes) {
				Directory.CreateDirectory(saveLocation + "/Previous Genomes/Genome " + g.ID.ToString());
				g.saveGenome(saveLocation + "/Previous Genomes/Genome " + g.ID.ToString());
			}
			
			//Finish up
			using (StreamWriter sw = saveStatusFile.CreateText()) { sw.WriteLine("0"); }
		}
		
        public void LiveConfigUpdate(string configPath)
        {
            //NEAT
            fitness_criterion = GetConfigValue(configPath, "fitness_criterion");
            pop_size = int.Parse(GetConfigValue(configPath, "pop_size"));

            //Node Bias
            bias_max_value = float.Parse(GetConfigValue(configPath, "bias_max_value"));
            bias_min_value = float.Parse(GetConfigValue(configPath, "bias_min_value"));
            bias_mutate_rate = float.Parse(GetConfigValue(configPath, "bias_mutate_rate"));

            //Connection Rates
            conn_add_prob = float.Parse(GetConfigValue(configPath, "conn_add_prob"));
            conn_delete_prob = float.Parse(GetConfigValue(configPath, "conn_delete_prob"));

            //Node Rates
            node_add_prob = float.Parse(GetConfigValue(configPath, "node_add_prob"));
            node_delete_prob = float.Parse(GetConfigValue(configPath, "node_delete_prob"));

            //Network Parameters
            num_inputs = int.Parse(GetConfigValue(configPath, "num_inputs"));
            num_outputs = int.Parse(GetConfigValue(configPath, "num_outputs"));
            num_hidden = int.Parse(GetConfigValue(configPath, "num_hidden"));
            num_connections = int.Parse(GetConfigValue(configPath, "num_connections"));

            //Connection Weight
            weight_mutate_prob = float.Parse(GetConfigValue(configPath, "weight_mutate_prob"));
            weight_replace_prob = float.Parse(GetConfigValue(configPath, "weight_replace_prob"));

            //Default Reproduction
            survival_threshold = float.Parse(GetConfigValue(configPath, "survival_threshold"));
            minimum_network_size = int.Parse(GetConfigValue(configPath, "minimum_network_size"));
			
			//Prepopulation Data
			numberOfLayers = int.Parse(GetConfigValue(configPath, "numberOfLayers"));
            nodesPerLayer = int.Parse(GetConfigValue(configPath, "nodesPerLayer"));
        }

        public float Clamp(float n, float minn, float maxn)
        {
            return Math.Max(Math.Min(maxn, n), minn);
        }

        public void GenerateNewRandomNetwork()
        {
            genomes = new List<Genome>();
            for (int i = 0; i < pop_size; i++)
            {
                Genome temp = new Genome();
                temp.GenerateNewRandomGenome(num_inputs, num_outputs, num_hidden, num_connections);
                genomes.Add(temp);
            }
        }
		
		public void GenerateNewPrepopulatedNetwork() {
			if (!silenceOutput) {
				Console.WriteLine("[NEAT AI][Info]: Prepopulating the network");
			}
			genomes = new List<Genome>();
			for (int i = 0; i < pop_size; i++) {
                Genome temp = new Genome();
                temp.GenerateNewPrepopulatedGenome(num_inputs, num_outputs, numberOfLayers, nodesPerLayer);
                genomes.Add(temp);
            }
		}

        string GetConfigValue(string path, string key)
        {
            StreamReader file = new StreamReader(path);
            string line = file.ReadLine();
            while (line != null)
            {
                if (line.Contains(key))
                {
                    line = line.Replace(" ", "");
                    line = line.Replace("\t", "");
                    line = line.Replace("\n", "");

                    return line.Split('=')[1];
                }

                line = file.ReadLine();
            }

            return "";
        }

        public double NextDouble(double minValue, double maxValue)
        {
            double temp = Random.rand.NextDouble() * (maxValue - minValue) + minValue;
            //Console.WriteLine(temp);
            return temp;
        }

        public Genome GetMutatedGenomeCopy(Genome orig)
        {
            Genome result = new Genome(orig);
			
            if (Random.rand.NextDouble() > conn_add_prob && result.genome.Count != 0)
            {
                int index_1 = (int)NextDouble(0, result.genome.Count - 1);
                int index_2 = (int)NextDouble(0, result.genome.Count - 1);
                while (index_1 == index_2)
                {
                    index_2 = (int)NextDouble(0, result.genome.Count - 1);
                }

                Node node_1 = result.genome[index_1];
                Node node_2 = result.genome[index_2];

                node_1.connected_nodes.Add(node_2);
                node_1.connection_weights.Add((float)Random.rand.NextDouble() * 2 - 1);

                if (!result.IsGenomeStable())
                {
                    node_1.connected_nodes.RemoveAt(node_1.connected_nodes.Count - 1);
                    node_1.connection_weights.RemoveAt(node_1.connection_weights.Count - 1);

                    node_2.connected_nodes.Add(node_1);
                    node_2.connection_weights.Add((float)Random.rand.NextDouble() * 2 - 1);
                }
            }

            if (Random.rand.NextDouble() > conn_delete_prob && result.genome.Count != 0)
            {
                if (result.genome.Count > 0)
                {
                    int index = (int)NextDouble(0, result.genome.Count - 1);
                    while (result.genome[index].node_type == "input")
                    {
                        index = (int)NextDouble(0, result.genome.Count - 1);
                    }

                    if (result.genome[index].connected_nodes.Count > 0)
                    {
                        int index_2 = (int)NextDouble(0, result.genome[index].connected_nodes.Count - 1);
                        result.genome[index].connected_nodes.RemoveAt(index_2);
                        result.genome[index].connection_weights.RemoveAt(index_2);
                    }
                }
            }
			
            if (Random.rand.NextDouble() > node_add_prob)
            {
                result.genome.Add(new Node("hidden"));
            }

            if ((Random.rand.NextDouble() > node_delete_prob) && (result.GetHiddenNodes().Count != 0))
            {
                if (result.genome.Count > 0)
                {
                    int index = (int)NextDouble(0, result.genome.Count - 1);
                    while ((result.genome[index].node_type == "input") || (result.genome[index].node_type == "output"))
                    {
                        index = (int)NextDouble(0, result.genome.Count - 1);
                    }

                    result.genome.RemoveAt(index);
                }
            }

            if (Random.rand.NextDouble() > weight_mutate_prob && result.genome.Count != 0)
            {
                if (result.genome.Count > 0)
                {
                    int index = (int)NextDouble(0, result.genome.Count - 1);
                    while (result.genome[index].node_type == "input")
                    {
                        index = (int)NextDouble(0, result.genome.Count - 1);
                    }

                    if (result.genome[index].connected_nodes.Count > 0)
                    {
                        int index_2 = (int)NextDouble(0, result.genome[index].connected_nodes.Count - 1);
                        result.genome[index].connection_weights[index_2] = (float)Random.rand.NextDouble() * 2 - 1;
                    }
                }
            }

            if (Random.rand.NextDouble() > weight_replace_prob && result.genome.Count != 0)
            {
                if (result.genome.Count > 0)
                {
                    int index = (int)NextDouble(0, result.genome.Count - 1);
                    while (result.genome[index].node_type == "input")
                    {
                        index = (int)NextDouble(0, result.genome.Count - 1);
                    }

                    if (result.genome[index].connected_nodes.Count > 0)
                    {
                        for (int looper = 0; looper < result.genome[index].connected_nodes.Count; looper++)
                        {
                            result.genome[index].connection_weights[looper] = (float)Random.rand.NextDouble() * 2 - 1;
                        }
                    }
                }
            }

            if (Random.rand.NextDouble() > bias_mutate_rate)
            {
                if (result.genome.Count > 0)
                {
                    int index = (int)NextDouble(0, result.genome.Count - 1);
                    while (result.genome[index].node_type == "input")
                    {
                        index = (int)NextDouble(0, result.genome.Count - 1);
                    }

                    result.genome[index].upperTriggerThreshold = Clamp((float)Random.rand.NextDouble() - 0.5f, bias_min_value, bias_max_value);
                    result.genome[index].lowerTriggerThreshold = Clamp((float)Random.rand.NextDouble() - 0.5f, bias_min_value, result.genome[index].upperTriggerThreshold);
                }
            }

            if (result.IsGenomeStable()) { return result; }
            return GetMutatedGenomeCopy(orig);
            //return orig;
        }

        public void UpdateGenomeList() {
            var watch = System.Diagnostics.Stopwatch.StartNew();
			
            // We now have the entire genome list ordered by fitness
            // 1 - Get the fitness list of all the genomes
            // 2 - Sort the genomes by fitness (Flip if we want minimums to win):
            // 3 - Perform the genetic death algorithms to wittle out poor performing genomes
            // 4 - Create mutated clones of winning genomes
            // 5 - Breed the winning genomes (NOT IMPLEMENTED)

            //We have a unique problem that I just ignored in python.
            //We have to sort list 1 by list 2 values

            //Stage 1/2
            List<Genome> genomesList = new List<Genome>(genomes);
			
			bool runOnce = true;
            for (int index = genomesList.Count - 1; index >= 0; index--)
            {
                int indexOfLargest = index;
                for (int index2 = 0; index2 < index; index2++)
                {
                    if (genomesList[index2].fitness >= genomesList[indexOfLargest].fitness)
                    {
                        indexOfLargest = index2;
                    }
                }
				
				if (runOnce) {
					runOnce = false;
					using (StreamWriter sw = File.AppendText(trainingDataPath + "/SaveData/override training values.txt")) {
						sw.WriteLine(genomesList[indexOfLargest].fitness.ToString());
					}
				}
				
                Genome temp2 = genomesList[indexOfLargest];
                genomesList.RemoveAt(indexOfLargest);
                genomesList.Add(temp2);
            }

            //Stage 3
            List<Genome> temp = new List<Genome>(genomesList);
            genomesList = new List<Genome>();
            float s_t = survival_threshold;
            int p_s = pop_size;
            for (int i = 0; i < temp.Count; i++)
            {
                float survivalThreshold = (float)((1 - s_t) * Math.Pow(Math.Sin((Math.PI / 2) * (((float)i) / p_s)), 2) + s_t);
                if (Random.rand.NextDouble() < survivalThreshold)
                {
                    temp[i].generationsSurvived++;
                    genomesList.Add(temp[i]);
                }
                else if (temp[i].generationsSurvived > 5)
                {
                    temp[i].generationsSurvived -= 3;
                    genomesList.Add(temp[i]);
                }
            }


            //Stage 4 (Somewhere in here, it gets stuck. I suspect it may be due to the random number generation not being random)
            if (genomesList.Count > 0)
            {
                if (genomesList.Count > minimum_network_size)
                {
					if (!silenceOutput) {
						Console.WriteLine("[NEAT AI][Info]: Number of surviving genomes: " + genomesList.Count.ToString());
					}
                    while (genomesList.Count < p_s)
                    {
                        int index = Random.rand.Next(genomesList.Count);
                        Genome i = genomesList[index];
						genomesList.Add(GetMutatedGenomeCopy(i));
                    }

                    genomes = genomesList;
                }
                else if (previousValidGenomes.Count > minimum_network_size)
                {
					if (!silenceOutput) {
						Console.WriteLine("[NEAT AI][Info]: Rebooting genome from previous success attempts");
					}
                    genomesList = new List<Genome>(previousValidGenomes);
                    while (genomesList.Count < p_s)
                    {
                        int index = Random.rand.Next(genomesList.Count);
                        Genome i = genomesList[index];
                        genomesList.Add(GetMutatedGenomeCopy(i));
                    }
					while (genomesList.Count > p_s)
                    {
                        int index = Random.rand.Next(genomesList.Count);
                        Genome i = genomesList[index];
                        genomesList.RemoveAt(index);
                    }

                    genomes = genomesList;
                }
                else if (previousValidGenomes.Count + genomesList.Count > minimum_network_size)
                {
                    foreach (Genome i in previousValidGenomes)
                    {
                        genomesList.Add(i);
                    }
					
					if (!silenceOutput) {
						Console.WriteLine("[NEAT AI][Info]: Rebooting genome from previous success attempts appended to current network data");
                    }
					while (genomesList.Count < p_s)
                    {
                        int index = Random.rand.Next(genomesList.Count);
                        Genome i = genomesList[index];
                        genomesList.Add(GetMutatedGenomeCopy(i));
                    }
					while (genomesList.Count > p_s)
                    {
                        int index = Random.rand.Next(genomesList.Count);
                        Genome i = genomesList[index];
                        genomesList.RemoveAt(index);
                    }

                    genomes = genomesList;
                }
                else
                {
					if (!silenceOutput) {
						if (genomesList.Count == 1)
						{
							Console.WriteLine("[NEAT AI][Info]: Discovered functional node. Storing node for later...");
						}
						else
						{
							Console.WriteLine("[NEAT AI][Info]: Discovered functional nodes. Storing " + genomesList.Count.ToString() + " nodes for later...");
						}
					}

                    foreach (Genome i in genomesList)
                    {
                        previousValidGenomes.Add(i);
                    }
                }
            }
            else
            {
				if (!silenceOutput) {
					Console.WriteLine("[NEAT AI][Info]: Complete extinction event, regenerating network!");
                }
				if (prepopulated) {
					GenerateNewPrepopulatedNetwork();
				} else {
					GenerateNewRandomNetwork();
				}
            }
			
            watch.Stop();

            if (printTrainingTimes) {
                Console.WriteLine("[NEAT AI][Info]: Generation Learning Time: " + ((float)watch.ElapsedMilliseconds / 1000).ToString() + "s");
                Console.WriteLine("[NEAT AI][Info]:  - Number of genomes: " + genomesList.Count.ToString());
            }
        }
		
		public void loadNetwork() { loadNetwork(null,null); }
		public void loadNetwork(dataScreen disp0, dataScreen disp1) {
			//if (genomes.Count != 0) { throw new Exception("Attempting to load network into pre-existing populated AI"); }
			genomes = new List<Genome>();
			
			string networkDataPath = trainingDataPath + "/SaveData/Saved AI Network 1";
			StreamReader file = new StreamReader(trainingDataPath + "/SaveData/saveStatus.txt");
            int saveStatus = int.Parse(file.ReadLine());
			if ((saveStatus == 0) || (saveStatus == 2)) {} else if (saveStatus == 1) {
				networkDataPath = trainingDataPath + "/SaveData/Saved AI Network 2";
			} else {
				throw new Exception("Error reading from NEAT AI save status file!");
			} //Code-Marker
			
			StreamReader networkReadout = new StreamReader(networkDataPath + "/Network Readout.txt");
			pop_size = (int)forcedStringToFloat(networkReadout.ReadLine());
			num_inputs = (int)forcedStringToFloat(networkReadout.ReadLine());
			num_outputs = (int)forcedStringToFloat(networkReadout.ReadLine());
			
			//Iterate through all genomes
			int genomesLoop = 0;
			string[] genomesPath = Directory.GetDirectories(networkDataPath + "/Active Genomes");
			foreach(string genomePath in genomesPath) {
				genomesLoop++;
				if ((disp0 != null) && (disp1 != null)) {
					disp1.data = genomesLoop.ToString() + "/" + genomesPath.Length.ToString();
					for (int i = 0; i < (23 - disp1.data.Length) / 2; i++) {
						disp1.data = " " + disp1.data;
					}
					
					disp0.data = "    Loading 1/2";
					disp0.updateScreen(); disp1.updateScreen();
				}
				
				//Console.WriteLine("Next genome path: " + genomePath.ToString() + "\t\tCurrent Genome: " + genomesLoop.ToString() + "/" + genomesPath.Length.ToString());
				StreamReader genomeReadout = new StreamReader(genomePath + "/Genome Readout.txt");
				
				Genome tempGenome = new Genome();
				tempGenome.ID = (ulong)forcedStringToFloat(genomeReadout.ReadLine());
				tempGenome.fitness = forcedStringToFloat(genomeReadout.ReadLine());
				tempGenome.generationsSurvived = (int)forcedStringToFloat(genomeReadout.ReadLine());
				
				//Iterate over all nodes
				string[] nodesPath = Directory.GetFiles(genomePath);
				foreach(string nodePath in nodesPath) {
					if (nodePath.Replace("\\","/") != genomePath.Replace("\\","/") + "/Genome Readout.txt") {
						StreamReader nodeData = new StreamReader(nodePath);
						
						//Find node with that matching ID. If it does not exist, create it
						int ID = (int)forcedStringToFloat(nodeData.ReadLine());
						Node tempNode = null;
						for (int index = 0; index < tempGenome.genome.Count; index++) {
							if (tempGenome.genome[index].ID == (ulong)ID) {
								tempNode = tempGenome.genome[index];
								index = tempGenome.genome.Count;
							}
						}
						
						if (tempNode == null) {
							tempNode = new Node("hidden");
							tempNode.ID = (ulong)ID;
							tempGenome.genome.Add(tempNode);
						}
						
						// Set the node type, and threshold values
						string tempStr = nodeData.ReadLine();
						tempNode.node_type = tempStr.Substring(tempStr.LastIndexOf(":") + 1,tempStr.Length - tempStr.LastIndexOf(":") - 1);
						
						tempNode.upperTriggerThreshold = (int)forcedStringToFloat(nodeData.ReadLine());
						tempNode.lowerTriggerThreshold = (int)forcedStringToFloat(nodeData.ReadLine());
							
						if (tempNode.node_type != "input") {
							nodeData.ReadLine();
							
							//Loop over all connected nodes in memory
							while(true) {
								tempStr = nodeData.ReadLine();
								if (tempStr.LastIndexOf("|") < 1) { break; }
								
								int tempNodeID = (int)forcedStringToFloat(tempStr.Split("|")[0]);
								float tempNodeWeight = forcedStringToFloat(tempStr.Split("|")[1]);
								
								//Does that node ID exist? If not, create it
								Node connectedNode = null;
								for (int index = 0; index < tempGenome.genome.Count; index++) {
									if (tempGenome.genome[index].ID == (ulong)tempNodeID) {
										connectedNode = tempGenome.genome[index];
										index = tempGenome.genome.Count;
									}
								}
								
								if (connectedNode == null) {
									Node tempNode2 = new Node("hidden");
									tempNode2.ID = (ulong)tempNodeID;
									tempGenome.genome.Add(tempNode2);
									connectedNode = tempNode2;
								}
								
								//Now that we have the node, simply apply the values
								tempNode.connected_nodes.Add(connectedNode);
								tempNode.connection_weights.Add(tempNodeWeight);
							}
						}
					}
				}
				
				genomes.Add(tempGenome);
			}
			
			disp1.data = "";
			DisplayManager.updateDisplays();
			
			genomesLoop = 0;
			string[] directories = Directory.GetDirectories(networkDataPath + "/Previous Genomes");
			foreach(string genomePath in genomesPath) {
				genomesLoop++;
				if ((disp0 != null) && (disp1 != null)) {
					disp1.data = genomesLoop.ToString() + "/" + genomesPath.Length.ToString();
					for (int i = 0; i < (23 - disp1.data.Length) / 2; i++) {
						disp1.data = " " + disp1.data;
					}
					
					disp0.data = "    Loading 2/2";
					disp0.updateScreen(); disp1.updateScreen();
				}
				
				//Console.WriteLine("Next genome path: " + genomePath.ToString() + "\t\tCurrent Genome: " + genomesLoop.ToString() + "/" + genomesPath.Length.ToString());
				StreamReader genomeReadout = new StreamReader(genomePath + "/Genome Readout.txt");
				
				Genome tempGenome = new Genome();
				tempGenome.ID = (ulong)forcedStringToFloat(genomeReadout.ReadLine());
				tempGenome.fitness = forcedStringToFloat(genomeReadout.ReadLine());
				tempGenome.generationsSurvived = (int)forcedStringToFloat(genomeReadout.ReadLine());
				
				//Iterate over all nodes
				string[] nodesPath = Directory.GetFiles(genomePath);
				foreach(string nodePath in nodesPath) {
					if (nodePath.Replace("\\","/") != genomePath.Replace("\\","/") + "/Genome Readout.txt") {
						StreamReader nodeData = new StreamReader(nodePath);
						
						//Find node with that matching ID. If it does not exist, create it
						int ID = (int)forcedStringToFloat(nodeData.ReadLine());
						Node tempNode = null;
						for (int index = 0; index < tempGenome.genome.Count; index++) {
							if (tempGenome.genome[index].ID == (ulong)ID) {
								tempNode = tempGenome.genome[index];
								index = tempGenome.genome.Count;
							}
						}
						
						if (tempNode == null) {
							tempNode = new Node("hidden");
							tempNode.ID = (ulong)ID;
							tempGenome.genome.Add(tempNode);
						}
						
						// Set the node type, and threshold values
						string tempStr = nodeData.ReadLine();
						tempNode.node_type = tempStr.Substring(tempStr.LastIndexOf(":") + 1,tempStr.Length - tempStr.LastIndexOf(":") - 1);
						
						tempNode.upperTriggerThreshold = (int)forcedStringToFloat(nodeData.ReadLine());
						tempNode.lowerTriggerThreshold = (int)forcedStringToFloat(nodeData.ReadLine());
						
						if (tempNode.node_type != "input") {
							nodeData.ReadLine();
							
							//Loop over all connected nodes in memory
							while(true) {
								tempStr = nodeData.ReadLine();
								if (tempStr.LastIndexOf("|") < 1) { break; }
								
								int tempNodeID = (int)forcedStringToFloat(tempStr.Split("|")[0]);
								float tempNodeWeight = forcedStringToFloat(tempStr.Split("|")[1]);
								
								//Does that node ID exist? If not, create it
								Node connectedNode = null;
								for (int index = 0; index < tempGenome.genome.Count; index++) {
									if (tempGenome.genome[index].ID == (ulong)tempNodeID) {
										connectedNode = tempGenome.genome[index];
										index = tempGenome.genome.Count;
									}
								}
								
								if (connectedNode == null) {
									Node tempNode2 = new Node("hidden");
									tempNode2.ID = (ulong)tempNodeID;
									tempGenome.genome.Add(tempNode2);
									connectedNode = tempNode2;
								}
								
								//Now that we have the node, simply apply the values
								tempNode.connected_nodes.Add(connectedNode);
								tempNode.connection_weights.Add(tempNodeWeight);
							}
						}
					}
				}
				
				previousValidGenomes.Add(tempGenome);
			}
			
			//Now that the network is fully loaded, just check that the population values add up
			if (pop_size != genomes.Count) {
				throw new Exception("Invalid input network. Population size does not match internal AI settings");
			}
			
			return;
		}
		
		static float forcedStringToFloat(string input) {
            string output = "";
            foreach (char i in input) {
                if (((i > 47) && (i < 58)) || (i == '.') || (i == '-')) {
                    output += i;
                }
            }
			
			if (output.Length > output.Replace("-","").Length) {
				output = ("a" + output.Replace("-","|-")).Split("|")[1];
			}
			
			try {
				return float.Parse(output);
			} catch {
				throw new Exception("Cannot Convert string to float: \"" + input.ToString() + "\"\t\tGot result: \"" + output + "\"");
			}
        }
		
		public Genome getBestGenome() {
			Genome best = genomes[0];
			foreach(Genome i in genomes) {
				if (i.fitness > best.fitness) { best = i; }
			}
			
			return best;
		}
    }
}


































