import time
loop = 1

while True:
    sentence = ""
    if (loop % 3 == 0):
        sentence += "Fizz"
    if (loop % 5 == 0):
        sentence += "Buzz"
    if (sentence == ""):
        sentence = loop
    print(sentence)
    time.sleep(0.5)
    loop += 1
