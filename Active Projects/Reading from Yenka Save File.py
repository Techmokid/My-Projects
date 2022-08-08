import os,shutil,zipfile,xmltodict,json

orig_filepath = "C:/Users/aj200/Desktop/Lookneat/Arduino Things/Logic Gates/Transistor Half-Adder.yka"
tempFilesPath = "C:/Temp/Python Yenka Decryption/"

if (not os.path.exists(orig_filepath)):
    raise Exception("Yenka save file does not exist!")
if (os.path.exists(tempFilesPath)):
    shutil.rmtree(tempFilesPath)
os.mkdir(tempFilesPath)

with zipfile.ZipFile(orig_filepath, 'r') as zip_ref:
    zip_ref.extractall(tempFilesPath)

XMLContents = ""
translationData = ""
with open(tempFilesPath + "model.xml",'r') as f:
    XMLContents = f.read()
with open(tempFilesPath + "translation.ts",'r') as f:
    translationData = f.read()

# I have experience working with json, but not XML
resultingJSON = xmltodict.parse(XMLContents)
json.dumps(resultingJSON)

resultingTranslationData = xmltodict.parse(translationData)
json.dumps(resultingTranslationData)

print(resultingJSON)
print(resultingTranslationData)
