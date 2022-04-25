// Standard OS Interface Libraries
using System;
using System.IO;
using System.Drawing;
using System.Linq;

// GPU Libraries
using ComputeSharp;

namespace dotnet {
    public partial class Program
    {
		public struct pixelAnalyzer {
			public int thisX = -1;
			public int thisY = -1;
			public int nextX = -1;
			public int nextY = -1;
			public float pixelCost;
			public float totalCost;
		}
		
		[AutoConstructor]
		public readonly partial struct ContentAwarenessAnalysis : IComputeShader
		{
			//This function analyses the input image and creates an awareness map
			//Effectively, it figures out what is considered important or not
			//States:
			// - 1: Use line detecting algorithm to figure out important pixels
			// - 2: Blur the important pixels to get important areas
			// - 3: (OBSOLETE)Calculate the awareness of each line. VERY simple, needs to be updated later
			public readonly ReadWriteBuffer<internal_color> inputImage;
			public readonly ReadWriteBuffer<float> inputImageFloats;
			public readonly ReadWriteBuffer<float> outputImage;
			public readonly internal_color defaultStruct; 
			public readonly int width;
			public readonly int height;
			public readonly int state;
			public readonly int blurVariable_checkSquareSize;
			
			public void Execute() {
				int x = ThreadIds.X;
				int y = ThreadIds.Y;
				int index = x + y*width;
				
				switch (state) {
					case 1:
						outputImage[index] = GetAwareness(ThreadIds.X,ThreadIds.Y)*4;
						break;
					case 2:
						outputImage[index] = BlurImage(ThreadIds.X,ThreadIds.Y);
						break;
					case 3:
						outputImage[index] = CalculateLineWeights(ThreadIds.X);
						break;
					default:
						outputImage[index] = 0;
						break;
				}
			}
			
			float CalculateLineWeights(int pos) {
				float result = 0;
				if (pos >= width) {
					//We are talking about calculating horizontal lines on the Y axis
					
					for (int i = 0; i < width; i++) {
						result += GetPixelFloat(i,pos-width);
					}
					return result;				
				}
				
				//We are talking about calculating vertical lines on the X axis
				for (int i = 0; i < height; i++) {
					result += GetPixelFloat(pos,i);
				}
				return result;
			}
			
			internal_color GetPixel(int x, int y) { return inputImage[x+y*width]; }
			float GetPixelFloat(int x, int y) { return inputImageFloats[x+y*width]; }
			internal_color GetPixelDifference(internal_color in1, internal_color in2) {
				internal_color result = defaultStruct;
				result.R = Math.Abs(in1.R - in2.R);
				result.G = Math.Abs(in1.G - in2.G);
				result.B = Math.Abs(in1.B - in2.B);
				result.A = Math.Abs(in1.A - in2.A);
				return result;
			}
			
			bool isValidPixel(int x, int y) {
				if (x < 0)
					return false;
				if (x > width - 1)
					return false;
				if (y < 0)
					return false;
				if (y > height - 1)
					return false;
				return true;
			}
			
			float NormalizeColor(internal_color x) {
				return (float)(Math.Sqrt(Math.Pow(x.R,2) + Math.Pow(x.G,2) + Math.Pow(x.B,2))/Math.Sqrt(2));
			}
			
			float GetAwareness(int x, int y) {
				float horizontalAwareness = 0;
				float verticalAwareness = 0;
				
				//Here we want to calculate the horizontal and vertical awareness of this pixel
				//NOTE: Take into account pixels on the edge of the image where "isValidPixel(X,Y)" will return false
				
				//For this, we shall use a simple color comparison algorithm to detect the change in color over the surrounding pixels
				//Idea being that if the surrounding pixels are the same or similiar color, they get a very small awareness value
				//The smaller the awareness value, the less damage occurs to the image when resizing
				//Effectively just doing line detection on a simple scale for the moment. Get something more advanced later
				
				float divider = 0;
				if (isValidPixel(x+1,y)) {
					horizontalAwareness += NormalizeColor(GetPixelDifference(GetPixel(x,y),GetPixel(x+1,y)));
					divider++;
				}
				if (isValidPixel(x-1,y)) {
					horizontalAwareness += NormalizeColor(GetPixelDifference(GetPixel(x,y),GetPixel(x-1,y)));
					divider++;
				}
				if (isValidPixel(x,y+1)) {
					verticalAwareness   += NormalizeColor(GetPixelDifference(GetPixel(x,y),GetPixel(x,y+1)));
					divider++;
				}
				if (isValidPixel(x,y-1)) {
					verticalAwareness   += NormalizeColor(GetPixelDifference(GetPixel(x,y),GetPixel(x,y-1)));
					divider++;
				}
				
				//This is optional, detect the corners of the pixel and analyse them
				float pixDiff;
				if (isValidPixel(x+1,y+1)) {
					pixDiff = NormalizeColor(GetPixelDifference(GetPixel(x,y),GetPixel(x+1,y+1))) / (float)Math.Sqrt(2);
					horizontalAwareness += pixDiff;
					verticalAwareness   += pixDiff;
					divider++;
				}
				if (isValidPixel(x-1,y+1)) {
					pixDiff = NormalizeColor(GetPixelDifference(GetPixel(x,y),GetPixel(x-1,y+1))) / (float)Math.Sqrt(2);
					horizontalAwareness += pixDiff;
					verticalAwareness   += pixDiff;
					divider++;
				}
				if (isValidPixel(x+1,y-1)) {
					pixDiff = NormalizeColor(GetPixelDifference(GetPixel(x,y),GetPixel(x+1,y-1))) / (float)Math.Sqrt(2);
					horizontalAwareness += pixDiff;
					verticalAwareness   += pixDiff;
					divider++;
				}
				if (isValidPixel(x-1,y-1)) {
					pixDiff = NormalizeColor(GetPixelDifference(GetPixel(x,y),GetPixel(x-1,y-1))) / (float)Math.Sqrt(2);
					horizontalAwareness += pixDiff;
					verticalAwareness   += pixDiff;
					divider++;
				}
				
				horizontalAwareness /= divider;
				verticalAwareness /= divider;
				
				return (float)Math.Sqrt(Math.Pow(horizontalAwareness,2) + Math.Pow(verticalAwareness,2))/(float)Math.Sqrt(2);
			}
			
			float distanceBetweenPixels(int x1, int y1, int x2, int y2, float maxDistX, float maxDistY) {
				float xDist = 1 - Math.Abs(x1 - x2) / maxDistX;
				float yDist = 1 - Math.Abs(y1 - y2) / maxDistY;
				if (xDist < 0 || xDist < 0)
					return 0;
				if (yDist < 0 || yDist < 0)
					return 0;
				
				return (float)Math.Sqrt(Math.Pow(xDist,2) + Math.Pow(yDist,2)) / (float)Math.Sqrt(2);
			}
			
			float BlurImage(int inX, int inY) {
				float result = 0;
				for(int y = -blurVariable_checkSquareSize; y <= blurVariable_checkSquareSize; y++) {
					for(int x = -blurVariable_checkSquareSize; x <= blurVariable_checkSquareSize; x++) {
						result += 10 * GetPixelFloat(inX+x,inY+y) * distanceBetweenPixels(inX+x,inY+y,inX,inY,blurVariable_checkSquareSize,blurVariable_checkSquareSize);
					}
				}
				return result / (float)Math.Pow(blurVariable_checkSquareSize*2,2);
			}
		}
		
		[AutoConstructor]
		public readonly partial struct finalPass1 : IComputeShader
		{
			//This funcion passes over all pixels in the image and creates a path-finding map
			//This mapping tells the system what the cheapest (Least costly) path is
			public readonly ReadWriteBuffer<float> inputData;
			public readonly ReadWriteBuffer<pixelAnalyzer> outputData;
			public readonly int width;
			public readonly int height;
			public readonly bool direction; // false=horizontal, true=vertical
			
			public void Execute() {
				int x = ThreadIds.X;
				int y = ThreadIds.Y;
				
				//We check to see the bottom-left, bottom-mid, and bottom-right spaces. Whichever one is lower, we point to.
				//Alternatively       right-upper, right-mid,  and right-lower
				
				if (direction) {
					float BL = GetPixelFloat(x-1,y+1);
					float BM = GetPixelFloat(x,  y+1);
					float BR = GetPixelFloat(x+1,y+1);
					if ((BL < BM) && (BL < BR)) {
						//BL is least costly
						pixelAnalyzer i = GetStructAtPosition(x,y);
						i.thisX = x;
						i.thisY = y;
						i.nextX = x-1;
						i.nextY = y+1;
						i.pixelCost = GetPixelFloat(i.nextX,i.nextY);
						SetPixel(x,y,i);
					}
					if ((BM < BR) && (BM < BL)) {
						//BM is least costly
						pixelAnalyzer i = GetStructAtPosition(x,y);
						i.thisX = x;
						i.thisY = y;
						i.nextX = x;
						i.nextY = y+1;
						i.pixelCost = GetPixelFloat(i.nextX,i.nextY);
						SetPixel(x,y,i);
					}
					if ((BR < BM) && (BR < BL)) {
						//BR is least costly
						pixelAnalyzer i = GetStructAtPosition(x,y);
						i.thisX = x;
						i.thisY = y;
						i.nextX = x+1;
						i.nextY = y+1;
						i.pixelCost = GetPixelFloat(i.nextX,i.nextY);
						SetPixel(x,y,i);
					}
				} else {
					float RU = GetPixelFloat(x+1,y-1);
					float RM = GetPixelFloat(x+1,y  );
					float RL = GetPixelFloat(x+1,y+1);
					if ((RU < RM) && (RU < RL)) {
						//RU is least costly
						pixelAnalyzer i = GetStructAtPosition(x,y);
						i.thisX = x;
						i.thisY = y;
						i.nextX = x+1;
						i.nextY = y-1;
						i.pixelCost = GetPixelFloat(i.nextX,i.nextY);
						SetPixel(x,y,i);
					}
					if ((RM < RU) && (RM < RL)) {
						//RM is least costly
						pixelAnalyzer i = GetStructAtPosition(x,y);
						i.thisX = x;
						i.thisY = y;
						i.nextX = x+1;
						i.nextY = y;
						i.pixelCost = GetPixelFloat(i.nextX,i.nextY);
						SetPixel(x,y,i);
					}
					if ((RL < RM) && (RL < RU)) {
						//RL is least costly
						pixelAnalyzer i = GetStructAtPosition(x,y);
						i.thisX = x;
						i.thisY = y;
						i.nextX = x+1;
						i.nextY = y+1;
						i.pixelCost = GetPixelFloat(i.nextX,i.nextY);
						SetPixel(x,y,i);
					}
				}
			}
			
			float GetPixelFloat(int x, int y) {
				if ((x < 0) || (y < 0) || (x > width) || (y > height))
					return 99999999;
				return inputData[x+y*width];
			}
			void SetPixel(int x, int y, pixelAnalyzer state) { outputData[x+y*width] = state; }
			pixelAnalyzer GetStructAtPosition(int x, int y) { return outputData[x+y*width]; }
		}
		
		[AutoConstructor]
		public readonly partial struct finalPass2 : IComputeShader
		{
			//This function scans all of the precomputed paths to find the total path cost
			//The CPU can then check all the path costs and pick the cheapest one
			public readonly ReadWriteBuffer<pixelAnalyzer> inputData;
			public readonly ReadWriteBuffer<float> outputData;
			public readonly int width;
			public readonly int height;
			public readonly bool direction;
			
			public void Execute() {
				int x = ThreadIds.X;
				float resultingPathCost = 0;
				pixelAnalyzer pixel;
				if (direction) {
					//Moving from top to bottom
					pixel = inputData[x];
					
					while(pixel.thisY < height - 1) {
						if ((pixel.nextX == pixel.thisX) && (pixel.nextY == pixel.thisY)) {
							outputData[x] = 987654321;
							return;
						}
						if ((pixel.nextX == -1) || (pixel.nextY == -1)) {
							outputData[x] = 987654321;
							return;
						}
						
						resultingPathCost += pixel.pixelCost;
						pixel = inputData[pixel.nextX + pixel.nextY*width];
					}
				} else {
					//Moving from left to right
					pixel = inputData[x*width];
					
					while(pixel.thisX < width - 1) {
						if ((pixel.nextX == pixel.thisX) && (pixel.nextY == pixel.thisY)) {
							outputData[x] = 987654321;
							return;
						}
						if ((pixel.nextX == -1) || (pixel.nextY == -1)) {
							outputData[x] = 987654321;
							return;
						}
						
						resultingPathCost += pixel.pixelCost;
						pixel = inputData[pixel.nextX + pixel.nextY*width];
					}
				}
				
				outputData[x] = resultingPathCost;
			}
		}
	}
}