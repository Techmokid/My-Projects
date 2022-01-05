import os,sys

try:
    import discord
except:
    os.system('start cmd /K python -m pip install discord && pause')
    import discord

try:
    from datetime import datetime
except:
    os.system('start cmd /K python -m pip install datetime && pause')
    from datetime import datetime

try:
    from xlrd import open_workbook
except:
    os.system('start cmd /K python -m pip install xlrd && pause')
    from xlrd import open_workbook

try:
    from xlwt import Workbook
except:
    os.system('start cmd /K python -m pip install xlwt && pause')
    from xlwt import Workbook

try:
    from xlutils.copy import copy
except:
    os.system('start cmd /K python -m pip install xlutils && pause')
    from xlutils.copy import copy

try:
    import time
except:
    os.system('start cmd /K python -m pip install time && pause')
    import time

try:
    import re
except:
    os.system('start cmd /K python -m pip install re && pause')
    import re
