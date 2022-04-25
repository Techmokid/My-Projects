// Standard OS Interface Libraries
using System;
using System.IO;
using System.Drawing;
using System.Linq;
using System.Collections.Generic;

// GPU Libraries
using ComputeSharp;

namespace dotnet {
    public partial class Program
    {
		public struct internal_color {
			public float R,G,B,A;
		}
		
        static void Main(string[] args)
        {
			//Arguments:
			// - Directory to the image we want resized
			// - Directory we want the output image to be saved to
			// - The dimensions of the resize
			// - OPTIONAL: if there is 4 arguments instead of 3, then the third and fourth arguments become resolution X and Y
			
			//We want to get rid of any situations that do not match the expected number of arguments immediately
			int resulting_width,resulting_height;
			switch (args.Length) {
				case 0:
					Console.WriteLine("ERROR: No arguments given!");
					return;
				case 1:
					if (args[0].ToLower() != "help" || args[0].ToLower() != "h") {
						Console.WriteLine("ERROR: Not enough arguments!");
						return;
					}
					
					//Here we will display a help screen
					Console.WriteLine("Seam Carve Help:");
					Console.WriteLine("Usage: dotnet run [Path to image] [Output path] [Resolution]");
					Console.WriteLine("       dotnet run [Path to image] [Output path] [New Height]");
					Console.WriteLine("");
					Console.WriteLine("Examples:");
					Console.WriteLine("dotnet run \"C:/Users/aj200/Desktop/image.jpg\" \"C:/Users/aj200/Desktop/output.jpg\" 1600x1200");
					Console.WriteLine("dotnet run \"C:/Users/aj200/Desktop/image.jpg\" \"C:/Users/aj200/Desktop/output.jpg\" 1600 1200");
					return;
				case 2:
					Console.WriteLine("ERROR: Not enough arguments!");
					return;
				case 3:
					try {
						resulting_width  = Int32.Parse(args[2].Split('x')[0]);
						resulting_height = Int32.Parse(args[2].Split('x')[1]);
					} catch {
						Console.WriteLine("ERROR: An error has occured while attempting to parse the input resolution");
						return;
					}
					break;
				case 4:
					try {
						resulting_width  = Int32.Parse(args[2]);
						resulting_height = Int32.Parse(args[3]);
					} catch {
						Console.WriteLine("ERROR: An error has occured while attempting to parse the input resolution");
						return;
					}
					break;
				default:
					Console.WriteLine("ERROR: Too many arguments given!");
					return;
			}
			
			//Now that we have the expected number of arguments handled, we want to check if the file we were given actually exists
			string input_image_dir = args[0].Replace("\\","/");
			string ouput_image_dir = args[1].Replace("\\","/");
			
			if (!File.Exists(input_image_dir)) {
				Console.WriteLine("ERROR: The input file does not exist!");
				return;
			}
			
			Bitmap img = new Bitmap(input_image_dir);
			if (img.Width < resulting_width) {
				Console.WriteLine("ERROR: The requested resize width must be smaller than the original image width!");
				return;
			}
			if (img.Height < resulting_height) {
				Console.WriteLine("ERROR: The requested resize height must be smaller than the original image height!");
				return;
			}
			
			if (File.Exists(ouput_image_dir)) { File.Delete(ouput_image_dir); }
			
			Console.WriteLine();
			Console.WriteLine("------------Seam Carve Tool------------");
			Console.WriteLine();
			Console.WriteLine("Input Parameters:");
			Console.WriteLine(" - Input  Image Directory:	" + input_image_dir);
			Console.WriteLine(" - Output Image Directory:	" + ouput_image_dir);
			Console.WriteLine(" - Output Image Resolution:	" + resulting_width.ToString() + "x" + resulting_height.ToString());
			Console.WriteLine();
			Console.WriteLine("Preprocessing");
			
			
			
			//We now have all the required information to start processing the image
			internal_color[] convertedImage = new internal_color[img.Width*img.Height];
			for (int y = 0; y < img.Height; y++) {
				for (int x = 0; x < img.Width; x++) {
					Color tmp = img.GetPixel(x,y);
					internal_color col = new internal_color();
					col.R = tmp.R;
					col.G = tmp.G;
					col.B = tmp.B;
					col.A = tmp.A;
					convertedImage[x+y*img.Width] = col;
				}
			}
			
			//Now we push "internal_color[] convertedImage" to the GPU to be precomputed
			
			
			
			//To go to the GPU:
			// - internal_color[] convertedImage:	The image pixel data to be input
			// - int resulting_width:		The output width dimension after scaling
			// - int resulting_height:		The output height dimension after scaling
			// - internal_color[] resultingImage:	The output image pixel data from the GPU once computed
			
			//Perform first pass where we identify lines and important features
			Console.WriteLine("Generating initial awareness array");
			float[] GPU_content_awareness_array = new float[img.Width*img.Height];
			using ReadWriteBuffer<internal_color> convertedImageBuffer = GraphicsDevice.Default.AllocateReadWriteBuffer(convertedImage);
			using ReadWriteBuffer<float> content_aware_first_pass = GraphicsDevice.Default.AllocateReadWriteBuffer(GPU_content_awareness_array);
            using ReadWriteBuffer<float> t = GraphicsDevice.Default.AllocateReadWriteBuffer(new float[1]);
			
			//GraphicsDevice.Default.For(Threads_X, new HLSL_function(buffer_params));
			//GraphicsDevice.Default.For(Threads_X, Threads_Y, new HLSL_function(buffer_params));
			//GraphicsDevice.Default.For(Threads_X, Threads_Y, Threads_Z, new HLSL_function(buffer_params));
			GraphicsDevice.Default.For(img.Width,img.Height, new ContentAwarenessAnalysis(
				convertedImageBuffer,
				t,
				content_aware_first_pass,
				new internal_color(),
				img.Width,
				img.Height,
				1,
				0
			));
			
			content_aware_first_pass.CopyTo(GPU_content_awareness_array);
			
			Console.WriteLine("Structuring GPU output");
			for(int y = 0; y < img.Height; y++) {
				for(int x = 0; x < img.Width; x++) {
					//Console.WriteLine(GPU_content_awareness_array[x+y*img.Width]);
					//if (x > 15) {
					//	return;
					//}
					int tmp = (int)GPU_content_awareness_array[x+y*img.Width];
					if (tmp < 0)
						tmp = 0;
					if (tmp > 255)
						tmp = 255;
					img.SetPixel(x, y, Color.FromArgb(255,tmp,tmp,tmp) );
				}
			}
			
			string tmp2 = ouput_image_dir;
			img.Save(tmp2.Substring(0,tmp2.LastIndexOf("/")+1) + "PreProcessing/Stage 1 PreProcessing.png");
			
			
			
			//Perform second pass where we take the first pass data and blur it
			using ReadWriteBuffer<float> content_aware_second_pass = GraphicsDevice.Default.AllocateReadWriteBuffer(GPU_content_awareness_array);
            
			Console.WriteLine("Generating secondary processing step");
			GraphicsDevice.Default.For(img.Width,img.Height, new ContentAwarenessAnalysis(
				convertedImageBuffer,
				content_aware_first_pass,
				content_aware_second_pass,
				new internal_color(),
				img.Width,
				img.Height,
				2,
				50
			));
			
			content_aware_second_pass.CopyTo(GPU_content_awareness_array);
			
			Console.WriteLine("Structuring GPU output");
			for(int y = 0; y < img.Height; y++) {
				for(int x = 0; x < img.Width; x++) {
					//Console.WriteLine(GPU_content_awareness_array[x+y*img.Width]);
					//if (x > 15) {
					//	return;
					//}
					int tmp = (int)GPU_content_awareness_array[x+y*img.Width];
					if (tmp < 0)
						tmp = 0;
					if (tmp > 255)
						tmp = 255;
					img.SetPixel(x, y, Color.FromArgb(255,tmp,tmp,tmp) );
				}
			}
			
			tmp2 = ouput_image_dir;
			img.Save(tmp2.Substring(0,tmp2.LastIndexOf("/")+1) + "PreProcessing/Stage 2 PreProcessing.png");
			
			
			
			// Now that we have a completely functional content awareness map, we can actually perform A*
			// Unfortunately, I do not know how to create a massive list of class objects that reference themselves on the GPU
			// Due to this limitation, just for now this part of the algorithm must be done on the CPU sadly
			
			Console.WriteLine("Performing final precalculations for seam carve");
			
			float[] finalTempArray = new float[img.Width + img.Height];
			using ReadWriteBuffer<float> finalTempBuffer = GraphicsDevice.Default.AllocateReadWriteBuffer(finalTempArray);
            
			GraphicsDevice.Default.For(img.Width + img.Height, new ContentAwarenessAnalysis(
				convertedImageBuffer,
				content_aware_second_pass,
				finalTempBuffer,
				new internal_color(),
				img.Width,
				img.Height,
				3,
				0
			));
			
			finalTempBuffer.CopyTo(finalTempArray);
			
			// NOTE: The image and awareness arrays are ordered "YX", NOT "XY"!!!
			
			List<List<internal_color>> originalImageConvertedToList = new List<List<internal_color>>();
			for(int y = 0; y < img.Height; y++) {
				originalImageConvertedToList.Add(new List<internal_color>());
				
				for(int x = 0; x < img.Width; x++) {
					originalImageConvertedToList[y].Add(convertedImage[x+y*img.Width]);
				}
			}
			
			List<List<float>> awarenessConvertedToList = new List<List<float>>();
			for(int y = 0; y < img.Height; y++) {
				awarenessConvertedToList.Add(new List<float>());
				
				for(int x = 0; x < img.Width; x++) {
					awarenessConvertedToList[y].Add(GPU_content_awareness_array[x+y*img.Width]);
				}
			}
			
			List<float> xAnalysisArray = new List<float>();
			for (int i = 0; i < img.Width; i++) {
				xAnalysisArray.Add(finalTempArray[i]);
			}
			List<float> yAnalysisArray = new List<float>();
			for (int i = 0; i < img.Height; i++) {
				yAnalysisArray.Add(finalTempArray[img.Width+i]);
			}
			
			//Loop until the dimensions are correct
			Console.WriteLine("Running final seam carve");
			while (originalImageConvertedToList.Count > resulting_height || originalImageConvertedToList[0].Count > resulting_width) {
				if (originalImageConvertedToList.Count > resulting_height) {
					//Here we want to shave down the height of the image by scanning across using a horizontal line
					pixelAnalyzer[] pixelAnalysisArray = new pixelAnalyzer[originalImageConvertedToList[0].Count * originalImageConvertedToList.Count];
					using ReadWriteBuffer<pixelAnalyzer> pixelAnalysisBuffer = GraphicsDevice.Default.AllocateReadWriteBuffer(pixelAnalysisArray);
					
					float[] awarenessFloatArray = new float[
						awarenessConvertedToList.Count*awarenessConvertedToList[0].Count
					];
					
					for (int y = 0; y < awarenessConvertedToList.Count; y++) {
						for (int x = 0; x < awarenessConvertedToList[0].Count; x++) {
							awarenessFloatArray[x+y*awarenessConvertedToList[0].Count] = awarenessConvertedToList[y][x];
						}
					}
					using ReadWriteBuffer<float> awarenessFloatBuffer = GraphicsDevice.Default.AllocateReadWriteBuffer(awarenessFloatArray);
					
					GraphicsDevice.Default.For(
						awarenessConvertedToList[0].Count,
						awarenessConvertedToList.Count,
						new finalPass1(
							awarenessFloatBuffer,
							pixelAnalysisBuffer,
							awarenessConvertedToList[0].Count,
							awarenessConvertedToList.Count,
							false
						)
					);
					
					for (int i = 0; i < originalImageConvertedToList[0].Count * originalImageConvertedToList.Count; i++) {
						//Console.WriteLine(pixelAnalysisArray[i].thisY);
						img.SetPixel(
							pixelAnalysisArray[i].thisX,
							pixelAnalysisArray[i].thisY,
							Color.FromArgb (
								255,
								(int)pixelAnalysisArray[i].pixelCost,
								(int)pixelAnalysisArray[i].pixelCost,
								(int)pixelAnalysisArray[i].pixelCost
							)
						);
					}
					tmp2 = ouput_image_dir;
					img.Save(tmp2.Substring(0,tmp2.LastIndexOf("/")+1) + "PreProcessing/Stage 3 PreProcessing.png");
					
					Console.WriteLine("DEBUGGING 1");
					
					//We just have to scan through all the precomputed paths and check which one has the lowest cost
					//The one with the lowest cost we get to delete permanantely from the list in memory
					//Then we can iterate again for the next line of pixels to shave off
					
					// Change this, remove the [0] for the other axis
					int GPU_Iterations = awarenessConvertedToList[0].Count;
					float[] GPU_Output_Array = new float[GPU_Iterations];
					using ReadWriteBuffer<float> GPU_Output_Buffer = GraphicsDevice.Default.AllocateReadWriteBuffer(GPU_Output_Array);
					
					GraphicsDevice.Default.For(
						GPU_Iterations,
						new finalPass2(
							pixelAnalysisBuffer,
							GPU_Output_Buffer,
							awarenessConvertedToList[0].Count,
							awarenessConvertedToList.Count,
							false
						)
					);
					
					GPU_Output_Buffer.CopyTo(GPU_Output_Array);
					
					int indexOfLowestCost = 0;
					for (int i = 0; i < GPU_Iterations; i++) {
						//Console.WriteLine(GPU_Output_Array[i]);
						if (GPU_Output_Array[i] <= GPU_Output_Array[indexOfLowestCost])
							indexOfLowestCost = i;
					}
					Console.WriteLine("Index of lowest cost: " + indexOfLowestCost + "\t\twith a cost of: " + GPU_Output_Array[indexOfLowestCost]);
					
					List<position> pos = new List<position>();
					pixelAnalyzer tmpObj = pixelAnalysisArray[indexOfLowestCost];
	
					for(int x = 0; x < originalImageConvertedToList[0].Count-1; x++) {
						Console.WriteLine(x);
						
						position tmpPos = new position();
						tmpPos.X = tmpObj.thisX;
						tmpPos.Y = tmpObj.thisY;
						pos.Add(tmpPos);
						
						tmpObj = pixelAnalysisArray[tmpObj.nextY + (x+1)*originalImageConvertedToList.Count];
					}
					
					for(int i = 0; i < pos.Count; i++) {
						Console.WriteLine("Y: " + pos[i].Y + "\t\tX: " + pos[i].X);
					}
					
					return;
				}
				
				Console.WriteLine("Next iteration");
				if (originalImageConvertedToList[0].Count > resulting_width) {
					//Here we want to shave down the width of the image by scanning across using a vertical line
					
				}
			}
			
			Bitmap newImg = new Bitmap(xAnalysisArray.Count,yAnalysisArray.Count);
			for (int y = 0; y < originalImageConvertedToList.Count; y++) {
				for (int x = 0; x < originalImageConvertedToList[y].Count; x++) {
					internal_color intCol = originalImageConvertedToList[y][x];
					newImg.SetPixel(x, y, Color.FromArgb((int)intCol.A,(int)intCol.R,(int)intCol.G,(int)intCol.B));
				}
			}
			
			newImg.Save(ouput_image_dir);
			Console.WriteLine("Successfully finished seam carve!");
        }
    }
	
	public class A_Star_Node {
		public A_Star_Node prevNode;
		public bool isFirstNode = false;
		public bool alreadySpread = false;
		public float H;	// Geometric distance to the end node (Irrelevant in our particular case)
		public float G;	// Cost of picking that path. Just directly take the value from the blurred awareness array
		public int x;
		public int y;
	}
	
	public class position {
		public int X;
		public int Y;
	}
}



















