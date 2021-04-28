using System;
using System.Collections.Generic;

namespace PointAnalysis {
	public class CompleteAnalysis {
		public double dataDirection;
		public double derivative;
		public double jumpDetection;
		public double concavity;
		public double bestFitLineR;
	}
	
	public class currencyData {
		public string currencyName = "";
		public List<dataPoint> currencyPoints = new List<dataPoint>();
	}
		
	public class dataPoint {
		public string id;
		public string price;
		public string time;
	}
	
	public static class PointAnalysis {
		public static List<double> smoothData(List<double> inputData, int iterations) {
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
		
		public static CompleteAnalysis analyseData(currencyData inputData) { return analyseData(inputData,inputData.currencyPoints.Count,false); }
		public static CompleteAnalysis analyseData(currencyData inputData, bool normalizeOutputValues) { return analyseData(inputData,inputData.currencyPoints.Count,normalizeOutputValues); }
		public static CompleteAnalysis analyseData(currencyData inputData, int numberOfPreviousPoints) { return analyseData(inputData,numberOfPreviousPoints,false); }
		public static CompleteAnalysis analyseData(currencyData inputData, int numberOfPreviousPoints, bool normalizeOutputValues) {
			int startingIndexOffset = 2;
			int endingIndexOffset = 2;
			
			//inputData[0] = id
			//inputData[1] = price
			//inputData[2] = time
			
			//Console.WriteLine(inputData.Count);
			//List<List<double>> smoothingInputData = new List<List<double>>();
			//for (int x = 0; x < inputData.currencyPoints.Count; x++) {
			//	List<double> temp_B = new List<double>();
			//	temp_B.Add(Convert.ToDouble(inputData.currencyPoints[x].id));
			//	temp_B.Add(Convert.ToDouble(inputData.currencyPoints[x].price));
			//	temp_B.Add(Convert.ToDouble(inputData.currencyPoints[x].time));
			//	
			//	smoothingInputData.Add(temp_B);
			//}
			
			List<double> smoothingInputData = new List<double>();
			for (int x = 0; x < inputData.currencyPoints.Count; x++) {
				smoothingInputData.Add(Convert.ToDouble(inputData.currencyPoints[x].price));
			}
			
			while (smoothingInputData.Count > numberOfPreviousPoints) { smoothingInputData.RemoveAt(0); }
			
			List<double> smoothedDataCache = smoothData(smoothingInputData,3);
			double val1 = 0;
			double val2 = 0;
			
			try {
				val1 = smoothedDataCache[smoothedDataCache.Count - endingIndexOffset - 1];
			} catch {
				return new CompleteAnalysis();
			}
			
			double dataDirection = val1 - val2;
			if (normalizeOutputValues) {
				if (dataDirection > 0) {
					dataDirection = 1;
				} else if (dataDirection == 0) {
					dataDirection = 0;
				} else {
					dataDirection = -1;
				}
			}
			
			double x1 = startingIndexOffset;
			double x2 = smoothedDataCache.Count - endingIndexOffset - 1;
			double y1 = smoothedDataCache[startingIndexOffset];
			double y2 = smoothedDataCache[smoothedDataCache.Count - endingIndexOffset - 1];
			double derivative = Math.Atan((y2 - y1)/(x2 - x1)) * 2 / Math.PI;
			
			double jumpDetection = 0;
			for(int i = startingIndexOffset; i < smoothedDataCache.Count - endingIndexOffset - 1; i++) {
				if (Math.Abs(smoothedDataCache[i] / smoothedDataCache[i - startingIndexOffset]) > 3) {
					jumpDetection = 1;
				}
			}
			
			double x_mid = (smoothedDataCache.Count - endingIndexOffset - 1 - startingIndexOffset) / 2 + startingIndexOffset;
			double y_mid = smoothedDataCache[(int)x_mid];
			double concavity_1 = Math.Atan((y_mid - y1)/(x_mid - x1));
			double concavity_2 = Math.Atan((y2 - y_mid)/(x2 - x_mid));
			double concavity = concavity_2 - concavity_1;
			
			double bestFitLineR = 0;
			
			CompleteAnalysis result = new CompleteAnalysis();
			result.dataDirection = dataDirection;
			result.derivative = derivative * 1000000;
			result.jumpDetection = jumpDetection;
			result.concavity = concavity * 1000000;				//This is a scaling offset
			result.bestFitLineR = bestFitLineR;
			return result;
		}
	}
}