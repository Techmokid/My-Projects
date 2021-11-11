//https://rapidapi.com/blog/how-to-use-an-api-with-c-sharp/

using System;
using System.IO;
using System.Net;
using System.Threading;
using System.Collections.Generic;
using System.Security.Cryptography;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

using Debugging;
using unirest_net.http;

//Kline/Candlestick data 			GET		/api/v3/klines
//New order 						POST 	/api/v3/order 		(HMAC SHA256)
//Test new order 					POST 	/api/v3/order/test 	(HMAC SHA256)
//Query order						GET		/api/v3/order		(HMAC SHA256)
//Cancel order						DELETE	/api/v3/order		(HMAC SHA256)
//Cancel all orders					DELETE  /api/v3/openOrders  (HMAC SHA256)
//Currently open orders				GET 	/api/v3/openOrders  (HMAC SHA256)
//All orders						GET 	/api/v3/allOrders 	(HMAC SHA256)
//etc                               etc		etc					etc

namespace Binance_API {
    public static class API {
		public static string filePath = "C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/HistoricDataCache.txt";
		static string key = "wWsD2wSqNNyyzAdk6RNeHwrF0chaREPLTIQBKAKUe6QkNlXXS4eEK5zEn5IKu0I7";
		static string secret = "IHMgTvIRQgcV0I3UiqFZqoj647K4YsaTC9DsEPK6v01HSYbsgb9h3NEiU9HEssiR";
		public static bool createdJSON = false;
		
		class deserializedJSON1 {
			[JsonPropertyName("serverTime")]
			public double time { get; set; }
		}
		
		class deserializedJSON2 {
			[JsonPropertyName("cummulativeQuoteQty")]
			public string price { get; set; }
		}
		
		class deserializedJSON3 {
			[JsonPropertyName("price")]
			public string price {get; set; }
		}
		
		public class walletDataPacket {
			[JsonPropertyName("coin")]
			public string ID { get; set; }
			
			[JsonPropertyName("name")]
			public string name { get; set; }
			
			[JsonPropertyName("free")]
			public string free { get; set; }
			
			[JsonPropertyName("locked")]
			public string locked { get; set; }
			
			[JsonPropertyName("freeze")]
			public string freeze { get; set; }
			
			[JsonPropertyName("withdrawing")]
			public string withdrawing { get; set; }
			
			[JsonPropertyName("storage")]
			public string storage { get; set; }
			
			[JsonPropertyName("networkList")]
			public List<walletDataSubnetworksPacket> networkList { get; set; }
		}
		
		public class walletDataSubnetworksPacket {
			[JsonPropertyName("coin")]
			public string coin { get; set; }
			
			[JsonPropertyName("network")]
			public string network { get; set; }
			
			[JsonPropertyName("withdrawMin")]
			public string withdrawMin { get; set; }
			
			[JsonPropertyName("withdrawFee")]
			public string withdrawFee { get; set; }
		}
		
		public static bool getServerConnectivity() {
			try {
				//HttpResponse<string> response = Unirest.get("https://api.binance.com/api/v3/time").asJson<string>();
				Unirest.get("https://api.binance.com/api/v3/time");
			} catch { return false;}
			return true;
		}
		
		public static double getServerTime() {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			HttpResponse<string> response;
			while(true) {
				try {
					response = Unirest.get("https://api.binance.com/api/v3/time").asJson<string>();
					break;
				} catch {}
			}
			
			return JsonSerializer.Deserialize<deserializedJSON1>(response.Body.ToString()).time;
		}
		
		public static string getExchangeInfo() {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string result;
			while(true) {
				try {
					result = Unirest.get("https://api.binance.com/api/v3/exchangeInfo").asJson<string>().Body.ToString();
					break;
				} catch {}
			}
			
			return result;
		}
		
		public static string getOrderBook(string symbol) { return getOrderBook(symbol,-1); }
		public static string getOrderBook(string symbol, int limit) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/depth?symbol=" + symbol;
			if (limit > 0) { resultingString += "&limit=" + limit.ToString(); }
			
			string result;
			while(true) {
				try {
					result = Unirest.get(resultingString).asJson<string>().Body.ToString();
					break;
				} catch {}
			}
			
			return result;
		}
		
		public static string getRecentTrades(string symbol) { return getRecentTrades(symbol,-1); }
		public static string getRecentTrades(string symbol, int limit) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/trades?symbol=" + symbol;
			if (limit > 0) { resultingString += "&limit=" + limit.ToString(); }
			
			string response = "";
			while(true) {
				try {
					response = Unirest.get(resultingString).asJson<string>().Body.ToString();
					break;
				} catch { Console.WriteLine("[API Interface][Warning]: Invalid response from server. Trying again..."); }
			}
			
			return response;
		}
		
		public static string getHistoricTrades() { return getHistoricTrades("LTCBTC",500,-1); }
		public static string getHistoricTrades(string symbol) { return getHistoricTrades(symbol,500,-1); }
		public static string getHistoricTrades(string symbol, int limit) { return getHistoricTrades(symbol,limit,-1); }
		public static string getHistoricTrades(string symbol, int limit, long fromId) {
			if (!createdJSON) {
				createdJSON = true;
				if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
				
				string resultingString = "https://api.binance.com/api/v3/historicalTrades?symbol=" + symbol;
				if (limit > 0) { resultingString += "&limit=" + limit.ToString(); }
				if (fromId > 0) { resultingString += "&fromId=" + fromId.ToString(); }
				
				string fileDataResult2;
				while(true) {
					try {
						fileDataResult2 = Unirest.get(resultingString).header("X-MBX-APIKEY",key).asJson<string>().Body.ToString();
						break;
					} catch {}
				}
				
				File.WriteAllText(filePath, fileDataResult2);
			}
			
			string fileDataResult = "";
			StreamReader file = new StreamReader(filePath);
			string line = file.ReadLine();
			while (line != null) {
				fileDataResult += line + "\n";
				line = file.ReadLine();
			}
				
			//Now we just empty out the last of it and close the file
			file.Close();
			
			return fileDataResult;
		}
		
		public static string getAggregateTrades(string symbol)                         { return getAggregateTrades(symbol,0,0,0,0); }
		public static string getAggregateTrades(string symbol, int limit)              { return getAggregateTrades(symbol,0,limit,0,0); }
		public static string getAggregateTrades(string symbol, long fromID)            { return getAggregateTrades(symbol,fromID,0,0,0); }
		public static string getAggregateTrades(string symbol, long fromID, int limit) { return getAggregateTrades(symbol,fromID,limit,0,0); }
		public static string getAggregateTrades(string symbol, long fromID, int limit, long startTime, long endTime) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/aggTrades?symbol=" + symbol;
			if (fromID > 0)    { resultingString += "&fromID="    + fromID.ToString();    }
			if (startTime > 0) { resultingString += "&startTime=" + startTime.ToString(); }
			if (endTime > 0)   { resultingString += "&endTime="   + endTime.ToString();   }
			if (limit > 0)     { resultingString += "&limit="     + limit.ToString();     }
			
			string result;
			while(true) {
				try {
					result = Unirest.get(resultingString).asJson<string>().Body.ToString();
					break;
				} catch {}
			}
			
			return result;
		}
		
		public static string getCurrentAveragePrice(string symbol) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/avgPrice?symbol=" + symbol;
			
			string result;
			while(true) {
				try {
					result = Unirest.get(resultingString).asJson<string>().Body.ToString();
					break;
				} catch {}
			}
			
			try {
				return JsonSerializer.Deserialize<deserializedJSON3>(result).price;
			} catch {
				return "-1";
			}
		}
		
		//With this function, we can get all supported symbols/currencies (Extended data)
		public static string get24hrTickerPriceChange(string symbol) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/ticker/24hr";
			if (symbol != "") { resultingString += "?symbol=" + symbol; }
			
			string result;
			while(true) {
				try {
					result = Unirest.get(resultingString).asJson<string>().Body.ToString();
					break;
				} catch {}
			}
			
			return result;
		}
		
		//With this function, we can get all supported symbols/currencies (Compact data)
		public static string getTickerPrice(string symbol) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/ticker/price";
			if (symbol != "") { resultingString += "?symbol=" + symbol; }
			
			string result;
			while(true) {
				try {
					result = Unirest.get(resultingString).asJson<string>().Body.ToString();
					break;
				} catch {}
			}
			
			return result;
		}
		
		public static string getSymbolOrderBook(string symbol) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/ticker/bookTicker";
			if (symbol != "") { resultingString += "?symbol=" + symbol; }
			
			string result;
			while(true) {
				try {
					result = Unirest.get(resultingString).asJson<string>().Body.ToString();
					break;
				} catch {}
			}
			
			return result;
		}
		
		public static string makeSecureCall(string URL) { return makeSecureCall(URL,"","GET"); }
		public static string makeSecureCall(string URL, string totalParams) { return makeSecureCall(URL,totalParams,"GET"); }
		public static string makeSecureCall(string URL, string totalParams, string side) {
			while (true) {
				string resultingURL = string.Empty;
				try {
					if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
					
					totalParams += "&timestamp=" + getServerTime();
					
					HMACSHA256 myhmacsha256 = new HMACSHA256(Encoding.UTF8.GetBytes(secret));
					byte[] encodedData = Encoding.UTF8.GetBytes(totalParams);
					byte[] hash = myhmacsha256.ComputeHash(encodedData);
					
					string signature = string.Empty;
					foreach	(byte x in hash) { signature += String.Format("{0:x2}", x); }
					
					if (totalParams != "") {
						resultingURL = URL + "?" + totalParams + "&signature=" + signature;
					} else {
						resultingURL = URL + "?signature=" + signature;
					}
					
					string result;
					if (side == "GET") {
						while(true) {
							try {
								result = Unirest.get(resultingURL).header("X-MBX-APIKEY",key).asJson<string>().Body.ToString();
								break;
							} catch {}
						}
						
						return result;
					}
					
					while(true) {
						try {
							result = Unirest.post(resultingURL).header("X-MBX-APIKEY",key).asJson<string>().Body.ToString();
							break;
						} catch {}
					}
					
					return result;
				} catch {
					DebugFile.WriteLine("Error making secure call to endpoint: " + resultingURL);
					Thread.Sleep(2000);
				}
			}
		}
		
		public static string getKlines(string symbol, string interval) { return getKlines(symbol,interval,0); }
		public static string getKlines(string symbol, string interval, int limit) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/klines?symbol=" + symbol + "&interval=" + interval;
			if (limit != 0) { resultingString += "&limit=" + limit.ToString(); }
			
			string result;
			while(true) {
				try {
					result = Unirest.get(resultingString).asJson<string>().Body.ToString();
					break;
				} catch {}
			}
			
			return result;
		}
		
		//public enum Sides {
		//	BUY,
		//	SELL
		//};
		//public enum Types {
		//	LIMIT,
		//	MARKET,
		//	STOP_LOSS,
		//	STOP_LOSS_LIMIT,
		//	TAKE_PROFIT,
		//	TAKE_PROFIT_LIMIT,
		//	LIMITMAKER
		//};
		public static string createNewBuySellOrder(string symbol, string side, double quantity) {
			return createNewBuySellOrder(symbol, side, (float)quantity);
		}
		public static string createNewBuySellOrder(string symbol, string side, float quantity) {
			return API.makeSecureCall(
				"https://api.binance.com/api/v3/order"
				, "symbol=" + symbol
				+ "&side=" + side
				+ "&type=MARKET"
				+ "&quoteOrderQty=" + quantity
				//+ "&quantity=" + quantity
				, "POST"
			);
		}
		
		public static void saveDebugFile(string data, string filePath) {
			File.WriteAllText(filePath, "");
			using (StreamWriter sw = File.AppendText(filePath)) {
				foreach(string x in data.Split(",")) {
					sw.WriteLine("\t" + x + ",");
				}
			}
		}
		
		public static List<walletDataPacket> getAllWalletContents() {
			string API_result = API.makeSecureCall("https://api.binance.com/sapi/v1/capital/config/getall"); //"symbol=" + symbol);
			List<walletDataPacket> outputResult;
			
			while(true) {
				try {
					outputResult = JsonSerializer.Deserialize<List<walletDataPacket>>(API_result);
					break;
				} catch {
					Console.WriteLine("Error");
					Thread.Sleep(61*10*1000);
				}
			}
			
			return outputResult;
		}
		
		//public static walletDataPacket getWalletContents(string symbol) {
		//	List<walletDataPacket> data = getAllWalletContents();
		//	foreach (walletDataPacket i in data) {
		//		if (i.ID == symbol) {
		//			return i;
		//		}
		//	}
		//	
		//	return null;
		//}
		
		public static float getWalletContents(string symbol) {
			List<walletDataPacket> data = getAllWalletContents();
			foreach (walletDataPacket i in data) {
				if (i.ID == symbol) {
					return float.Parse(i.free);
				}
			}
			
			return -1;
		}
		
		public static List<walletDataPacket> getWalletsContents(List<string> symbols) {
			List<walletDataPacket> data = getAllWalletContents();
			
			List<walletDataPacket> result = new List<walletDataPacket>();
			foreach (walletDataPacket i in data) {
				foreach (string symbol in symbols) {
					if (i.ID == symbol) { result.Add(i); }
				}
			}
			
			return result;
		}
		
		public static List<List<string>> networkMinimums = new List<List<string>>();
		public static void getNetworkMinimums() {
			List<walletDataPacket> mins = getAllWalletContents();
			foreach(walletDataPacket i in mins) {
				foreach (walletDataSubnetworksPacket x in i.networkList) {
					networkMinimums.Add(
						new List<string> {
							x.network + x.coin,
							(Convert.ToDouble(x.withdrawMin) + Convert.ToDouble(x.withdrawFee)).ToString()
						}
					);
				}
			}
		}
		
		public static double getBuyMinimum(string x) {
			foreach(List<string> i in networkMinimums) {
				 if (i[0] == x) {
					 //Console.WriteLine("INTERNAL: " + i[1]);
					 return Convert.ToDouble(i[1]);
				}
			}
			
			return -1;
		}
		
		public static List<string> getAllTradableCoins() {
			List<string> result = new List<string>();
			
			
			
			return result;
		}
	}
}