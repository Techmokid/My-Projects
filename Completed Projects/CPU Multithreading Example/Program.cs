using System;  
using System.Threading;  
using System.Collections.Generic;

namespace CPU_Test {
	class Program {
		static void Main() {
			List<ThreadDataContainer2> TDC_List = new List<ThreadDataContainer2>();
			
			List<string> tempStringList = new List<string>();
			foreach(Genome g in genomes) {
				tempStringList.Add(saveLocation + "/Active Genomes/Genome " + g.ID.ToString());
			}
			
			bool run = true;
			int genomeIndex = 0;
			int currentThreadCount = 0;
			while(run) {
				while (currentThreadCount < maxThreadCount) {
					if(genomeIndex == tempStringList.Count) {
						run = false;
						break;
					}
					
					//HERE WE WANT TO ACTUALLY START THE THREAD PROCESS
					ThreadClass p = new ThreadClass();
					ThreadDataContainer2 TDC = new ThreadDataContainer2();
					TDC.threadInputFilepath = tempStringList[genomeIndex];
					TDC_List.Add(TDC);
					Thread workerThread2 = new Thread(p.ThreadFunction);  
					workerThread2.Start(TDC);
						
					currentThreadCount++;
					genomeIndex++;
					genomeCount.data = "       1:" + genomeIndex + "/" + tempStringList.Count;
					genomeCount.updateScreen();
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
		//	int genCount = 0;
		//	Genome bestFitnessGen = genomes[0];
		//	foreach (Genome g in genomes) {
		//		genCount++;
		//		if (genomeCount != null) {
		//			genomeCount.data = "       1:" + genCount.ToString() + "/" + genomes.Count;
		//			genomeCount.updateScreen();
		//		}
		//		
		//		Directory.CreateDirectory(saveLocation + "/Active Genomes/Genome " + g.ID.ToString());
		//		g.saveGenome(saveLocation + "/Active Genomes/Genome " + g.ID.ToString());
		//		if (g.fitness > bestFitnessGen.fitness) {
		//			bestFitnessGen = g;
		//		}
		//	}
		}     
	}
	
	public class ThreadClass {  
		public void ThreadFunction(object data) {  
			ThreadDataContainer2 TDC = (ThreadDataContainer2)data;
			Directory.CreateDirectory(TDC.threadInput);
			g.saveGenome(TDC.threadInput);
			TDC.threadCompletionStatus = true;
		}
	}
	  
	public class ThreadDataContainer2 {  
		public bool threadCompletionStatus = false;
		public string threadInput = "";
		public string threadOutput = "";
	}
}