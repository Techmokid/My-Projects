import win32con,winreg

result = []

def foo(hive, flag):
    global result
    
    aReg = winreg.ConnectRegistry(None, hive)
    aKey = winreg.OpenKey(aReg, r"SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall", 
                          0, win32con.KEY_READ | flag)

    count_subkey = winreg.QueryInfoKey(aKey)[0]
    for i in range(count_subkey):
        try:
            asubkey_name = winreg.EnumKey(aKey, i)
            asubkey = winreg.OpenKey(aKey, asubkey_name)
            val = winreg.QueryValueEx(asubkey, "DisplayName")[0]
            result += [val]
        except EnvironmentError:
            continue

def LocatePrograms():
    foo(win32con.HKEY_LOCAL_MACHINE, win32con.KEY_WOW64_32KEY)
    foo(win32con.HKEY_LOCAL_MACHINE, win32con.KEY_WOW64_64KEY)
    foo(win32con.HKEY_CURRENT_USER, 0)

LocatePrograms()
result.sort()

f = open("result.txt",'w')
sentence = ""

for i in result:
    sentence += i + "\n"

print("Writing to file")
f.write(sentence)
f.close()
print("File write complete")
