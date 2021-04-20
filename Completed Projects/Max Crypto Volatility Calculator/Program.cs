using System;
using System.IO;
using System.Net;
using System.Linq;
using System.Threading;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

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
		
		class deserializedDataPoint3JSON {
			//[JsonPropertyName("")]
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
		
		static void print(object i) {
			Console.WriteLine(i);
		}
		
        static void Main(string[] args) {
			Console.Clear();
			
			DisplayManager.StartDisplay();
			
			Console.ForegroundColor = ConsoleColor.Red;
			
			dataScreen AIStatusText1 =   DisplayManager.addScreen(40,2,"Left","Top","     AI  Status      ");
			dataScreen AIStatusText2 =   DisplayManager.addScreen(40,3,"Left","Top","        N/A    ");
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
			
			API.filePath = filePath + "/SaveData/HistoricDataCache.txt";
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
			DisplayManager.updateDisplays();
			
			List<currencyData> currencyReadouts = new List<currencyData>();
			for (int currencyIndex = 0; currencyIndex < currencies.Count; currencyIndex++) {
				PointAnalysis.currencyData parentData = new currencyData();
				parentData.currencyName = currencies[currencyIndex];
					
				histStatusText3.data = "       " + (currencyIndex + 1).ToString() + "/" + currencies.Count.ToString();
				DisplayManager.updateDisplays(false);
					
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

			Console.SetCursorPosition(0,50);
			int loops = 0;
            
			Console.WriteLine(currencyReadouts.Count);
            List<List<string>> temp2 = new List<List<string>>();
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
                if (tempCount > 150) {
                    for (int AI_Input_Index = 0; AI_Input_Index < 150; AI_Input_Index++) {
                        string temp = algorithmCurrencyInputData.currencyPoints[tempCount - AI_Input_Index].price;
                        AI_Inputs.Add((float)Convert.ToDouble(temp));
                    }

                    float currentPrice = (float)Convert.ToDouble(algorithmCurrencyInputData.currencyPoints[tempCount - 1].price);

                }

                double potentialEarnings = 1;
                double prevDataPoint = 0;
                for (int i = 1; i < AI_Inputs.Count; i++) {
                    if (AI_Inputs[i] > AI_Inputs[i - 1]) {
                        potentialEarnings *= AI_Inputs[i] / AI_Inputs[i - 1];
                    }
                }

                temp2.Add(new List<string> {algorithmCurrencyInputData.currencyName.ToString(), potentialEarnings.ToString()});
			}

            double totalEarnings = 0;
            Console.SetCursorPosition(0, 51);
            foreach (List<string> i in temp2)
            {
                Console.WriteLine(
                	"Crypto Currency Code: " + i[0] + 
                	"\t\t\tMaximum Network Potential via Crypto Volatility: " + i[1]
                );
				if (totalEarnings < double.Parse(i[1]) - 1) {
					totalEarnings = double.Parse(i[1]) - 1;
				}
            }

            Console.WriteLine("Total Earnings Possible Increase: " + (Math.Round(totalEarnings * 100)).ToString() + "%");
        }
	}
}
