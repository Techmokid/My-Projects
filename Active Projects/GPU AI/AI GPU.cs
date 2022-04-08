using ComputeSharp;

namespace CryptoAI {
	// The indexing for the nodes array:
	//  - Genome_GPU[i].Nodes_Start_Index   gives us where to start in the index array.
	//  - Genome_GPU[i+1].Nodes_Start_Index gives us where to end   in the index array.
	//  - The nodes are ordered in genome 1, genome 2, genome 3, etc with data positions listed above
	//  - In each genome, the nodes in the nodes array is ordered "Starting nodes", "Hidden nodes", "Output nodes"
	
	// So, to get the outputs of a genome, we:
	// - Get the genome index from the thread.x
	// - Read out the "Nodes_Start_Index" variable in the genome to figure out where to start reading the node data from
	// - Set each of the node inputs from "Nodes_Start_Index" all the way up until the nodes starting showing (nII==False)
	// - Now iterate forward in memory until we get (nIO==True) and put this in index variable integer "OutputNodesStartIndex"
	// - For each node between "OutputNodesStartIndex" and "Genome_GPU[i+1].Nodes_Start_Index - 1", we ask it for it's output
	
	// To get a nodes output:
	// - for (int i = nodes[nodeIndex].weightIndexes; i < nodes[nodeIndex+1].weightIndexes; i++)
	// - Now that we are iterating over every connection, we simply call the node in nodes[nodeConnections[i].NodeID] and do the algorithm
	
	public partial class Program {
		Network_GPU NGPU;
		
		public struct Node_GPU {
			public char NodeActivationType = ' ';				// 'c' is classic. 'n' is neural
			public int ID = -1;									// The ID of this node
			
			public float tT = 0;								// Minimum amount of input before triggering
			public float prev_tT = 0;
			public float tS = 0;								// Strength of the output transmition
			public float prev_tS = 0;
			
			public bool nII = false; 							// Is the node is an input or not
			public bool nIO = false; 							// Is the node is an output or not
			public float nIV = 0;								// If the node is an input, what have we entered
			public float pO = -99999;							// This variable just allows for quicker genome output computing
			
			public int weightIndexes = 0; 							// Complex. This is the position in the array where the weights are held
		}
		
		public struct NodeConnection_GPU {
			public int NodeID;
			public float Weight;
		}
		
		public struct Genome_GPU {
			public int ID;
			public int Nodes_Start_Index;
		}
		
		public struct Network_GPU {
			Genome_GPU[] genomes;
			Node_GPU[] nodes;
		}
		
		public void Convert_CPU_Network_To_GPU_Network(Network N) {
			
		}
		
		[AutoConstructor]
		public readonly partial struct GetAIOutput : IComputeShader {
			public readonly ReadWriteBuffer<Genome_GPU> genomes;	             // This contains the genome objects that tell the GPU where each genome starts
			public readonly ReadWriteBuffer<Node_GPU> nodes;		             // This contains the node object
			public readonly ReadWriteBuffer<int> nodeWeightStartIndex;		     // This is the indexes of the start of each node connection
			public readonly ReadWriteBuffer<NodeConnection_GPU> nodeConnections; // This contains all of the node connections data
			
			public readonly ReadWriteBuffer<float> genomeInputs;
			public readonly ReadWriteBuffer<float> genomeOutputs;
			
			public readonly int numberOfIterations;								 // How many times do we want to iterate the AI before handing back to the CPU
			
			public void Execute() {
				int x = ThreadIds.X;
				
				int genomeID = genomes[x].ID;
				int nodeStartingIndex = genomes[x].Nodes_Start_Index;
				int nodeEndingIndex = nodes.Length - 1;
				if (x != genomes.Length - 1)
					nodeEndingIndex = genomes[x+1].Nodes_Start_Index;
				
				for (int iteration = 0; iteration < numberOfIterations; iteration++) {
					//The first set of nodes is going to be inputs. Set their values
					for (int i = 0; i < genomeInputs.Length; i++) {
						nodes[nodeStartingIndex + i].nIV = genomeInputs[i];
					}
					
					//Now that we have all the input nodes set, we simply request the output nodes to give us their outputs iteratively
					int outputNodesStart = nodeStartingIndex + genomeInputs.Length;
					while(true) {
						if (nodes[outputNodesStart].nIO) { break; }	// We just found the first output node in this genome
						outputNodesStart++;
					}
					
					int outputNodeCount = 1 + nodeEndingIndex - outputNodesStart;
					for (int i = outputNodesStart; i <= nodeEndingIndex; i++) {
						//Here we just call the node to give us it's output
						genomeOutputs[outputNodeCount*x + i] = GetNodeOutput(i);
					}
				}
			}
			
			public float GetNodeOutput(int nodeMemoryPosition) {
				if (nodes[nodeMemoryPosition].nII)							// If the node is an input, just return it's value
					return nodes[nodeMemoryPosition].nIV;					
				if (nodes[nodeMemoryPosition].pO == -99999)					// If the node has already calculated it's output, just return that
					return nodes[nodeMemoryPosition].pO;
				if (nodes[nodeMemoryPosition].NodeActivationType == ' ')
					return -99999;
				
				//Here we wanna calculate the nodes output
				float result = 0;
				
				char nAT= nodes[nodeMemoryPosition].NodeActivationType;
				if (nAT == 'c') {			// A classic node: "Output is just the sum all all the incoming values multiplied by their weight"
					
				} else if (nAT == 'n') { 	// A neural node: "Output will fire with output value 'tS' when the sum of all incoming values multiplied by their weight equals or exceeds 'tT'"
					
				} else { return -999999; }
				
				nodes[nodeMemoryPosition].pO = result;
				return result;
			}
		}
	}
}