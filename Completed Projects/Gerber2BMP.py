import os
import tkinter as tk
from tkinter import filedialog
from gerber import load_layer
from gerber.render import RenderSettings, theme
from gerber.render.cairo_backend import GerberCairoContext
from PIL import Image
import numpy as np
import trimesh

# Disable Pillows decompression attack safety feature
# For some reason these images show up as something insane like a 630MP image
# I have absolutely no clue why, but this fixes it anyways
Image.MAX_IMAGE_PIXELS = None 

# Function to open the folder selection dialog
def select_folder():
    root = tk.Tk()
    root.withdraw()  # Hide the root window
    folder_path = filedialog.askdirectory(
        title="Select the folder containing Gerber files",
        initialdir=r"Z:\Fusion360 CAMJOBs"
    )
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

#(x0, y0), (x1, y1) = copper_bottom.bounds
#real_width_in = abs(x1 - x0)
#real_height_in = abs(y1 - y0)

copper_color = (184, 115, 51)

def downscale_image(path, target_width):
    print("Downscaling: 1/6 - Opening image")
    img = Image.open(path).convert('RGB')
    print("Downscaling: 2/6 - Calculating resize")

    # Calculate target height to preserve aspect ratio
    aspect_ratio = img.height / img.width
    target_height = int(target_width * aspect_ratio)

    # Resize first
    img_resized = img.resize((target_width, target_height), Image.LANCZOS)
    
    # Convert image to numpy array for faster processing
    print("Downscaling: 3/6 - Calculating array compression")
    img_np = np.array(img_resized)

    # Define your allowed colors
    copper_color = (184, 115, 51)
    green_color = (74, 88, 0)
    black = (0, 0, 0)
    white = (255, 255, 255)
    palette = np.array([copper_color, black, white, green_color])

    # Reshape image to a 2D list of pixels
    flat_pixels = img_np.reshape(-1, 3)

    # For each pixel, find closest palette color
    def closest_color(pixel):
        distances = np.linalg.norm(palette - pixel, axis=1)
        return palette[np.argmin(distances)]

    # Apply snapping
    print("Downscaling: 4/6 - Calculating pixel color snapping")
    snapped_pixels = np.array([closest_color(p) for p in flat_pixels], dtype=np.uint8)
    snapped_img = snapped_pixels.reshape(img_np.shape)

    # Convert back to image
    print("Downscaling: 5/6 - Applying pixel snap")
    img_snapped = Image.fromarray(snapped_img, 'RGB')
    print("Downscaling: 6/6 - Saving resulting image to file")
    img_snapped.save(path)
    print(f"Downscaled and color-snapped image saved: {path} ({target_width}x{target_height})")


# Draw and save image to disk for top
print("Generating top layer data")
ctx = GerberCairoContext()
ctx.render_layer(profile,  settings=RenderSettings(color=theme.COLORS['red'],alpha=0.0))
ctx.render_layer(silk_top, settings=RenderSettings(color=theme.COLORS['white']))
ctx.render_layer(drill,    settings=RenderSettings(color=theme.COLORS['black']))
print("Saving top layer image")
filePath = os.path.join(GERBER_FOLDER, 'PCB Top View.bmp')
ctx.dump(filePath)
downscale_image(filePath,2000)




# Generate the raw bottom image. This will be manipulated later
print("Generating bottom layer data")
ctx = GerberCairoContext()
ctx.render_layer(profile, settings=RenderSettings(color=theme.COLORS['red'],alpha=0.0))
ctx.render_layer(copper_bottom)
ctx.render_layer(drill, settings=render_white)
filePath = os.path.join(GERBER_FOLDER, 'PCB Raw Bottom.bmp')
ctx.dump(filePath)
downscale_image(filePath,2000)




# Clone the raw bottom image and make it pretty by turning black traces into a nice copper color
print("Generating bottom layer images")
image_path = os.path.join(GERBER_FOLDER, 'PCB Raw Bottom.bmp')
img = Image.open(image_path)
img = img.convert('RGB')

# Now color and save
pixels = img.load()
for i in range(img.width):
    for j in range(img.height):
        if pixels[i, j] == (0, 0, 0):  # pure black
            pixels[i, j] = copper_color

img.save(os.path.join(GERBER_FOLDER, 'PCB Bottom View.bmp'))
print("Saved PCB bottom view")



# Clone the raw bottom image and create an etching mask with it by turning the weird default PCB green into white
img = Image.open(image_path)
pixels = img.load()
for i in range(img.width):
    for j in range(img.height):
        if pixels[i, j] != (0, 0, 0):  # pure black
            pixels[i, j] = (255, 255, 255)

img.save(os.path.join(GERBER_FOLDER, 'PCB Etch.bmp'))
print("Saved PCB etch")

def png_to_stl(png_path, stl_path, thickness=1.0, pixel_size=0.1):
    # Load image as grayscale
    img = Image.open(png_path).convert('L')
    data = np.array(img)
    
    # Threshold to binary: 0 = empty, 1 = solid
    binary = data < 128
    height, width = binary.shape
    
    thickness_voxels = max(int(thickness / pixel_size), 1)
    voxels = np.repeat(binary[:, :, np.newaxis], thickness_voxels, axis=2)
    
    # Create a mesh from voxel grid
    mesh = trimesh.voxel.ops.matrix_to_marching_cubes(voxels, pitch=pixel_size)
    
    # Save STL
    mesh.export(stl_path)
    print(f"STL saved: {stl_path}")

thickness=1.0
pixel_size=0.1
inputFile = os.path.join(GERBER_FOLDER, "PCB Etch.bmp")
outputFile = os.path.join(GERBER_FOLDER, "PCB Etch.stl")
png_to_stl(inputFile, outputFile, thickness, pixel_size)


print("Drilling Bounds:   " + str(drill.bounds))
print("Copper Bounds:     " + str(copper_bottom.bounds))
print("Silkscreen Bounds: " + str(silk_top.bounds))
print("Gerber layers rendered successfully!")
































