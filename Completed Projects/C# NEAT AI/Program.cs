using System;
using System.Net;
using System.IO;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

<<<<<<< HEAD
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

=======
>>>>>>> bf71fb01dd2582e9a7106c7c8807ec1de14ba95c
using NEAT_AI;
using Binance_API;

namespace WebAPIClient {
	class Program {
		static int iterations = 500000;
		static Network nn;
		
		class deserializedJSON2 {
			[JsonPropertyName("id")]
			public double id { get; set; }
			
			[JsonPropertyName("time")]
			public double time { get; set; }
			
			[JsonPropertyName("price")]
			public string price { get; set; }
		}
		
        static void Main(string[] args) {
			for(int i = 0; i < 50; i++) { Console.WriteLine(); }
			
			Console.WriteLine("[Main Thread][Info]: Collecting historic prices....");
<<<<<<< HEAD
			
			API.getHistoricTrades();
			//string data = API.getExchangeInfo();
			
            nn = new Network("C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Completed Projects/C# NEAT AI",false,true,false);
=======
			API.getHistoricTrades();
			//string data = API.getExchangeInfo();
			
            nn = new Network("C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/config.txt",false,true);
>>>>>>> bf71fb01dd2582e9a7106c7c8807ec1de14ba95c
			//nn.loadNetwork();
			
			Console.WriteLine("[Main Thread][Info]: Running Network....");
			for (int currentIteration = 0; currentIteration < iterations; currentIteration++) {
				for (int i = 0; i < nn.genomes.Count; i++) {
					Console.WriteLine("[Main Thread][Info]: - Training genome: " + i.ToString());
					nn.genomes[i].fitness = getGenomeFitness(nn.genomes[i]);
					
					if (nn.genomes[i].fitness == 500) {
						Console.WriteLine("[Main Thread][Info]: Set genome for destruction");
					}
				}
				
				Console.WriteLine("[Main Thread][Info]: Scanning for destruct-marked genomes");
				for (int i = 0; i < nn.genomes.Count; i++) {
					//if ((nn.genomes[i].fitness == 500) || (nn.genomes[i].fitness == 0)) {
					if (nn.genomes[i].fitness == 500) {
						nn.genomes.RemoveAt(i);
						i--;
						Console.WriteLine("[Main Thread][Info]: Destroyed genome for invalid output");
					}
				}
				
<<<<<<< HEAD
				Console.WriteLine("[NEAT AI][Info]: Saving Network...");
				nn.saveNetwork();
				Console.WriteLine("[NEAT AI][Info]: Saved Network");
				Console.WriteLine("[NEAT AI][Info]: Updating Network...");
				nn.UpdateGenomeList();
				Console.WriteLine("[NEAT AI][Info]: Network Updated");
				Console.WriteLine("[Main Thread][Info]: Next Iteration");
=======
				nn.saveNetwork(true);
				nn.UpdateGenomeList();
>>>>>>> bf71fb01dd2582e9a7106c7c8807ec1de14ba95c
			}
			
            return;
		}
		
		static float getGenomeFitness(Genome genome) {
<<<<<<< HEAD
			StreamReader file = new StreamReader("C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Completed Projects/C# NEAT AI/SaveData/HistoricDataCache.txt");
=======
			StreamReader file = new StreamReader("C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/HistoricDataCache.txt");
>>>>>>> bf71fb01dd2582e9a7106c7c8807ec1de14ba95c
			//StreamReader file = new StreamReader("C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/example.json");
            string line = file.ReadLine(); string jsonOutput = "";
            while (line != null) { jsonOutput += line; line = file.ReadLine(); }
			
			float fakeWallet = 500;
			JsonElement obj = JsonSerializer.Deserialize<JsonElement>(jsonOutput);
			
			//Here we wanna cycle over each combination and ask the network if it wants to buy or sell
			for (int i = 1; i < obj.GetArrayLength() - nn.num_inputs; i++) {
				string objString1 = obj[i-1].ToString();
				string objString2 = obj[i].ToString();
				//Console.WriteLine("objString: " + (string)objString);
				
				deserializedJSON2 data1 = JsonSerializer.Deserialize<deserializedJSON2>(objString1);
				deserializedJSON2 data2 = JsonSerializer.Deserialize<deserializedJSON2>(objString2);
				//Console.WriteLine("Price: " + (string)data1.price);
				
				List<float> genomeInputValues = new List<float>();
				for (int pricePointIndex = i; pricePointIndex < nn.num_inputs + i; pricePointIndex++) {
					float y = float.Parse(data2.price) - float.Parse(data1.price);
					genomeInputValues.Add(((float)Math.Atan(y)) / ((float)Math.PI));
				}
				
				List<float> genomeOutput = genome.GetOutput(nn,genomeInputValues);
				//Console.WriteLine(genomeOutput[0].ToString() + ":" + genomeOutput[1].ToString());
				if (Math.Pow(genomeOutput[0],20) > -0.5f) {
					//Here we wanna buy
					fakeWallet -= float.Parse(data2.price);
				} else if (Math.Pow(genomeOutput[1],20) > -0.5f) {
					//Here we wanna sell
					fakeWallet += float.Parse(data2.price) - 0.5f;
				}
			}
			
			//Console.WriteLine(fakeWallet);
			
			return fakeWallet;
		}
	}
}





























