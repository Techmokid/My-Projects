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
		
		void liveConfigUpdate(self,configPath) {
			//NEAT
			fitness_criterion = 	getConfigValue(configPath,"fitness_criterion");
			pop_size = 				int(getConfigValue(configPath,"pop_size"));
			
			//Node Bias
			bias_max_value = 		float(getConfigValue(configPath,"bias_max_value"));
			bias_min_value = 		float(getConfigValue(configPath,"bias_min_value"));
			bias_mutate_rate = 		float(getConfigValue(configPath,"bias_mutate_rate"));
			
			//Connection Rates
			conn_add_prob = 		float(getConfigValue(configPath,"conn_add_prob"));
			conn_delete_prob = 		float(getConfigValue(configPath,"conn_delete_prob"));

			//Node Rates
			node_add_prob = 		float(getConfigValue(configPath,"node_add_prob"));
			node_delete_prob = 		float(getConfigValue(configPath,"node_delete_prob"));

			//Network Parameters
			num_inputs = 			int(getConfigValue(configPath,"num_inputs"));
			num_outputs = 			int(getConfigValue(configPath,"num_outputs"));
			num_hidden = 			int(getConfigValue(configPath,"num_hidden"));
			num_connections = 		int(getConfigValue(configPath,"num_connections"));
			
			//Connection Weight
			weight_mutate_prob = 	float(getConfigValue(configPath,"weight_mutate_prob"));
			weight_replace_prob = 	float(getConfigValue(configPath,"weight_replace_prob"));
			
			//Default Reproduction
			survival_threshold = 	float(getConfigValue(configPath,"survival_threshold"));
			minimum_network_size = 	int(getConfigValue(configPath,"minimum_network_size"));
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
					line = line.Replace(' ','');
					line = line.Replace('\t','');
					line = line.Replace('\n','');
					
					return line.Split('=')[1];
				}
			}
		}
		
		void updateGenomeList() { updateGenomeList(null); }
		void updateGenomeList(void optionalSecondaryFitnessCalculator) {
			
		}
		
		//void generateNewRandomNetwork() {}
		//Genome getMutatedGenomeCopy(Genome orig) {}
    }
}





























