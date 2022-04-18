using System.Threading;
using System.Collections.Generic;

namespace BasicAlgorithm {
	public class CryptoAlgorithm {
		public static List<double[]> trainingData = null;
		public static List<string[]> result = new List<string[]>();
		
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
					ThreadDataContainer TDC = new ThreadDataContainer();
					
					TDC.ID = genomeIndex;
					TDC.data = trainingData[genomeIndex];
					TDC_List.Add(TDC);
					Thread workerThread = new Thread(CalculateOutput); 
					workerThread.Start(TDC);
						
					currentThreadCount++;
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
			
			
			
			
			
			
			
			TDC.threadCompletionStatus = true;
		}
	}
	
	public class ThreadDataContainer {
		public int ID;
		public double[] data;
		public bool threadCompletionStatus = false;
	}
}