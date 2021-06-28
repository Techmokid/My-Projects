allRentValues = []
allRentValues.append(["10/06/2021",130,"Ami"])

allRentValues.append(["9/02/2021",440 - 260,"Kieran"])     #Original $440. $260 pet bond
allRentValues.append(["17/02/2021",180,"Kieran"])
allRentValues.append(["22/02/2021",180,"Kieran"])
allRentValues.append(["05/03/2021",180,"Kieran"])
allRentValues.append(["17/03/2021",180,"Kieran"])
allRentValues.append(["08/04/2021",180,"Kieran"])
allRentValues.append(["21/04/2021",180,"Kieran"])
allRentValues.append(["05/05/2021",300,"Kieran"])         #Paid in cash, bank messed up
allRentValues.append(["19/05/2021",300,"Kieran"])         #Paid in cash, bank messed up

allRentValues.append(["08/12/2020",240,"Tyler"])
allRentValues.append(["29/12/2020",115 + 65,"Tyler"])           #Paid for some of my things that week
allRentValues.append(["18/01/2021",363,"Tyler"])
allRentValues.append(["19/01/2021",180,"Tyler"])
allRentValues.append(["19/02/2021",180,"Tyler"])

allRentValues.append(["14/12/2020",240,"Daimon"])
allRentValues.append(["21/12/2020",150,"Daimon"])
allRentValues.append(["29/12/2020",240,"Daimon"])
allRentValues.append(["11/01/2021",240,"Daimon"])
allRentValues.append(["18/01/2021",123 + 117,"Daimon"])    #Paid for some of my things that week
allRentValues.append(["25/01/2021",240,"Daimon"])
allRentValues.append(["08/02/2021",240,"Daimon"])
allRentValues.append(["22/02/2021",280,"Daimon"])
allRentValues.append(["08/03/2021",180,"Daimon"])
allRentValues.append(["19/03/2021",180,"Daimon"])
allRentValues.append(["26/03/2021",180,"Daimon"])
allRentValues.append(["09/04/2021",180,"Daimon"])
allRentValues.append(["20/04/2021",20,"Daimon"])           #Paid for some of my things that week
allRentValues.append(["03/05/2021",180,"Daimon"])
allRentValues.append(["17/05/2021",180,"Daimon"])

allRentValues.append(["16/11/2020",720,"Rent",1])
allRentValues.append(["30/11/2020",720,"Rent",1])
allRentValues.append(["14/12/2020",720,"Rent",3])
allRentValues.append(["29/12/2020",720,"Rent",3])
allRentValues.append(["11/01/2021",720,"Rent",3])
allRentValues.append(["25/01/2021",720,"Rent",3])
allRentValues.append(["08/02/2021",720,"Rent",3])
allRentValues.append(["22/02/2021",720,"Rent",4])
allRentValues.append(["08/03/2021",720,"Rent",4])
allRentValues.append(["22/03/2021",720,"Rent",4])
allRentValues.append(["06/04/2021",720,"Rent",4])
allRentValues.append(["19/04/2021",720,"Rent",4])
allRentValues.append(["03/05/2021",720,"Rent",4])
allRentValues.append(["20/05/2021",720,"Rent",4])
allRentValues.append(["31/05/2021",720,"Rent",4])
allRentValues.append(["14/06/2021",720,"Rent",5])
allRentValues.append(["28/06/2021",720,"Rent",5])

#------------------------------------------------------------------------------------------------------------------------------

# i[0] = Date
# i[1] = Amount
# i[2] = Person

import datetime

for i in allRentValues:
    i[0] = dt_object = datetime.datetime.strptime(i[0], "%d/%m/%Y")
    #print(i)

rentSortedByDate = []
temp = allRentValues.copy()

while(len(temp) > 1):
    # Here we wanna iterate through all rent values and find the earliest
    indexOfEarliest = 0
    currentIndex = 0
    for i in temp:
        if (i[0] < temp[indexOfEarliest][0]):
            indexOfEarliest = currentIndex
        currentIndex += 1
    rentSortedByDate.append(temp[indexOfEarliest])
    temp.pop(indexOfEarliest)



rentSortedByDate.append(temp[0])
temp.pop(0)

tempRentVal = 0
andreyPaidRent = []
for i in rentSortedByDate:
    if (i[2] == "Rent"):
        andreyPaidRent.append([i[0],i[1] - tempRentVal,"Andrey"])
        tempRentVal = 0
    else:
        tempRentVal += i[1]

#for i in rentSortedByDate:
#    print(i)

#------------------------------------------------------------------------------------------------------------------------------

peopleData = []
for rentPayment in allRentValues:
    indexOfPerson = -1
    currentIndex = 0
    for person in peopleData:
        TempPerson = person[0][2]
        if (TempPerson == rentPayment[2]):
            indexOfPerson = currentIndex
        currentIndex += 1
    
    if (indexOfPerson == -1):
        peopleData.append([rentPayment])
    else:
        peopleData[indexOfPerson].append(rentPayment)

temp = []
rentValues = []
for i in peopleData:
    if (i[0][2] == "Rent"):
        rentValues = i
    else:
        temp.append(i)
peopleData = temp

detailedRentData = []
for i in peopleData:
    person = i[0][2]
    
    #We want to be able to search each person and ask when they started
    startDate = i[0][0]
    for rentDataPoint in i:
        if (rentDataPoint[0] < startDate):
            startDate = rentDataPoint[0]
    
    personValidRentOwing = []
    for x in rentValues:
        if (x[0] > startDate):
            personValidRentOwing.append(x)
    
    detailedRentData.append([person,startDate,personValidRentOwing,i])

totalRentPaid = 0
for i in rentValues:
    totalRentPaid += i[1]

#------------------------------------------------------------------------------------------------------------------------------

for detailedRentDataSingleUser in detailedRentData:
    person = detailedRentDataSingleUser[0]
    startDate = detailedRentDataSingleUser[1]
    rentOwing = detailedRentDataSingleUser[2]
    rentPaid = detailedRentDataSingleUser[3]
    
    
    totalOwing = 0
    for i in rentOwing:
        totalOwing += i[1] / i[3]
    
    temp1 = totalOwing
    temp2 = 0
    for i in rentPaid:
        totalOwing -= i[1]
        temp2 += i[1]
    
    if (totalOwing > 0):
        print("Person: " + person + "\t\tOwes: $" + str(totalOwing) + "\t\t\tPercentage: " + str(round(100*temp2/temp1)) + "%")
    elif (totalOwing < 0):
        print("Person: " + person + "\t\tIn credit of: $" + str(-totalOwing) + "\t\tPercentage: " + str(round(100*temp2/temp1)) + "%")
    else:
        print("Person: " + person + "\t\tEmpty balance  \t\Percentage of total rent paid: " + str(round(100*temp2/temp1)) + "%")

print()    
print("Rent Paid By Andrey:")

totalRentPaidByAndrey = 0
for i in andreyPaidRent:
    print(" - Date: " + str(i[0]) + "\t\tAmount: " + str(i[1]))
    totalRentPaidByAndrey += i[1]
    
print("Andrey total paid:                 $" + str(totalRentPaidByAndrey))
print("Household total rent paid:         $" + str(totalRentPaid))
print("Percentage of rent paid by andrey: " + str(round(100*totalRentPaidByAndrey / totalRentPaid,2)) + "%")



























