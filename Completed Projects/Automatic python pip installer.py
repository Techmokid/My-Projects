import subprocess,sys,os
import sys

def install_pip():
    pip_script_url = 'https://bootstrap.pypa.io/get-pip.py'

    try:
        # Python 3.x
        from urllib.request import urlretrieve
    except ImportError:
        # Python 2.x
        from urllib import urlretrieve

    # Download the get-pip.py script
    urlretrieve(pip_script_url, 'get-pip.py')
    subprocess.call([sys.executable, 'get-pip.py'])
    os.remove('get-pip.py')

def check_pip():
    try:
        import pip
        print("pip is already installed.")
    except ImportError:
        print("pip not installed, installing now...")
        install_pip()
        print("pip has been installed.")
    finally:
        try:
            import pip
            print("pip is available")
        except ImportError:
            print("Failed to install pip.")

def upgrade_pip():
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", "--upgrade","pip"])
    except subprocess.CalledProcessError:
        print("Error upgrading pip")

    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", "--upgrade","setuptools", "wheel"])
    except subprocess.CalledProcessError:
        print("Error upgrading setuptools")

def install_package(package_name):
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", package_name])
    except subprocess.CalledProcessError as e:
        print(f"Error installing package {package_name}: {e.output}")

def upgrade_package(package_name):
    try:
        subprocess.check_call([sys.executable, "-m", "pip", "install", package_name, "--upgrade"])
    except subprocess.CalledProcessError as e:
        print(f"Error upgrading package {package_name}: {e.output}")

packages = ["requests",         #HTML web page handler
            "keyboard",         #Keyboard reading/control
            "mouse",            #Mouse reading/control
            "selenium",         #Advanced HTML web page handler with JS execution and browser control
            "numpy",            #Maths analysis and arrays support
            "pygame",
            "chime",            #Windows audio engine
            "PySocks",          #Networking sockets handler
            "opencv-python",    #Computer Vision AI library
            "trimesh",          #3D mesh manipulation tool
            "bs4",              #beautifulsoup4, HTML parser
            "pandas",           #Data analysis and manipulation
            "matplotlib",       #Data visualisation library
            "scikit-learn",     #Data anlysis AI tools
            "Flask",            #Web framework for building web applications and APIs
            "Django",           #High level web framework. Auth, ORM, etc
            "torch",            #AI Machine Learning library
            "torchvision",
            "torchaudio",
            "simpleaudio",
            "serial",           #Serial communications
            "pyttsx3",          #TTS engine
            "playsound",        #Sound engine
            "pyaudio",           #Audio engine
            "gtts",
            "openai",
            "Pillow",
            "moviepy"
            ]

print("Checking pip")
check_pip()
print("Upgrading pip")
upgrade_pip()
print()
print()

for i in range(0,len(packages)):
    print("Installing package (" + str(i+1) + "/" + str(len(packages)) + ") " + packages[i])
    install_package(packages[i])
for i in range(0,len(packages)):
    print("Upgrading package (" + str(i+1) + "/" + str(len(packages)) + ") " + packages[i])
    upgrade_package(packages[i])
