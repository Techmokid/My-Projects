import time
import matplotlib.pyplot as plt
from neuron import Neuron  # Import the Neuron class

# Configuration
voltagesConfig = [-70, -62, 20, -77]
timingsConfig = [0.75, 0.8, 1.6, 4.0]
myNeuron = Neuron(voltagesConfig, "mV", timingsConfig, "ms")

# Simulation
startingTime = time.perf_counter()
time_points = []
voltage_points = []
while time.perf_counter() - startingTime < 0.006:
    time_points.append((time.perf_counter() - startingTime) * 1000)
    voltage_points.append(myNeuron.getVoltage("mv"))

    # Probe the neuron
    if time.perf_counter() - startingTime > 0.001:
        if time.perf_counter() - startingTime > 0.004:
            myNeuron.updateInput(-60)
        else:
            myNeuron.updateInput(10)

# Plotting
plt.plot(time_points, voltage_points)
plt.axhline(y=myNeuron.rV*1000, color='green', linestyle=':', alpha=0.5)  # Resting Voltage
plt.axhline(y=myNeuron.tV*1000, color='red', linestyle=':', alpha=0.5)    # Trigger Voltage Threshold
plt.xlabel("Time (ms)")
plt.ylabel("Voltage (mV)")
plt.title("Neuron Voltage Over Time")
plt.grid(True)
plt.show()
