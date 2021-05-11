using ILGPU;
using ILGPU.Runtime;
using System;
using System.Linq;

namespace Basic_GPU_Start {
    class Program {
		const int AllocationSize1D = 512;
		const int AllocationSize2D = 256;
		const int AllocationSize3D = 128;
		
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
							Alloc3D(accelerator);
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
		
		static void Alloc3D(Accelerator accelerator) {
            Console.WriteLine($"Performing 3D allocation on {accelerator.Name}");
			
            var data = new int[AllocationSize1D, AllocationSize2D, AllocationSize3D];
            for (int i = 0; i < AllocationSize1D; ++i) {
                for (int j = 0; j < AllocationSize2D; ++j)
                    for (int k = 0; k < AllocationSize3D; ++k)
                        data[i, j, k] = ((k * AllocationSize2D) + j) * AllocationSize1D + i;
            }
			
            var targetData = new int[AllocationSize1D, AllocationSize2D, AllocationSize3D];
            using (var buffer = accelerator.Allocate<int>(AllocationSize1D + 32, AllocationSize2D, AllocationSize3D))
            // You can also use:
            // using (var buffer = accl.Allocate<int>(new Index3(AllocationSize1D + 32, AllocationSize2D, AllocationSize3D)))
            {
                // Copy to accelerator
                buffer.CopyFrom(
                    data,                                                               // data source
                    new Index3(),                                                       // source index in the scope of the data source
                    new Index3(32, 0, 0),                                               // target index in the scope of the buffer
                    new Index3(AllocationSize1D, AllocationSize2D, AllocationSize3D));  // the number of elements to copy

                // Copy from accelerator
                buffer.CopyTo(
                    targetData,                                                         // data target
                    new Index3(32, 0, 0),                                               // target index in the scope of the buffer
                    new Index3(),                                                       // source index in the scope of the data source
                    new Index3(AllocationSize1D, AllocationSize2D, AllocationSize3D));  // the number of elements to copy
            }

            // Verify data
            for (int i = 0; i < AllocationSize1D; ++i) {
                for (int j = 0; j < AllocationSize2D; ++j) {
                    for (int k = 0; k < AllocationSize3D; ++k) {
                        if (data[i, j, k] != targetData[i, j, k])
                            Console.WriteLine($"Error comparing data and target data at {i}, {j}, {k}: {targetData[i, j, k]} found, but {data[i, j, k]} expected");
                    }
                }
            }
        }
    }
}
