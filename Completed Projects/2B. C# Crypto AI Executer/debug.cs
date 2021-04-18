using System.IO;

namespace Debugging {
	static class DebugFile {
		public static string filePath = "";
		public static void Create(string _filePath) { filePath = _filePath; Create(); }
		public static void Create() { File.WriteAllText(filePath, ""); }
		public static void WriteLine() { WriteLine(""); }
		//public static void WriteLine(int x) { File.AppendText(x.ToString()); }
		//public static void WriteLine(string x) { File.AppendText(x); }
		public static void WriteLine(dynamic x) {
			using (StreamWriter sw = File.AppendText(filePath)) {
				sw.WriteLine(x);
			}	
		}
	}
}