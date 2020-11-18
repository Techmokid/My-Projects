using namespace std;﻿#include "Program.h"
using namespace std;
using namespace std;//To add:
using namespace std;
using namespace std;//float getRandomFloat() {
using namespace std;//	return float(rand())/float((RAND_MAX))
using namespace std;//}
using namespace std;
using namespace std;//int getRandomInt(min,max) {
using namespace std;//	return (min + rand()%(max - min));
using namespace std;//}
using namespace std;
using namespace std;using namespace std;
using namespace std;
using namespace std;namespace NEAT_AI
using namespace std;{
using namespace std;	Node::Node(const wstring &nodeType)
using namespace std;	{
using namespace std;		node_type = nodeType;
using namespace std;	}
using namespace std;
using namespace std;	float Node::GetNodeOutput()
using namespace std;	{
using namespace std;		return GetNodeOutput(vector<shared_ptr<Node>>());
using namespace std;	}
using namespace std;
using namespace std;	float Node::GetNodeOutput(vector<shared_ptr<Node>> &nodeManager)
using namespace std;	{
using namespace std;		if (find(nodeManager.begin(), nodeManager.end(), shared_from_this()) != nodeManager.end())
using namespace std;		{
using namespace std;			return -1000;
using namespace std;		}
using namespace std;		nodeManager.push_back(shared_from_this());
using namespace std;
using namespace std;		if (node_type == L"input")
using namespace std;		{
using namespace std;			return node_input;
using namespace std;		}
using namespace std;
using namespace std;		float result = 0;
using namespace std;		int loops = 0;
using namespace std;		for (auto i : connected_nodes)
using namespace std;		{
using namespace std;			float temp = connected_nodes[loops]->GetNodeOutput(nodeManager) * connection_weights[loops];
using namespace std;			if ((temp > upperTriggerThreshold) && (temp < lowerTriggerThreshold))
using namespace std;			{
using namespace std;				result += temp;
using namespace std;			}
using namespace std;			loops += 1;
using namespace std;		}
using namespace std;
using namespace std;		return static_cast<float>(tanh(result));
using namespace std;	}
using namespace std;
using namespace std;	void Node::SetNodeInput(float x)
using namespace std;	{
using namespace std;		node_input = x;
using namespace std;	}
using namespace std;
using namespace std;	Genome::Genome()
using namespace std;	{
using namespace std;	}
using namespace std;
using namespace std;	Genome::Genome(const shared_ptr<Genome> &orig)
using namespace std;	{
using namespace std;		this->orig = orig;
using namespace std;	}
using namespace std;
using namespace std;	void Genome::ClearGenomeData()
using namespace std;	{
using namespace std;		genome = vector<shared_ptr<Node>>();
using namespace std;	}
using namespace std;
using namespace std;	void Genome::GenerateNewRandomGenome(int inputs, int outputs, int hidden, int connections)
using namespace std;	{
using namespace std;		ClearGenomeData();
using namespace std;
using namespace std;		for (int i = 0; i < inputs; i++)
using namespace std;		{
using namespace std;			this->genome.push_back(make_shared<Node>(L"input"));
using namespace std;		}
using namespace std;		for (int i = 0; i < outputs; i++)
using namespace std;		{
using namespace std;			this->genome.push_back(make_shared<Node>(L"output"));
using namespace std;		}
using namespace std;		for (int i = 0; i < hidden; i++)
using namespace std;		{
using namespace std;			this->genome.push_back(make_shared<Node>(L"hidden"));
using namespace std;		}
using namespace std;		for (int i = 0; i < connections; i++)
using namespace std;		{
using namespace std;			bool runAgain = true;
using namespace std;			while (runAgain)
using namespace std;			{
using namespace std;				int index_1 = Random::rand->Next(0, this->genome.size());
using namespace std;				int index_2 = Random::rand->Next(0, this->genome.size());
using namespace std;
using namespace std;				while (index_1 == index_2)
using namespace std;				{
using namespace std;					index_2 = Random::rand->Next(0, this->genome.size());
using namespace std;				}
using namespace std;
using namespace std;				shared_ptr<Node> test_node_1 = this->genome[index_1];
using namespace std;				shared_ptr<Node> test_node_2 = this->genome[index_2];
using namespace std;				test_node_1->connected_nodes.push_back(test_node_2);
using namespace std;				test_node_1->connection_weights.push_back(static_cast<float>(Random::rand->NextDouble()));
using namespace std;				if (!IsGenomeStable())
using namespace std;				{
using namespace std;					int newPosition = test_node_1->connected_nodes.size() - 1;
using namespace std;					test_node_1->connected_nodes.erase(test_node_1->connected_nodes.begin() + newPosition);
using namespace std;					test_node_1->connection_weights.erase(test_node_1->connection_weights.begin() + newPosition);
using namespace std;
using namespace std;					test_node_2->connected_nodes.push_back(test_node_1);
using namespace std;					test_node_2->connection_weights.push_back(static_cast<float>(Random::rand->NextDouble()));
using namespace std;					if (!IsGenomeStable())
using namespace std;					{
using namespace std;						int newPos = test_node_2->connected_nodes.size() - 1;
using namespace std;						test_node_2->connected_nodes.erase(test_node_2->connected_nodes.begin() + newPos);
using namespace std;						test_node_2->connection_weights.erase(test_node_2->connection_weights.begin() + newPos);
using namespace std;					}
using namespace std;					else
using namespace std;					{
using namespace std;						runAgain = false;
using namespace std;					}
using namespace std;				}
using namespace std;				else
using namespace std;				{
using namespace std;					runAgain = false;
using namespace std;				}
using namespace std;			}
using namespace std;		}
using namespace std;	}
using namespace std;
using namespace std;	vector<shared_ptr<Node>> Genome::GetInputNodes()
using namespace std;	{
using namespace std;		vector<shared_ptr<Node>> result;
using namespace std;		for (auto i : genome)
using namespace std;		{
using namespace std;			if (i->node_type == L"input")
using namespace std;			{
using namespace std;				result.push_back(i);
using namespace std;			}
using namespace std;		}
using namespace std;		return result;
using namespace std;	}
using namespace std;
using namespace std;	vector<shared_ptr<Node>> Genome::GetOutputNodes()
using namespace std;	{
using namespace std;		vector<shared_ptr<Node>> result;
using namespace std;		for (auto i : genome)
using namespace std;		{
using namespace std;			if (i->node_type == L"output")
using namespace std;			{
using namespace std;				result.push_back(i);
using namespace std;			}
using namespace std;		}
using namespace std;		return result;
using namespace std;	}
using namespace std;
using namespace std;	vector<shared_ptr<Node>> Genome::GetHiddenNodes()
using namespace std;	{
using namespace std;		vector<shared_ptr<Node>> result;
using namespace std;		for (auto i : genome)
using namespace std;		{
using namespace std;			if (i->node_type == L"hidden")
using namespace std;			{
using namespace std;				result.push_back(i);
using namespace std;			}
using namespace std;		}
using namespace std;		return result;
using namespace std;	}
using namespace std;
using namespace std;	bool Genome::IsGenomeStable()
using namespace std;	{
using namespace std;		for (auto i : GetOutputNodes())
using namespace std;		{
using namespace std;			if (i->GetNodeOutput() == -1000)
using namespace std;			{
using namespace std;				return false;
using namespace std;			}
using namespace std;		}
using namespace std;
using namespace std;		return true;
using namespace std;	}
using namespace std;
using namespace std;	vector<float> Genome::GetOutput(vector<float> &inputValues)
using namespace std;	{
using namespace std;		if (inputValues.size() != GetInputNodes().size())
using namespace std;		{
using namespace std;//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
using namespace std;			throw system.InvalidOperationException(L"Number Of Supplied Inputs Does Not Match AI Configuration!");
using namespace std;		}
using namespace std;
using namespace std;		int index = 0;
using namespace std;		for (auto node_object : GetInputNodes())
using namespace std;		{
using namespace std;			node_object->SetNodeInput(inputValues[index]);
using namespace std;			index++;
using namespace std;		}
using namespace std;
using namespace std;		index = 0;
using namespace std;		vector<float> result;
using namespace std;		for (auto node_object : GetOutputNodes())
using namespace std;		{
using namespace std;			result.push_back(node_object->GetNodeOutput());
using namespace std;			index++;
using namespace std;		}
using namespace std;
using namespace std;		return result;
using namespace std;	}
using namespace std;
using namespace std;	Network::Network(const wstring &configPath, bool updateValuesRealtime, bool _printTrainingTimes)
using namespace std;	{
using namespace std;		Random::setupRandom();
using namespace std;
using namespace std;		wcout << L"NEAT AI: Setting up Variables. Please be aware this can take quite some time depending on config" << endl;
using namespace std;
using namespace std;		LiveConfigUpdate(configPath);
using namespace std;
using namespace std;		printTrainingTimes = _printTrainingTimes;
using namespace std;		GenerateNewRandomNetwork();
using namespace std;
using namespace std;		wcout << L"NEAT AI: Population size set to " << to_wstring(pop_size) << endl;
using namespace std;		wcout << L"NEAT AI: Input count " << to_wstring(num_inputs) << endl;
using namespace std;		wcout << L"NEAT AI: Output count " << to_wstring(num_outputs) << endl;
using namespace std;	}
using namespace std;
using namespace std;	void Network::LiveConfigUpdate(const wstring &configPath)
using namespace std;	{
using namespace std;		//NEAT
using namespace std;		fitness_criterion = GetConfigValue(configPath, L"fitness_criterion");
using namespace std;		pop_size = stoi(GetConfigValue(configPath, L"pop_size"));
using namespace std;
using namespace std;		//Node Bias
using namespace std;		bias_max_value = stof(GetConfigValue(configPath, L"bias_max_value"));
using namespace std;		bias_min_value = stof(GetConfigValue(configPath, L"bias_min_value"));
using namespace std;		bias_mutate_rate = stof(GetConfigValue(configPath, L"bias_mutate_rate"));
using namespace std;
using namespace std;		//Connection Rates
using namespace std;		conn_add_prob = stof(GetConfigValue(configPath, L"conn_add_prob"));
using namespace std;		conn_delete_prob = stof(GetConfigValue(configPath, L"conn_delete_prob"));
using namespace std;
using namespace std;		//Node Rates
using namespace std;		node_add_prob = stof(GetConfigValue(configPath, L"node_add_prob"));
using namespace std;		node_delete_prob = stof(GetConfigValue(configPath, L"node_delete_prob"));
using namespace std;
using namespace std;		//Network Parameters
using namespace std;		num_inputs = stoi(GetConfigValue(configPath, L"num_inputs"));
using namespace std;		num_outputs = stoi(GetConfigValue(configPath, L"num_outputs"));
using namespace std;		num_hidden = stoi(GetConfigValue(configPath, L"num_hidden"));
using namespace std;		num_connections = stoi(GetConfigValue(configPath, L"num_connections"));
using namespace std;
using namespace std;		//Connection Weight
using namespace std;		weight_mutate_prob = stof(GetConfigValue(configPath, L"weight_mutate_prob"));
using namespace std;		weight_replace_prob = stof(GetConfigValue(configPath, L"weight_replace_prob"));
using namespace std;
using namespace std;		//Default Reproduction
using namespace std;		survival_threshold = stof(GetConfigValue(configPath, L"survival_threshold"));
using namespace std;		minimum_network_size = stoi(GetConfigValue(configPath, L"minimum_network_size"));
using namespace std;	}
using namespace std;
using namespace std;	float Network::Clamp(float n, float minn, float maxn)
using namespace std;	{
using namespace std;		return max(min(maxn, n), minn);
using namespace std;	}
using namespace std;
using namespace std;	void Network::GenerateNewRandomNetwork()
using namespace std;	{
using namespace std;		genomes = vector<shared_ptr<Genome>>();
using namespace std;		for (int i = 0; i < pop_size; i++)
using namespace std;		{
using namespace std;			shared_ptr<Genome> temp = make_shared<Genome>();
using namespace std;			temp->GenerateNewRandomGenome(num_inputs, num_outputs, num_hidden, num_connections);
using namespace std;			genomes.push_back(temp);
using namespace std;		}
using namespace std;	}
using namespace std;
using namespace std;	wstring Network::GetConfigValue(const wstring &path, const wstring &key)
using namespace std;	{
using namespace std;		shared_ptr<system::IO::StreamReader> file = make_shared<system::IO::StreamReader>(path);
using namespace std;		wstring line = file->ReadLine();
using namespace std;		while (line != L"")
using namespace std;		{
using namespace std;			if (line.find(key) != wstring::npos)
using namespace std;			{
using namespace std;				line = StringHelper::replace(line, L" ", L"");
using namespace std;				line = StringHelper::replace(line, L"\t", L"");
using namespace std;				line = StringHelper::replace(line, L"\n", L"");
using namespace std;
using namespace std;				return StringHelper::split(line, L'=')[1];
using namespace std;			}
using namespace std;
using namespace std;			line = file->ReadLine();
using namespace std;		}
using namespace std;
using namespace std;		return L"";
using namespace std;	}
using namespace std;
using namespace std;	double Network::NextDouble(double minValue, double maxValue)
using namespace std;	{
using namespace std;		double temp = Random::rand->NextDouble() * (maxValue - minValue) + minValue;
using namespace std;		//Console.WriteLine(temp);
using namespace std;		return temp;
using namespace std;	}
using namespace std;
using namespace std;	shared_ptr<Genome> Network::GetMutatedGenomeCopy(const shared_ptr<Genome> &orig)
using namespace std;	{
using namespace std;		shared_ptr<Genome> result = make_shared<Genome>(orig);
using namespace std;
using namespace std;		if (Random::rand->NextDouble() > conn_add_prob && result->genome.size() != 0)
using namespace std;		{
using namespace std;			int index_1 = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;			int index_2 = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;			while (index_1 == index_2)
using namespace std;			{
using namespace std;				index_2 = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;			}
using namespace std;
using namespace std;			shared_ptr<Node> node_1 = result->genome[index_1];
using namespace std;			shared_ptr<Node> node_2 = result->genome[index_2];
using namespace std;
using namespace std;			node_1->connected_nodes.push_back(node_2);
using namespace std;			node_1->connection_weights.push_back(static_cast<float>(Random::rand->NextDouble()));
using namespace std;
using namespace std;			if (!result->IsGenomeStable())
using namespace std;			{
using namespace std;				node_1->connected_nodes.pop_back();
using namespace std;				node_1->connection_weights.pop_back();
using namespace std;
using namespace std;				node_2->connected_nodes.push_back(node_1);
using namespace std;				node_2->connection_weights.push_back(static_cast<float>(Random::rand->NextDouble()));
using namespace std;			}
using namespace std;		}
using namespace std;
using namespace std;		if (Random::rand->NextDouble() > conn_delete_prob && result->genome.size() != 0)
using namespace std;		{
using namespace std;			if (result->genome.size() > 0)
using namespace std;			{
using namespace std;				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				while (result->genome[index]->node_type == L"input")
using namespace std;				{
using namespace std;					wcout << L"Test 2" << endl;
using namespace std;					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				}
using namespace std;
using namespace std;				if (result->genome[index]->connected_nodes.size() > 0)
using namespace std;				{
using namespace std;					int index_2 = static_cast<int>(NextDouble(0, result->genome[index]->connected_nodes.size() - 1));
using namespace std;					result->genome[index]->connected_nodes.erase(result->genome[index]->connected_nodes.begin() + index_2);
using namespace std;					result->genome[index]->connection_weights.erase(result->genome[index]->connection_weights.begin() + index_2);
using namespace std;				}
using namespace std;			}
using namespace std;		}
using namespace std;
using namespace std;		if (Random::rand->NextDouble() > node_add_prob)
using namespace std;		{
using namespace std;			result->genome.push_back(make_shared<Node>(L"hidden"));
using namespace std;		}
using namespace std;
using namespace std;		if ((Random::rand->NextDouble() > node_delete_prob) && (result->GetHiddenNodes().size() != 0))
using namespace std;		{
using namespace std;			if (result->genome.size() > 0)
using namespace std;			{
using namespace std;				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				while ((result->genome[index]->node_type == L"input") || (result->genome[index]->node_type == L"output"))
using namespace std;				{
using namespace std;					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				}
using namespace std;
using namespace std;				result->genome.erase(result->genome.begin() + index);
using namespace std;			}
using namespace std;		}
using namespace std;
using namespace std;		if (Random::rand->NextDouble() > weight_mutate_prob && result->genome.size() != 0)
using namespace std;		{
using namespace std;			if (result->genome.size() > 0)
using namespace std;			{
using namespace std;				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				while (result->genome[index]->node_type == L"input")
using namespace std;				{
using namespace std;					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				}
using namespace std;
using namespace std;				if (result->genome[index]->connected_nodes.size() > 0)
using namespace std;				{
using namespace std;					int index_2 = static_cast<int>(NextDouble(0, result->genome[index]->connected_nodes.size() - 1));
using namespace std;					result->genome[index]->connection_weights[index_2] = static_cast<float>(Random::rand->NextDouble());
using namespace std;				}
using namespace std;			}
using namespace std;		}
using namespace std;
using namespace std;		if (Random::rand->NextDouble() > weight_replace_prob && result->genome.size() != 0)
using namespace std;		{
using namespace std;			if (result->genome.size() > 0)
using namespace std;			{
using namespace std;				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				while (result->genome[index]->node_type == L"input")
using namespace std;				{
using namespace std;					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				}
using namespace std;
using namespace std;				if (result->genome[index]->connected_nodes.size() > 0)
using namespace std;				{
using namespace std;					for (int looper = 0; looper < result->genome[index]->connected_nodes.size(); looper++)
using namespace std;					{
using namespace std;						result->genome[index]->connection_weights[looper] = static_cast<float>(Random::rand->NextDouble());
using namespace std;					}
using namespace std;				}
using namespace std;			}
using namespace std;		}
using namespace std;
using namespace std;		if (Random::rand->NextDouble() > bias_mutate_rate)
using namespace std;		{
using namespace std;			if (result->genome.size() > 0)
using namespace std;			{
using namespace std;				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				while (result->genome[index]->node_type == L"input")
using namespace std;				{
using namespace std;					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
using namespace std;				}
using namespace std;
using namespace std;				result->genome[index]->upperTriggerThreshold = Clamp(static_cast<float>(Random::rand->NextDouble()) - 0.5f, bias_min_value, bias_max_value);
using namespace std;				result->genome[index]->lowerTriggerThreshold = Clamp(static_cast<float>(Random::rand->NextDouble()) - 0.5f, bias_min_value, result->genome[index]->upperTriggerThreshold);
using namespace std;			}
using namespace std;		}
using namespace std;
using namespace std;		if (result->IsGenomeStable())
using namespace std;		{
using namespace std;			return result;
using namespace std;		}
using namespace std;		return GetMutatedGenomeCopy(orig);
using namespace std;		//return orig;
using namespace std;	}
using namespace std;
using namespace std;	void Network::UpdateGenomeList()
using namespace std;	{
using namespace std;		auto watch = system::Diagnostics::Stopwatch::StartNew();
using namespace std;
using namespace std;		// We now have the entire genome list ordered by fitness
using namespace std;		// 1 - Get the fitness list of all the genomes
using namespace std;		// 2 - Sort the genomes by fitness (Flip if we want minimums to win):
using namespace std;		// 3 - Perform the genetic death algorithms to wittle out poor performing genomes
using namespace std;		// 4 - Create mutated clones of winning genomes
using namespace std;		// 5 - Breed the winning genomes (NOT IMPLEMENTED)
using namespace std;
using namespace std;		//We have a unique problem that I just ignored in python.
using namespace std;		//We have to sort list 1 by list 2 values
using namespace std;
using namespace std;		//Stage 1/2
using namespace std;		vector<shared_ptr<Genome>> genomesList(genomes);
using namespace std;
using namespace std;		for (int index = genomesList.size() - 1; index >= 0; index--)
using namespace std;		{
using namespace std;			int indexOfLargest = index;
using namespace std;			for (int index2 = 0; index2 < index; index2++)
using namespace std;			{
using namespace std;				if (genomesList[index2]->fitness >= genomesList[indexOfLargest]->fitness)
using namespace std;				{
using namespace std;					indexOfLargest = index2;
using namespace std;				}
using namespace std;			}
using namespace std;
using namespace std;			shared_ptr<Genome> temp2 = genomesList[indexOfLargest];
using namespace std;			genomesList.erase(genomesList.begin() + indexOfLargest);
using namespace std;			genomesList.push_back(temp2);
using namespace std;		}
using namespace std;
using namespace std;		//Stage 3
using namespace std;		vector<shared_ptr<Genome>> temp(genomesList);
using namespace std;		genomesList = vector<shared_ptr<Genome>>();
using namespace std;		float s_t = survival_threshold;
using namespace std;		int p_s = pop_size;
using namespace std;		for (int i = 0; i < temp.size(); i++)
using namespace std;		{
using namespace std;			float survivalThreshold = static_cast<float>((1 - s_t) * pow(sin((M_PI / 2) * ((static_cast<float>(i)) / p_s)), 2) + s_t);
using namespace std;			if (Random::rand->NextDouble() < survivalThreshold)
using namespace std;			{
using namespace std;				temp[i]->generationsSurvived++;
using namespace std;				genomesList.push_back(temp[i]);
using namespace std;			}
using namespace std;			else if (temp[i]->generationsSurvived > 5)
using namespace std;			{
using namespace std;				temp[i]->generationsSurvived -= 3;
using namespace std;				genomesList.push_back(temp[i]);
using namespace std;			}
using namespace std;		}
using namespace std;
using namespace std;
using namespace std;		//Stage 4 (Somewhere in here, it gets stuck. I suspect it may be due to the random number generation not being random)
using namespace std;		if (genomesList.size() > 0)
using namespace std;		{
using namespace std;			if (genomesList.size() > minimum_network_size)
using namespace std;			{
using namespace std;				wcout << L"NEAT AI: Number of surviving genomes: " << to_wstring(genomesList.size()) << endl;
using namespace std;
using namespace std;				while (genomesList.size() < p_s)
using namespace std;				{
using namespace std;					int index = Random::rand->Next(genomesList.size());
using namespace std;					shared_ptr<Genome> i = genomesList[index];
using namespace std;					genomesList.push_back(GetMutatedGenomeCopy(i));
using namespace std;				}
using namespace std;
using namespace std;				genomes = genomesList;
using namespace std;			}
using namespace std;			else if (previousValidGenomes.size() > minimum_network_size)
using namespace std;			{
using namespace std;				wcout << L"NEAT AI: Rebooting genome from previous success attempts" << endl;
using namespace std;
using namespace std;				genomesList = vector<shared_ptr<Genome>>(previousValidGenomes);
using namespace std;				while (genomesList.size() != p_s)
using namespace std;				{
using namespace std;					int index = Random::rand->Next(genomesList.size());
using namespace std;					shared_ptr<Genome> i = genomesList[index];
using namespace std;					genomesList.push_back(GetMutatedGenomeCopy(i));
using namespace std;				}
using namespace std;
using namespace std;				genomes = genomesList;
using namespace std;			}
using namespace std;			else if (previousValidGenomes.size() + genomesList.size() > minimum_network_size)
using namespace std;			{
using namespace std;				for (auto i : previousValidGenomes)
using namespace std;				{
using namespace std;					genomesList.push_back(i);
using namespace std;				}
using namespace std;
using namespace std;				wcout << L"NEAT AI: Rebooting genome from previous success attempts appended to current network data" << endl;
using namespace std;				while (genomesList.size() != p_s)
using namespace std;				{
using namespace std;					int index = Random::rand->Next(genomesList.size());
using namespace std;					shared_ptr<Genome> i = genomesList[index];
using namespace std;					genomesList.push_back(GetMutatedGenomeCopy(i));
using namespace std;				}
using namespace std;
using namespace std;				genomes = genomesList;
using namespace std;			}
using namespace std;			else
using namespace std;			{
using namespace std;				if (genomesList.size() == 1)
using namespace std;				{
using namespace std;					wcout << L"NEAT AI: Discovered functional node. Storing node for later..." << endl;
using namespace std;				}
using namespace std;				else
using namespace std;				{
using namespace std;					wcout << L"NEAT AI: Discovered functional nodes. Storing " << to_wstring(genomesList.size()) << L" nodes for later..." << endl;
using namespace std;				}
using namespace std;
using namespace std;				for (auto i : genomesList)
using namespace std;				{
using namespace std;					previousValidGenomes.push_back(i);
using namespace std;				}
using namespace std;			}
using namespace std;		}
using namespace std;		else
using namespace std;		{
using namespace std;			wcout << L"NEAT AI: Complete extinction event, regenerating network!" << endl;
using namespace std;			GenerateNewRandomNetwork();
using namespace std;		}
using namespace std;
using namespace std;		watch->Stop();
using namespace std;
using namespace std;		if (printTrainingTimes)
using namespace std;		{
using namespace std;			wcout << L"NEAT AI: Generation Learning Time: " << to_wstring(static_cast<float>(watch->ElapsedMilliseconds) / 1000) << L"s" << endl;
using namespace std;			wcout << L" - Number of genomes: " << to_wstring(genomesList.size()) << endl;
using namespace std;			wcout << endl;
using namespace std;		}
using namespace std;	}
using namespace std;}
using namespace std;
using namespace std;namespace NEAT_AI
using namespace std;{
using namespace std;
using namespace std;	void Program::cleanupGenomes(shared_ptr<Network> &nn)
using namespace std;	{
using namespace std;		for (int i = 0; i < nn->genomes.size(); i++)
using namespace std;		{
using namespace std;			if (nn->genomes[i]->fitness == 500)
using namespace std;			{
using namespace std;				nn->genomes.erase(nn->genomes.begin() + i);
using namespace std;			}
using namespace std;		}
using namespace std;	}
using namespace std;
using namespace std;	void Program::Main(vector<wstring> &args)
using namespace std;	{
using namespace std;		shared_ptr<Network> nn = make_shared<Network>(L"C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/config.txt",true,true);
using namespace std;
using namespace std;		for (int i = 0; i < nn->genomes.size(); i++)
using namespace std;		{
using namespace std;			nn->genomes[i]->fitness = static_cast<float>(Random::rand->NextDouble());
using namespace std;		}
using namespace std;
using namespace std;		//cleanupGenomes(ref nn);
using namespace std;		//nn.UpdateGenomeList();
using namespace std;
using namespace std;		return;
using namespace std;	}
using namespace std;}
