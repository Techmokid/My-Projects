import tkinter as tk
from tkinter import filedialog
import xml.etree.ElementTree as ET
import os

def select_file():
    """Open a file dialog to select an SVG file."""
    root = tk.Tk()
    root.withdraw()  # Hide the main Tkinter window
    file_path = filedialog.askopenfilename(
        title="Select an SVG File",
        filetypes=[("SVG Files", "*.svg")],
    )
    return file_path

def extract_by_color(svg_file, color):
    """Extract all elements with the specified fill color from an SVG file."""
    tree = ET.parse(svg_file)
    root = tree.getroot()
    svg_ns = {"svg": "http://www.w3.org/2000/svg"}

    # List of SVG element types to process
    element_types = ["path", "rect", "circle", "ellipse"]

    extracted_elements = []
    for elem_type in element_types:
        for elem in root.findall(f".//svg:{elem_type}", namespaces=svg_ns):
            style = elem.attrib.get('style', '')
            fill = elem.attrib.get('fill', '')
            if f"fill:{color}" in style or fill == color:  # Match both style and attribute
                extracted_elements.append(elem)

    # Create a new SVG root with the extracted elements
    new_svg = ET.Element(
        "svg",
        attrib={
            **root.attrib,
            "xmlns": "http://www.w3.org/2000/svg"  # Ensure namespace is defined
        }
    )
    for elem in extracted_elements:
        new_svg.append(elem)

    return ET.ElementTree(new_svg)

def save_svg(tree, original_path, suffix):
    """Save the extracted SVG to a new file."""
    base, ext = os.path.splitext(original_path)
    new_file_path = f"{base}_{suffix}.svg"
    tree.write(new_file_path)
    print(f"Saved {suffix} SVG to: {new_file_path}")

# Main script
file_path = select_file()
if not file_path:
    print("No file selected.")
    quit()

print(f"Selected file: {file_path}")

# Extract and save SVG elements by color
black_tree = extract_by_color(file_path, "#000000")  # Black
save_svg(black_tree, file_path, "BLACK_PATHS")

red_tree = extract_by_color(file_path, "#ff0000")  # Red
save_svg(red_tree, file_path, "RED_PATHS")
