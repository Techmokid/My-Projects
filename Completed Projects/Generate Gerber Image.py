import os
import tkinter as tk
from tkinter import filedialog
from gerber import load_layer
from gerber.render import RenderSettings, theme
from gerber.render.cairo_backend import GerberCairoContext
from PIL import Image

# Disable Pillows decompression attack safety feature
# For some reason these images show up as something insane like a 630MP image
# I have absolutely no clue why, but this fixes it anyways
Image.MAX_IMAGE_PIXELS = None 

# Function to open the folder selection dialog
def select_folder():
    root = tk.Tk()
    root.withdraw()  # Hide the root window
    folder_path = filedialog.askdirectory(title="Select the folder containing Gerber files")
    return folder_path

# Ask the user to select the folder containing the Gerber files
GERBER_FOLDER = select_folder()

# Check if a folder was selected
if not GERBER_FOLDER:
    print("No folder selected, exiting...")
    exit()

# Define file paths for the Gerber layers (adjust these names if needed)
copper_bottom_file  = os.path.join(GERBER_FOLDER, 'GerberFiles', 'copper_bottom.gbr')
silk_top_file       = os.path.join(GERBER_FOLDER, 'GerberFiles', 'silkscreen_top.gbr')
drill_file          = os.path.join(GERBER_FOLDER, 'DrillFiles', 'drill_1_16.xln')
profile_file        = os.path.join(GERBER_FOLDER, 'GerberFiles', 'profile.gbr')

render_white = RenderSettings(color=theme.COLORS['white'])
render_black = RenderSettings(color=theme.COLORS['black'])

copper_bottom = load_layer(copper_bottom_file)
silk_top = load_layer(silk_top_file)
drill = load_layer(drill_file)
profile = load_layer(profile_file)


# Draw and save image to disk for top
print("Generating top layer data")
ctx = GerberCairoContext()
ctx.render_layer(profile,  settings=RenderSettings(color=theme.COLORS['red'],alpha=0.0))
ctx.render_layer(silk_top, settings=RenderSettings(color=theme.COLORS['white']))
ctx.render_layer(drill,    settings=RenderSettings(color=theme.COLORS['black']))
print("Saving top layer image")
ctx.dump(os.path.join(GERBER_FOLDER, 'PCB Top View.png'))



# Generate the raw bottom image. This will be manipulated later
print("Generating bottom layer data")
ctx = GerberCairoContext()
ctx.render_layer(profile, settings=RenderSettings(color=theme.COLORS['red'],alpha=0.0))
ctx.render_layer(copper_bottom)
ctx.render_layer(drill, settings=render_white)
ctx.dump(os.path.join(GERBER_FOLDER, 'PCB Raw Bottom.png'))



# Clone the raw bottom image and make it pretty by turning black traces into a nice copper color
print("Generating bottom layer images")
image_path = os.path.join(GERBER_FOLDER, 'PCB Raw Bottom.png')
img = Image.open(image_path)
copper_color = (184, 115, 51)
img = img.convert('RGB')

pixels = img.load()
for i in range(img.width):
    for j in range(img.height):
        if pixels[i, j] == (0, 0, 0):  # pure black
            pixels[i, j] = copper_color

img.save(os.path.join(GERBER_FOLDER, 'PCB Bottom View.png'))
print("Saved PCB bottom view")



# Clone the raw bottom image and create an etching mask with it by turning the weird default PCB green into white
img = Image.open(image_path)
pixels = img.load()
for i in range(img.width):
    for j in range(img.height):
        if pixels[i, j] != (0, 0, 0):  # pure black
            pixels[i, j] = (255, 255, 255)

img.save(os.path.join(GERBER_FOLDER, 'PCB Etch.png'))
print("Saved PCB etch")




print("Drilling Bounds:   " + str(drill.bounds))
print("Copper Bounds:     " + str(copper_bottom.bounds))
print("Silkscreen Bounds: " + str(silk_top.bounds))
print("Gerber layers rendered successfully!")
































