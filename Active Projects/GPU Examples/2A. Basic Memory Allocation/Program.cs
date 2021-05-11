using ILGPU;
using ILGPU.Runtime;
using System;
using System.Linq;

namespace Basic_GPU_Start {
    class Program {
		const int AllocationSize1D = 512;
		
        static void Main(string[] args) {
            // Create main context
            using (var context = new Context()) {
                // Perform memory allocations and operations on all available accelerators
				foreach (var acceleratorId in Accelerator.Accelerators) {
					if (acceleratorId.GetHashCode() == 0) {
						// This would be a CPU
					} else if (acceleratorId.GetHashCode() == 1) {
						// This would be a CUDA GPU
						using (var accelerator = Accelerator.Create(context, acceleratorId)) {
							ClearGPUMemory(accelerator);
							Alloc1D(accelerator);
						}
					} else if (acceleratorId.GetHashCode() == 2) {
						// This would be a non-CUDA GPU
					}
				}
			}
        }
		
		static void ClearGPUMemory(Accelerator accelerator) {
            using (var data = accelerator.Allocate<int>(1024)) {
				data.MemSetToZero();
			}
        }
		
		static void Alloc1D(Accelerator accelerator) {
            Console.WriteLine($"Performing 1D Memory allocation on {accelerator.Name}");
            var data = Enumerable.Range(0, AllocationSize1D).ToArray();
            var targetData = new int[AllocationSize1D];
            using (var buffer = accelerator.Allocate<int>(data.Length + 32)) {
                // Copy to accelerator
                buffer.CopyFrom(
                    data,         // data source
                    0,            // source index in the scope of the data source
                    32,           // target index in the scope of the buffer
                    data.Length); // the number of elements to copy

                // Copy from accelerator
                buffer.CopyTo(
                    targetData,   // data target
                    32,           // source index in the scope of the buffer
                    0,            // target index in the scope of the data target
                    data.Length); // the number of elements to copy
            }

            // Verify data
            for (int i = 0; i < AllocationSize1D; ++i) {
                if (data[i] != targetData[i])
                    Console.WriteLine($"Error comparing data and target data at {i}: {targetData[i]} found, but {data[i]} expected");
            }
        }
    }
}
