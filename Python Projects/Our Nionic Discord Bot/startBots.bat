Taskkill /IM python.exe /F
Taskkill /IM pythonw.exe /F
start /min cmd /c python "getRequiredLibraries.py"
pause
start /min cmd /c python "Nionic Data Collection.py"
start /min cmd /c python "Swear Monitor.py"