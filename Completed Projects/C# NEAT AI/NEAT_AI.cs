using System;
using System.IO;
using System.Collections.Generic;

namespace NEAT_AI
{
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

    public class Node
    {
		public ulong ID = Random.getNextNodeID();
        public string node_type = "";
        public List<Node> connected_nodes = new List<Node>();
        public List<float> connection_weights = new List<float>();
        public float node_input = -1000;
        public float upperTriggerThreshold = 1;
        public float lowerTriggerThreshold = -1;
		
        public Node(string nodeType)
        {
            node_type = nodeType;
        }

        public float GetNodeOutput() { return GetNodeOutput(new List<Node>()); }
        public float GetNodeOutput(List<Node> nodeManager)
        {
            if (nodeManager.Contains(this)) { return -1000; }
            nodeManager.Add(this);

            if (node_type == "input") { return node_input; }

            float result = 0;
            int loops = 0;
            foreach (Node i in connected_nodes)
            {
                float temp = connected_nodes[loops].GetNodeOutput(nodeManager) * connection_weights[loops];
                if ((temp < upperTriggerThreshold) && (temp > lowerTriggerThreshold)) { result += temp; }
                loops += 1;
            }

            return (float)Math.Tanh(result);
        }

        public void SetNodeInput(float x) { node_input = x; }
    }

    public class Genome
    {
		public ulong ID = Random.getNextGeneID();
        public float fitness = 0;
        public int generationsSurvived = 0;
        public List<Node> genome = new List<Node>();
        private Genome orig;

        public Genome() { }
        public Genome(Genome orig) { this.orig = orig; }

        public void ClearGenomeData() { genome = new List<Node>(); }
		
		public void GenerateNewPrepopulatedGenome(int num_inputs, int num_outputs, int numberOfLayers, int nodesPerLayer) {
			ClearGenomeData();
			
			for (int i = 0; i < num_inputs; i++) { this.genome.Add(new Node("input")); }
			
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
						tempNode.connection_weights.Add((float)Random.rand.NextDouble());
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
					tempNode.connection_weights.Add((float)Random.rand.NextDouble());
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
                    test_node_1.connection_weights.Add((float)Random.rand.NextDouble());
                    if (!IsGenomeStable())
                    {
                        int newPosition = test_node_1.connected_nodes.Count - 1;
                        test_node_1.connected_nodes.RemoveAt(newPosition);
                        test_node_1.connection_weights.RemoveAt(newPosition);

                        test_node_2.connected_nodes.Add(test_node_1);
                        test_node_2.connection_weights.Add((float)Random.rand.NextDouble());
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

    public class Network
    {
		public string trainingDataPath = "";
        public bool printTrainingTimes = false;
        public List<Genome> genomes = new List<Genome>();
        List<Genome> previousValidGenomes = new List<Genome>();

        //NEAT Variables
        public string fitness_criterion = "";
        public int pop_size = 0;
        public float bias_max_value = 0;
        public float bias_min_value = 0;
        public float bias_mutate_rate = 0;
        public float conn_add_prob = 0;
        public float conn_delete_prob = 0;
        public float node_add_prob = 0;
        public float node_delete_prob = 0;
        public int num_inputs = 0;
        public int num_outputs = 0;
        public int num_hidden = 0;
        public int num_connections = 0;
        public float weight_mutate_prob = 0;
        public float weight_replace_prob = 0;
        public float survival_threshold = 0;
        public int minimum_network_size = 0;
		public int numberOfLayers = 0;
		public int nodesPerLayer = 0;
		public bool prepopulated = false;
		
        public Network(string configPath, bool _printTrainingTimes, bool prepopulate)
        {
			trainingDataPath = configPath + "_override training values.txt";
			using (FileStream fs = File.Create(trainingDataPath)) {}
			
            Random.SetupRandom();

            Console.WriteLine("[NEAT AI][Info]: Setting up Variables. Please be aware this can take quite some time depending on config");

            LiveConfigUpdate(configPath);

            printTrainingTimes = _printTrainingTimes;
			
			if (prepopulate) {
				prepopulated = true;
				GenerateNewPrepopulatedNetwork();
			} else {
				GenerateNewRandomNetwork();
			}

            Console.WriteLine("[NEAT AI][Info]: Population size set to " + pop_size.ToString());
            Console.WriteLine("[NEAT AI][Info]: Input count " + num_inputs.ToString());
            Console.WriteLine("[NEAT AI][Info]: Output count " + num_outputs.ToString());
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
			Console.WriteLine("[NEAT AI][Info]: Prepopulating the network");
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
                node_1.connection_weights.Add((float)Random.rand.NextDouble());

                if (!result.IsGenomeStable())
                {
                    node_1.connected_nodes.RemoveAt(node_1.connected_nodes.Count - 1);
                    node_1.connection_weights.RemoveAt(node_1.connection_weights.Count - 1);

                    node_2.connected_nodes.Add(node_1);
                    node_2.connection_weights.Add((float)Random.rand.NextDouble());
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
                        result.genome[index].connection_weights[index_2] = (float)Random.rand.NextDouble();
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
                            result.genome[index].connection_weights[looper] = (float)Random.rand.NextDouble();
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
					using (StreamWriter sw = File.AppendText(trainingDataPath)) {
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
                    Console.WriteLine("[NEAT AI][Info]: Number of surviving genomes: " + genomesList.Count.ToString());

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
                    Console.WriteLine("[NEAT AI][Info]: Rebooting genome from previous success attempts");

                    genomesList = new List<Genome>(previousValidGenomes);
                    while (genomesList.Count != p_s)
                    {
                        int index = Random.rand.Next(genomesList.Count);
                        Genome i = genomesList[index];
                        genomesList.Add(GetMutatedGenomeCopy(i));
                    }

                    genomes = genomesList;
                }
                else if (previousValidGenomes.Count + genomesList.Count > minimum_network_size)
                {
                    foreach (Genome i in previousValidGenomes)
                    {
                        genomesList.Add(i);
                    }

                    Console.WriteLine("[NEAT AI][Info]: Rebooting genome from previous success attempts appended to current network data");
                    while (genomesList.Count != p_s)
                    {
                        int index = Random.rand.Next(genomesList.Count);
                        Genome i = genomesList[index];
                        genomesList.Add(GetMutatedGenomeCopy(i));
                    }

                    genomes = genomesList;
                }
                else
                {
                    if (genomesList.Count == 1)
                    {
                        Console.WriteLine("[NEAT AI][Info]: Discovered functional node. Storing node for later...");
                    }
                    else
                    {
                        Console.WriteLine("[NEAT AI][Info]: Discovered functional nodes. Storing " + genomesList.Count.ToString() + " nodes for later...");
                    }

                    foreach (Genome i in genomesList)
                    {
                        previousValidGenomes.Add(i);
                    }
                }
            }
            else
            {
                Console.WriteLine("[NEAT AI][Info]: Complete extinction event, regenerating network!");
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
		
		string saveStatusPath = "C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/saveStatus.txt";
		public string safeLoad(string path) {
			StreamReader file = new StreamReader(saveStatusPath);
            int saveStatus = int.Parse(file.ReadLine());
			
			if ((saveStatus == 0) || (saveStatus == 2)) {
				//0 	- The system correctly saved everything
				//2 	- The system was interrupted while saving "1"
				//null 	- The system had finished saving, but was interrupted in the middle of editing the status
				file = new StreamReader(path + "0.json");
			} else if (saveStatus == 1) {
				//1 - The system was interrupted while saving "0"
				file = new StreamReader(path + "1.json");
			} else {
				Console.ForegroundColor = ConsoleColor.Red;
				Console.WriteLine("[NEAT AI][Error]: Network error in reading from file: " + saveStatusPath);
				Console.ResetColor();
			}
			
			string line = file.ReadLine();
			string totalData = "";
			while (line != null) {
				totalData += line + "\n";
				line = file.ReadLine();
			}
			
			return totalData;
		}
		
		public void saveNetwork() { saveNetwork(false); }
		public void saveNetwork(bool overrideUserInputRequirement) {
			if (!overrideUserInputRequirement) {
				Console.ForegroundColor = ConsoleColor.Magenta;
				Console.WriteLine("[NEAT AI][Request]: Press Key To Save Network Data");
				Console.ResetColor();
				Console.ReadKey(true);
			}
			Console.WriteLine("[NEAT AI][Info]: Saving Network Data...");
			
			string path = "C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/networkDump";
			
			File.WriteAllText(saveStatusPath, "1");
			if (File.Exists(path + "0.json")) { File.Delete(path + "0.json"); }
			using (StreamWriter sw = File.CreateText(path + "0.json")) { }
			using (StreamWriter sw = File.AppendText(path + "0.json")) {
				sw.WriteLine("[");
				sw.WriteLine("\t{");
				for(int genomeIndex = 0; genomeIndex < genomes.Count; genomeIndex++) {
					sw.WriteLine("\t\t\"Genome Data\": [");
					sw.WriteLine("\t\t\t{");
					for (int nodeIndex = 0; nodeIndex < genomes[genomeIndex].genome.Count; nodeIndex++) {
						sw.WriteLine("\t\t\t\t\"Current Node ID\": " + genomes[genomeIndex].genome[nodeIndex].ID.ToString() + ",");
						
						if (genomes[genomeIndex].genome[nodeIndex].node_type.ToString() != "input") {
							sw.WriteLine("\t\t\t\t\"Current Node Type\": \"" + genomes[genomeIndex].genome[nodeIndex].node_type.ToString() + "\",");
							sw.WriteLine("\t\t\t\t\"Node Connections\": [");
							sw.WriteLine("\t\t\t\t\t{");
							
							for (int index = 0; index < genomes[genomeIndex].genome[nodeIndex].connected_nodes.Count; index++) {
								sw.WriteLine("\t\t\t\t\t\t\"Node ID\":" + genomes[genomeIndex].genome[nodeIndex].connected_nodes[index].ID + ",");
								sw.WriteLine("\t\t\t\t\t\t\"Node Weight\":" + genomes[genomeIndex].genome[nodeIndex].connection_weights[index] + "");
								if (index != genomes[genomeIndex].genome[nodeIndex].connected_nodes.Count - 1) {
									sw.WriteLine("\t\t\t\t\t},{");
								} else {
									sw.WriteLine("\t\t\t\t\t}");
								}
							}
							
							sw.WriteLine("\t\t\t\t]");
						} else {
							sw.WriteLine("\t\t\t\t\"Current Node Type\": \"" + genomes[genomeIndex].genome[nodeIndex].node_type.ToString() + "\"");
						}
						
						if (nodeIndex != genomes[genomeIndex].genome.Count - 1) {
							sw.WriteLine("\t\t\t},{");
						} else {
							sw.WriteLine("\t\t\t}");
						}
					}
					
					sw.WriteLine("\t\t]");
					if (genomeIndex != genomes.Count - 1) {
						sw.WriteLine("\t},{");
					} else {
						sw.WriteLine("\t}");
					}
				}
				
				sw.WriteLine("]");
			}
			
			Console.WriteLine("[NEAT AI][Info]: Backing Up Network Data...");
			File.WriteAllText(saveStatusPath, "2");
			if (File.Exists(path + "1.json")) { File.Delete(path + "1.json"); }
			using (StreamWriter sw = File.CreateText(path + "1.json")) { }
			using (StreamWriter sw = File.AppendText(path + "1.json")) {
				sw.WriteLine("[");
				sw.WriteLine("\t{");
				for(int genomeIndex = 0; genomeIndex < genomes.Count; genomeIndex++) {
					sw.WriteLine("\t\t\"Genome Data\": [");
					sw.WriteLine("\t\t\t{");
					for (int nodeIndex = 0; nodeIndex < genomes[genomeIndex].genome.Count; nodeIndex++) {
						sw.WriteLine("\t\t\t\t\"Current Node ID\": " + genomes[genomeIndex].genome[nodeIndex].ID.ToString() + ",");
						
						if (genomes[genomeIndex].genome[nodeIndex].node_type.ToString() != "input") {
							sw.WriteLine("\t\t\t\t\"Current Node Type\": \"" + genomes[genomeIndex].genome[nodeIndex].node_type.ToString() + "\",");
							sw.WriteLine("\t\t\t\t\"Node Connections\": [");
							sw.WriteLine("\t\t\t\t\t{");
							
							for (int index = 0; index < genomes[genomeIndex].genome[nodeIndex].connected_nodes.Count; index++) {
								sw.WriteLine("\t\t\t\t\t\t\"Node ID\":" + genomes[genomeIndex].genome[nodeIndex].connected_nodes[index].ID + ",");
								sw.WriteLine("\t\t\t\t\t\t\"Node Weight\":" + genomes[genomeIndex].genome[nodeIndex].connection_weights[index] + "");
								if (index != genomes[genomeIndex].genome[nodeIndex].connected_nodes.Count - 1) {
									sw.WriteLine("\t\t\t\t\t},{");
								} else {
									sw.WriteLine("\t\t\t\t\t}");
								}
							}
							
							sw.WriteLine("\t\t\t\t]");
						} else {
							sw.WriteLine("\t\t\t\t\"Current Node Type\": \"" + genomes[genomeIndex].genome[nodeIndex].node_type.ToString() + "\"");
						}
						
						if (nodeIndex != genomes[genomeIndex].genome.Count - 1) {
							sw.WriteLine("\t\t\t},{");
						} else {
							sw.WriteLine("\t\t\t}");
						}
					}
					
					sw.WriteLine("\t\t]");
					if (genomeIndex != genomes.Count - 1) {
						sw.WriteLine("\t},{");
					} else {
						sw.WriteLine("\t}");
					}
				}
				
				sw.WriteLine("]");
			}
			
			File.WriteAllText(saveStatusPath, "0");
		}
		
		public void loadNetwork() {
			Console.ForegroundColor = ConsoleColor.Yellow;
			Console.WriteLine("[NEAT AI][Warning]: Network Loading Failure: Empty Function!");
			Console.WriteLine("[NEAT AI][Warning]:  - Using blank network");
			Console.ResetColor();
			return;
		}
    }
}


































