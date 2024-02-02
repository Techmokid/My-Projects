import subprocess
import sys

def upgrade_pip():
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", "--upgrade","pip"])
    except subprocess.CalledProcessError:
        print("Error installing package")

def install_package(package_name):
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", package_name])
    except subprocess.CalledProcessError:
        print("Error installing package")
    
packages = ["requests",         #HTML web page handler
            "keyboard",         #Keyboard reading/control
            "mouse",            #Mouse reading/control
            "selenium",         #Advanced HTML web page handler with JS execution and browser control
            "numpy",            #Maths analysis and arrays support
            "pygame",
            "chime",            #Windows audio engine
            "PySocks",          #Part of pygame
            "opencv-python",    #Computer Vision AI library
            "trimesh",          #3D mesh manipulation tool
            "bs4",              #beautifulsoup4, HTML parser
            "pandas",           #Data analysis and manipulation
            "matplotlib",       #Data visualisation library
            "scikit-learn",     #Data anlysis AI tools
            "Flask",            #Web framework for building web applications and APIs
            "Django",           #High level web framework. Auth, ORM, etc
            "torch"             #AI Machine Learning library
            ]

print("Upgrading pip")
upgrade_pip()
for i in range(0,len(packages)):
    print("Installing package (" + str(i+1) + "/" + str(len(packages)) + ") " + packages[i])
    install_package(packages[i])
