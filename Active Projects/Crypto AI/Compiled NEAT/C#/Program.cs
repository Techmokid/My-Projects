using System;
using System.Collections.Generic;

using NEAT_AI;
using Binance_API;

namespace WebAPIClient {
	class Program {
		static int iterations = 500;

        static void Main(string[] args) {
            Network nn = new Network("C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/config.txt",true,true,true);
			nn.loadNetwork();
			
			Console.WriteLine("Running Network....");
			for (int currentIteration = 0; currentIteration < iterations; currentIteration++) {
				for (int i = 0; i < nn.genomes.Count; i++) {
					nn.genomes[i].fitness = getGenomeFitness(nn.genomes[i]);
				}
				
				for (int i = 0; i < nn.genomes.Count; i++) {
					if (nn.genomes[i].fitness == 500) {
						nn.genomes.RemoveAt(i);
					}
				}
				
				nn.UpdateGenomeList();
			}
			
            return;
		}
		
		static float getGenomeFitness(Genome genome) {
			float fakeWallet = 501;
			
			//Console.WriteLine("INCOMPLETE SECTION: This is the last function before the code is ready");
			//Console.WriteLine(Binance_API.API.getHistoricTrades("ETHBTC"));
			//Console.ReadKey(true);
			
			return fakeWallet;
		}
	}
}





























