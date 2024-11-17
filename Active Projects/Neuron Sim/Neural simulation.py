import time
import math
import matplotlib.pyplot as plt

class Neuron:
    def __init__(self, voltagesConfig, voltageUnits, timingsConfig, timingUnits):
        assert len(voltagesConfig) == 4, "Voltages configuration should have 4 values"
        assert len(timingsConfig) == 4, "Timings configuration should have 4 values"

        self.voltDict = {"kv":1e3, "v":1, "mv":1e-3, "uv":1e-6, "μv":1e-6, "nv":1e-9, "pv":1e-12}
        self.timeDict = {"min":60, "s":1, "ms":1e-3, "us":1e-6, "μs":1e-6, "ns":1e-9, "ps":1e-12}
        
        voltMult = self.voltDict[voltageUnits.lower()]
        self.rV = voltagesConfig[0] * voltMult # Resting Voltage
        self.tV = voltagesConfig[1] * voltMult # Trigger Voltage Threshold
        self.sV = voltagesConfig[2] * voltMult # Spiking "Depolarization" voltage (Upper segment of spike)
        self.hV = voltagesConfig[3] * voltMult # Hyperpolarization voltage (How low the neuron now spikes downwards)
        
        timeMult = self.timeDict[timingUnits.lower()]
        self.tTST = timingsConfig[0] * timeMult # Time between initial trigger and tip of depolarization "spike"
        self.sTHT = timingsConfig[1] * timeMult # Time between tip of depolarization "Spike" to bottom of hyperpolarization "Dip"
        self.hTRT = timingsConfig[2] * timeMult # Time between hyperpolarization "Dip" to repolarization "Normal resting voltage"
        self.tRT  = timingsConfig[3] * timeMult  # Time after initial trigger before the neuron will allow the next trigger cycle to start
        
        self.lastTrigger = -9999 # Arbitrary time in the past, anything less than (0 - time for spike) should work

    def updateInput(self,voltage): # NOTE: The triggering signal is "Current cell voltage + input voltage", so this neuron triggers at a positive voltage, not a negative one
        now = time.perf_counter()
        if now < self.lastTrigger + self.tRT:    # If the cell is not ready to trigger again, return
            return
        if (self.getVoltage() + voltage < self.tV): # If the voltage isn't high enough to trigger, return
        #if (voltage < self.tV):
            return
        self.lastTrigger = now

    def sineInterpolate(self,start, end, t):
        return start + (end - start) * (1 - math.cos(math.pi * t)) / 2

    def getVoltage(self,voltageUnits="v"):
        # Here we use the values provided to approximate the trigger curve
        now = time.perf_counter()
        timeSinceTrigger = now - self.lastTrigger
        
        if timeSinceTrigger < self.tTST: # We are spiking
            t = timeSinceTrigger / self.tTST
            return self.sineInterpolate(self.rV,self.sV,t) / self.voltDict[voltageUnits]
        if timeSinceTrigger < self.tTST + self.sTHT: # We are dipping
            t = (timeSinceTrigger - self.tTST) / self.sTHT
            return self.sineInterpolate(self.sV,self.hV,t) / self.voltDict[voltageUnits]
        if timeSinceTrigger < self.tTST + self.sTHT + self.hTRT: # We are resetting
            t = (timeSinceTrigger - self.tTST - self.sTHT) / self.hTRT
            return self.sineInterpolate(self.hV,self.rV,t) / self.voltDict[voltageUnits]
        return self.rV / self.voltDict[voltageUnits]

voltagesConfig = [-70, -62, 20, -77]
timingsConfig = [0.75, 0.8, 1.6, 4.0]
myNeuron = Neuron(voltagesConfig, "mV", timingsConfig, "ms")

#print(myNeuron.hV)













# Simulation
startingTime = time.perf_counter()
time_points = []
voltage_points = []
while time.perf_counter() - startingTime < 0.006:
    time_points.append((time.perf_counter() - startingTime) * 1000)
    voltage_points.append(myNeuron.getVoltage("mv"))

    # Probe the neuron
    currentTime = time.perf_counter() - startingTime
    if time.perf_counter() - startingTime > 0.001:
        if time.perf_counter() - startingTime > 0.004:
            myNeuron.updateInput(-60)
        else:
            myNeuron.updateInput(10)
    



# Plotting
plt.plot(time_points, voltage_points)
plt.axhline(y=myNeuron.rV*1000, color='green', linestyle=':', alpha=0.5)  # Vertical dotted line at 5ms
plt.axhline(y=myNeuron.tV*1000, color='red', linestyle=':', alpha=0.5)
plt.xlabel("Time (ms)")
plt.ylabel("Voltage (mV)")
plt.title("Neuron Voltage Over Time")
plt.grid(True)
plt.show()
