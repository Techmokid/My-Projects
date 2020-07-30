import random
random.seed(152)

puzzle = [["3"," "," ",  " "," "," ",    " "," "," "],
          ["6","5"," ",  " ","1"," ",    " ","7"," "],
          [" "," ","4",  "2"," ","7",    "5"," "," "],
           
          [" "," "," ",  "9"," "," ",    " "," "," "],
          [" "," "," ",  "7"," "," ",    " "," ","9"],
          [" ","9"," ",  " ","6","3",    " ","4","2"],
           
          ["1","7","5",  " ","3"," ",    " ","6","4"],
          [" ","4"," ",  " "," "," ",    " "," ","5"],
          [" "," ","8",  " "," "," ",    " "," "," "]
          ]

puzzleOrig = puzzle

def isValid():
    #This just scans the puzzle to see if it is valid or not by scanning for double ups of numbers in rows or columns
    y = 0
    while (y < 9):
        detectedNumbers = []
        x = 0
        while(x < 9):
            if (puzzle[y][x] != " "):
                if (puzzle[y][x] in str(detectedNumbers)):
                    return False
                detectedNumbers.append(puzzle[y][x])
            x += 1
        y += 1
     
    y = 0
    while (y < 9):
        detectedNumbers = []
        x = 0
        while(x < 9):
            if (puzzle[x][y] != " "):
                if (puzzle[x][y] in str(detectedNumbers)):
                    return False
                detectedNumbers.append(puzzle[x][y])
            x += 1
        y += 1
     
    return True
 
def getAllConflictingSquares(x_start,y_start):
    result = []
     
    #Get all conflicting horizontal lines
    x = 0
    while(x < 9):
        if (puzzle[y_start][x] != " "):
            result.append(puzzle[y_start][x])
        x += 1
    
    #Get all conflicting vertical lines
    y = 0
    while(y < 9):
        if (puzzle[y][x_start] != " "):
            result.append(puzzle[y][x_start])
        y += 1
    
    sq1 = [*puzzle[0][:3],*puzzle[1][:3],*puzzle[2][:3]]
    sq2 = [*puzzle[0][3:6],*puzzle[1][3:6],*puzzle[2][3:6]]
    sq3 = [*puzzle[0][6:9],*puzzle[1][6:9],*puzzle[2][6:9]]
    
    sq4 = [*puzzle[3][:3],*puzzle[4][:3],*puzzle[5][:3]]
    sq5 = [*puzzle[3][3:6],*puzzle[4][3:6],*puzzle[5][3:6]]
    sq6 = [*puzzle[3][6:9],*puzzle[4][6:9],*puzzle[5][6:9]]
    
    sq7 = [*puzzle[6][:3],*puzzle[7][:3],*puzzle[8][:3]]
    sq8 = [*puzzle[6][3:6],*puzzle[7][3:6],*puzzle[8][3:6]]
    sq9 = [*puzzle[6][6:9],*puzzle[7][6:9],*puzzle[8][6:9]]
    
    #Here all we need to do is figure out which square the cell is in, then append "result" with the contents of that square
    square = []
    if ((0 <= x_start <= 2) and (0 <= y_start <= 2)):
        square = sq1
    elif ((3 <= x_start <= 5) and (0 <= y_start <= 2)):
        square = sq2
    elif ((6 <= x_start <= 8) and (0 <= y_start <= 2)):
        square = sq3
    elif ((0 <= x_start <= 2) and (3 <= y_start <= 5)):
        square = sq4
    elif ((3 <= x_start <= 5) and (3 <= y_start <= 5)):
        square = sq5
    elif ((6 <= x_start <= 8) and (3 <= y_start <= 5)):
        square = sq6
    elif ((0 <= x_start <= 2) and (6 <= y_start <= 8)):
        square = sq7
    elif ((3 <= x_start <= 5) and (6 <= y_start <= 8)):
        square = sq8
    elif ((6 <= x_start <= 8) and (6 <= y_start <= 8)):
        square = sq9
    
    for i in square:
        if (i != " "):
            result.append(i)
    
    result.sort()
    return list(dict.fromkeys(result))
 
if (isValid() == False):
    print("ERROR: NOT A VALID PUZZLE!")
    quit()

def solve():
    #We know we have a valid file. Now actually start solving it!
    x_question = 0
    y_question = 0
    while (y_question < 9):
        while(x_question < 9):
            if (puzzle[y_question][x_question] == " "):
                conflict = getAllConflictingSquares(x_question,y_question)
                possibleSolutions = list({'1','2','3','4','5','6','7','8','9'} - set(conflict))
                 
                #if (len(possibleSolutions) == 0):
                    #print("No possible solutions error!")
                    #quit()
                #el
                if (len(possibleSolutions) == 1):
                    puzzle[y_question][x_question] = str(possibleSolutions[0])
                     
                    x_question = -1 #We want x_question to be equal to 0. SO, we set it to -1 so that on the next loop around it adds 1 and sets it to 0.
                    y_question = 0
            x_question += 1
        x_question = 0
        y_question += 1

def attemptPuzzleFix():
    #for i in puzzle:
    #    print(i)
    
    puzzleIsComplete = True
    for i in puzzle:
        for x in i:
            if (x == " "):
                puzzleIsComplete = False
    
    numConflicts = 10
    x_pos = 0
    y_pos = 0
    if (puzzleIsComplete == False):
        y_loops = 0
        for i in puzzle:
            x_loops = 0
            for x in i:
                if (puzzle[y_loops][x_loops] == " "):
                    temp = len(getAllConflictingSquares(x_pos,y_pos))
                    if (temp < numConflicts):
                        numConflicts = temp
                        x_pos = x_loops
                        y_pos = y_loops
                x_loops += 1
            y_loops += 1
        
        conflict = getAllConflictingSquares(x_pos,y_pos)
        possibleSolutions = list({'1','2','3','4','5','6','7','8','9'} - set(conflict))
        
        if (len(possibleSolutions) != 0):
            temp = random.choice(possibleSolutions)
            puzzle[y_pos][x_pos] = temp
            solve()
        else:
            print("No solutions, trying again\t\tX: " + str(x_pos) + "\t\tY: " + str(y_pos))

def puzzleSolved():
    for y in puzzle:
        for x in y:
            if (x == " "):
                return False
    return True

while True:
    solve()
    attemptPuzzleFix()
    if (puzzleSolved()):
        break
    puzzle = puzzleOrig

print("Puzzle Complete!")

#Contents of "puzzle" contains the solution
x = 0
y = 0
print()
for i in puzzle:
    if ((x % 3 == 0) and (x > 0)):
        print("-------------------------------")
    x += 1
    result = ""
    for z in i:
        if ((y % 3 == 0) and (y > 0)):
            result += "|  "
        result += z + "  "
        y += 1
    print(result)
    y = 0
