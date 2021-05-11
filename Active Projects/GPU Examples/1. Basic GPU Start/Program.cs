using ILGPU;
using ILGPU.Runtime;
using System;
using System.Linq;

namespace Basic_GPU_Start {
    class Program {
        static void Main(string[] args) {
            // Create main context
            using (var context = new Context()) {
                // Perform memory allocations and operations on all available accelerators
				foreach (var acceleratorId in Accelerator.Accelerators) {
					if (acceleratorId.GetHashCode() == 0) {
						// This would be a CPU
						using (var accelerator = Accelerator.Create(context, acceleratorId)) {
							
						}
					} else if (acceleratorId.GetHashCode() == 1) {
						// This would be a CUDA GPU
						using (var accelerator = Accelerator.Create(context, acceleratorId)) {
							
						}
					} else if (acceleratorId.GetHashCode() == 2) {
						// This would be a non-CUDA GPU
						using (var accelerator = Accelerator.Create(context, acceleratorId)) {
							
						}
					}
				}
			}
        }
    }
}
