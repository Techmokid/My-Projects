using ILGPU;
using ILGPU.Runtime;
using System;

namespace Basic_GPU_Start {
    class Program {
        static void Main(string[] args) {
            // Create main context
            using (var context = new Context()) {
                // Perform memory allocations and operations on all available accelerators
				foreach (var acceleratorId in Accelerator.Accelerators) {
					if (acceleratorId.GetHashCode() == 1) {
						// This would be a CUDA GPU
						using (var accelerator = Accelerator.Create(context, acceleratorId)) {
							Console.WriteLine($"Performing operations on {accelerator}");
							var kernel = accelerator.LoadAutoGroupedStreamKernel<Index1, ArrayView<CustomDataType>>(MyKernel);
							using (var buffer = accelerator.Allocate<CustomDataType>(1024)) {
								// Launch buffer.Length many threads and pass a view to buffer
								kernel(buffer.Length, buffer.View);

								// Wait for the kernel to finish...
								accelerator.Synchronize();
							}
						}
					}
				}
			}
        }
		
		static void MyKernel(Index1 index, ArrayView<CustomDataType> dataView) {
            dataView[index] = new CustomDataType(index);
        }
		
		internal readonly struct CustomDataType {
            public CustomDataType(int value) {
                First = value;
                Second = value * value;
            }

            public int First { get; }
            public int Second { get; }
        }
    }
}
