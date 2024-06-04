from PIL import Image
import colorsys

def get_average_rgb(image_path):
    # Open the image file
    with Image.open(image_path) as img:
        # Convert the image into RGB
        img = img.convert('RGB')
        
        # Initialize sum variables for RGB
        r_total = 0
        g_total = 0
        b_total = 0
        
        # Total number of pixels
        count = 0
        
        # Iterate over each pixel in the image
        for x in range(img.width):
            for y in range(img.height):
                r, g, b = img.getpixel((x, y))
                r_total += r
                g_total += g
                b_total += b
                count += 1
        
        # Calculate average RGB values
        r_avg = r_total / count
        g_avg = g_total / count
        b_avg = b_total / count
        
        return (r_avg, g_avg, b_avg)

def rgb_to_hsb(r, g, b):
    # Normalize RGB values to range 0-1
    r_norm = r / 255.0
    g_norm = g / 255.0
    b_norm = b / 255.0
    
    # Convert RGB to HSB
    h, s, v = colorsys.rgb_to_hsv(r_norm, g_norm, b_norm)
    
    # Convert hue to degrees, saturation and brightness to percentage
    h_deg = h * 360
    s_perc = s * 100
    v_perc = v * 100
    
    return (h_deg, s_perc, v_perc)

# Usage example
image_path = r'C:\Users\Techmo\Desktop\petty.gif'
average_rgb = get_average_rgb(image_path)
average_hsb = rgb_to_hsb(*average_rgb)

print("Average RGB:", average_rgb)
print("Average HSB:", average_hsb)
