//https://rapidapi.com/blog/how-to-use-an-api-with-c-sharp/

using System;
using System.Net;
using System.Security.Cryptography;
using System.Text;
using System.Text.Json;
using System.Text.Json.Serialization;

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
		static string key = "wWsD2wSqNNyyzAdk6RNeHwrF0chaREPLTIQBKAKUe6QkNlXXS4eEK5zEn5IKu0I7";
		static string secret = "IHMgTvIRQgcV0I3UiqFZqoj647K4YsaTC9DsEPK6v01HSYbsgb9h3NEiU9HEssiR";
		static bool createdJSON = false;
		
		class deserializedJSON {
			[JsonPropertyName("serverTime")]
			public double time { get; set; }
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
			HttpResponse<string> response = Unirest.get("https://api.binance.com/api/v3/time").asJson<string>();
			return JsonSerializer.Deserialize<deserializedJSON>(response.Body.ToString()).time;
		}
		
		public static string getExchangeInfo() {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			return Unirest.get("https://api.binance.com/api/v3/exchangeInfo").asJson<string>().Body.ToString();
		}
		
		public static string getOrderBook(string symbol) { return getOrderBook(symbol,-1); }
		public static string getOrderBook(string symbol, int limit) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/depth?symbol=" + symbol;
			if (limit > 0) { resultingString += "&limit=" + limit.ToString(); }
			
			return Unirest.get(resultingString).asJson<string>().Body.ToString();
		}
		
		public static string getRecentTrades(string symbol) { return getRecentTrades(symbol,-1); }
		public static string getRecentTrades(string symbol, int limit) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/trades?symbol=" + symbol;
			if (limit > 0) { resultingString += "&limit=" + limit.ToString(); }
			
			return Unirest.get(resultingString).asJson<string>().Body.ToString();
		}
		
		public static string getHistoricTrades(string symbol) { return getHistoricTrades(symbol,500,-1); }
		public static string getHistoricTrades(string symbol, int limit) { return getHistoricTrades(symbol,limit,-1); }
		public static string getHistoricTrades(string symbol, int limit, long fromId) {
			string filePath = "C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/Crypto AI/Compiled NEAT/C#/SaveData/HistoricDataCache.txt";
			
			if (!createdJSON) {
				createdJSON = true;
				if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
				
				string resultingString = "https://api.binance.com/api/v3/historicalTrades?symbol=" + symbol;
				if (limit > 0) { resultingString += "&limit=" + limit.ToString(); }
				if (fromId > 0) { resultingString += "&fromId=" + fromId.ToString(); }
				
				string fileDataResult2 = Unirest.get(resultingString).header("X-MBX-APIKEY",key).asJson<string>().Body.ToString();
				System.IO.File.WriteAllText(filePath, fileDataResult2);
			}
			
			System.IO.StreamReader file = new System.IO.StreamReader(filePath);
            string line = file.ReadLine();
			string fileDataResult = "";
            while (line != null) {
                fileDataResult += line + "\n";
                line = file.ReadLine();
            }
			
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
			
			return Unirest.get(resultingString).asJson<string>().Body.ToString();
		}
		
		public static string getCurrentAveragePrice(string symbol) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/avgPrice?symbol=" + symbol;
			
			return Unirest.get(resultingString).asJson<string>().Body.ToString();
		}
		
		//With this function, we can get all supported symbols/currencies (Extended data)
		public static string get24hrTickerPriceChange(string symbol) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/ticker/24hr";
			if (symbol != "") { resultingString += "?symbol=" + symbol; }
			
			return Unirest.get(resultingString).asJson<string>().Body.ToString();
		}
		
		//With this function, we can get all supported symbols/currencies (Compact data)
		public static string getTickerPrice(string symbol) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/ticker/price";
			if (symbol != "") { resultingString += "?symbol=" + symbol; }
			
			return Unirest.get(resultingString).asJson<string>().Body.ToString();
		}
		
		public static string getSymbolOrderBook(string symbol) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			string resultingString = "https://api.binance.com/api/v3/ticker/bookTicker";
			if (symbol != "") { resultingString += "?symbol=" + symbol; }
			
			return Unirest.get(resultingString).asJson<string>().Body.ToString();
		}
		
		public static string makeSecureCall(string URL) { return makeSecureCall(URL,""); }
		public static string makeSecureCall(string URL, string totalParams) {
			if (!getServerConnectivity()) { throw new Exception("No Server Connection"); }
			
			totalParams += "&timestamp=" + getServerTime();
			
			HMACSHA256 myhmacsha256 = new HMACSHA256(Encoding.UTF8.GetBytes(secret));
			byte[] encodedData = Encoding.UTF8.GetBytes(totalParams);
			byte[] hash = myhmacsha256.ComputeHash(encodedData);
			
			string resultingURL = string.Empty;
			string signature = string.Empty;
			foreach	(byte x in hash) { signature += String.Format("{0:x2}", x); }
			
			if (totalParams != "") {
				resultingURL = URL + "?" + totalParams + "&signature=" + signature;
			} else {
				resultingURL = URL + "?signature=" + signature;
			}
			
			return Unirest.get(resultingURL).header("X-MBX-APIKEY",key).asJson<string>().Body.ToString();
		}
    }
}