salary = 80000
taxBrackets = [18200, 45200, 135000, 190000]
taxValues = [0.16, 0.30, 0.37, 0.45]
noTaxThreshold = 22575
taxPaid = 17000



salary = round(salary)
tax = 0
origSalary = salary
taxIndex = 0

if salary > noTaxThreshold:
    if salary > taxBrackets[0]:
        if salary < taxBrackets[-1]:
            # We know the salary is between the first and last tax brackets
            salary -= taxBrackets[0]
            for i in range(len(taxBrackets)): # This for loop is untested
                if salary > taxBrackets[i + 1]:
                    tax += taxValues[i]*(taxBrackets[i + 1] - taxBrackets[i])
                else:
                    tax += taxValues[i]*salary
                    break
                salary -= taxBrackets[i + 1] - taxBrackets[i]
        else:
            # The salary is larger than the biggest bracket, so handle differently
            salary -= taxBrackets[0]
            for i in range(len(taxBrackets)-1):
                tax += taxValues[i]*(taxBrackets[i+1] - taxBrackets[i])
            salary -= (taxBrackets[len(taxBrackets)-1] - taxBrackets[0])
            tax += salary*taxValues[len(taxValues)-1]

print(f"The tax to be paid on a salary of ${origSalary} is ${tax:.2f}")

if taxPaid != None:
    if taxPaid > tax:
        print(f"After paying ${taxPaid}, your will be getting back ${taxPaid - tax}")
    else:
        print(f"After paying ${taxPaid}, you will owe the government ${tax - taxPaid}")
