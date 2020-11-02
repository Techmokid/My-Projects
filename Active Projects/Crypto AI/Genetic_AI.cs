//Might have to go through and spam "this.function();"

using System.Collections.Generic;
using System;

namespace NEAT_AI {
    public class Node {
        public String node_type = "";
        public List<Node> connected_nodes = new List<Node>();
        public List<Node> connection_weights = new List<Node>();
        public float node_input = -1000;
        public float upperTriggerThreshold = 1;
        public float lowerTriggerThreshold = -1;

        public Node(String nodeType) {
            node_type = nodeType;
        }
        public float getNodeOutput() { return getNodeOutput(new List<Node>()); }
        public float getNodeOutput(List<Node> nodeManager) {
            if (nodeManager.Contains(nodeManager)) { return -1000; }
            nodeManager.Add(this);

            if (node_type == "input") { return node_input; }

            float result = 0;
            int loops = 0;
            foreach (Node i in connected_nodes) {
                float temp = connected_nodes[loops].getNodeOutput(nodeManager) * connection_weights[loops];
                if ((temp > upperTriggerThreshold) && (temp < lowerTriggerThreshold)) { result += temp; }
                loops += 1;
            }

            return Math.Tanh(result);
        }

        public void setNodeInput(float x) { node_input = x; }
    }

    public class Genome {
        public float fitness = 0;
        public int generationsSurvived = 0;
        public List<Node> genome = new List<Node>();

        public void clearGenomeData() { genome = new List<Node>(); }

        public static double NextDouble(this Random random, double minValue, double maxValue) {
            return random.NextDouble() * (maxValue - minValue) + minValue;
        }

        public void generateNewRandomGenome(int inputs, int outputs, int hidden, int connections) {
            clearGenomeData();

            for (int i = 0; i < inputs; i++) { genome.Add(new Node("input")); }
            for (int i = 0; i < outputs; i++) { genome.Add(new Node("output")); }
            for (int i = 0; i < hidden; i++) { genome.Add(new Node("hidden")); }
            for (int i = 0; i < connections; i++) {
                bool runAgain = true;
                while(runAgain) {
                    index_1 = new Random().Next(0, genome.Count);
                    index_2 = new Random().Next(0, genome.Count);

                    while (index_1 == index_2) { index_2 = new Random().Next(0, genome.Count); }

                    Node test_node_1 = genome[index_1];
                    Node test_node_2 = genome[index_2];
                    test_node_1.connected_nodes.Add(test_node_2);
                    test_node_1.connection_weights.Add(new Random().NextDouble());
                    if (!isGenomeStable()) {
                        int newPosition = test_node_1.connected_nodes.Count - 1;
                        test_node_1.connected_nodes.RemoveAt(newPosition);
                        test_node_1.connection_weights.RemoveAt(newPosition);

                        test_node_2.connected_nodes.Add(test_node_1);
                        test_node_2.connection_weights.Add(new Random().NextDouble());
                        if (!isGenomeStable()) {
                            int newPosition = test_node_2.connected_nodes.Count - 1;
                            test_node_2.connected_nodes.RemoveAt(newPosition);
                            test_node_2.connection_weights.RemoveAt(newPosition);
                        } else { runAgain = true; }
                    } else { runAgain = true; }
                }
            }
        }

        public List<Node> getInputNodes() {
            List<Node> result = new List<Node>();
            foreach (Node i in genome) {
                if (i.node_type == "input") { result.Add(i); }
            }
            return result;
        }

        public List<Node> getOutputNodes() {
            List<Node> result = new List<Node>();
            foreach (Node i in genome) {
                if (i.node_type == "output") { result.Add(i); }
            }
            return result;
        }

        public List<Node> getHiddenNodes() {
            List<Node> result = new List<Node>();
            foreach (Node i in genome) {
                if (i.node_type == "hidden") { result.Add(i); }
            }
            return result;
        }

        public bool isGenomeStable() {
            foreach (Node i in getOutputNodes()) {
                if (i.getNodeOutput() == -1000) { return false; }
            }

            return true;
        }

        public float getOutput(List<float> inputValues) {
            if (inputValues.Count != getInputNodes().Count) {
                throw new System.InvalidOperationException("Number Of Supplied Inputs Does Not Match AI Configuration!");
            }

            int index = 0;
            foreach (Node node_object in getInputNodes()) {
                node_object.setNodeInput(inputValues[index]);
                index++;
            }

            index = 0;
            List<Node> result = new List<Node>();
            foreach (Node node_object in getOutputNodes()) {
                result.Add(node_object.getNodeOutput());
                index++;
            }
            
            return result;
        }
    }

    public class Network {
		bool printTrainingTimes;
		List<Genome> previousValidGenomes = new List<Genome>();
		List<Genome> genomes = new List<Genome>();
		
		//NEAT Variables
		string fitness_criterion;
		int pop_size;
		float bias_max_value;
		float bias_min_value;
		float bias_mutate_rate;
		float conn_add_prob;
		float conn_delete_prob;
		float node_add_prob;
		float node_delete_prob;
		int num_inputs;
		int num_outputs;
		int num_hidden;
		int num_connections;
		float weight_mutate_prob;
		float weight_replace_prob;
		float survival_threshold;
		int minimum_network_size;
		
        public Network(String configPath) { return Network(configPath, true, false); }
        public Network(String configPath, bool updateValuesRealtime) { return Network(configPath, updateValuesRealtime,false); }
        public Network(String configPath, bool updateValuesRealtime, bool _printTrainingTimes) {
			liveConfigUpdate(configPath);

			printTrainingTimes = _printTrainingTimes;
			generateNewRandomNetwork();

			System.Console.WriteLine("NEAT AI: Population size set to " + self.pop_size.ToString());
			System.Console.WriteLine("NEAT AI: Input count " + self.num_inputs.ToString());
			System.Console.WriteLine("NEAT AI: Output count " + self.num_outputs.ToString());
        }
		
		void liveConfigUpdate(string configPath) {
			//NEAT
			fitness_criterion = 	getConfigValue(configPath,"fitness_criterion");
			pop_size = 				int.Parse(getConfigValue(configPath,"pop_size"));
			
			//Node Bias
			bias_max_value = 		float.Parse(getConfigValue(configPath,"bias_max_value"));
			bias_min_value = 		float.Parse(getConfigValue(configPath,"bias_min_value"));
			bias_mutate_rate = 		float.Parse(getConfigValue(configPath,"bias_mutate_rate"));
			
			//Connection Rates
			conn_add_prob = 		float.Parse(getConfigValue(configPath,"conn_add_prob"));
			conn_delete_prob = 		float.Parse(getConfigValue(configPath,"conn_delete_prob"));

			//Node Rates
			node_add_prob = 		float.Parse(getConfigValue(configPath,"node_add_prob"));
			node_delete_prob = 		float.Parse(getConfigValue(configPath,"node_delete_prob"));

			//Network Parameters
			num_inputs = 			int.Parse(getConfigValue(configPath,"num_inputs"));
			num_outputs = 			int.Parse(getConfigValue(configPath,"num_outputs"));
			num_hidden = 			int.Parse(getConfigValue(configPath,"num_hidden"));
			num_connections = 		int.Parse(getConfigValue(configPath,"num_connections"));
			
			//Connection Weight
			weight_mutate_prob = 	float.Parse(getConfigValue(configPath,"weight_mutate_prob"));
			weight_replace_prob = 	float.Parse(getConfigValue(configPath,"weight_replace_prob"));
			
			//Default Reproduction
			survival_threshold = 	float.Parse(getConfigValue(configPath,"survival_threshold"));
			minimum_network_size = 	int.Parse(getConfigValue(configPath,"minimum_network_size"));
		}
		
		float clamp(float n, float minn, float maxn) {
			return Math.Max(Math.Min(maxn,n),minn);
		}
		
		void generateNewRandomNetwork() {
			genomes = new List<Genome>();
			for(int i = 0; i < pop_size; i++) {
				Genome temp = new Genome();
				temp.generateNewRandomGenome(num_inputs,num_outputs,num_hidden,num_connections);
				genomes.append(temp);
			}
		}
		
		string getConfigValue(string path, string key) {
			System.IO.StreamReader file = new System.IO.StreamReader(@path);
			while((line = file.ReadLine()) != null) {
				if (line.Contains(key)) {
					line = line.Replace(" ","");
					line = line.Replace("\t","");
					line = line.Replace("\n","");
					
					return line.Split('=')[1];
				}
			}
		}
		
		public static double NextDouble(double minValue, double maxValue) {
            return new Random().NextDouble() * (maxValue - minValue) + minValue;
        }
		
		Genome getMutatedGenomeCopy(Genome orig) {
			Genome result = new Genome(orig);

            if (new Random().NextDouble() > conn_add_prob) {
                int index_1 = NextDouble(0, result.genome.Count - 1);
                int index_2 = NextDouble(0, result.genome.Count - 1);
                while (index_1 == index_2) { index_2 = NextDouble(0, result.genome.Count - 1); }

                Node node_1 = result.genome[index_1];
                Node node_2 = result.genome[index_2];

                node_1.connected_nodes.append(node_2);
                node_1.connection_weights.append(new Random().NextDouble());

                if (!temp.isGenomeStable()) {
                    node_1.connected_nodes.RemoveAt(node_1.connected_nodes.Count - 1);
                    node_1.connection_weights.RemoveAt(node_1.connection_weights.Count - 1);

                    node_2.connected_nodes.append(node_1);
                    node_2.connection_weights.append(new Random().NextDouble());
                }
            }

            if (new Random().NextDouble() > conn_delete_prob) {
                if (result.genome.Count > 0) {
                    int index = NextDouble(0, result.genome.Count - 1);
                    while (result.genome[index].node_type == "input") {
                        index = NextDouble(0, result.genome.Count - 1);
                    }

                    if (result.genome[index].connected_nodes > 0) {
                        int index_2 = NextDouble(0, result.genome[index].connected_nodes - 1);
                        result.genome[index].connected_nodes.RemoveAt(index_2);
                        result.genome[index].connection_weights.RemoveAt(index_2);
                    }
                }
            }

            if (new Random().NextDouble() > node_add_prob) {
                result.genome.append(new Node { node_type = "hidden" });
            }

            if ((new Random().NextDouble() > node_delete_prob) && (result.getHiddenNodes().count != 0)) {
                if (result.genome.Count > 0) {
                    int index = NextDouble(0, result.genome.Count - 1);
                    while ((result.genome[index].node_type == "input") || (result.genome[index].node_type == "output")) {
                        index = NextDouble(0, result.genome.Count - 1);
                    }

                    result.genome.RemoveAt(index);
                }
            }

            if (new Random().NextDouble() > weight_mutate_prob) {
                if (result.genome.Count > 0) {
                    int index = NextDouble(0, result.genome.Count - 1);
                    while (result.genome[index].node_type == "input") {
                        index = NextDouble(0, result.genome.Count - 1);
                    }

                    if (result.genome[index].connected_nodes.Count > 0) {
                        int index_2 = NextDouble(0, result.genome[index].connected_nodes.Count - 1);
                        result.genome[index].connection_weights[index_2] = new Random().NextDouble();
                    }
                }
            }

            if (new Random().NextDouble() > weight_replace_prob) {
                if (result.genome.Count > 0) {
                    int index = NextDouble(0, result.genome.Count - 1);
                    while (result.genome[index].node_type == "input") {
                        index = NextDouble(0, result.genome.Count - 1);
                    }

                    if (result.genome[index].connected_nodes.Count > 0) {
                        for (int looper = 0; looper < result.genome[index].connected_nodes.Count; looper++) {
                            result.genome[index].connection_weights[looper] = new Random().NextDouble();
                        }
                    }
                }
            }

            if (new Random().NextDouble() > bias_mutate_rate) {
                if (result.genome.Count > 0) {
                    int index = NextDouble(0, result.genome.Count - 1);
                    while (result.genome[index].node_type == "input") {
                        index = NextDouble(0, result.genome.Count - 1);
                    }

                    result.genome[index].upperTriggerThreshold = clamp(new Random().NextDouble() - 0.5f, bias_min_value, bias_max_value);
                    result.genome[index].lowerTriggerThreshold = clamp(new Random().NextDouble() - 0.5f, bias_min_value, result.genome[index].upperTriggerThreshold);
                }
            }
			
			if (result.isGenomeStable()) { return result; }
			return getMutatedGenomeCopy(orig);
            //return orig;
		}
		
		void updateGenomeList() {
            // We now have the entire genome list ordered by fitness
            // 1 - Get the fitness list of all the genomes
            // 2 - Sort the genomes by fitness (Flip if we want minimums to win):
            // 3 - Perform the genetic death algorithms to wittle out poor performing genomes
            // 4 - Create mutated clones of winning genomes
            // 5 - Breed the winning genomes (NOT IMPLEMENTED)

            //We have a unique problem that I just ignored in python.
            //We have to sort list 1 by list 2 values
            List<float> fitnessesList = new List<float>();
            List<Genome> genomesList = new List<Genome>(genomes);
            for (int index = 0; index < genomesList.Count; index++) {
                fitnessesList.append(i.fitness);
            }
        }
    }
}





























