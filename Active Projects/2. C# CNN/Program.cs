using System;
using System.IO;
using System.Net;
using System.Linq;
using System.Threading;
using System.Collections.Generic;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

//using NEAT_AI;
using Display;
using Binance_API;
using PointAnalysis;

namespace WebAPIClient {
	class Program {
		static string filePath = "C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/4. C# CNN";
		static string API_Time_Enum = "1h";
		
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
		
        static void Main(string[] args) {
			Console.Clear();
			
			DisplayManager.StartDisplay();
			
			Console.ForegroundColor = ConsoleColor.Red;
			dataScreen apiStatusText1 =  DisplayManager.addScreen(10,5,"Left","Top"," API Interface Status ");
			dataScreen apiStatusText2 =  DisplayManager.addScreen(10,6,"Left","Top","       Starting       ");
			DisplayManager.createGroup(new List<dataScreen> {apiStatusText1,apiStatusText2});
			
			API.filePath = filePath + "/SaveData/HistoricDataCache.txt";
			DisplayManager.updateDisplays();
			
			dataScreen histStatusText1 = DisplayManager.addScreen(40,5,"Left","Top","  Currency Pricings  ");
			dataScreen histStatusText2 = DisplayManager.addScreen(40,6,"Left","Top","       Paused        ");
			dataScreen histStatusText3 = DisplayManager.addScreen(40,7,"Left","Top","                     ");
			DisplayManager.createGroup(new List<dataScreen> {histStatusText1,histStatusText2,histStatusText3});
			
			dataScreen saveStatusText1 = DisplayManager.addScreen(40,11,"Left","Top","     Save Status     ");
			dataScreen saveStatusText2 = DisplayManager.addScreen(40,12,"Left","Top","      Not Saved      ");
			DisplayManager.createGroup(new List<dataScreen> {saveStatusText1,saveStatusText2});
			
			dataScreen curStatusText1 =  DisplayManager.addScreen(70,5,"Left","Top","  Currency Symbols  ");
			dataScreen curStatusText2 =  DisplayManager.addScreen(70,6,"Left","Top","       Loading      ");
			DisplayManager.createGroup(new List<dataScreen> {curStatusText1,curStatusText2});
			DisplayManager.updateDisplays();
			
			List<string> currencies = retrieveAllCurrencySymbols();
			curStatusText2.data =  "        Done  ";
			histStatusText2.data = "       Running";
			apiStatusText2.data =  "       Running";
			
			Console.ForegroundColor = ConsoleColor.Green;
			apiStatusText1.color = ConsoleColor.Green;
			apiStatusText2.color = ConsoleColor.Green;
			saveStatusText1.color = ConsoleColor.Red;
			saveStatusText2.color = ConsoleColor.Red;
			curStatusText1.color = ConsoleColor.Green;
			curStatusText2.color = ConsoleColor.Green;
			histStatusText1.color = ConsoleColor.Yellow;
			histStatusText2.color = ConsoleColor.Yellow;
			histStatusText3.color = ConsoleColor.Yellow;
			DisplayManager.updateDisplays();
			
			//List of currencies
			//Each currency has multiple data points
			//Each data point has id, time, and price
			List<currencyData> currencyReadouts = new List<currencyData>();
			
			while (true) {
				//for (int currencyIndex = 0; currencyIndex < currencies.Count - 1; currencyIndex++) {
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
			
				SortedDictionary <string,double> algorithmOutput = new SortedDictionary <string,double>();
				string finalResultsTemp = "";
				foreach (currencyData algorithmCurrencyInputData in currencyReadouts) {
					PointAnalysis.CompleteAnalysis dataPointAnalysis = PointAnalysis.PointAnalysis.analyseData(algorithmCurrencyInputData,1000000,true);
					double currentAlgorithmOutput = 0;
					currentAlgorithmOutput += dataPointAnalysis.derivative;
					//currentAlgorithmOutput += dataPointAnalysis.dataDirection;							//Irrelevant as the derivative takes that into account
					//if (dataPointAnalysis.jumpDetection == 1) { currentAlgorithmOutput /= 2; }
					//currentAlgorithmOutput *= dataPointAnalysis.concavity;
					//currentAlgorithmOutput *= dataPointAnalysis.bestFitLineR;
					
					algorithmOutput.Add(algorithmCurrencyInputData.currencyName,currentAlgorithmOutput);
					
					finalResultsTemp += "Cncy: " + algorithmCurrencyInputData.currencyName + "\n";
					finalResultsTemp += "\tStart UNIX Time: " + algorithmCurrencyInputData.currencyPoints[0].time + "\n";
					finalResultsTemp += "\tMid UNIX Time: " + algorithmCurrencyInputData.currencyPoints[algorithmCurrencyInputData.currencyPoints.Count / 2].time + "\n";
					finalResultsTemp += "\tEnd UNIX Time: " + algorithmCurrencyInputData.currencyPoints[algorithmCurrencyInputData.currencyPoints.Count - 1].time + "\n";
					finalResultsTemp += "\tStart Value: " + algorithmCurrencyInputData.currencyPoints[0].price + "\n";
					finalResultsTemp += "\tMid Value: " + algorithmCurrencyInputData.currencyPoints[algorithmCurrencyInputData.currencyPoints.Count / 2].price + "\n";
					finalResultsTemp += "\tEnd Value: " + algorithmCurrencyInputData.currencyPoints[algorithmCurrencyInputData.currencyPoints.Count - 1].price + "\n";
					finalResultsTemp += "\tDerivative: " + dataPointAnalysis.derivative + "\n";
					finalResultsTemp += "\tConcavity: " + dataPointAnalysis.concavity + "\n";
					finalResultsTemp += "\tDirection: " + dataPointAnalysis.dataDirection + "\n";
					finalResultsTemp += "\tAlgorithm Output: " + currentAlgorithmOutput + "\n";
					finalResultsTemp += "\n";
				}
				File.WriteAllText(filePath + "/SaveData/Results_temp.txt", finalResultsTemp);
				
				var result = algorithmOutput.OrderBy(key => key.Value).Reverse();
				
				int loops = 0;
				List<List<string>> results = new List<List<string>>();
				foreach (KeyValuePair<string,double> val in result) {
					if (loops < currencies.Count) {
						results.Add(new List<string> { val.Key, val.Value.ToString() });
					}
					
					loops++;
				}
				
				Console.ForegroundColor = ConsoleColor.Green;
				apiStatusText1.color = ConsoleColor.Green;
				apiStatusText2.color = ConsoleColor.Green;
				curStatusText1.color = ConsoleColor.Green;
				curStatusText2.color = ConsoleColor.Green;
				saveStatusText1.color = ConsoleColor.Yellow;
				saveStatusText2.color = ConsoleColor.Yellow;
				histStatusText1.color = ConsoleColor.Green;
				histStatusText2.color = ConsoleColor.Green;
				histStatusText3.color = ConsoleColor.Green;
				curStatusText2.data =  "        Done";
				saveStatusText2.data = "Saving Results To File";
				DisplayManager.updateDisplays();
				
				string tempLine = "";
				for(int i = 0; i < results.Count; i++) {
					tempLine += " - Currency: " + results[i][0].ToString();
					tempLine += "\t\tAlgorithm Output: " + results[i][1].ToString();
					tempLine += "\n";
				}
				
				File.WriteAllText(filePath + "/SaveData/Results.txt", tempLine);
				
				//https://www.binance.com/en/convert
				saveStatusText1.color = ConsoleColor.Green;
				saveStatusText2.color = ConsoleColor.Green;
				saveStatusText2.data =  "        Saved";
				DisplayManager.updateDisplays();
				
				while(true);
			}
		}
	}
}





























