import subprocess,time

cmd = ['cat','/dev/ttyS0']
subprocess.Popen(cmd,stdout=subprocess.PIPE).communicate()[0]
time.sleep(1)
output = str(subprocess.Popen(cmd,stdout=subprocess.PIPE).communicate()[0])
print(output)

for i in output.split("\\r\\n"):
    print(i)
