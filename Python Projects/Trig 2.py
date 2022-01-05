import matplotlib.pyplot as plt
import numpy as np

filepath = "C:/Users/aj200/Documents/Unity Projects/Drone Simulation/Assets/Unity3D Neat AI/Recorded Fitness Overtime.txt"

with open(filepath,'r',encoding = 'utf8') as f:
    data = f.read()

data = data.split('\n')
print(len(data))

x = 0
while (x < len(data) - 1):
    print(x)
    y = float(data[x])
    plt.plot(x,y,'ob')
    x += 1

plt.show()
