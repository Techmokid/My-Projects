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
		static int maxNumberOfCryptos = 10;
		static bool liveTrading = true;
		static List<deserializedSymbolJSON2> limits = new List<deserializedSymbolJSON2>();
		static bool coinProt = false;
		
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
		
		class deserializedSymbolsJSON3 {
			[JsonPropertyName("symbols")]
			public string symbols { get; set; }
			
			[JsonPropertyName("baseAsset")]
			public string baseAsset { get; set; }
			
			[JsonPropertyName("quoteAsset")]
			public string quoteAsset { get; set; }
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
		
		public static List<string> getAllTradableCoins() {
			List<string> result = new List<string>();
			List<string[]> sharedCoins = new List<string[]>();
			List<string> temp1 = retrieveAllCurrencySymbols();
			List<API.walletDataPacket> temp2 = API.getAllWalletContents();
			for(int x = 0; x < temp1.Count; x++) {
				for(int y = 0; y < temp2.Count; y++) {
					for (int i = 0; i < temp2[y].networkList.Count; i++) {
						string temp = temp2[y].ID + temp2[y].networkList[i].network;
						if (coinProt)
							temp = temp2[y].name + temp2[y].networkList[i].network;
						if (temp1[x] == temp) {
							//Console.WriteLine("Shared Coin: " + temp);
							sharedCoins.Add(new string[] { temp2[y].ID,temp2[y].networkList[i].network });
							result.Add(temp1[x]);
						}
					}
				}
			}
			if (coinProt) { result = new List<string> { "RENBTC" }; }
			
			string msg = "";
			for(int y = 0; y < temp2.Count; y++) {
				for (int i = 0; i < temp2[y].networkList.Count; i++) {
					msg += temp2[y].ID + temp2[y].networkList[i].network+ "\n";
				}
			}
			File.WriteAllText("Tradable coinpairs.txt",msg);
			
			msg = "";
			for(int i = 0; i < temp1.Count; i++) {
				msg += temp1[i] + "\n";
			}
			File.WriteAllText("Analyzable coinpairs.txt",msg);
			
			msg = "";
			for(int i = 0; i < result.Count; i++) {
				msg += result[i] + "\n";
			}
			File.WriteAllText("Shared coinpairs.txt",msg);
			
			return result;
		}
		
		static void printList(List<string> result) {
			string msg = "{";
			for(int i = 0; i < result.Count; i++) {
				msg += result[i];
				if (i != result.Count-1) { msg += ","; }
			}
			msg += "}";
			Console.WriteLine(msg);
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
			
			//------------------------------------
			API.filePath = filePath + "/SaveData/HistoricDataCache.txt";
			API.filePath = "SaveData/HistoricDataCache.txt";
			API.getNetworkMinimums();
			
			Console.Clear();
			Console.SetCursorPosition(0,30);
			Console.WriteLine("Converted Code:  " + getConvertedCode("BNBBTC"));
			Console.WriteLine("Wallet contents: " + API.getWalletContents("USDT"));
			Console.WriteLine("Wallet contents of converted code: " + API.getWalletContents(getConvertedCode("BNBBTC")));
			Console.WriteLine("Converted code:  " + getConvertedCode("BTCBNB"));
			
			Console.WriteLine("Coins we have to work with:");
			//printList(getAllTradableCoins());
			//return;
			
			Console.WriteLine("Network minimums: ");
			foreach (List<string> i in API.networkMinimums) {
				string spaces = "";
				if (i[0] == "ETHBTC") {
					Console.WriteLine("Fouund it!");
					Console.WriteLine(i[1]);
				}
				//for (int x = 0; x < 35 - i[0].Length; x++) { spaces += " "; }
				//Console.WriteLine(" - Code: " + i[0] + spaces + i[1]);
			}
			Console.WriteLine("Buy minimum of ETHBTC: " + API.getBuyMinimum("ETHBTC"));
			
			for(int x = 0; x < 5; x++) { Console.WriteLine(""); }
			Console.WriteLine("COMPLETE!");
			
			
			//while(true) {}
			//------------------------------------
			
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
			
			//Console.WriteLine(API.createNewBuySellOrder("BTCUSDT", "SELL", 95.0f));
			
			while (true) {
				//List<string> currencies = retrieveAllCurrencySymbols();
				List<string> currencies = getAllTradableCoins();
				DebugFile.Create("debugging_refined.txt");
				
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
					
					float temp2 = API.getWalletContents(getConvertedCode(parentData.currencyName));
					string msg = "Currency Code: " + parentData.currencyName + "\t\tWallet Value: " + temp2.ToString();
					//Console.WriteLine(currencyIndex.ToString() + "/" + currencies.Count.ToString());
					
					//if (temp2 != 0) {
					//	DebugFile.WriteLine(msg);
					//}
				}
				
				//while (true) {}
				
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
					
					//CompleteAnalysis networkOutput = PointAnalysis.PointAnalysis.analyseData(algorithmCurrencyInputData);
					currencyData largestCurve = PointAnalysis.PointAnalysis.GetLargestNoticableCurve(algorithmCurrencyInputData, 80);
					CompleteAnalysis networkOutput_Final_Pass = PointAnalysis.PointAnalysis.analyseData(largestCurve);
					
					//if (networkOutput_Final_Pass.CurveLineOfBestFitR < Math.Sqrt(networkOutput_Final_Pass.StandardLineOfBestFitR)) {
					if (false) {
						//This is just a straight line
						double M = networkOutput_Final_Pass.StandardLineOfBestFit_M;
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
						
						double nOIP_A = networkOutput_Final_Pass.CurveOfBestFitA;
						double nOIP_B = networkOutput_Final_Pass.CurveOfBestFitB;
						double nOIP_C = networkOutput_Final_Pass.CurveOfBestFitC;
						
						//Here we get the analyzed output from the upper bounds of the main curve
						currencyData upper_Curve = PointAnalysis.PointAnalysis.copy(largestCurve,false);
						currencyData lower_Curve = PointAnalysis.PointAnalysis.copy(largestCurve,false);
						for (int i = 0; i < largestCurve.currencyPoints.Count; i++) {
							// Y = ax2 + bx + c | Where Y is the price and X is the date
							dataPoint dP = largestCurve.currencyPoints[i];
							double predictedPriceAtPoint = nOIP_A*Math.Pow(Convert.ToDouble(dP.time),2) + nOIP_B*Convert.ToDouble(dP.time) + nOIP_C;
							if (Convert.ToDouble(dP.price) >= predictedPriceAtPoint) { upper_Curve.currencyPoints.Add(dP); }
							if (Convert.ToDouble(dP.price) <= predictedPriceAtPoint) { lower_Curve.currencyPoints.Add(dP); }
						}
						
						CompleteAnalysis networkOutput_Final_Pass_Upper_Bound = PointAnalysis.PointAnalysis.analyseData(upper_Curve);
						CompleteAnalysis networkOutput_Final_Pass_Lower_Bound = PointAnalysis.PointAnalysis.analyseData(lower_Curve);
						
						
						// W.I.P CODE-MARKER
						// Must add in the upper and lower bound analysis into the buy/sell calculation
						// We want to analyze the upper bound curve and ask if we are above the upper bound average (Sell)
						// We want to analyze the lower bound curve and ask if we are below the lower bound average (Buy)
						dataPoint latestVal = algorithmCurrencyInputData.currencyPoints[algorithmCurrencyInputData.currencyPoints.Count - 1];
						
						bool isAboveUpperBoundAverage = Convert.ToDouble(latestVal.price) > networkOutput_Final_Pass_Upper_Bound.getYAtX(Convert.ToDouble(latestVal.time));
						bool isBelowLowerBoundAverage = Convert.ToDouble(latestVal.price) < networkOutput_Final_Pass_Lower_Bound.getYAtX(Convert.ToDouble(latestVal.time));
						if (isAboveUpperBoundAverage) {
							sellList.Add(
								new List<string> {
									algorithmCurrencyInputData.currencyName,
									networkOutput_Final_Pass_Upper_Bound.CurveOfBestFitA.ToString()
								}
							);
						}
						if (isBelowLowerBoundAverage) {
							buyList.Add(
								new List<string> {
									algorithmCurrencyInputData.currencyName,
									networkOutput_Final_Pass_Lower_Bound.CurveOfBestFitA.ToString()
								}
							);
						}
					}
				}
				
				AIStatusText3.data = "";
				DisplayManager.updateDisplays();
				
				for (int index = 0; index < buyList.Count; index++) {
					if (getConvertedCode(buyList[index][0]) == "UNTRUSTED BASE COIN") {
						buyList.RemoveAt(index);
						index--;
					}
				}
				
				for (int index = 0; index < sellList.Count; index++) {
					if (getConvertedCode(sellList[index][0]) == "UNTRUSTED BASE COIN") {
						sellList.RemoveAt(index);
						index--;
					}
				}
				
				Console.SetCursorPosition(0,45);
				
				// Convert the crypto codes into wallet codes
				//List<List<string>> temp9 = new List<List<string>>();
				//foreach (List<string> i in sellList) {
				//	string tempX = getConvertedCode(i[0]);
				//	if (tempX != "ERROR") {
				//		i[0] = tempX;
				//		temp9.Add(i);
				//	}  else {
				//		Console.WriteLine("ERROR: " + i[0]);
				//	}
				//}
				//sellList = temp9;
				
				//                     "       Starting       ";
				AIStatusText1.color = ConsoleColor.Cyan;
				AIStatusText2.color = ConsoleColor.Cyan;
				AIStatusText3.color = ConsoleColor.Cyan;
				apiStatusText1.color = ConsoleColor.Cyan;
				apiStatusText2.color = ConsoleColor.Cyan;
				AIStatusText2.data =   "";
				AIStatusText3.data =   "";
				apiStatusText2.data =  "";
				
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
				
				Console.Clear();
				Console.WriteLine("Ready for selling");
				
				int count = 0;
				foreach(List<string> i in sellList) {
					//DisplayManager.resizeCheck();
					count++;
					
					if ((i[0] != "USDTBTC") && (i[0] != "BTCUSDT")) {
						float sellWalletValue = API.getWalletContents(getConvertedCode(i[0]));
						
						if (sellWalletValue != -1) {
							if (sellWalletValue > 0) {
								sellWalletValue -= 1;
								Console.WriteLine("Selling: " + i[0] + "\t\tAmount: " + sellWalletValue.ToString());
								Thread.Sleep(50);
								if (liveTrading) {
									Console.WriteLine(API.createNewBuySellOrder(i[0], "SELL", sellWalletValue));
								}
							} else {
								//Console.WriteLine("Empty Wallet Found On Token: " + i[0]);
							}
						}// else { Console.WriteLine("Invalid Token: " + i[0]); }
					}
				}
				
				apiStatusText2.data =  "  Buying New Crypto  ";
				apiStatusText2.updateScreen();
				
				//---------------------------------------------------------------------------------------------------------------------------------------------------
				//Read difference between network minimum values and the percentage of requested buy coins
				Console.WriteLine("\n\nGetting network minimum value differences");
				List<List<string>> networkDistances = new List<List<string>>();
				for (int x = 0; x < buyList.Count; x++) {
					double buyMinimum = API.getBuyMinimum(buyList[x][0]);		//TODO: ERROR STATE! Returns "-1" only!!
					if (buyMinimum != -1) {
						Console.WriteLine(" - " + buyList[x][0] + "|" +
												  getConvertedCode(buyList[x][0]) + "|" +
												  buyMinimum.ToString()
										  );
						
						networkDistances.Add(
							new List<string> {
								buyList[x][0],
								buyList[x][1],
								buyMinimum.ToString()
							}
						);
						
						Console.WriteLine(
							" - Coin: " + networkDistances[networkDistances.Count - 1][0] +
							"\t\t- Amount: " + networkDistances[networkDistances.Count - 1][1] +
							"\t\t- Buy Minimum: " + networkDistances[networkDistances.Count - 1][2] + 
							"\n"
						);
					}
				}
				
				Console.WriteLine(" DONE DONE DONE DONE DONE DONE DONE DONE DONE ");
				while(true){}
				
				List<List<string>> sortedList = new List<List<string>>();
				// sortedList[i][0]: Coin ID
				// sortedList[i][1]: Amount To Buy
				// sortedList[i][2]: Minimum Buy Value
				sortedList = orderList(networkDistances);
				
				//Create the coin percentage mapping
				List<float> coinPercentageMapping = new List<float>();
				float current = 0.5f;
				foreach(List<string> i in sortedList) {
					coinPercentageMapping.Add(current);
					current /= 2;
				}
				coinPercentageMapping[coinPercentageMapping.Count - 1] = coinPercentageMapping[coinPercentageMapping.Count - 2];
				
				//Delete coins that cannot afford the percentage mapping
				for (int i = 0; i < sortedList.Count; i++) {
					// TODO: Remove this
					float temp_wallet_contents = 600.00f;
					
					if (
						Convert.ToDouble(sortedList[i][2]) + Convert.ToDouble(sortedList[i][2]) * 0.05f
						>
						// TODO: Here we just swap "temp_wallet_contents" for whatever the function for figuring out how much money we have to work from was
						//		-I do not for the life of me recall which of the API functions that was. This is literally all that's left before I test it
						coinPercentageMapping[i] * temp_wallet_contents
					) {
						sortedList.RemoveAt(i);
						
						coinPercentageMapping.RemoveAt(i);
						coinPercentageMapping[coinPercentageMapping.Count - 1] = coinPercentageMapping[coinPercentageMapping.Count - 2];
						
						i--;
					}
				}
				
				//Finally buy the coins
				for (int i = 0; i < sortedList.Count; i++) {
					DisplayManager.resizeCheck();
					
					Console.WriteLine(
						"Buying: " + sortedList[i][0] +
						"\t\tPrice: " + sortedList[i][1]
					);
					
					Thread.Sleep(61);
					
					if (liveTrading) {
						Console.WriteLine(
							API.createNewBuySellOrder(
								buyList[i][0],
								"BUY",
								Convert.ToDouble(
									buyList[i][1]
								)
							)
						);
					}
				}
				
				AIStatusText4.data =   "  Paused For 10 minutes  ";
				apiStatusText2.data =  "        Done!        ";
				apiStatusText2.color = ConsoleColor.Green;
				//DisplayManager.updateDisplays();
				
				//Thread.Sleep(1000 * 60 * 10);
				Console.WriteLine("Done");
				while(true) {}
				
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

		public static string getConvertedCode(string input) {
			if (input.Substring(len(input) - 4) == "USDT") { return input.Substring(0,len(input) - 4); }
			if (input.Substring(len(input) - 3) == "BTC")  { return input.Substring(0,len(input) - 3); }
			if (input.Substring(len(input) - 3) == "BNB")  { return input.Substring(0,len(input) - 3); }
			if (input.Substring(len(input) - 3) == "ETH")  { return input.Substring(0,len(input) - 3); }
			//if (input.Substring(len(input) - 3) == "USD")  { return input.Substring(0,len(input) - 3); }
			//if (input.Substring(len(input) - 3) == "PAX")  { return input.Substring(0,len(input) - 3); }
			//if (input.Substring(len(input) - 3) == "XRP")  { return input.Substring(0,len(input) - 3); }
			//if (input.Substring(len(input) - 3) == "RUB")  { return input.Substring(0,len(input) - 3); }
			//if (input.Substring(len(input) - 4, 3) == "USD")  { return input.Substring(0,len(input) - 4); }
			return "UNTRUSTED BASE COIN";
			
			foreach(API.walletDataPacket i in API.getAllWalletContents()) {
				foreach(API.walletDataSubnetworksPacket x in i.networkList) {
					//Here we wanna scan to see if the input exists in "getAllWalletContents"
					//Console.WriteLine(x.coin + x.network);
					if (x.coin + x.network == input) {
						return x.coin;
					}
				}
			}
			return "ERROR";
		}

		public static int len(string x) { return x.Length; }			
	}
}
