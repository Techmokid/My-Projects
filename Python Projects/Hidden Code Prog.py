#This Programs Design Is To Make A Readable File That You Can't
#Access Unless You Have This Program

def menu():
    wr = False
    print('Do You Want A File (W)ritten To Or (R)ead From?')
    choice = input('Type (q) To Quit or (a) for About\t')
    if (choice == 'w'):
        wr = True
    elif (choice == 'W'):
        wr = True
    elif (choice == 'r'):
        wr = False
    elif (choice == 'R'):
        wr = False
    elif (choice == 'q'):
        raise SystemExit
    elif (choice == 'Q'):
        raise SystemExit
    elif (choice == 'a'):
        about()
    elif (choice == 'A'):
        about()
    else:
        print('That Was NOT An Option')
        time.sleep(2)
        menu()
    if (wr == True):
        write()
    else:
        read()

def read():
    print('\nMake Sure that the File You Want Read')
    print('is in this programs Main Directory\n')
    filename = input('What is the File Name (with the File Extention)?\t\t')
    try:
        file = open(filename,'r')
        print('File Open Complete. Reading...\n\n\n')
        var = file.read()
        print(var)
        unused_var = input('\n\n\n\nFile Reading Complete. Press enter to continue')
        menu()

    except (IOError):
        print('\nFile Open/Read Error. Cannot Continue In Script')
        unused_var = input('Press enter to return to the menu')
        menu()

def write():
    full = ''
    filename = input('Type Your File Name Without the Extention\t')
    fileextention = input('Type Your File Extention. Remember to add the Full Stop\t')
    filename = filename+fileextention
    print('You Can Now Write What You Want.\n')
    print('Type On A New Line "File Complete" to Finish and Save\n\n')
    userWrite(full,filename)

def userWrite(full,filename):
    sentence = input()
    print(sentence,'\n')
    if (sentence != 'File Complete'):
        full = full + '\n' + sentence
        userWrite(full,filename)
    str(full)
    print('Your File Says:\n\n',full,'\n\n')
    
    with open(filename,'w') as f:
        f.write(full)
    menu()

def about():
    print('\n\nThis Program is Designed for Making and Decoding Secret Messages')
    print('It is also Used for Reading Corrupted Files and Locating Errors')
    print('To Fix an Error, First Copy The Original Code After Opening')
    print('Then, Make the Modifications to the Code, Copy it, Open up the File Using')
    print('This Program, and Paste it in. No Problem')
    unused_var = input('\nPress enter to continue\n\n')
    menu()

menu()
