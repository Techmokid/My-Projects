using System.Threading;
using System.Collections.Generic;

namespace BasicAlgorithm {
	public class CryptoAlgorithm {
		public static List<double[]> trainingData = null;
		public static List<string[]> result = new List<string[]>();
		public static int dataAnalyticsViewWidth = 200;
		public static int minimumDataAnalysisLoops = 50;
		
		
		public void analyzeData(List<double[]> data) { trainingData = data; analyzeData(); }
		public void analyzeData() {
			List<ThreadDataContainer> TDC_List = new List<ThreadDataContainer>();
			bool run = true;
			int genomeIndex = 0;
			int maxThreadCount = 16;
			int currentThreadCount = 0;
			while(run) {
				while (currentThreadCount < maxThreadCount) {
					if(genomeIndex == trainingData.Count) { run = false; break; }
				
					//HERE WE WANT TO ACTUALLY START THE THREAD PROCESS
					if (trainingData[genomeIndex].Length > dataAnalyticsViewWidth + minimumDataAnalysisLoops) {
						ThreadDataContainer TDC = new ThreadDataContainer();
						
						TDC.ID = genomeIndex;
						TDC.data = trainingData[genomeIndex];
						TDC_List.Add(TDC);
						Thread workerThread = new Thread(CalculateOutput); 
						workerThread.Start(TDC);
							
						currentThreadCount++;
					}
					
					genomeIndex++;
				}
				
				if (run) {
					for (int x = 0; x < TDC_List.Count; x++) {
						if (TDC_List[x].threadCompletionStatus) {
							TDC_List.RemoveAt(x);
							currentThreadCount--;
							x--;
						}
					}
				}
			}
			while(TDC_List.Count > 0) {
				for (int x = 0; x < TDC_List.Count; x++) {
					if (TDC_List[x].threadCompletionStatus) {
						TDC_List.RemoveAt(x);
						currentThreadCount--;
						x--;
					}
				}
			}
		}
		
		public void CalculateOutput(object data) {
			ThreadDataContainer TDC = (ThreadDataContainer)data;
			
			int ID = TDC.ID;
			double[] inputData = TDC.data;
			
			for(int iteration = 0; iteration < inputData.Length - dataAnalyticsViewWidth; iteration++) {
				double networkStartVal = inputData[iteration];
				double networkInstability = 0;
				double lastValue = networkStartVal;
				for(int i = 1; i < dataAnalyticsViewWidth; i++) {
					//networkInstability
					double instability = lastValue / inputData[iteration + i];
					if (instability < 0) { instability = 1/instability; }
					networkInstability += instability;
					lastValue = inputData[iteration + i];
				}
				
				TDC.networkInstability += networkInstability;
				TDC.networkDelta += inputData[iteration + dataAnalyticsViewWidth - 1] - networkStartVal;
			}
			
			TDC.latestNetworkDelta = 0;
			TDC.latestNetworkInstability = 0;
			for(int i = inputData.Length - dataAnalyticsViewWidth; i < inputData.Length - 1; i++) {
				double instability = TDC.latestNetworkDelta / inputData[i];
				if (instability < 0) { instability = 1/instability; }
				TDC.latestNetworkInstability += instability;
				TDC.latestNetworkDelta = inputData[i + 1];
			}
			
			TDC.latestNetworkChange = inputData[inputData.Length - 1] - inputData[inputData.Length - dataAnalyticsViewWidth - 1];
			
			TDC.threadCompletionStatus = true;
		}
	}
	
	public class ThreadDataContainer {
		// Inputs
		public int ID;
		public double[] data;
		
		// Outputs
		public double networkInstability;
		public double networkDelta;
		public double latestNetworkInstability;
		public double latestNetworkDelta;
		public double latestNetworkChange;
		
		//Thread completion
		public bool threadCompletionStatus = false;
	}
}