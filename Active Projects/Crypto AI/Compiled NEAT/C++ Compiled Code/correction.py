import os

def prepend_line(file_name, line, index):
    """ Insert given string as a new line at the beginning of a file """
    # define name of temporary dummy file
    dummy_file = file_name + '.bak'
    # open original file in read mode and dummy file in write mode
    with open(file_name, 'r') as read_obj, open(dummy_file, 'w') as write_obj:
        # Read lines from original file one by one and append them to the dummy file
        x = 0
        for line2 in read_obj:
            if (x == index):
                write_obj.write(line)
            write_obj.write(line2)
    # remove original file
    os.remove(file_name)
    # Rename dummy file as the original file
    os.rename(dummy_file, file_name)

prepend_line("Program.cpp","using namespace std;\n\n",0)
