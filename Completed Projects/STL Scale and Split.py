
# ----------------------------------------------
# --------                              --------
# --------      Editable Variables      --------
# --------                              --------
# ----------------------------------------------

segment_size = (220, 220, 220)  # Set your desired segment size in (X, Y, Z)
scale_factor = 30  # Scale the model by this factor

















# ----------------------------------------------
# --------                              --------
# --------            Script            --------
# --------                              --------
# ----------------------------------------------

import sys
import subprocess
import os
import numpy as np
from stl import mesh
from tkinter import Tk
from tkinter.filedialog import askopenfilename

# Ensure numpy and numpy-stl are installed
def install_package(package):
    subprocess.check_call([sys.executable, "-m", "pip", "install", package])

try:
    import numpy as np
    from stl import mesh
except ImportError:
    print("Required packages not found. Installing numpy and numpy-stl...")
    install_package("numpy")
    install_package("numpy-stl")
    import numpy as np
    from stl import mesh

def split_stl(input_stl, segment_size, scale_factor=1.0):
    # Load the STL file
    original_mesh = mesh.Mesh.from_file(input_stl)
    
    # Scale the STL if necessary
    if scale_factor != 1.0:
        original_mesh.vectors *= scale_factor
        print(f"Scaled STL by factor {scale_factor}")

    # Calculate model bounds after scaling
    min_bounds = original_mesh.points.min(axis=0).reshape(-1, 3).min(axis=0)
    max_bounds = original_mesh.points.max(axis=0).reshape(-1, 3).max(axis=0)
    print(f"Model Bounds after scaling: min {min_bounds}, max {max_bounds}")

    # Determine segmentation limits based on segment size
    x_segments = np.arange(min_bounds[0], max_bounds[0], segment_size[0])
    y_segments = np.arange(min_bounds[1], max_bounds[1], segment_size[1])
    z_segments = np.arange(min_bounds[2], max_bounds[2], segment_size[2])

    # Generate output folder name based on input STL file name
    base_name = os.path.splitext(os.path.basename(input_stl))[0]
    output_folder = os.path.join(os.path.dirname(input_stl), f"{base_name}_SPLIT_SEGMENTS")
    os.makedirs(output_folder, exist_ok=True)
    print(f"Output directory: {output_folder}")

    # Function to check if a triangle is within a bounding box
    def is_triangle_in_box(triangle, box_min, box_max):
        return np.all(triangle >= box_min, axis=1).all() and np.all(triangle <= box_max, axis=1).all()

    # Split the model into segments
    segment_counter = 0
    for x_min in x_segments:
        for y_min in y_segments:
            for z_min in z_segments:
                box_min = np.array([x_min, y_min, z_min])
                box_max = box_min + segment_size
                box_triangles = []

                # Check each triangle in the mesh
                for triangle in original_mesh.vectors:
                    if is_triangle_in_box(triangle, box_min, box_max):
                        box_triangles.append(triangle)
                
                if box_triangles:
                    # Create a new mesh for the current segment
                    segment_mesh = mesh.Mesh(np.zeros(len(box_triangles), dtype=mesh.Mesh.dtype))
                    segment_mesh.vectors = np.array(box_triangles)
                    
                    # Save the segment as a new STL file
                    segment_filename = os.path.join(output_folder, f"segment_{segment_counter}.stl")
                    segment_mesh.save(segment_filename)
                    print(f"Saved segment {segment_counter} as {segment_filename}")
                    segment_counter += 1

# Prompt user to select the STL file
def select_stl_file():
    Tk().withdraw()  # Hide the root window
    file_path = askopenfilename(title="Select STL File", filetypes=[("STL files", "*.stl")])
    if not file_path:
        print("No file selected.")
        sys.exit()
    return file_path

input_stl = select_stl_file()
split_stl(input_stl, segment_size, scale_factor)
