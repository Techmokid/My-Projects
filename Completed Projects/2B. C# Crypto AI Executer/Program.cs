using System;
using System.IO;
using System.Net;
using System.Linq;
using System.Threading;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

using NEAT_AI;
using Display;
using Binance_API;
using PointAnalysis;
using Debugging;

namespace WebAPIClient {
	class Program {
		static string filePath = "";
		static string API_Time_Enum = "1h";
		static float tax_percentage = 0.1f;
		static float startingWalletValue = 5000;
		static Network nn;
		static int maxNumberOfCryptos = 99999;
		
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
			
			string fileLocation = filePath + "currencySymbols.txt";
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
			DisplayManager.createGroup(new List<dataScreen> {apiStatusText1,apiStatusText2});
			
			//API.filePath = filePath + "/SaveData/HistoricDataCache.txt";
			API.filePath = "SaveData/HistoricDataCache.txt";
			DisplayManager.updateDisplays();
			
			dataScreen histStatusText1 = DisplayManager.addScreen(40,9,"Left","Top","  Currency Pricings  ");
			dataScreen histStatusText2 = DisplayManager.addScreen(40,10,"Left","Top","       Paused        ");
			dataScreen histStatusText3 = DisplayManager.addScreen(40,11,"Left","Top","                     ");
			DisplayManager.createGroup(new List<dataScreen> {histStatusText1,histStatusText2,histStatusText3});
			
			dataScreen saveStatusText1 = DisplayManager.addScreen(40,15,"Left","Top","     Save Status     ");
			dataScreen saveStatusText2 = DisplayManager.addScreen(40,16,"Left","Top","     Deactivated     ");
			DisplayManager.createGroup(new List<dataScreen> {saveStatusText1,saveStatusText2});
			
			dataScreen curStatusText1 =  DisplayManager.addScreen(70,9,"Left","Top","  Currency Symbols  ");
			dataScreen curStatusText2 =  DisplayManager.addScreen(70,10,"Left","Top","       Loading      ");
			DisplayManager.createGroup(new List<dataScreen> {curStatusText1,curStatusText2});
			DisplayManager.updateDisplays();
			
			//List<string> currencies = retrieveAllCurrencySymbols();
			AIStatusText2.data =   "    Loading Genome";
			curStatusText2.data =  "        Done  ";
			histStatusText2.data = "       Running";
			apiStatusText2.data =  "       Running";
			
			Console.ForegroundColor = ConsoleColor.Green;
			AIStatusText1.color = ConsoleColor.Yellow;
			AIStatusText2.color = ConsoleColor.Yellow;
			AIStatusText3.color = ConsoleColor.Yellow;
			apiStatusText1.color = ConsoleColor.Green;
			apiStatusText2.color = ConsoleColor.Green;
			saveStatusText1.color = ConsoleColor.Gray;
			saveStatusText2.color = ConsoleColor.Gray;
			curStatusText1.color = ConsoleColor.Green;
			curStatusText2.color = ConsoleColor.Green;
			histStatusText1.color = ConsoleColor.Yellow;
			histStatusText2.color = ConsoleColor.Yellow;
			histStatusText3.color = ConsoleColor.Yellow;
			AIMaxFitnessText1.color = ConsoleColor.Gray;
			AIMaxFitnessText2.color = ConsoleColor.Gray;
			AIMinFitnessText1.color = ConsoleColor.Gray;
			AIMinFitnessText2.color = ConsoleColor.Gray;
			DisplayManager.updateDisplays();
			
			Console.SetCursorPosition(0,25);
			nn = new Network("C:/Users/aj200/Desktop/Backups",false,false,true);
			
			AIStatusText1.color = ConsoleColor.Green;
			AIStatusText2.color = ConsoleColor.Green;
			AIStatusText3.color = ConsoleColor.Green;
			AIStatusText4.color = ConsoleColor.Green;
			AIStatusText2.data =   "      Running";
			AIStatusText3.data = "";
			AIStatusText4.data = "";
			DisplayManager.updateDisplays();
			
			DebugFile.Create("debugging.txt");
			while (true) {
				Genome activeAIGenome = nn.loadBestGenome();
				
				List<string> currencies = retrieveAllCurrencySymbols();
				
				List<currencyData> currencyReadouts = new List<currencyData>();
				for (int currencyIndex = 0; currencyIndex < currencies.Count; currencyIndex++) {
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
					
					//DebugFile.WriteLine("Currency: " + currencies[currencyIndex].ToString() + "\t\t\tCurrency Data Count: " + parentData.currencyPoints.Count.ToString());
					currencyReadouts.Add(parentData);
				}
				
				histStatusText3.data = "";
				DisplayManager.updateDisplays();
				
				List<List<string>> algorithmOutput = new List<List<string>>();
				int loops = 0;
				foreach (currencyData algorithmCurrencyInputData in currencyReadouts) {
					loops++;
					AIStatusText3.data = " Currency:" + loops.ToString() + "/" + currencyReadouts.Count.ToString();
					DisplayManager.resizeCheck();
					DisplayManager.updateDisplays(false);
					
					double currentAlgorithmOutput = 0;
					//float fakeWallet = startingWalletValue;
					//float numberOfCryptoCoins = 0;
					
					//Here we are iterating over every single section of the currency data
					List<float> AI_Inputs = new List<float>();
					int tempCount = algorithmCurrencyInputData.currencyPoints.Count - 1;
					if (tempCount > nn.num_inputs) {
						for (int AI_Input_Index = 0;  AI_Input_Index < nn.num_inputs; AI_Input_Index++) {
							string temp = algorithmCurrencyInputData.currencyPoints[tempCount - AI_Input_Index].price;
							AI_Inputs.Add((float)Convert.ToDouble(temp));
						}
						
						float currentPrice = (float)Convert.ToDouble(algorithmCurrencyInputData.currencyPoints[tempCount - 1].price);
						List<float> genomeOutput = activeAIGenome.GetOutput(nn,AI_Inputs);
						algorithmOutput.Add(new List<string> {algorithmCurrencyInputData.currencyName,genomeOutput[0].ToString(),genomeOutput[1].ToString()});
					}
				}
				
				AIStatusText3.data = "";
				DisplayManager.updateDisplays();
				
				while (algorithmOutput.Count > maxNumberOfCryptos) {
					algorithmOutput.RemoveAt(algorithmOutput.Count - 1);
				}
				
				//algorithmOutput[0] contains the crypto namespace
				//algorithmOutput[1] contains the AI output "Buy" function
				//algorithmOutput[2] contains the AI output "Sell" function
				
				//Console.SetCursorPosition(0,22);
				List<List<string>> sellList = new List<List<string>>();
				List<List<string>> buyList = new List<List<string>>();
				List<List<string>> sitList = new List<List<string>>();
				List<List<string>> instabList = new List<List<string>>();
				foreach(List<string> i in algorithmOutput) {
					if ((float.Parse(i[1]) > 0) && (float.Parse(i[2]) < 0))
						//Console.WriteLine("BUY DATA: " + API.createNewBuySellOrder(tempSingleCurrencyData[0],"BUY",20));
						buyList.Add(i);
					if ((float.Parse(i[1]) < 0) && (float.Parse(i[2]) > 0))
						//Console.WriteLine("SELL DATA: " + API.createNewBuySellOrder(tempSingleCurrencyData[0],"SELL",20));
						sellList.Add(i);
					if ((float.Parse(i[1]) > 0) && (float.Parse(i[2]) > 0))
						//Console.WriteLine("BUY/SELL INSTABILITY: " + API.createNewBuySellOrder(tempSingleCurrencyData[0],"SELL",20));
						instabList.Add(i);
					if ((float.Parse(i[1]) < 0) && (float.Parse(i[2]) < 0))
						//Console.WriteLine("SITTING");
						sitList.Add(i);
				}
				
				//                     "       Starting       ";
				AIStatusText1.color = ConsoleColor.Cyan;
				AIStatusText2.color = ConsoleColor.Cyan;
				AIStatusText3.color = ConsoleColor.Cyan;
				apiStatusText1.color = ConsoleColor.Cyan;
				apiStatusText2.color = ConsoleColor.Cyan;
				AIStatusText2.data =   "    Awaiting User...  ";
				AIStatusText3.data =   "";
				apiStatusText2.data =  "    Awaiting User...  ";
				//DisplayManager.updateDisplays();
				//Console.ReadKey(true);
				
				AIStatusText1.color = ConsoleColor.Green;
				AIStatusText2.color = ConsoleColor.Green;
				AIStatusText3.color = ConsoleColor.Green;
				apiStatusText1.color = ConsoleColor.Yellow;
				apiStatusText2.color = ConsoleColor.Yellow;
				AIStatusText2.data =   "                      ";
				AIStatusText3.data =   "";
				apiStatusText2.data =  "  Selling Old Crypto  ";
				DisplayManager.updateDisplays();
				Console.SetCursorPosition(0,25);
				
				foreach(List<string> i in sellList) {
					DisplayManager.resizeCheck();
					//Console.WriteLine("TEST: 1");
					if ((i[0] != "USDTBTC") && (i[0] != "BTCUSDT")) {
						float sellWalletValue = API.getWalletContents(i[0]);
						
						if (sellWalletValue != -1) {
							//Console.WriteLine("TEST: 2");
							if (sellWalletValue > 20) {
								//Console.WriteLine("Selling: " + i[0]);
								Thread.Sleep(450);
								API.createNewBuySellOrder(i[0], "SELL", sellWalletValue - 20);
							}
						} else {
							//Console.WriteLine("Error while selling: " + i[0]);
						}
					}
				}
				
				apiStatusText2.data =  "  Buying New Crypto  ";
				apiStatusText2.updateScreen();
				
				int counter = 0;
				buyList = orderList(buyList);
				float buyWalletValue = API.getWalletContents("USDTBTC");
				foreach(List<string> i in buyList) {
					DisplayManager.resizeCheck();
					counter++;
					
					if (counter < 10) {
						if (buyWalletValue > 20) {
							//Console.WriteLine("Buying: " + i[0]);
							Thread.Sleep(450);
							API.createNewBuySellOrder(i[0], "BUY", buyWalletValue / buyList.Count);
						}
					}
				}
				
				AIStatusText4.data =   "  Paused For 1 Hour  ";
				apiStatusText2.data =  "        Done!        ";
				apiStatusText2.color = ConsoleColor.Green;
				DisplayManager.updateDisplays();
				
				Thread.Sleep(1000 * 60 * 60);
				
				AIStatusText4.data =   "  ";
				DisplayManager.updateDisplays();
			}
		}
		
		public static List<List<string>> orderList(List<List<string>> input) {
			List<List<string>> results = new List<List<string>>();
			
			while (input.Count != 0) {
				int indexOfHighest = 0;
				for (int i = 0; i < input.Count; i++) {
					if (double.Parse(input[indexOfHighest][1]) < double.Parse(input[i][1])) {
						indexOfHighest = i;
					}
				}
				
				results.Add(input[indexOfHighest]);
				input.RemoveAt(indexOfHighest);
			}
			
			return results;
		}			
	}
}
