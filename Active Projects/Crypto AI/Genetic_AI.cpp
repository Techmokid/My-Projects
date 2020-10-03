#include "list2.h"
#include <iostream>
#include <fstream>
using namespace std;

#define print(x) cout << x << endl

class Node {
public:
	bool null_result = false;
	unsigned long long id = getNextInt();
	string node_type;
	list<Node> connected_nodes;
	list<float> connection_weights;
	float node_input = -1000;
	float node_bias = (float)rand() * 2 / RAND_MAX - 1;

	float getNodeOutput() { getNodeOutput(list<Node>()); }
	float getNodeOutput(list<Node> nodeManager) {
		if (nodeManager.contains(this)) {
			return -1000;
		}
		else {
			nodeManager.append(this);
		}

		if (node_type == "input") { return node_input; }

		int result = 0;
		for (int loops = 0; loops < connected_nodes.count; loops++) {
			Node node_data_1 = *connected_nodes.get(loops);
			float node_data_2 = *connection_weights.get(loops);

			result += node_data_1.getNodeOutput(nodeManager) * node_data_2 + node_bias;
		}
	}

	void setNodeInput(float x) { node_input = x; }
private:
	static int currentValue;
	static int getNextInt() {
		currentValue++;
		return currentValue;
	}
};

class genome {
private:
	void clearGenomeData() {
		genomes = new list<Node>;
	}

	Node getListObject(list<Node> myList, int index) {
		list<Node>::iterator it = myList.begin();
		advance(it, index);
		return *it;
	}

	float getListObject(list<float> myList, int index) {
		list<float>::iterator it = myList.begin();
		advance(it, index);
		return *it;
	}
public:
	float fitness = 0;
	int generationsSurvived = 0;
	list<Node> genomes;
	
	list<Node> getInputNodes() {
		list<Node> result;
		for (Node i : genomes) { if (i.node_type == "input") { result.append(i); } }
		return result;
	}

	list<Node> getOutputNodes() {
		list<Node> result;
		for (Node i : genomes) { if (i.node_type == "output") { result.append(i); } }
		return result;
	}

	list<Node> getHiddenNodes() {
		list<Node> result;
		for (Node i : genomes) {
			if ((i.node_type != "input") && (i.node_type != "output")) {
				result.append(i);
			}
		}
		return result;
	}

	void generateNewRandomGenome(int inputs, int outputs, int hidden, int connections) {
		clearGenomeData();

		for (int n = 0; i < inputs; ++i) {
			Node temp;
			temp.node_type = "input";
			genomes.append(temp);
		}

		for (int n = 0; i < outputs; ++i) {
			Node temp;
			temp.node_type = "output";
			genomes.append(temp);
		}

		for (int n = 0; i < hidden; ++i) {
			Node temp;
			temp.node_type = "hidden";
			genomes.append(temp);
		}

		for (int n = 0; i < connections; ++i) {
			//Now here's the random part. In here we connect a bunch of nodes randomly and simply ask if the structure is stable
			int index_1 = rand() % genomes.count;
			int index_2 = rand() % genomes.count;
			while (index_1 == index_2) {
				index_2 = rand() % genomes.count;
			}

			//Now we have our 2 indexes. Simply connect them
			genome testGenome = *this;
			Node test_node_1 = getListObject(testGenome.genomes, index_1);
			Node test_node_2 = getListObject(testGenome.genomes, index_2);

			test_node_1.connected_nodes.append(test_node_2);
			test_node_1.connection_weights.append((float)rand() * 2 / RAND_MAX - 1);

			if (testGenome.isGenomeStable()) {
				genomes = testGenome.genomes;
			} else {
				testGenome = *this;
				Node test_node_1 = getListObject(testGenome.genomes, index_2);
				Node test_node_2 = getListObject(testGenome.genomes, index_1);
				test_node_1.connected_nodes.append(test_node_2);
				test_node_1.connection_weights.append((float)rand() * 2 / RAND_MAX - 1);
				if (testGenome.isGenomeStable()) {
					genomes = testGenome.genomes;
				} else { print("ERROR! INVALID STRUCTURE"); }
			}
		}
	}

	bool isGenomeStable() {
		for (Node i : getOutputNodes()) {
			if (i.getNodeOutput() == -1000) {
				return false;
			}
		}
		return true;
	}

	list<float> getOutput(list<float> inputValues) {
		if (inputValues.count != getInputNodes().count) {
			throw "Number Of Supplied Inputs Does Not Match AI Configuration!";
		}

		int looper = 0;
		for (Node node_object : getInputNodes()) {
			node_object.setNodeInput(getListObject(inputValues, looper));
			looper++;
		}

		list<float> result;
		looper = 0;
		for (Node node_object : getOutputNodes()) {
			result.append(node_object.getNodeOutput());
			looper++;
		}
		return result;
	}
};

class network {
private:
	Node getListObject(list<Node> myList, int index) {
		list<Node>::iterator it = myList.begin();
		advance(it, index);
		return *it;
	}

	float getListObject(list<float> myList, int index) {
		list<float>::iterator it = myList.begin();
		advance(it, index);
		return *it;
	}
public:
	bool printTrainingTime;
	list<genome> previousValidGenomes;
	list<genome> genomes;

	//Internal values
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

	void init(string configPath, bool updateValuesRealtime, bool printTrainingTimes) {
		printTrainingTime = printTrainingTimes;
		//liveConfigUpdate(configPath);
		//generateNewRandomNetwork();
	}

	
	string removeCharsFromString(string stringIn, char key) {
		string temp = stringIn;
		string previousValue = stringIn.erase(key);

		while (previousValue != temp) {
			previousValue = temp;
			temp.erase(key);
		}

		return temp;
	}
	string removeCharsFromString(string stringIn, list<char> key) {
		string str;
		for (char i : key) { removeCharsFromString(stringIn, i); }
	}

	string getConfigValue(string path, string key) {
		ifstream file(path);
		string str;
		while (getline(file, str)) {
			if (str.find(key) != string::npos) {
				string temp = removeCharsFromString(str, list<char> { ' ', '\t', '\n' });
				return temp.substr(1, temp.find('='));
			}
		}
		return "";
	}

	void liveConfigUpdate(string configPath) {
		//NEAT
		fitness_criterion = getConfigValue(configPath, "fitness_criterion");
		pop_size = stoi(getConfigValue(configPath, "pop_size"));

		//Node Biases
		bias_max_value = stof(getConfigValue(configPath, "bias_max_value"));
		bias_min_value = stof(getConfigValue(configPath, "bias_min_value"));
		bias_mutate_rate = stof(getConfigValue(configPath, "bias_mutate_rate"));

		//Connection Rates
		conn_add_prob = stof(getConfigValue(configPath, "conn_add_prob"));
		conn_delete_prob = stof(getConfigValue(configPath, "conn_delete_prob"));

		//Node Rates
		node_add_prob = stof(getConfigValue(configPath, "node_add_prob"));
		node_delete_prob = stof(getConfigValue(configPath, "node_delete_prob"));

		//Network Parameters
		num_inputs = stoi(getConfigValue(configPath, "num_inputs"));
		num_outputs = stoi(getConfigValue(configPath, "num_outputs"));
		num_hidden = stoi(getConfigValue(configPath, "num_hidden"));
		num_connections = stoi(getConfigValue(configPath, "num_connections"));

		//Connection Weights
		weight_mutate_prob = stof(getConfigValue(configPath, "weight_mutate_prob"));
		weight_replace_prob = stof(getConfigValue(configPath, "weight_replace_prob"));

		//Reproduction rates
		survival_threshold = stof(getConfigValue(configPath, "survival_threshold"));
		minimum_network_size = stoi(getConfigValue(configPath, "minimum_network_size"));
	}

	network(string configPath) {
		init(configPath, true, false);
	}
	network(string configPath, bool updateValuesRealtime) {
		init(configPath, updateValuesRealtime, false);
	}
	network(string configPath, bool updateValuesRealtime, bool printTrainingTimes) {
		init(configPath, updateValuesRealtime, printTrainingTimes);
	}

	void generateNewRandomNetwork() {
		genomes = list<genome>();
		for (int i : range(0, pop_size)) {
			genome temp;
			temp.generateNewRandomGenome(num_inputs, num_outputs, num_hidden, num_connections);
			genomes.append(temp);
		}
	}

	float clamp(float n, float min, float max) {
		if (n > max) { n = max; }
		if (n < min) { n = min; }
		return n;
	}

	genome getMutatedGenomeCopy(genome orig) {
		//Remember, the input value "result" is a "genome()" object
		//result.genomes gives the list of the nodes
		genome result = orig;

		if ((float)rand() / RAND_MAX > conn_add_prob) {
			int index_1 = rand() % genomes.count;
			int index_2 = rand() % genomes.count;
			while (index_1 == index_2) {
				index_2 = rand() % genomes.count;
			}

			genome temp = result;
			Node node_1 = getListObject(temp.genomes, index_1);
			Node node_2 = getListObject(temp.genomes, index_2);
			node_1.connected_nodes.append(node_2);
			node_1.connection_weights.append((float)rand() * 2 / RAND_MAX - 1);
			if (!temp.isGenomeStable()) {
				temp = result;
				Node node_1 = getListObject(temp.genomes, index_2);
				Node node_2 = getListObject(temp.genomes, index_1);
				node_1.connected_nodes.append(node_2);
				node_1.connection_weights.append((float)rand() * 2 / RAND_MAX - 1);
			}
			if (temp.isGenomeStable()) {
				result = temp;
			}
		}

		if ((float)rand() / RAND_MAX > conn_delete_prob) {
			if (result.genomes.count != 0) {
				int index = rand() % result.genomes.count;
				while (getListObject(result.genomes, index).node_type == "input") {
					index = rand() % result.genomes.count;
				}

				if (getListObject(result.genomes, index).connected_nodes.count != 0) {
					int index_2 = rand() % getListObject(result.genomes, index).connected_nodes.count;
					getListObject(result.genomes, index).connected_nodes.erase(index_2 - 1);
					getListObject(result.genomes, index).connection_weights.erase(index_2 - 1);
				}
			}
		}
	}
};

int main(int argc, char **argv) {
	system("PAUSE");
	return 0;
}

