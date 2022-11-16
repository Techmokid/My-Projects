from subprocess import check_output

x = check_output("dir C:", shell=True).decode("utf-8")
print(x)
print()
for i in x.split("\r\n"):
    print(i)
