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

namespace WebAPIClient {
	class Program {
		static string filePath = "";
		static string API_Time_Enum = "1h";
		static float tax_percentage = 0.1f;
		static float startingWalletValue = 5000;
		static int maxNumberOfCryptos = 10;
		static bool liveTrading = false;
		
		static List<deserializedSymbolJSON2> limits = new List<deserializedSymbolJSON2>();
		
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
			
			[JsonPropertyName("rateLimits")]
			public dynamic rateLimits { get; set; }
		}
		
		class deserializedSymbolJSON {
			[JsonPropertyName("symbol")]
			public string symbol { get; set; }
		}
		
		class deserializedSymbolJSON2 {
			[JsonPropertyName("rateLimitType")]
			public string rateLimitType { get; set; }
			
			[JsonPropertyName("interval")]
			public string interval { get; set; }
			
			[JsonPropertyName("limit")]
			public int limit { get; set; }
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
			
			limits = new List<deserializedSymbolJSON2>();
			for(int i = 0; i < temp2.rateLimits.GetArrayLength(); i++) {
				deserializedSymbolJSON2 temp3 = JsonSerializer.Deserialize<deserializedSymbolJSON2>(temp2.rateLimits[i].ToString());
				limits.Add(temp3);
			}
			
			Console.SetCursorPosition(0,35);
			for(int i = 0; i < limits.Count; i++) {
				Console.WriteLine("Rate Limit Type: " + limits[i].rateLimitType);
				Console.WriteLine("Interval: " + limits[i].interval);
				Console.WriteLine("API Endpoint Limit: " + limits[i].limit);
				Console.WriteLine("");
			}
			
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
			
			dataScreen AIStatusText1 =   DisplayManager.addScreen(40,2,"Left","Top"," Algorithm  Status ");
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
			//nn = new Network("F:",false,false,true);
			
			AIStatusText1.color = ConsoleColor.Green;
			AIStatusText2.color = ConsoleColor.Green;
			AIStatusText3.color = ConsoleColor.Green;
			AIStatusText4.color = ConsoleColor.Green;
			AIStatusText2.data =   "      Running";
			AIStatusText3.data = "";
			AIStatusText4.data = "";
			DisplayManager.updateDisplays();
			
			while (true) {
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
					
					currencyReadouts.Add(parentData);
				}
				
				histStatusText3.data = "------";
				DisplayManager.updateDisplays();
				
				List<List<string>> sellList = new List<List<string>>();
				List<List<string>> buyList = new List<List<string>>();
				List<List<string>> algorithmOutput = new List<List<string>>();
				int loops = 0;
				foreach (currencyData algorithmCurrencyInputData in currencyReadouts) {
					loops++;
					AIStatusText3.data = " Currency:" + loops.ToString() + "/" + currencyReadouts.Count.ToString();
					DisplayManager.resizeCheck();
					DisplayManager.updateDisplays(false);
					
					CompleteAnalysis networkOutput = PointAnalysis.PointAnalysis.analyseData(algorithmCurrencyInputData);
					networkOutput = PointAnalysis.PointAnalysis.GetClosestNoticableCurve(networkOutput);
					
					// W.I.P CODE-MARKER
					if (networkOutput.CurveLineOfBestFitR < Math.Sqrt(networkOutput.StandardLineOfBestFitR)) {
						//This is just a straight line
						double M = networkOutput.StandardLineOfBestFit_M;
						if (M > 0) {
							buyList.Add(
								new List<string> {
									algorithmCurrencyInputData.currencyName,
									M.ToString()
								}
							);
						} else {
							sellList.Add(
								new List<string> {
									algorithmCurrencyInputData.currencyName,
									M.ToString()
								}
							);
						}
					} else {
						//We legit think it's a curve
						double M = networkOutput.CurveOfBestFitA;
						if (M > 0) {
							// The curve is convex (Valley)
							dataPoint latestVal = algorithmCurrencyInputData.currencyPoints[algorithmCurrencyInputData.currencyPoints.Count - 1];
							if (networkOutput.CurveOfBestFitTurnoverPointX < Convert.ToDouble(latestVal.time)) {
								buyList.Add(
									new List<string> {
										algorithmCurrencyInputData.currencyName,
										M.ToString()
									}
								);
							} else {
								sellList.Add(
									new List<string> {
										algorithmCurrencyInputData.currencyName,
										M.ToString()
									}
								);
							}
						} else {
							// The curve is concave (Hill)
							dataPoint latestVal = algorithmCurrencyInputData.currencyPoints[algorithmCurrencyInputData.currencyPoints.Count - 1];
							if (networkOutput.CurveOfBestFitTurnoverPointX > Convert.ToDouble(latestVal.time)) {
								buyList.Add(
									new List<string> {
										algorithmCurrencyInputData.currencyName,
										M.ToString()
									}
								);
							} else {
								sellList.Add(
									new List<string> {
										algorithmCurrencyInputData.currencyName,
										M.ToString()
									}
								);
							}
						}
					}
				}
				
				AIStatusText3.data = "";
				DisplayManager.updateDisplays();
				
				while (buyList.Count > maxNumberOfCryptos) {
					buyList.RemoveAt(buyList.Count - 1);
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
				Console.WriteLine(sellList.Count);
				
				int count = 0;
				foreach(List<string> i in sellList) {
					DisplayManager.resizeCheck();
					count++;
					
					Console.WriteLine(count.ToString() + "/" + sellList.Count);
					if ((i[0] != "USDTBTC") && (i[0] != "BTCUSDT")) {
						float sellWalletValue = API.getWalletContents(i[0]);
						
						if (sellWalletValue != -1) {
							if (sellWalletValue > 20) {
								Console.WriteLine("Selling: " + i[0]);
								Thread.Sleep(50);
								if (liveTrading) {
									API.createNewBuySellOrder(i[0], "SELL", sellWalletValue - 20);
								}
							}
						} else {
							Console.WriteLine("Error while selling: " + i[0]);
						}
					}
				}
				
				apiStatusText2.data =  "  Buying New Crypto  ";
				apiStatusText2.updateScreen();
				
				buyList = orderList(buyList);
				while(buyList.Count > ) {
					buyList.RemoveAt(buyList.Count - 1);
				}
				
				double EbuyVal = 0.00f;
				foreach(List<string> i in buyList) {
					EbuyVal += Convert.ToDouble(i[1]);
				}
				
				float buyWalletValue = API.getWalletContents("USDTBTC");
				foreach(List<string> i in buyList) {
					DisplayManager.resizeCheck();
					
					double buyPercentage = Convert.ToDouble(i[1]) / EbuyVal;
				
					if (buyPercentage * buyWalletValue > 50) {				
						Console.WriteLine("Buying: " + i[0] + "\t\tPrice: " + (buyPercentage*buyWalletValue).ToString());
						Thread.Sleep(50);
						
						if (liveTrading) {
							API.createNewBuySellOrder(i[0], "BUY", buyPercentage*buyWalletValue);
						}
					}
				}
				
				AIStatusText4.data =   "  Paused For 10 minutes  ";
				apiStatusText2.data =  "        Done!        ";
				apiStatusText2.color = ConsoleColor.Green;
				DisplayManager.updateDisplays();
				
				Thread.Sleep(1000 * 60 * 10);
				
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
