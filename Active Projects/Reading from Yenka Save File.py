with open("C:/Users/aj200/Desktop/Lookneat/Arduino Things/Logic Gates/Transistor Half-Adder.yka",'rb') as f:
    x = str(f.read())[2:-1]
    x = x.replace("\\x","\n\\x")
    print(x)
