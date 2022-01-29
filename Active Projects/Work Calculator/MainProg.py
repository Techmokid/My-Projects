from tkinter import *
import time

SLA_Batteries = [
    [6,12],
    [6,4.5],
    [6,1.3],
    [12,18],
    [12,12],
    [12,9],
    [12,7.2],
    [12,6.5],
    [12,4.5],
    [12,2.2],
    [12,1.3]
    [12,38],
    [12,26],
    [
]
LIFEPO4_Batteries = [
    [12,150],
    [12,100],
    [24,100],
    [12,200],
    [12,120],
    [12,25],
    [12,18],
    [12,12],
    [12,7],
    [12,4.5]
]
AGM_Batteries = []
GEL_Batteries = []

def solveResistorCalculations(voltage,milliAmps):
    return 1000*voltage/milliAmps

def VI2P(V,I):
    return V*I
def VP2I(V,P):
    return P/V
def IV2P(I,V):
    return I*V
def IP2V(I,P):
    return P/I
def PI2V(P,I):
    return P/I
def PV2I(P,V):
    return P/V

def BattConst(x):
    if (x == "SLA"):
        return 0.5
    if ((x == "LIFEPO4") or (x == "AGM") or (x == "GEL")):
        return 0.8
    return -1

def getClosestBatteryMatch(Ah,volts):
    if (volts == 6):
        #
        print()
    if (volts == 12):
        #
        print()
    if (volts == 24):
        #
        print()

def solveSolarCalculations(SlrRatedWatts,BattRatedAmpHrs,BattType,BattRatedVoltage,TimeToRun,LoadAmps):
    #We could be given just the load and time to run
    if ((SlrRatedWatts == None) and (BattRatedAmpHrs == None) and (BattRatedVoltage == None) and (TimeToRun == None) and (LoadAmps == None)):
        raise ValueError("No data was input!")

    if ((LoadAmps != None) and (BattType != None) and (TimeToRun != None)):
        BattRatedAmpHrs = max(BattRatedAmpHrs,LoadAmps * TimeToRun / BattConst(BattType))
    
