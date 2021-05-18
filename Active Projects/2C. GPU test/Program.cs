//https://github.com/Sergio0694/ComputeSharp
using System;
using System.Linq;


namespace SimpleAlloc {
    class Program
    {
		public static void Main() {
			int[] array = Enumerable.Range(1,100000).ToArray();
		}
    }
}