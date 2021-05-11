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
							var kernel = accelerator.LoadAutoGroupedStreamKernel<
								Index1, ArrayView<float>, ArrayView<double>, ArrayView<double>>(MathKernel);

							var buffer = accelerator.Allocate<float>(128);
							var buffer2 = accelerator.Allocate<double>(128);
							var buffer3 = accelerator.Allocate<double>(128);

							// Launch buffer.Length many threads
							kernel(buffer.Length, buffer.View, buffer2.View, buffer3.View);

							// Wait for the kernel to finish...
							accelerator.Synchronize();

							// Resolve and verify data
							var data = buffer.GetAsArray();
							var data2 = buffer2.GetAsArray();
							var data3 = buffer3.GetAsArray();
							for (int i = 0, e = data.Length; i < e; ++i)
								Console.WriteLine($"Math results: {data[i]} (float) {data2[i]} (double [GPUMath]) {data3[i]} (double [.Net Math])");

							buffer.Dispose();
							buffer2.Dispose();
							buffer3.Dispose();
						}
					}
				}
			}
        }
		
		static void MathKernel(
            Index1 index,                    // The global thread index (1D in this case)
            ArrayView<float> singleView,    // A view of floats to store float results from GPUMath
            ArrayView<double> doubleView,   // A view of doubles to store double results from GPUMath
            ArrayView<double> doubleView2)  // A view of doubles to store double results from .Net Math
        {
            // Note the different returns type of GPUMath.Sqrt and Math.Sqrt.
            singleView[index] = IntrinsicMath.Abs(index);
            doubleView[index] = IntrinsicMath.Clamp((double)(int)index, 0.0, 12.0);

            // Note that use can safely use functions from the Math class as long as they have a counterpart
            // in the IntrinsicMath class.
            doubleView2[index] = Math.Min(0.2, index);
        }
    }
}
