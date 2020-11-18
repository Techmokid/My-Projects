#include "Program.h"

namespace NEAT_AI
{

std::shared_ptr<System::Random> Random::rand = std::make_shared<System::Random>();

	Node::Node(const std::wstring &nodeType)
	{
		node_type = nodeType;
	}

	float Node::GetNodeOutput()
	{
		return GetNodeOutput(std::vector<std::shared_ptr<Node>>());
	}

	float Node::GetNodeOutput(std::vector<std::shared_ptr<Node>> &nodeManager)
	{
		if (std::find(nodeManager.begin(), nodeManager.end(), shared_from_this()) != nodeManager.end())
		{
			return -1000;
		}
		nodeManager.push_back(shared_from_this());

		if (node_type == L"input")
		{
			return node_input;
		}

		float result = 0;
		int loops = 0;
		for (auto i : connected_nodes)
		{
			float temp = connected_nodes[loops]->GetNodeOutput(nodeManager) * connection_weights[loops];
			if ((temp > upperTriggerThreshold) && (temp < lowerTriggerThreshold))
			{
				result += temp;
			}
			loops += 1;
		}

		return static_cast<float>(std::tanh(result));
	}

	void Node::SetNodeInput(float x)
	{
		node_input = x;
	}

	Genome::Genome()
	{
	}

	Genome::Genome(const std::shared_ptr<Genome> &orig)
	{
		this->orig = orig;
	}

	void Genome::ClearGenomeData()
	{
		genome = std::vector<std::shared_ptr<Node>>();
	}

	void Genome::GenerateNewRandomGenome(int inputs, int outputs, int hidden, int connections)
	{
		ClearGenomeData();

		for (int i = 0; i < inputs; i++)
		{
			this->genome.push_back(std::make_shared<Node>(L"input"));
		}
		for (int i = 0; i < outputs; i++)
		{
			this->genome.push_back(std::make_shared<Node>(L"output"));
		}
		for (int i = 0; i < hidden; i++)
		{
			this->genome.push_back(std::make_shared<Node>(L"hidden"));
		}
		for (int i = 0; i < connections; i++)
		{
			bool runAgain = true;
			while (runAgain)
			{
				int index_1 = Random::rand->Next(0, this->genome.size());
				int index_2 = Random::rand->Next(0, this->genome.size());

				while (index_1 == index_2)
				{
					index_2 = Random::rand->Next(0, this->genome.size());
				}

				std::shared_ptr<Node> test_node_1 = this->genome[index_1];
				std::shared_ptr<Node> test_node_2 = this->genome[index_2];
				test_node_1->connected_nodes.push_back(test_node_2);
				test_node_1->connection_weights.push_back(static_cast<float>(Random::rand->NextDouble()));
				if (!IsGenomeStable())
				{
					int newPosition = test_node_1->connected_nodes.size() - 1;
					test_node_1->connected_nodes.erase(test_node_1->connected_nodes.begin() + newPosition);
					test_node_1->connection_weights.erase(test_node_1->connection_weights.begin() + newPosition);

					test_node_2->connected_nodes.push_back(test_node_1);
					test_node_2->connection_weights.push_back(static_cast<float>(Random::rand->NextDouble()));
					if (!IsGenomeStable())
					{
						int newPos = test_node_2->connected_nodes.size() - 1;
						test_node_2->connected_nodes.erase(test_node_2->connected_nodes.begin() + newPos);
						test_node_2->connection_weights.erase(test_node_2->connection_weights.begin() + newPos);
					}
					else
					{
						runAgain = false;
					}
				}
				else
				{
					runAgain = false;
				}
			}
		}
	}

	std::vector<std::shared_ptr<Node>> Genome::GetInputNodes()
	{
		std::vector<std::shared_ptr<Node>> result;
		for (auto i : genome)
		{
			if (i->node_type == L"input")
			{
				result.push_back(i);
			}
		}
		return result;
	}

	std::vector<std::shared_ptr<Node>> Genome::GetOutputNodes()
	{
		std::vector<std::shared_ptr<Node>> result;
		for (auto i : genome)
		{
			if (i->node_type == L"output")
			{
				result.push_back(i);
			}
		}
		return result;
	}

	std::vector<std::shared_ptr<Node>> Genome::GetHiddenNodes()
	{
		std::vector<std::shared_ptr<Node>> result;
		for (auto i : genome)
		{
			if (i->node_type == L"hidden")
			{
				result.push_back(i);
			}
		}
		return result;
	}

	bool Genome::IsGenomeStable()
	{
		for (auto i : GetOutputNodes())
		{
			if (i->GetNodeOutput() == -1000)
			{
				return false;
			}
		}

		return true;
	}

	std::vector<float> Genome::GetOutput(std::vector<float> &inputValues)
	{
		if (inputValues.size() != GetInputNodes().size())
		{
//C# TO C++ CONVERTER TODO TASK: The following line could not be converted:
			throw System.InvalidOperationException(L"Number Of Supplied Inputs Does Not Match AI Configuration!");
		}

		int index = 0;
		for (auto node_object : GetInputNodes())
		{
			node_object->SetNodeInput(inputValues[index]);
			index++;
		}

		index = 0;
		std::vector<float> result;
		for (auto node_object : GetOutputNodes())
		{
			result.push_back(node_object->GetNodeOutput());
			index++;
		}

		return result;
	}

	Network::Network(const std::wstring &configPath, bool updateValuesRealtime, bool _printTrainingTimes)
	{
		std::wcout << L"NEAT AI: Setting up Variables. Please be aware this can take quite some time depending on config" << std::endl;

		LiveConfigUpdate(configPath);

		printTrainingTimes = _printTrainingTimes;
		GenerateNewRandomNetwork();

		std::wcout << L"NEAT AI: Population size set to " << std::to_wstring(pop_size) << std::endl;
		std::wcout << L"NEAT AI: Input count " << std::to_wstring(num_inputs) << std::endl;
		std::wcout << L"NEAT AI: Output count " << std::to_wstring(num_outputs) << std::endl;
	}

	void Network::LiveConfigUpdate(const std::wstring &configPath)
	{
		//NEAT
		fitness_criterion = GetConfigValue(configPath, L"fitness_criterion");
		pop_size = std::stoi(GetConfigValue(configPath, L"pop_size"));

		//Node Bias
		bias_max_value = std::stof(GetConfigValue(configPath, L"bias_max_value"));
		bias_min_value = std::stof(GetConfigValue(configPath, L"bias_min_value"));
		bias_mutate_rate = std::stof(GetConfigValue(configPath, L"bias_mutate_rate"));

		//Connection Rates
		conn_add_prob = std::stof(GetConfigValue(configPath, L"conn_add_prob"));
		conn_delete_prob = std::stof(GetConfigValue(configPath, L"conn_delete_prob"));

		//Node Rates
		node_add_prob = std::stof(GetConfigValue(configPath, L"node_add_prob"));
		node_delete_prob = std::stof(GetConfigValue(configPath, L"node_delete_prob"));

		//Network Parameters
		num_inputs = std::stoi(GetConfigValue(configPath, L"num_inputs"));
		num_outputs = std::stoi(GetConfigValue(configPath, L"num_outputs"));
		num_hidden = std::stoi(GetConfigValue(configPath, L"num_hidden"));
		num_connections = std::stoi(GetConfigValue(configPath, L"num_connections"));

		//Connection Weight
		weight_mutate_prob = std::stof(GetConfigValue(configPath, L"weight_mutate_prob"));
		weight_replace_prob = std::stof(GetConfigValue(configPath, L"weight_replace_prob"));

		//Default Reproduction
		survival_threshold = std::stof(GetConfigValue(configPath, L"survival_threshold"));
		minimum_network_size = std::stoi(GetConfigValue(configPath, L"minimum_network_size"));
	}

	float Network::Clamp(float n, float minn, float maxn)
	{
		return std::max(std::min(maxn, n), minn);
	}

	void Network::GenerateNewRandomNetwork()
	{
		genomes = std::vector<std::shared_ptr<Genome>>();
		for (int i = 0; i < pop_size; i++)
		{
			std::shared_ptr<Genome> temp = std::make_shared<Genome>();
			temp->GenerateNewRandomGenome(num_inputs, num_outputs, num_hidden, num_connections);
			genomes.push_back(temp);
		}
	}

	std::wstring Network::GetConfigValue(const std::wstring &path, const std::wstring &key)
	{
		std::shared_ptr<System::IO::StreamReader> file = std::make_shared<System::IO::StreamReader>(path);
		std::wstring line = file->ReadLine();
		while (line != L"")
		{
			if (line.find(key) != std::wstring::npos)
			{
				line = StringHelper::replace(line, L" ", L"");
				line = StringHelper::replace(line, L"\t", L"");
				line = StringHelper::replace(line, L"\n", L"");

				return StringHelper::split(line, L'=')[1];
			}

			line = file->ReadLine();
		}

		return L"";
	}

	double Network::NextDouble(double minValue, double maxValue)
	{
		return Random::rand->NextDouble() * (maxValue - minValue) + minValue;
	}

	std::shared_ptr<Genome> Network::GetMutatedGenomeCopy(const std::shared_ptr<Genome> &orig)
	{
		std::shared_ptr<Genome> result = std::make_shared<Genome>(orig);

		if (Random::rand->NextDouble() > conn_add_prob)
		{
			int index_1 = static_cast<int>(NextDouble(0, result->genome.size() - 1));
			int index_2 = static_cast<int>(NextDouble(0, result->genome.size() - 1));
			while (index_1 == index_2)
			{
				index_2 = static_cast<int>(NextDouble(0, result->genome.size() - 1));
			}

			std::shared_ptr<Node> node_1 = result->genome[index_1];
			std::shared_ptr<Node> node_2 = result->genome[index_2];

			node_1->connected_nodes.push_back(node_2);
			node_1->connection_weights.push_back(static_cast<float>(Random::rand->NextDouble()));

			if (!result->IsGenomeStable())
			{
				node_1->connected_nodes.pop_back();
				node_1->connection_weights.pop_back();

				node_2->connected_nodes.push_back(node_1);
				node_2->connection_weights.push_back(static_cast<float>(Random::rand->NextDouble()));
			}
		}

		if (Random::rand->NextDouble() > conn_delete_prob)
		{
			if (result->genome.size() > 0)
			{
				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				while (result->genome[index]->node_type == L"input")
				{
					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				}

				if (result->genome[index]->connected_nodes.size() > 0)
				{
					int index_2 = static_cast<int>(NextDouble(0, result->genome[index]->connected_nodes.size() - 1));
					result->genome[index]->connected_nodes.erase(result->genome[index]->connected_nodes.begin() + index_2);
					result->genome[index]->connection_weights.erase(result->genome[index]->connection_weights.begin() + index_2);
				}
			}
		}

		if (Random::rand->NextDouble() > node_add_prob)
		{
			result->genome.push_back(std::make_shared<Node>(L"hidden"));
		}

		if ((Random::rand->NextDouble() > node_delete_prob) && (result->GetHiddenNodes().size() != 0))
		{
			if (result->genome.size() > 0)
			{
				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				while ((result->genome[index]->node_type == L"input") || (result->genome[index]->node_type == L"output"))
				{
					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				}

				result->genome.erase(result->genome.begin() + index);
			}
		}

		if (Random::rand->NextDouble() > weight_mutate_prob)
		{
			if (result->genome.size() > 0)
			{
				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				while (result->genome[index]->node_type == L"input")
				{
					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				}

				if (result->genome[index]->connected_nodes.size() > 0)
				{
					int index_2 = static_cast<int>(NextDouble(0, result->genome[index]->connected_nodes.size() - 1));
					result->genome[index]->connection_weights[index_2] = static_cast<float>(Random::rand->NextDouble());
				}
			}
		}

		if (Random::rand->NextDouble() > weight_replace_prob)
		{
			if (result->genome.size() > 0)
			{
				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				while (result->genome[index]->node_type == L"input")
				{
					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				}

				if (result->genome[index]->connected_nodes.size() > 0)
				{
					for (int looper = 0; looper < result->genome[index]->connected_nodes.size(); looper++)
					{
						result->genome[index]->connection_weights[looper] = static_cast<float>(Random::rand->NextDouble());
					}
				}
			}
		}

		if (Random::rand->NextDouble() > bias_mutate_rate)
		{
			if (result->genome.size() > 0)
			{
				int index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				while (result->genome[index]->node_type == L"input")
				{
					index = static_cast<int>(NextDouble(0, result->genome.size() - 1));
				}

				result->genome[index]->upperTriggerThreshold = Clamp(static_cast<float>(Random::rand->NextDouble()) - 0.5f, bias_min_value, bias_max_value);
				result->genome[index]->lowerTriggerThreshold = Clamp(static_cast<float>(Random::rand->NextDouble()) - 0.5f, bias_min_value, result->genome[index]->upperTriggerThreshold);
			}
		}

		if (result->IsGenomeStable())
		{
			return result;
		}
		return GetMutatedGenomeCopy(orig);
		//return orig;
	}

	void Network::UpdateGenomeList()
	{
		auto watch = System::Diagnostics::Stopwatch::StartNew();

		// We now have the entire genome list ordered by fitness
		// 1 - Get the fitness list of all the genomes
		// 2 - Sort the genomes by fitness (Flip if we want minimums to win):
		// 3 - Perform the genetic death algorithms to wittle out poor performing genomes
		// 4 - Create mutated clones of winning genomes
		// 5 - Breed the winning genomes (NOT IMPLEMENTED)

		//We have a unique problem that I just ignored in python.
		//We have to sort list 1 by list 2 values

		//Stage 1/2
		std::vector<std::shared_ptr<Genome>> genomesList(genomes);

		for (int index = genomesList.size() - 1; index >= 0; index--)
		{
			int indexOfLargest = index;
			for (int index2 = 0; index2 < index; index2++)
			{
				if (genomesList[index2]->fitness >= genomesList[indexOfLargest]->fitness)
				{
					indexOfLargest = index2;
				}
			}

			std::shared_ptr<Genome> temp2 = genomesList[indexOfLargest];
			genomesList.erase(genomesList.begin() + indexOfLargest);
			genomesList.push_back(temp2);
		}

		//Stage 3
		std::vector<std::shared_ptr<Genome>> temp(genomesList);
		genomesList = std::vector<std::shared_ptr<Genome>>(genomesList);
		float s_t = survival_threshold;
		int p_s = pop_size;
		for (int i = 0; i < temp.size(); i++)
		{
			float survivalThreshold = static_cast<float>((1 - s_t) * std::pow(std::sin((M_PI / 2) * ((static_cast<float>(i)) / p_s)), 2) + s_t);
			if (Random::rand->NextDouble() < survivalThreshold)
			{
				temp[i]->generationsSurvived++;
				genomesList.push_back(temp[i]);
			}
			else if (temp[i]->generationsSurvived > 5)
			{
				temp[i]->generationsSurvived -= 3;
				genomesList.push_back(temp[i]);
			}
		}

		//Stage 4
		if (genomesList.size() > 0)
		{
			if (genomesList.size() > minimum_network_size)
			{
				std::wcout << L"NEAT AI: Number of surviving genomes: " << std::to_wstring(genomesList.size()) << std::endl;

				while (genomesList.size() != p_s)
				{
					int index = Random::rand->Next(genomesList.size());
					std::shared_ptr<Genome> i = genomesList[index];
					genomesList.push_back(GetMutatedGenomeCopy(i));
				}

				genomes = genomesList;
			}
			else if (previousValidGenomes.size() > minimum_network_size)
			{
				std::wcout << L"NEAT AI: Rebooting genome from previous success attempts" << std::endl;

				genomesList = std::vector<std::shared_ptr<Genome>>(previousValidGenomes);
				while (genomesList.size() != p_s)
				{
					int index = Random::rand->Next(genomesList.size());
					std::shared_ptr<Genome> i = genomesList[index];
					genomesList.push_back(GetMutatedGenomeCopy(i));
				}

				genomes = genomesList;
			}
			else if (previousValidGenomes.size() + genomesList.size() > minimum_network_size)
			{
				for (auto i : previousValidGenomes)
				{
					genomesList.push_back(i);
				}

				std::wcout << L"NEAT AI: Rebooting genome from previous success attempts appended to current network data" << std::endl;
				while (genomesList.size() != p_s)
				{
					int index = Random::rand->Next(genomesList.size());
					std::shared_ptr<Genome> i = genomesList[index];
					genomesList.push_back(GetMutatedGenomeCopy(i));
				}

				genomes = genomesList;
			}
			else
			{
				if (genomesList.size() == 1)
				{
					std::wcout << L"NEAT AI: Discovered functional node. Storing node for later..." << std::endl;
				}
				else
				{
					std::wcout << L"NEAT AI: Discovered functional nodes. Storing " << std::to_wstring(genomesList.size()) << L" nodes for later..." << std::endl;
				}

				for (auto i : genomesList)
				{
					previousValidGenomes.push_back(i);
				}
			}
		}
		else
		{
			std::wcout << L"NEAT AI: Complete extinction event, regenerating network!" << std::endl;
			GenerateNewRandomNetwork();
		}

		watch->Stop();

		if (printTrainingTimes)
		{
			std::wcout << L"NEAT AI: Generation Learning Time: " << std::to_wstring(watch->ElapsedMilliseconds) << L"s" << std::endl;
			std::wcout << L" - Number of genomes: " << std::to_wstring(genomesList.size()) << std::endl;
		}
	}
}

namespace Crypto_AI
{

	void Crypto_AI::Main(std::vector<std::wstring> &args)
	{
		std::shared_ptr<NEAT_AI::Network> nn = std::make_shared<NEAT_AI::Network>(L"C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/C#/config.txt",true,false);
		//nn.UpdateGenomeList();
		return;
	}
}
