using ILGPU;
using ILGPU.Runtime;
using System;
using System.Collections.Generic;

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
							var kernel = accelerator.LoadAutoGroupedStreamKernel<Index1, myClass, ArrayView<myClass>>(MyKernel);
							using (var buffer = accelerator.Allocate<myClass>(1024)) {
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
		
		static void MyKernel(Index1 index, ArrayView<myClass> dataView) {
            dataView[index] = new myClass(index);
        }
		
		public struct myClass {
			myClass2 myRef;
            public myClass(Index1 value) {
                myRef = new myClass2();
            }
		}
		
		public class myClass2 {
			string x;
		}
    }
}
