# http://www.mcmanis.com/chuck/robotics/projects/esc2/FET-power.html
import math

mjt         = float(input("Question 1/6: What is the max junction temperature(C):         "))
rt          = float(input("Question 2/6: What will the room temperature be (C):           "))
if (rt >= mjt):
    print("ERROR: Room temperature is above maximum junction temperature. \nERROR: MOSFET would instantly be destroyed!")
    print()
    print("-------------------")
    input("Press enter to quit\n\n")
    quit()

jc          = float(input("Question 3/6: What is the junction-to-case rating (jc):        "))
ja          = float(input("Question 4/6: What is the junction to ambient air value (ja):  "))
if (ja >= jc):
    print("WARNING: Ambient-air to junction coupling value is higher than case to junction")
    print("WARNING: Was this intended? Please check")

maxRatedAmp = float(input("Question 5/6: What is the maximum rated amps:                  "))
volts       = float(input("Question 6/6: What is the maximum voltage this MOSFET will see: "))

tempDiff = mjt - rt
maxWatts = tempDiff/jc
res = maxWatts / pow(maxRatedAmp,2)
airWatts = tempDiff/ja
airAmps = math.sqrt(airWatts/res)

print()
print("Thermal difference between case and junction: " + str(tempDiff) + " C")
print("Theoretical maximum wattage:                  " + str(maxWatts) + " W")
print("Theoretical resistance at max temp:           " + str(res) + " Ohms")
print("Ambient air max wattage:                      " + str(airWatts) + " W")
print("Ambient air max amps:                         " + str(airAmps) + " A")
print()
print("-------------------")
input("Press enter to quit\n\n")
