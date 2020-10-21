from SymbolReplacement import *

directory = "C:/Users/aj200/Documents/GitHub/My-Projects/My-Projects/Active Projects/ROM Scraper/Zip Downloads/Hero's_Quest_2.zip"
for i in replaceAllOfSymbol(directory," ",["|","","-","_"]):
    print(i.replace("|"," "))
