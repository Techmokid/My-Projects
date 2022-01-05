In_A = float(input("Quantum Probability A: "))
In_B = float(input("Quantum Probability B: "))
decimals = int(input("Number of Decimal Places: "))

QNOT_A = round(1 - In_A,decimals)
QNOT_B = round(1 - In_B,decimals)
QAND = round(In_A * In_B,decimals)
QNAND = round(1 - In_A * In_B,decimals)
QOR = round(1 - ((1 - In_A) * (1 - In_B)),decimals)
QNOR = round((1 - In_A) * (1 - In_B),decimals)
QXOR = round((1 - In_A * In_B) * (1 - ((1 - In_A) * (1 - In_B))),decimals)
QXNOR = round(1 - (1 - In_A * In_B) * (1 - ((1 - In_A) * (1 - In_B))),decimals)

print("\nStandard Gates Modified To Work With Quantum Probabilities")
print("A QNOT: " + str(QNOT_A))
print("B QNOT: " + str(QNOT_B))
print("A QAND B: " + str(QAND))
print("A QNAND B: " + str(QNAND))
print("A QOR B: " + str(QOR))
print("A QNOR B: " + str(QNOR))
print("A QXOR B: " + str(QXOR))
print("A QXNOR B: " + str(QXNOR))

def QNOT(Gate_Input):
    ans = 1 - In_A
    return ans

def QAND(In_A, In_B):
    ans = In_A * In_B
    return ans

def QNAND(In_A, In_B):
    ans = 1 - In_A * In_B
    return ans

def QOR(In_A, In_B):
    ans = 1 - ((1 - In_A) * (1 - In_B))
    return ans

def QNOR(In_A, In_B):
    ans = (1 - In_A) * (1 - In_B)
    return ans

def QXOR(In_A, In_B):
    ans = (1 - In_A * In_B) * (1 - ((1 - In_A) * (1 - In_B)))
    return ans

def QXNOR(In_A, In_B):
    ans = 1 - (1 - In_A * In_B) * (1 - ((1 - In_A) * (1 - In_B)))
    return ans
