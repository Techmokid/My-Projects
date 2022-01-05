import math

numberOfDigits = int(input("How many digits do you want to calculate?\n"))

def is_autobiographical(n):
    s = str(n)
    count_digits = ''.join([str(s.count(str(i))) for i in range(len(s))])
    return s == count_digits

loop = 0

while (loop < math.pow(10,numberOfDigits)):
    if (is_autobiographical(loop)):
        print(loop)
    loop += 1
