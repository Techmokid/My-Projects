using System;
using System.Threading.Tasks;
using System.Collections.Generic;

using NEAT_AI;
using Binance_API;

namespace WebAPIClient {
	class Program {
        static void CleanupGenomes(ref Network nn) {
			for (int i = 0; i < nn.genomes.Count; i++) {
				if (nn.genomes[i].fitness == 500) {
					nn.genomes.RemoveAt(i);
				}
			}
		}

        
        static void Main(string[] args) {
            //Network nn = new Network("C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/config.txt",true,true);
			
			//for (int i = 0; i < nn.genomes.Count; i++) {
			//	nn.genomes[i].fitness = (float)NEAT_AI.Random.rand.NextDouble();
			//}
			
			//CleanupGenomes(ref nn);
			//nn.UpdateGenomeList();

            //Console.WriteLine(Binance_API.API.makeCall("https://api.binance.com/sapi/v1/capital/config/getall","symbol=LTCBTC",true));
			//Console.WriteLine(Binance_API.API.getServerConnectivity());
			//Console.WriteLine(Binance_API.API.getServerTime());
			
            return;
		}
	}
}





























