from PIL import Image
import numpy as np
import trimesh
import os

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
inputFile = "PCB Etch.bmp"
outputFile = "PCB Etch.stl"
png_to_stl(inputFile, outputFile, thickness, pixel_size)
