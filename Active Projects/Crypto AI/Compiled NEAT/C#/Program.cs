using System;
using System.Collections.Generic;

using NEAT_AI;
using Binance_API;

namespace WebAPIClient {
	class Program {
		static int iterations = 500;

        static void Main(string[] args) {
			for(int i = 0; i < 50; i++) { Console.WriteLine(); }
			
            Network nn = new Network("C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/config.txt",true,true,true);
			nn.loadNetwork();
			
			Console.WriteLine("[Main Thread][Info]: Running Network....");
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
			
			Console.ForegroundColor = ConsoleColor.Yellow;
			Console.WriteLine("[Main Thread][Warning]: Genome Fitness Calculation Error: Empty Function!");
			Console.ResetColor();
			
			Console.WriteLine(Binance_API.API.getHistoricTrades("ETHBTC"));
			Console.ReadKey(true);
			
			return fakeWallet;
		}
	}
}





























