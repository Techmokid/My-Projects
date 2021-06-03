//https://github.com/Sergio0694/ComputeSharp
using System;
using System.Linq;
using System.Collections.Generic;
using ComputeSharp;

namespace SimpleAlloc {
	public struct test {
		public int[] w;
	}
	
    class Program
    {
		public static void Main() {
			int[] array_internal = Enumerable.Range(1,100000).ToArray();
			int aic = array_internal.Count();
			
			test[] array;
			array = new test[aic];
			foreach(int i in array_internal) {
				test z = new test();
				z.w = i;
				
				array.Append(z);
			}
			
			//array[0].matrix[0][0] = "Hello";
			//Console.WriteLine("Result: " + array[0].matrix[0][0].ToString());
			
			using ReadWriteBuffer<test> buffer = Gpu.Default.AllocateReadWriteBuffer(array);
			
			// Launch the shader
			Gpu.Default.For(buffer.Length, new MultiplyByTwo(buffer));

			// Get the data back
			buffer.CopyTo(array);
		}
    }
	
	[AutoConstructor]
	public readonly partial struct MultiplyByTwo : IComputeShader
	{
		public readonly ReadWriteBuffer<test> buffer;

		public void Execute()
		{
			test x = buffer[ThreadIds.X];
		}
	}
}