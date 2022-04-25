usrDist = float(input("(1/6) Please enter the distance to your location (Km): "))
usrCnsmptn = float(input("(2/6) Please enter your fuel consumpmtion (L/100Km): "))
usrFlTtl = float(input("(3/6) Please enter your fuel tank capacity (L): "))
usrTicks = int(input("(4/6) How many lines are on your fuel gauge: "))
usFlLft = int(input("(5/6) How many fuel lines do you have left: "))
usrReturn = bool(input("(6/6) Finally, will this be a return trip: "))

if (usrReturn == True):
    usrDist *= 2

usrCnsmptnPerKm = usrCnsmptn / 100
fuelUsageOverTrip = usrDist * usrCnsmptnPerKm

print("You will use " + str(fuelUsageOverTrip) + " L of fuel")

# usrFlTtl when scaled is the same as usrTicks

percFuelLeftStart = round(100 * usFlLft / usrTicks)
fuelInTankStart = percFuelLeftStart * usrFlTtl / 100
print("At the start of the trip, you will have " + str(percFuelLeftStart) + " % of your fuel")

percFuelLeftEnd = round(100 * (fuelInTankStart - fuelUsageOverTrip) / usrFlTtl)
print("At the end of the trip, you will have " + str(percFuelLeftEnd) + " % of your fuel left")

ticksLeft = percFuelLeftEnd * usrTicks / 100
print("This will show up on your fuel gauge as " + str(ticksLeft) + " lines of fuel left")
print()
input("Press enter to quit\n\n")
