using namespace std; 

#include <iostream>
#define print(x) cout << x << endl
#include "list2.h"

class Node {
public:
	bool null_result = false;
	unsigned long long id = getNextInt();
	string node_type;
	referenced_list<Node> connected_nodes;
	list<float> connection_weights;
	float node_input = -1000;
	float node_bias = (float)rand() * 2 / RAND_MAX - 1;

	float getNodeOutput() { getNodeOutput(referenced_list<Node>()); }
	float getNodeOutput(referenced_list<Node> nodeManager) {
		if (nodeManager.contains(this)) {
			return -1000;
		} else { nodeManager.append(this); }

		if (node_type == "input") { return node_input; }

		int result = 0;
		for (int loops = 0; loops < connected_nodes.count; loops++) {
			Node node_data_1 = *connected_nodes.get(loops);
			float node_data_2 = connection_weights.get(loops);

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
public:
	float fitness = 0;
	int generationsSurvived = 0;
	referenced_list<Node> genomes = referenced_list<Node>();

	void clearGenomeData() { genomes = referenced_list<Node>(); }

	referenced_list<Node> getInputNodes() {
		referenced_list<Node> result;
		for (int i = 0; i < genomes.count; i++) {
			if (genomes.get(i)->node_type == "input") { result.append(genomes.get(i)); }
		}
		return result;
	}

	referenced_list<Node> getOutputNodes() {
		referenced_list<Node> result;
		for (int i = 0; i < genomes.count; i++) {
			if (genomes.get(i)->node_type == "output") { result.append(genomes.get(i)); }
		}
		return result;
	}

	referenced_list<Node> getHiddenNodes() {
		referenced_list<Node> result;
		for (int i = 0; i < genomes.count; i++) {
			if (genomes.get(i)->node_type == "hidden") { result.append(genomes.get(i)); }
		}
		return result;
	}

	void generateNewRandomGenome(int inputs, int outputs, int hidden, int connections) {
		clearGenomeData();

		for (int i = 0; i < inputs; ++i) {
			Node temp = *new Node();
			temp.node_type = "input";
			genomes.append(&temp);
		}

		for (int i = 0; i < outputs; ++i) {
			Node temp = *new Node();
			temp.node_type = "output";
			genomes.append(&temp);
		}

		for (int i = 0; i < hidden; ++i) {
			Node temp = *new Node();
			temp.node_type = "hidden";
			genomes.append(&temp);
		}

		for (int i = 0; i < connections; ++i) {
			//Now here's the random part. In here we connect a bunch of nodes randomly and simply ask if the structure is stable
			int index_1 = rand() % genomes.count;
			int index_2 = rand() % genomes.count;
			while (index_1 == index_2) {
				index_2 = rand() % genomes.count;
			}

			//Now we have our 2 indexes. Simply connect them
			genome testGenome = *this;
			Node test_node_1 = *testGenome.genomes.get(index_1);
			Node test_node_2 = *testGenome.genomes.get(index_2);

			test_node_1.connected_nodes.append(&test_node_2);
			test_node_1.connection_weights.append((float)rand() * 2 / RAND_MAX - 1);

			if (testGenome.isGenomeStable()) {
				genomes = testGenome.genomes;
			} else {
				testGenome = *this;
				test_node_1 = *testGenome.genomes.get(index_2);
				test_node_2 = *testGenome.genomes.get(index_1);
				test_node_1.connected_nodes.append(&test_node_2);
				test_node_1.connection_weights.append((float)rand() * 2 / RAND_MAX - 1);
				if (testGenome.isGenomeStable()) {
					genomes = testGenome.genomes;
				} else { print("ERROR! INVALID STRUCTURE"); }
			}
		}
	}

	bool isGenomeStable() {
		referenced_list<Node> temp = getOutputNodes();
		for (int i = 0; i < temp.count; ++i) {
			if (temp.get(i)->getNodeOutput() == -1000) {
				return false;
			}
		}
		return true;
	}

	list<float> getOutput(list<float> inputValues) {
		if (inputValues.count != getInputNodes().count) {
			throw "Number Of Supplied Inputs Does Not Match AI Configuration!";
		}

		referenced_list<Node> temp = getInputNodes();
		for (int i = 0; i < temp.count; ++i) {
			temp.get(i)->setNodeInput(inputValues.get(i));
		}

		list<float> result;
		temp = getOutputNodes();
		for (int i = 0; i < temp.count; ++i) {
			float temp2 = temp.get(i)->getNodeOutput();
			result.append(temp2);
		}

		return result;
	}
};

class network {
	
};

int main() {
	return 0;
}