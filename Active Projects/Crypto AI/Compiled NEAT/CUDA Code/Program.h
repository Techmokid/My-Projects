#pragma once

#define _USE_MATH_DEFINES
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "exceptionhelper.h"
#include <memory>
#include "stringhelper.h"

#include <std>
using namespace System;

namespace NEAT_AI {
	
	class Random final : public enable_shared_from_this<Random> {
	public:
		static shared_ptr<System::Random> rand;
	};

	class Node : public enable_shared_from_this<Node>
	{
	public:
		wstring node_type = L"";
		vector<shared_ptr<Node>> connected_nodes = vector<shared_ptr<Node>>();
		vector<float> connection_weights = vector<float>();
		float node_input = -1000;
		float upperTriggerThreshold = 1;
		float lowerTriggerThreshold = -1;

		Node(const wstring &nodeType);

		float GetNodeOutput();
		float GetNodeOutput(vector<shared_ptr<Node>> &nodeManager);

		void SetNodeInput(float x);
	};

	class Genome : public enable_shared_from_this<Genome>
	{
	public:
		float fitness = 0;
		int generationsSurvived = 0;
		vector<shared_ptr<Node>> genome = vector<shared_ptr<Node>>();
	private:
		shared_ptr<Genome> orig;

	public:
		Genome();
		Genome(const shared_ptr<Genome> &orig);

		void ClearGenomeData();

		//public static double NextDouble(Random random, double minValue, double maxValue) {
		//    return random.NextDouble() * (maxValue - minValue) + minValue;
		//}

		void GenerateNewRandomGenome(int inputs, int outputs, int hidden, int connections);

		vector<shared_ptr<Node>> GetInputNodes();

		vector<shared_ptr<Node>> GetOutputNodes();

		vector<shared_ptr<Node>> GetHiddenNodes();

		bool IsGenomeStable();

		vector<float> GetOutput(vector<float> &inputValues);
	};

	class Network : public enable_shared_from_this<Network>
	{
	public:
		bool printTrainingTimes = false;
		vector<shared_ptr<Genome>> genomes = vector<shared_ptr<Genome>>();
	private:
		vector<shared_ptr<Genome>> previousValidGenomes = vector<shared_ptr<Genome>>();

		//NEAT Variables
		wstring fitness_criterion;
		int pop_size = 0;
		float bias_max_value = 0;
		float bias_min_value = 0;
		float bias_mutate_rate = 0;
		float conn_add_prob = 0;
		float conn_delete_prob = 0;
		float node_add_prob = 0;
		float node_delete_prob = 0;
		int num_inputs = 0;
		int num_outputs = 0;
		int num_hidden = 0;
		int num_connections = 0;
		float weight_mutate_prob = 0;
		float weight_replace_prob = 0;
		float survival_threshold = 0;
		int minimum_network_size = 0;

		//public Network(string configPath) { return Network(configPath, true, false); }
		//public Network(string configPath, bool updateValuesRealtime) { return Network(configPath, updateValuesRealtime, false); }
	public:
		Network(const wstring &configPath, bool updateValuesRealtime, bool _printTrainingTimes);

		void LiveConfigUpdate(const wstring &configPath);

		float Clamp(float n, float minn, float maxn);

		void GenerateNewRandomNetwork();

	private:
		wstring GetConfigValue(const wstring &path, const wstring &key);

	public:
		double NextDouble(double minValue, double maxValue);

		shared_ptr<Genome> GetMutatedGenomeCopy(const shared_ptr<Genome> &orig);

		void UpdateGenomeList();
	};
}

namespace Crypto_AI
{
	class Crypto_AI : public enable_shared_from_this<Crypto_AI>
	{
	public:
		static void Main(vector<wstring> &args);
	};
}





























