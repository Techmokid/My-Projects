sentence = "ooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooooo"

while (True):
    try:
        with open("E:\\test.txt", "a") as myfile:
            myfile.write(sentence)
    except:
        print("Error writing to file. Trying again")
