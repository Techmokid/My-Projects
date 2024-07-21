import tkinter as tk
from tkinter import filedialog, messagebox
from stl import mesh
import os

def get_mesh_dimensions(mesh):
    # Calculate the dimensions of the mesh
    min_coords = mesh.vectors.min(axis=(0, 1))
    max_coords = mesh.vectors.max(axis=(0, 1))
    dimensions = max_coords - min_coords
    return dimensions

def scale_stl_file(filepath, scale_factor=1000):
    # Load the STL file
    original_mesh = mesh.Mesh.from_file(filepath)
    
    # Scale the mesh
    original_mesh.vectors *= scale_factor
    
    # Calculate the new dimensions
    new_dimensions = get_mesh_dimensions(original_mesh)
    
    # Create a new filename
    base, ext = os.path.splitext(filepath)
    new_filename = f"UPSCALED_{os.path.basename(base)}{ext}"
    new_filepath = os.path.join(os.path.dirname(filepath), new_filename)
    
    # Save the new mesh
    original_mesh.save(new_filepath)
    return new_filepath, new_dimensions

def open_file_dialog():
    root = tk.Tk()
    root.withdraw()  # Hide the root window
    file_path = filedialog.askopenfilename(filetypes=[("STL files", "*.stl")])
    if file_path:
        try:
            new_file_path, new_dimensions = scale_stl_file(file_path)
            # Display the new file path and dimensions
            messagebox.showinfo("File Saved", f"File saved as: {new_file_path}\n\nNew dimensions (x, y, z): {new_dimensions}")
        except Exception as e:
            messagebox.showerror("Error", f"An error occurred: {e}")
    else:
        messagebox.showinfo("No File", "No file selected")

if __name__ == "__main__":
    open_file_dialog()
