import time

print('\n\n\n\t\tHello.')
print('\t\tThis program should setup Trig 2')
time.sleep(1)
file = open('Extra_Features.trigfile','a')
file.write('There are no Extras')
file.close
file = open('serial.trigfile','a')
file.write('YGKF7-HALU3-67NF9-NSD7F-34950-code=1234891531864132745944152378541594538')
file.close
print('\t\tFiles have been created')
print('\t\tGood. That completes setup. Have fun!')
time.sleep(1)
quit()
