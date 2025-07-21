import argparse
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

def main():
    parser = argparse.ArgumentParser(description="Convert a BMP/PNG image to an STL file.")
    parser.add_argument("input_file", help="Input image file (BMP or PNG)")
    parser.add_argument("-o", "--output", help="Output STL file name (optional)", default="output.stl")
    parser.add_argument("-thickness", type=float, default=1.0, help="Thickness of the extrusion in mm")
    parser.add_argument("-pixelsize", type=float, default=0.1, help="Pixel size in mm")

    args = parser.parse_args()

    input_file = args.input_file
    output_file = args.output
    thickness = args.thickness
    pixel_size = args.pixelsize

    if output_file is None:
        base, _ = os.path.splitext(input_file)
        output_file = base + ".stl"
    else:
        if not output_file.lower().endswith(".stl"):
            output_file += ".stl"


    png_to_stl(input_file, output_file, thickness, pixel_size)

if __name__ == "__main__":
    main()
