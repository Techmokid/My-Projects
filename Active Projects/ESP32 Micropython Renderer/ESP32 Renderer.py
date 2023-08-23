import math,exampleShapes

shapes = []
def createLineDefinition(point1,point2,dotsBudget):
    x1 = point1[0]
    y1 = point1[1]
    x2 = point2[0]
    y2 = point2[1]
    
    result = []
    for i in range(0,dotsBudget):
        perc = i/(dotsBudget-1)
        x = x1+(x2-x1)*perc
        y = y1+(y2-y1)*perc
        result.append([x,y])
    return result

def getLength(point1,point2):
    return math.sqrt(math.pow(point1[0]-point2[0],2) + math.pow(point1[1]-point2[1],2))

def createShape(points,dotsBudget):
    lines = []
    result = []
    perimeter = 0
    
    #Here we want to scan the shape for its total perimeter
    #That way we can designate a particular amount of points to each line segment equally across the shape
    for i in range(0,len(points)-1):
        perimeter += getLength(points[i],points[i+1])

    #Now that we have the perimeter, we can scan each line to get the percentage of our dots budget it can get and create it's line segment
    dotsUsedTotal = 0
    for i in range(1,len(points)):
        dotsAllowed = math.floor(dotsBudget * (getLength(points[i],points[i-1])/perimeter))
        dotsUsedTotal += dotsAllowed
        
        result.append(createLineDefinition(points[i-1],points[i],dotsAllowed))
    dotCorrector = []
    for i in range(0,dotsBudget - dotsUsedTotal):
        lastLine = result[len(result)-1]
        lastPoint = lastLine[len(lastLine)-1]
        dotCorrector.append(lastPoint)
    result.append(dotCorrector)
    return result





# Now, we can call the function createShape with circle_points
shapes.append(createShape(exampleShapes.circle_points, 200))
#-----------------------------------------------------------------------------------------------





import matplotlib.pyplot as plt

def convertShapeToXYArray():
    global shapes
    shape = shapes[0]
    
    X_Arr = []
    Y_Arr = []
    for line in shape:
        for point in line:
            X_Arr.append(point[0])
            Y_Arr.append(point[1])
    return [X_Arr,Y_Arr]

shapeArray = convertShapeToXYArray()
X_Array = shapeArray[0]
Y_Array = shapeArray[1]

plt.figure(figsize=(5,5)) # Creates a new figure with specific size (optional)
plt.scatter(X_Array, Y_Array) # Plots the points
plt.plot(X_Array, Y_Array) # Connects the points with lines
plt.xlim(0, 1) # Sets the limits of x-axis (optional)
plt.ylim(0, 1) # Sets the limits of y-axis (optional)
plt.gca().set_aspect('equal', adjustable='box') # Equal aspect ratio ensures that the scale on the x-axis is same as the y-axis.
plt.show() # Displays the figure
