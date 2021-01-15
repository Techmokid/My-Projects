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
using Binance_API;

namespace WebAPIClient {
	class Program {
		static string filePath = "C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/C# CNN";
		
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
			for(int i = 0; i < 50; i++) { Console.WriteLine(); }
			
			Console.WriteLine("[Main Thread][Info]: Starting API Interface...");
			Console.WriteLine("[API Interface][Info]: Collecting historic prices");
			API.filePath = filePath + "/SaveData/HistoricDataCache.txt";
			
			Console.WriteLine("[API Interface][Info]: Gathering Currency Symbols");
			List<string> currencies = retrieveAllCurrencySymbols();
			Console.WriteLine("[Main Thread][Info]: Running Algorithm...");
			
			while (true) {
				SortedDictionary <string,double> algorithmOutput = new SortedDictionary <string,double>();
				int looper = 0;
				foreach (string currency in currencies) {
					//if (looper < 100) {
					looper++;
					API.createdJSON = false;
					
					//NOTE!!! MUST FIX! Currently it can only see the last day, not the last year!
					//https://sammchardy.github.io/binance/2018/01/08/historical-data-download-binance.html
					API.getHistoricTrades(currency,1000);
					
					StreamReader file = new StreamReader(filePath + "/SaveData/HistoricDataCache.txt");
					string line = file.ReadLine(); string jsonOutput = "";
					while (line != null) { jsonOutput += line; line = file.ReadLine(); }
					file.Close();
					
					//obj contains all data about the specific crypto
					JsonElement obj = JsonSerializer.Deserialize<JsonElement>(jsonOutput);
					
					List<List<double>> dataPoints = new List<List<double>>();
					for(int i = 0; i < obj.GetArrayLength(); i++) {
						//obj[i] contains a specific price/date data point
						string objString = obj[i].ToString();
						deserializedJSON2 data = JsonSerializer.Deserialize<deserializedJSON2>(objString);
						
						List<double> temp = new List<double>();
						temp.Add(data.id);
						temp.Add(Convert.ToDouble(data.price));
						temp.Add(data.time);
						
						dataPoints.Add(temp);
					}
					
					List<double> dataPointAnalysis = analyseData(dataPoints);
					//dataPointAnalysis[0] is overall direction (Is the data going up or down)
					//dataPointAnalysis[1] is overall derivative (Is the data concave or convex)
					//dataPointAnalysis[2] is jump detection
					//dataPointAnalysis[3] is overall standard deviation
					
					double currentAlgorithmOutput = dataPointAnalysis[0];
					//currentAlgorithmOutput -= dataPointAnalysis[1];
					if (dataPointAnalysis[2] == 1) { currentAlgorithmOutput /= 2; }
					//currentAlgorithmOutput /= dataPointAnalysis[3];
					
					algorithmOutput.Add(currency,currentAlgorithmOutput);
					//}
				}
				
				var result = algorithmOutput.OrderBy(key => key.Value).Reverse();
				
				int loops = 0;
				double totalOutput = 0;
				List<List<string>> results = new List<List<string>>();
				foreach (KeyValuePair<string,double> val in result) {
					if (loops < 10) {
						results.Add(new List<string> { val.Key, val.Value.ToString() });
					}
					
					loops++;
				}
				
				Console.WriteLine("Best Currency Readouts");
				foreach (List<string> i in results) {
					Console.WriteLine(" - Currency: " + i[0] + "\t\tAlgorithm Output: " + i[1]);
				}
				
				//https://www.binance.com/en/convert
				
				
				Console.WriteLine("Paused");
				Thread.Sleep(1000000);
			}
		}
		
		static List<double> smoothData(List<double> inputData, int iterations) {
			List<double> result = new List<double> { inputData[0] };
			
			for (int i = 1; i < inputData.Count - 1; i++) {
				result.Add((inputData[i - 1] + inputData[i]) / 2);
			}
			
			iterations -= 1;
			if (iterations <= 0) {
				return result;
			} else {
				return smoothData(result,iterations);
			}
		}
		
		static List<double> smoothData(List<List<double>> inputData, int iterations) {
			List<double> result = new List<double> { inputData[0][1] };
			
			for (int i = 1; i < inputData.Count - 1; i++) {
				double in1 = inputData[i - 1][1];
				double in2 = inputData[i][1];
				result.Add((in1 + in2) / 2);
			}
			
			iterations -= 1;
			if (iterations <= 0) {
				return result;
			} else {
				return smoothData(result,iterations);
			}
		}
		
		static List<double> analyseData(List<List<double>> inputData) {
			//inputData[0] = id
			//inputData[1] = price
			//inputData[2] = time
			
			//Console.WriteLine(inputData.Count);
			List<double> smoothedDataCache = smoothData(inputData,3);
			
			double directionData = smoothedDataCache[smoothedDataCache.Count - 3] - smoothedDataCache[2];
			
			//Console.WriteLine("1: " + smoothedDataCache[smoothedDataCache.Count - 3]);
			//Console.WriteLine("2: " + smoothedDataCache[2]);
			//Console.WriteLine("Result: " + directionData);
			
			//Console.WriteLine("1:" + inputData[0][2]);
			//Console.WriteLine("2:" + inputData[inputData.Count - 1][2]);
			//Console.WriteLine();
			
			double deriv1 = smoothedDataCache[smoothedDataCache.Count/2] - smoothedDataCache[2];
			double deriv2 = smoothedDataCache[smoothedDataCache.Count - 3] - smoothedDataCache[smoothedDataCache.Count/2];
			double deriv = deriv2 - deriv1;
			
			double jumpDetection = 0;
			for(int i = 5; i < smoothedDataCache.Count; i++) {
				if (Math.Abs(smoothedDataCache[i] / smoothedDataCache[i - 5]) > 3) {
					jumpDetection = 1;
				}
			}
			
			double standardDeviation = 1;
			
			return new List<double> {directionData, deriv, jumpDetection, standardDeviation};
		}
	}
}





























