import os
def sendMessage(phoneNumber,body):
    command = "curl \"https://api.twilio.com/2010-04-01/Accounts/AC715653ed2adcaf4ca653470fb3ce7740/Messages.json\" -X POST --data-urlencode \"To=" + phoneNumber + "\" --data-urlencode \"From=+61488844045\" "
    command += "--data-urlencode \"Body=" + body + "\" -u AC715653ed2adcaf4ca653470fb3ce7740:510996988097dd33867c3d3f38454117"
    print(command)
    os.system("cmd /k \"" + command + "\"")
sendMessage("+61498580292","Hello From Python!")
