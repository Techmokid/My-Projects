import math

square = [
    [0,0],
    [0,1],
    [1,1],
    [1,0],
    [0,0]
]

rocket_points = [
    [0.5, 1.0],  # Tip of the rocket
    [0.3, 0.7], # Upper left corner of the body
    [0.3, 0.3], # Lower left corner of the body
    [0.2, 0.3], # Left booster top
    [0.4, 0.0], # Left booster bottom
    [0.5, 0.2], # Middle of the bottom
    [0.6, 0.0], # Right booster bottom
    [0.8, 0.3], # Right booster top
    [0.7, 0.3], # Lower right corner of the body
    [0.7, 0.7], # Upper right corner of the body
    [0.5, 1.0]  # Back to the tip of the rocket to complete the shape
]

nautilus_points = [
    [0.5, 0.5],  # Center point
    [0.7, 0.5],  # First spiral
    [0.65, 0.65],
    [0.5, 0.7],
    [0.35, 0.65],
    [0.3, 0.5],  # Second spiral
    [0.35, 0.35],
    [0.5, 0.3],
    [0.65, 0.35],
    [0.7, 0.5],  # Close the outer spiral
    [0.6, 0.5],  # Third spiral
    [0.55, 0.55],
    [0.5, 0.6],
    [0.45, 0.55],
    [0.4, 0.5],  # Close the middle spiral
    [0.5, 0.5],  # Close the inner spiral
]

num_points = 50
circle_points = [[0.5 + math.cos(2 * math.pi / num_points * i) * 0.5, 
                  0.5 + math.sin(2 * math.pi / num_points * i) * 0.5] 
                 for i in range(num_points)]
