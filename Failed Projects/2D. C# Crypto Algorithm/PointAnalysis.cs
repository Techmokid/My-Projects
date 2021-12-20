using System;
using System.Collections.Generic;

namespace PointAnalysis {
	public class CompleteAnalysis {
		//Curve of best fit
		public double CurveOfBestFitA;									// Manual (Before)
		public double CurveOfBestFitB;									// Manual (Before)
		public double CurveOfBestFitC;									// Manual (Before)
		public double CurveOfBestFitR;									// Manual
		public bool CurveInflectionPointOccursWithinDatasetParameters;	// Automatic
		
		//Line of best fit
		public double StandardLineOfBestFit_M;							// Automatic
		public double StandardLineOfBestFit_C;							// Automatic
		public double StandardLineOfBestFitR;							// Manual (After)
		 
		//Modified curve of best fit
		public double CurveOfBestFitTurnoverPointX;						// Automatic
		public double CurveOfBestFitTurnoverPointY;						// Automatic
		public double CurveLineOfBestFit_M1;							// Automatic
		public double CurveLineOfBestFit_M2;							// Automatic
		public double CurveLineOfBestFit_C1;							// Automatic
		public double CurveLineOfBestFit_C2;							// Automatic
		public double CurveLineOfBestFitR;								// Manual (After)
		
		public void AutoGenerateCurveOfBestFitValues(double X_First, double X_Last, double Y_First, double Y_Last) {
			//Curve lines of best fit calculations
			// y = ax2 + bx + c
			// Integrated (y = ax2 + bx + c) = 2ax + b
			// Integration:		0 = 2ax + b
			// Integration:		2ax = -b
			// Integration:		x = (-b) / (2a)
			// Turn over point of curve (T.O.P) = (-b / (2*a), a*(-b / (2*a))2 + b*(-b / (2*a)) + c)
			double a = CurveOfBestFitA;
			double b = CurveOfBestFitB;
			double c = CurveOfBestFitC;
			
			double CURVEESTIMATION_Y_First = a * Math.Pow(X_First,2) + b * X_First + c;
			double CURVEESTIMATION_Y_Last  = a * Math.Pow(X_Last,2)  + b * X_Last  + c;
			CurveLineOfBestFit_M1 = (CurveOfBestFitTurnoverPointY-CURVEESTIMATION_Y_First)/(CurveOfBestFitTurnoverPointX-X_First);
			CurveLineOfBestFit_M2 = (CURVEESTIMATION_Y_Last-CurveOfBestFitTurnoverPointY)/(X_Last-CurveOfBestFitTurnoverPointX);
			
			CurveLineOfBestFit_C1 = CURVEESTIMATION_Y_First - CurveLineOfBestFit_M1 * X_First;
			CurveLineOfBestFit_C2 = CURVEESTIMATION_Y_Last  - CurveLineOfBestFit_M2 * X_Last;
			
			//Standard line of best fit
			StandardLineOfBestFit_M = (CURVEESTIMATION_Y_Last - CURVEESTIMATION_Y_First)/(X_Last - X_First); 
			StandardLineOfBestFit_C = CURVEESTIMATION_Y_First - X_First * StandardLineOfBestFit_M;
		}
		
		public double getYAtX(double X) {
			return CurveOfBestFitA*Math.Pow(X,2) + CurveOfBestFitB*X + CurveOfBestFitC;
		}
	}
	
	public class currencyData {
		public string currencyName = "";
		public List<dataPoint> currencyPoints = new List<dataPoint>();
	}
		
	public class dataPoint {
		public string id;
		public string price;
		public string time;
	}
	
	public static class PointAnalysis {
		public static currencyData copy(currencyData input) { return copy(input,true);}
		public static currencyData copy(currencyData input, bool keepCurrencyPoints) {
			currencyData result = new currencyData();
			result.currencyName = input.currencyName;
			if (!keepCurrencyPoints) { return result; }
			
			foreach (dataPoint i in input.currencyPoints) {
				dataPoint temp = new dataPoint();
				temp.id = i.id;
				temp.price = i.price;
				temp.time = i.time;
				result.currencyPoints.Add(temp);
			}
			return result;
		}
		
		public static CompleteAnalysis analyseData(currencyData inputData) {
			double errorMultiplier = 2.5f;
			
			//inputData[0] = id
			//inputData[1] = price
			//inputData[2] = time
			
			CompleteAnalysis results = new CompleteAnalysis();
			CalculateCurveParameters(ref results, inputData);
			
			//Auto generate analysis parameters
			double Y_First = Convert.ToDouble(inputData.currencyPoints[0].price);
			double X_First = Convert.ToDouble(inputData.currencyPoints[0].time);
			double Y_Last = Convert.ToDouble(inputData.currencyPoints[inputData.currencyPoints.Count - 1].price);
			double X_Last = Convert.ToDouble(inputData.currencyPoints[inputData.currencyPoints.Count - 1].time);
			results.AutoGenerateCurveOfBestFitValues(X_First, X_Last, Y_First, Y_Last);
			
			//Calculate "R" value for simple r line of best fit
			double Simple_LOBF_R = 0.00f;
			int turnOver_Index = 0;
			for (int i = 0; i < inputData.currencyPoints.Count; i++) {
				double x = Convert.ToDouble(inputData.currencyPoints[i].time);
				
				// y = mx + c
				double Expected_Y = results.StandardLineOfBestFit_M * x + results.StandardLineOfBestFit_C;
				double error = Math.Abs(Expected_Y - Convert.ToDouble(inputData.currencyPoints[i].price));
				Simple_LOBF_R += Math.Pow(error,errorMultiplier);
				
				//Prepare for the curve calculations
				if (x <= results.CurveOfBestFitTurnoverPointX) {
					turnOver_Index = i;
				}
			}
			results.StandardLineOfBestFitR = Simple_LOBF_R;
			
			//Calculate "R" value for curve lines of best fit
			double Curve_LOBF_R1 = 0.00f;
			double Curve_LOBF_R2 = 0.00f;
			for (int i = 0; i < turnOver_Index; i++) {
				double x = Convert.ToDouble(inputData.currencyPoints[i].time);
				double Expected_Y = results.CurveLineOfBestFit_M1 * x + results.CurveLineOfBestFit_C1; // y = mx + c
				double error = Math.Abs(Expected_Y - Convert.ToDouble(inputData.currencyPoints[i].price));
				Curve_LOBF_R1 += Math.Pow(error,errorMultiplier);
			}
			for (int i = turnOver_Index; i < inputData.currencyPoints.Count; i++) {
				double x = Convert.ToDouble(inputData.currencyPoints[i].time);
				double Expected_Y = results.CurveLineOfBestFit_M2 * x + results.CurveLineOfBestFit_C2; // y = mx + c
				double error = Math.Abs(Expected_Y - Convert.ToDouble(inputData.currencyPoints[i].price));
				Curve_LOBF_R2 += Math.Pow(error,errorMultiplier);
			}
			results.CurveLineOfBestFitR = Curve_LOBF_R1 + Curve_LOBF_R2;
			
			//Calculate "R" value for curve of best fit
			double COBF_R = 0.00f;
			for (int i = 0; i < inputData.currencyPoints.Count; i++) {
				double x = Convert.ToDouble(inputData.currencyPoints[i].time);
				
				// y = ax2 + bx + c
				double a = results.CurveOfBestFitA;
				double b = results.CurveOfBestFitB;
				double c = results.CurveOfBestFitC;
				double Expected_Y = a * Math.Pow(x,2) + b * x + c;
				
				double error = Math.Abs(Expected_Y - Convert.ToDouble(inputData.currencyPoints[i].price));
				COBF_R += Math.Pow(error,errorMultiplier);
			}
			results.CurveOfBestFitR = COBF_R;
			
			return results;
		}
		
		public static void CalculateCurveParameters(ref CompleteAnalysis inputAnalysis, currencyData inputData) {
			//Quadratic Regression Line: https://www.easycalculation.com/statistics/learn-quadratic-regression.php
			// a = { [ Σ x2 y * Σ xx ] - [Σ xy * Σ xx2 ] } / { [ Σ xx * Σ x2x 2] - [Σ xx2 ]2 }
			// b = { [ Σ xy * Σ x2x2 ] - [Σ x2y * Σ xx2 ] } / { [ Σ xx * Σ x2x 2] - [Σ xx2 ]2 }
			// c = [ Σ y / n ] - { b * [ Σ x / n ] } - { a * [ Σ x 2 / n ] }
			
			double n = inputData.currencyPoints.Count;
			double Ex = 0.00f;
			double Ey = 0.00f;
			double Ex2 = 0.00f;
			double Ex3 = 0.00f;
			double Ex4 = 0.00f;
			double Exy = 0.00f;
			double Ex2y = 0.00f;
			for (int i = 0; i < (int)n; i++) {
				double x = Convert.ToDouble(inputData.currencyPoints[i].time);
				double y = Convert.ToDouble(inputData.currencyPoints[i].price);
				Ex += x;
				Ey += y;
				Ex2 += Math.Pow(x,2);
				Ex3 += Math.Pow(x,3);
				Ex4 += Math.Pow(x,4);
				Exy += x*y;
				Ex2y += Math.Pow(x,2)*y;
			}
			
			double Exx = Ex2 - Math.Pow(Ex,2)/n;
			Exy = Exy - Ex*Ey/n;
			double Exx2 = Ex3 - Ex2*Ex/n;
			Ex2y = Ex2y - Ex2*Ey/n;
			double Ex2x2 = Ex4 - Math.Pow(Ex2,2)/n;
			
			double a = (Ex2y*Exx - Exy*Exx2)/(Exx*Ex2x2-Math.Pow(Exx2,2));
			double b = (Exy*Ex2x2 - Ex2y*Exx2)/(Exx*Ex2x2 - Math.Pow(Exx2,2));
			double c = Ey/n - b*(Ex/n) - a*(Ex2/n);
			
			inputAnalysis.CurveOfBestFitA = a;
			inputAnalysis.CurveOfBestFitB = b;
			inputAnalysis.CurveOfBestFitC = c;
			
			inputAnalysis.CurveOfBestFitTurnoverPointX = -b / (2*a);
			inputAnalysis.CurveOfBestFitTurnoverPointY = Math.Pow(a*(-b / (2*a)),2) + b*(-b / (2*a)) + c;
			
			bool COBF_Inflection_Within_Data_1 = Convert.ToDouble(inputData.currencyPoints[0].time) < inputAnalysis.CurveOfBestFitTurnoverPointX;
			bool COBF_Inflection_Within_Data_2 = Convert.ToDouble(inputData.currencyPoints[(int)n - 1].time) > inputAnalysis.CurveOfBestFitTurnoverPointX;
			inputAnalysis.CurveInflectionPointOccursWithinDatasetParameters = COBF_Inflection_Within_Data_1 && COBF_Inflection_Within_Data_2;
		}
		
		public static currencyData GetLargestNoticableCurve(currencyData inputData, int minimumDatapointCount) {
			CompleteAnalysis outputCurveAnalysis = new CompleteAnalysis();
			CompleteAnalysis outputLineAnalysis = new CompleteAnalysis();
			currencyData outputCurveResult = new currencyData();
			currencyData outputLineResult = new currencyData();
			
			//Complete this function before executing!!!
			for (int i = minimumDatapointCount; i < inputData.currencyPoints.Count - 1; i++) {
				currencyData lastDataPointCalc = GetLastDatapointsSection(inputData,i);
				
				CompleteAnalysis tempAnalysis = analyseData(lastDataPointCalc);
				if (tempAnalysis.CurveOfBestFitR < outputCurveAnalysis.CurveOfBestFitR) {
					outputCurveAnalysis = tempAnalysis;
					outputCurveResult = lastDataPointCalc;
				}
				
				//if (tempAnalysis.StandardLineOfBestFitR < outputCurveAnalysis.StandardLineOfBestFitR) {
				//	outputLineAnalysis = tempAnalysis;
				//	outputLineResult = lastDataPointCalc;
				//}
			}
			
			if (outputCurveResult.currencyPoints.Count != 0) {
				return outputCurveResult;
				//return outputLineResult;
			}
			
			
			//Console.WriteLine("CAUGHT ERROR! GOING TO CRASH NOW!");
			//return outputCurveResult;
			return inputData;
		}
		
		public static currencyData GetLastDatapointsSection(currencyData inputData, int values) {
			currencyData result = new currencyData();
			
			// W.I.P
			for (int i = 0; i < values; i++) {
				int index = inputData.currencyPoints.Count - 1 - i;
				if (index >= 0) {
					result.currencyPoints.Add(inputData.currencyPoints[index]);
				}
			}
			
			return result;
		}
	}
}