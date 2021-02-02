using System;
using System.Collections.Generic;
using Debugging;

namespace Display {
	class DisplayManager {
		static int w = 0;
		static int h = 0;
		
		public static List<dataScreen> dataScreens = new List<dataScreen>();
		public static List<DisplayGroup> groups = new List<DisplayGroup>();
		
		public static void StartDisplay() {
			w = Console.WindowWidth;
			h = Console.WindowHeight;
		}
		
		public static void resizeCheck() {
			if ((w != Console.WindowWidth) || (h != Console.WindowHeight)) {
				updateDisplays();
			}
		}
		
		public static dataScreen addScreen(int x_offset, int y_offset, string hor, string ver, string data) {
			dataScreen temp = new dataScreen();
			temp.x = x_offset;
			temp.y = y_offset;
			temp.data = data;
			
			if (hor == "Left") {
				temp.hDR = dataScreen.horizontalDisplayRelation.Left;
			} else if ((hor == "Center") || (hor == "Middle")) {
				temp.hDR = dataScreen.horizontalDisplayRelation.Center;
			} else if (hor == "Right") {
				temp.hDR = dataScreen.horizontalDisplayRelation.Right;
			}
			
			if (ver == "Top") {
				temp.vDR = dataScreen.verticalDisplayRelation.Top;
			} else if ((ver == "Center") || (ver == "Middle")) {
				temp.vDR = dataScreen.verticalDisplayRelation.Middle;
			} else if (ver == "Bottom") {
				temp.vDR = dataScreen.verticalDisplayRelation.Bottom;
			}
			
			dataScreens.Add(temp);
			return temp;
		}
		
		public static void updateDisplays() { updateDisplays(true); }
		public static void updateDisplays(bool clearScreens) {
			if ((w != Console.WindowWidth) || (h != Console.WindowHeight) || clearScreens) {
				w = Console.WindowWidth;
				h = Console.WindowHeight;
				Console.Clear();
			}
			
			for (int i = 0; i < dataScreens.Count; i++) {
				dataScreens[i].updateScreen();
			}
			for (int i = 0; i < groups.Count; i++) {
				groups[i].showBorder();
			}
		}
		
		public static void createGroup(List<dataScreen> tempScreens) {
			DisplayGroup tempGroups = new DisplayGroup();
			for (int i = 0; i < tempScreens.Count; i++) {
				tempGroups.grouping.Add(tempScreens[i]);
			}
			tempGroups.showBorder();
			groups.Add(tempGroups);
		}
	}
	
	public class dataScreen {
		public int x = 0;
		public int y = 0;
		
		public ConsoleColor color = Console.ForegroundColor;
		
		public enum horizontalDisplayRelation { Left, Center, Right }
		public enum verticalDisplayRelation { Top, Middle, Bottom }
		
		public horizontalDisplayRelation hDR = horizontalDisplayRelation.Left;
		public verticalDisplayRelation vDR = verticalDisplayRelation.Top;
		
		public string data;
		
		public void updateScreen() {
			if (x >= Console.WindowWidth) {return;}
			
			ConsoleColor oldColor = Console.ForegroundColor;
			Console.ForegroundColor = color;
			
			int tempX = 0;
			int tempY = 0;
			
			if (hDR == horizontalDisplayRelation.Left) {
				tempX = x;
			} else if (hDR == horizontalDisplayRelation.Center) {
				tempX = x + (Console.WindowWidth / 2);
			} else if (hDR == horizontalDisplayRelation.Right) {
				tempX = Console.WindowWidth - x;
			}
			
			if (vDR == verticalDisplayRelation.Top) {
				tempY = y;
			} else if (vDR == verticalDisplayRelation.Middle) {
				tempY = y + (Console.WindowHeight / 2);
			} else if (vDR == verticalDisplayRelation.Bottom) {
				tempY = Console.WindowHeight - y;
			}
			
			if (tempX < Console.WindowWidth) {
				Console.SetCursorPosition(tempX,tempY);
				for (int i = 0; (i < data.Length) && (i + tempX < Console.WindowWidth); i++) {
					Console.Write(data[i]);
				}
			}
			
			Console.ForegroundColor = oldColor;
		}
	}
	
	public class DisplayGroup {
		public List<dataScreen> grouping = new List<dataScreen>();
		
		public void addToGroup(dataScreen screen) { grouping.Add(screen); }
		public void showBorder() {
			if(grouping.Count == 0){return;}
			
			int minX = grouping[0].x;
			int maxX = grouping[0].x + grouping[0].data.Length;
			int minY = grouping[0].y;
			int maxY = grouping[0].y;
			
			for (int indexVar = 0; indexVar < grouping.Count; indexVar++) {
				if (grouping[indexVar].x < minX) {
					minX = grouping[indexVar].x;
				}
				
				if (grouping[indexVar].x + grouping[indexVar].data.Length > maxX) {
					maxX = grouping[indexVar].x + grouping[indexVar].data.Length;
				}
				
				if (grouping[indexVar].y < minY) {
					minY = grouping[indexVar].y;
				}
				
				if (grouping[indexVar].y > maxY) {
					maxY = grouping[indexVar].y;
				}
			}
			
			if (minX < Console.WindowWidth) {
				Console.SetCursorPosition(minX - 1, minY - 1);
				Console.Write("+");
				for (int a = 0; a < maxX - minX; a++) {
					if (minX + a < Console.WindowWidth) { Console.Write("-"); }
				}
				
				if (maxX < Console.WindowWidth) {
					Console.Write("+");
				}
			}
			
			if (minX < Console.WindowWidth) {
				Console.SetCursorPosition(minX - 1, maxY + 1);
				Console.Write("+");
				for (int a = 0; a < maxX - minX; a++) {
					if (minX + a < Console.WindowWidth) { Console.Write("-"); }
				}
				
				if (maxX < Console.WindowWidth) {
					Console.Write("+");
				}
			}
			
			for (int a = minY; a <= maxY; a++) {
				if (minX < Console.WindowWidth) {
					Console.SetCursorPosition(minX - 1,a);
					Console.Write("|");
				}
			}
			
			for (int a = minY; a <= maxY; a++) {
				if (maxX < Console.WindowWidth) {
					Console.SetCursorPosition(maxX,a);
					Console.Write("|");
				}
			}
		}
	}
}



























