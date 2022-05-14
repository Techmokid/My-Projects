import xlrd

input_excel_file = "Work Z-tray Readout.xls"
output_text_file = "ITEMID~1.TXT"

def getFormattedSentence(ID, X, Y):
    try:
        return str(int(X)) + "," + str(int(Y)) + ":" + str(ID).upper()
    except:
        return ""

def isValidPartCode(ID):
    if (len(ID) != 6):
        return False
    if (ID[0].isalpha() and ID[1].isalpha()):
        if (ID[2].isdigit() and ID[3].isdigit() and ID[4].isdigit() and ID[5].isdigit()):
            return True
    return False

wb = xlrd.open_workbook(input_excel_file)
sheet = wb.sheet_by_index(0)

fileContents = []
for y in range(1,sheet.ncols):
    for x in range(1,sheet.nrows):
        formattedString = getFormattedSentence(sheet.cell_value(x,y),y,x)
        
        if (isValidPartCode(sheet.cell_value(x,y))):
            fileContents.append(formattedString)

f = open(output_text_file, 'w+')
for i in fileContents:
    f.write(i + "\n")
f.close()


