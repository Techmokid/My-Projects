﻿using System;
using System.IO;
using System.Net;
using System.Linq;
using System.Threading;
using System.Diagnostics;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

using NEAT_AI;
using Display;
using Binance_API;
using PointAnalysis;

namespace WebAPIClient {
	class Program {
		static string filePath = "F:";
		static string API_Time_Enum = "1h";
		static float tax_percentage = 0.1f;
		static float startingWalletValue = 5000;
		static Network nn;
		
		class deserializedJSON2 {
			[JsonPropertyName("id")]
			public double id { get; set; }
			
			[JsonPropertyName("price")]
			public string price { get; set; }
			
			[JsonPropertyName("time")]
			public double time { get; set; }
		}
		
		class deserializedSymbolsJSON {
			[JsonPropertyName("symbols")]
			public dynamic symbols { get; set; }
			
			[JsonPropertyName("timezone")]
			public string timezone { get; set; }
		}
		
		class deserializedSymbolJSON {
			[JsonPropertyName("symbol")]
			public string symbol { get; set; }
		}
		
		class deserializedDataPoint1JSON {
			[JsonPropertyName("id")]
			public long id { get; set; }
			
			[JsonPropertyName("price")]
			public string price { get; set; }
			
			[JsonPropertyName("time")]
			public long time { get; set; }
		}
		
		class deserializedDataPoint2JSON {
			[JsonPropertyName("a")]
			public long id { get; set; }
			
			[JsonPropertyName("p")]
			public string price { get; set; }
			
			[JsonPropertyName("T")]
			public long time { get; set; }
		}
		
		static List<string> retrieveAllCurrencySymbols() {
			List<string> result = new List<string>();
			deserializedSymbolsJSON temp2 = JsonSerializer.Deserialize<deserializedSymbolsJSON>(API.getExchangeInfo());
			
			string fileLocation = filePath + "/currencySymbols.txt";
			if (File.Exists(fileLocation)) { File.Delete(fileLocation); }
			
			FileStream stream = new FileStream(fileLocation, FileMode.OpenOrCreate);  
			using(StreamWriter writer = new StreamWriter(stream, Encoding.UTF8)) {
				for(int i = 0; i < temp2.symbols.GetArrayLength(); i++) {
					deserializedSymbolJSON temp3 = JsonSerializer.Deserialize<deserializedSymbolJSON>(temp2.symbols[i].ToString());
					writer.WriteLine(temp3.symbol);
					result.Add(temp3.symbol);
				}
			}
			
			return result;
		}
		
		static int getNumberOfProcessorThreads() {
			Process cmd = new Process();
			cmd.StartInfo.FileName = "cmd.exe";
			cmd.StartInfo.RedirectStandardInput = true;
			cmd.StartInfo.RedirectStandardOutput = true;
			cmd.StartInfo.CreateNoWindow = true;
			cmd.StartInfo.UseShellExecute = false;
			cmd.Start();

			cmd.StandardInput.WriteLine("echo %NUMBER_OF_PROCESSORS%");
			cmd.StandardInput.Flush();
			cmd.StandardInput.Close();
			cmd.WaitForExit();
			
			string result = "";
			bool triggerNextLine = false;
			foreach(string i in cmd.StandardOutput.ReadToEnd().Split('\n')) {
				//Console.WriteLine("Line: " + i);
				if (triggerNextLine) { result = i; triggerNextLine = false; }
				if (i.Contains("echo %NUMBER_OF_PROCESSORS%")) { triggerNextLine = true; }
			}
			
			return int.Parse(result);
		}
		
		static double roundToClosest(double x, int digits) {
			double mult = Math.Pow(10,digits);
			double precursor_result = Math.Ceiling(x * mult - 0.5f);
			return precursor_result / mult;
		}
		
		static string StripChars(string x) {
			string result = "";
			foreach(char y in x) {
				if (char.IsDigit(y) || (y == '-') || (y == '.')) {
					result += y;
				}
			}
			return result;
		}
		
        static void Main(string[] args) {
			Console.Clear();
			
			DisplayManager.StartDisplay();
			
			Console.ForegroundColor = ConsoleColor.Red;
			
			dataScreen AIStatusText1 =   DisplayManager.addScreen(40,2,"Left","Top","     AI  Status      ");
			dataScreen AIStatusText2 =   DisplayManager.addScreen(40,3,"Left","Top","      Offline    ");
			dataScreen AIStatusText3 =   DisplayManager.addScreen(40,4,"Left","Top","");
			dataScreen AIStatusText4 =   DisplayManager.addScreen(40,5,"Left","Top","");
			DisplayManager.createGroup(new List<dataScreen> {AIStatusText1,AIStatusText2,AIStatusText3,AIStatusText4});
			
			dataScreen AIMaxFitnessText1 =  DisplayManager.addScreen(10,2,"Left","Top","    Max AI Fitness    ");
			dataScreen AIMaxFitnessText2 =  DisplayManager.addScreen(10,3,"Left","Top","      Unavailable     ");
			DisplayManager.createGroup(new List<dataScreen> {AIMaxFitnessText1,AIMaxFitnessText2});
			
			dataScreen AIMinFitnessText1 =  DisplayManager.addScreen(70,2,"Left","Top","    Min AI Fitness    ");
			dataScreen AIMinFitnessText2 =  DisplayManager.addScreen(70,3,"Left","Top","      Unavailable     ");
			DisplayManager.createGroup(new List<dataScreen> {AIMinFitnessText1,AIMinFitnessText2});
			
			dataScreen apiStatusText1 =  DisplayManager.addScreen(10,9,"Left","Top"," API Interface Status ");
			dataScreen apiStatusText2 =  DisplayManager.addScreen(10,10,"Left","Top","       Starting       ");
			dataScreen apiStatusText3 =  DisplayManager.addScreen(10,11,"Left","Top","");
			DisplayManager.createGroup(new List<dataScreen> {apiStatusText1,apiStatusText2,apiStatusText3});
			
			API.filePath = filePath + "/SaveData/HistoricDataCache.txt";
			DisplayManager.updateDisplays();
			
			dataScreen histStatusText1 = DisplayManager.addScreen(40,9,"Left","Top","  Currency Pricings  ");
			dataScreen histStatusText2 = DisplayManager.addScreen(40,10,"Left","Top","       Paused        ");
			dataScreen histStatusText3 = DisplayManager.addScreen(40,11,"Left","Top","                     ");
			DisplayManager.createGroup(new List<dataScreen> {histStatusText1,histStatusText2,histStatusText3});
			
			dataScreen saveStatusText1 = DisplayManager.addScreen(40,15,"Left","Top","     Save Status     ");
			dataScreen saveStatusText2 = DisplayManager.addScreen(40,16,"Left","Top","      Not Saved      ");
			DisplayManager.createGroup(new List<dataScreen> {saveStatusText1,saveStatusText2});
			
			dataScreen curStatusText1 =  DisplayManager.addScreen(70,9,"Left","Top","  Currency Symbols  ");
			dataScreen curStatusText2 =  DisplayManager.addScreen(70,10,"Left","Top","       Loading      ");
			DisplayManager.createGroup(new List<dataScreen> {curStatusText1,curStatusText2});
			DisplayManager.updateDisplays();
			
			List<string> currencies = retrieveAllCurrencySymbols();
			curStatusText2.data =  "        Done  ";
			histStatusText2.data = "       Running";
			apiStatusText2.data =  "       Running";
			
			Console.ForegroundColor = ConsoleColor.Green;
			AIStatusText1.color = ConsoleColor.Yellow;
			AIStatusText2.color = ConsoleColor.Yellow;
			AIStatusText3.color = ConsoleColor.Yellow;
			apiStatusText1.color = ConsoleColor.Green;
			apiStatusText2.color = ConsoleColor.Green;
			apiStatusText3.color = ConsoleColor.Green;
			saveStatusText1.color = ConsoleColor.Red;
			saveStatusText2.color = ConsoleColor.Red;
			curStatusText1.color = ConsoleColor.Green;
			curStatusText2.color = ConsoleColor.Green;
			histStatusText1.color = ConsoleColor.Yellow;
			histStatusText2.color = ConsoleColor.Yellow;
			histStatusText3.color = ConsoleColor.Yellow;
			DisplayManager.updateDisplays();
			
			AIStatusText2.data =   "";
			DisplayManager.updateDisplays();
			
			Console.SetCursorPosition(0,25);
			Console.WriteLine("NEAT AI Direct Serial Output:");
			Console.WriteLine();
			
			nn = new Network(filePath,false,false,true);
			try {
				nn.loadNetwork(AIStatusText2,AIStatusText3);
			} catch {
				nn = new Network(filePath, false, true, true);
			}
			
			NEAT_AI.Random.n = nn;
			
			AIStatusText1.color = ConsoleColor.Magenta;
			AIStatusText2.color = ConsoleColor.Magenta;
			AIStatusText3.color = ConsoleColor.Magenta;
			AIStatusText4.color = ConsoleColor.Magenta;
			AIMaxFitnessText1.color = ConsoleColor.Magenta;
			AIMaxFitnessText2.color = ConsoleColor.Magenta;
			AIMinFitnessText1.color = ConsoleColor.Magenta;
			AIMinFitnessText2.color = ConsoleColor.Magenta;
			AIStatusText3.data =   " Currency:-/-";
			DisplayManager.updateDisplays();
			
			//List of currencies
			//Each currency has multiple data points
			//Each data point has id, time, and price
			List<currencyData> currencyReadouts = new List<currencyData>();
			
			
			//for (int currencyIndex = 0; currencyIndex < 5; currencyIndex++) {
			for (int currencyIndex = 0; currencyIndex < currencies.Count; currencyIndex++) {
				//List<List<string>> currencyData = new List<List<string>> { currencies[currencyIndex] };
				PointAnalysis.currencyData parentData = new currencyData();
				parentData.currencyName = currencies[currencyIndex];
				
				histStatusText3.data = "       " + (currencyIndex + 1).ToString() + "/" + currencies.Count.ToString();
				DisplayManager.updateDisplays(false);
				Console.SetCursorPosition(0,0);
				
				JsonElement obj2 = JsonSerializer.Deserialize<JsonElement>(API.getKlines(currencies[currencyIndex],API_Time_Enum));
				
				for (int i = 0; i < obj2.GetArrayLength(); i++) {
					DisplayManager.resizeCheck();
					
					JsonElement obj3 = JsonSerializer.Deserialize<JsonElement>(obj2[i].ToString());
					
					dataPoint temp = new dataPoint();
					temp.price 	= obj3[1].ToString();
					temp.time 	= obj3[0].ToString();
					parentData.currencyPoints.Add(temp);
				}
				
				currencyReadouts.Add(parentData);
			}
			
			int iterations = 0;
			while (true) {
				var watch1 = System.Diagnostics.Stopwatch.StartNew();
				iterations++;
				AIStatusText2.data =   "    Iteration: " + iterations.ToString();
				AIMaxFitnessText2.data = "        0";
				AIMinFitnessText2.data = "       0";
				DisplayManager.updateDisplays();
				
				SortedDictionary <string,double> algorithmOutput = new SortedDictionary <string,double>();
				int loops = 0;
				
				foreach (currencyData algorithmCurrencyInputData in currencyReadouts) {
					loops++;
					AIStatusText3.data = " Currency:" + loops.ToString() + "/" + currencyReadouts.Count.ToString();
					
					double currentAlgorithmOutput = 0;
					
					watch1.Stop();
				
					//Here we impliment the AI
					var watch2 = System.Diagnostics.Stopwatch.StartNew();
					for (int x = 0; x < nn.genomes.Count; x++) {
						AIStatusText4.data =   " Genome: " + (x + 1).ToString() + "/" + nn.genomes.Count.ToString();
						DisplayManager.resizeCheck();
						DisplayManager.updateDisplays(false);
						
						//bool once = true;
						float fakeWallet = startingWalletValue;
						float numberOfCryptoCoins = 0;
						float lastKnownPrice = 0;
						
						for(int i = nn.num_inputs; i < algorithmCurrencyInputData.currencyPoints.Count; i++) {
							//Here we are iterating over every single section of the currency data
							List<float> AI_Inputs = new List<float>();
							for (int AI_Input_Index = i;  AI_Input_Index > i - nn.num_inputs; AI_Input_Index--) {
								//Console.WriteLine(AI_Input_Index.ToString() + "\t\t" + (i - nn.num_inputs).ToString() + "\t\t" + i.ToString() + "\t\t" + algorithmCurrencyInputData.currencyPoints.Count.ToString());
								string temp = algorithmCurrencyInputData.currencyPoints[AI_Input_Index-1].price;
								AI_Inputs.Add((float)Convert.ToDouble(temp));
							}
							
							float currentPrice = (float)Convert.ToDouble(algorithmCurrencyInputData.currencyPoints[i].price);
							lastKnownPrice = currentPrice;
							
							List<float> genomeOutput = nn.genomes[x].GetOutput(nn,AI_Inputs);
							if (genomeOutput[0] > 0) {
								//Buy crypto
								numberOfCryptoCoins += fakeWallet * (1 - tax_percentage) / currentPrice;
								fakeWallet = 0;
							} else if (genomeOutput[1] > 0) {
								//Sell crypto
								fakeWallet += numberOfCryptoCoins * currentPrice;
								numberOfCryptoCoins = 0;
							}
							
							//if (once) {
							//	once = false;
							//	Console.SetCursorPosition(0,20);
							//	Console.WriteLine("NEAT AI Buy: " + genomeOutput[0]);
							//	Console.WriteLine("NEAT AI Sell: " + genomeOutput[1]);
							//}
						}
						
						nn.genomes[x].fitness = fakeWallet + numberOfCryptoCoins * lastKnownPrice;
						if (nn.genomes[x].fitness == 5000) {
							nn.genomes.RemoveAt(x);
						} else {
							if (roundToClosest(nn.genomes[x].fitness / 50 - 100,2) > Convert.ToDouble(StripChars(AIMaxFitnessText2.data))) { AIMaxFitnessText2.data = roundToClosest(nn.genomes[x].fitness / 50 - 100,2).ToString() + "%"; }
							if (roundToClosest(nn.genomes[x].fitness / 50 - 100,2) < Convert.ToDouble(StripChars(AIMinFitnessText2.data))) { AIMinFitnessText2.data = roundToClosest(nn.genomes[x].fitness / 50 - 100,2).ToString() + "%"; }
						}
						
						DisplayManager.updateDisplays();
					}
					watch2.Stop();
					
					var watch3 = System.Diagnostics.Stopwatch.StartNew();
					//AIMaxFitnessText2.data = "       " + bestGenome.fitness;
					//AIMinFitnessText2.data = "       " + worstGenome.fitness;
					
					//algorithmOutput.Add(algorithmCurrencyInputData.currencyName,currentAlgorithmOutput);
					nn.UpdateGenomeList();
					watch3.Stop();
					
					var watch4 = System.Diagnostics.Stopwatch.StartNew();
					
					Console.ForegroundColor = ConsoleColor.Green;
					apiStatusText1.color = ConsoleColor.Green;
					apiStatusText2.color = ConsoleColor.Green;
					apiStatusText3.color = ConsoleColor.Green;
					curStatusText1.color = ConsoleColor.Green;
					curStatusText2.color = ConsoleColor.Green;
					saveStatusText1.color = ConsoleColor.Yellow;
					saveStatusText2.color = ConsoleColor.Yellow;
					histStatusText1.color = ConsoleColor.Green;
					histStatusText2.color = ConsoleColor.Green;
					histStatusText3.color = ConsoleColor.Green;
					curStatusText2.data =  "        Done";
					saveStatusText2.data =   "  Saving AI Genomes";
					DisplayManager.updateDisplays();
					watch4.Stop();
					
					var watch5 = System.Diagnostics.Stopwatch.StartNew();
					nn.saveNetwork(apiStatusText3);
					watch5.Stop();
					
					var watch6 = System.Diagnostics.Stopwatch.StartNew();
					//https://www.binance.com/en/convert
					saveStatusText1.color = ConsoleColor.Green;
					saveStatusText2.color = ConsoleColor.Green;
					saveStatusText2.data =  "        Saved";
					apiStatusText3.data = "";
					DisplayManager.updateDisplays();
					
					//Console.Beep(523,300);
					//Console.Beep(659,300);
					//Console.Beep(784,300);
					//Console.Beep(1046,600);
					watch6.Stop();
					
					Console.SetCursorPosition(0,45);
					Console.WriteLine("Watch 1 (Pre-Genome Setup):			" + (watch1.ElapsedMilliseconds / 1000).ToString());
					Console.WriteLine("Watch 2 (Genome Training):			" + (watch2.ElapsedMilliseconds / 1000).ToString());
					Console.WriteLine("Watch 3 (Genome Update Function):	" + (watch3.ElapsedMilliseconds / 1000).ToString());
					Console.WriteLine("Watch 4 (Display Updates):			" + (watch4.ElapsedMilliseconds / 1000).ToString());
					Console.WriteLine("Watch 5 (Genome Save Function):		" + (watch5.ElapsedMilliseconds / 1000).ToString());
					Console.WriteLine("Watch 6 (Display Updates):			" + (watch6.ElapsedMilliseconds / 1000).ToString());
					while(true){}
				}
				
				//var result = algorithmOutput.OrderBy(key => key.Value).Reverse();
				
				//int loops = 0;
				//List<List<string>> results = new List<List<string>>();
				//foreach (KeyValuePair<string,double> val in result) {
				//	if (loops < currencies.Count) {
				//		results.Add(new List<string> { val.Key, val.Value.ToString() });
				//	}
				//	
				//	loops++;
				//}
			}
		}
	}
}





























