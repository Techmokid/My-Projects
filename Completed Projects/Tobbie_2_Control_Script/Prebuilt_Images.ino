void displayHeart() {
  int temp[][5] = {
    {0,1,0,1,0},
    {1,1,1,1,1},
    {1,1,1,1,1},
    {0,1,1,1,0},
    {0,0,1,0,0}
  };
  
  setDisplay(temp);
}

void displayBoxRings() {
  int temp[][5] = {
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,1,0,1},
    {1,0,0,0,1},
    {1,1,1,1,1}
  };
  
  setDisplay(temp);
}

void displayBoxRingsReverse() {
  int temp[][5] = {
    {0,0,0,0,0},
    {0,1,1,1,0},
    {0,1,0,1,0},
    {0,1,1,1,0},
    {0,0,0,0,0}
  };
  
  setDisplay(temp);
}

void displayChessboard() {
  int temp[][5] = {
    {1,0,1,0,1},
    {0,1,0,1,0},
    {1,0,1,0,1},
    {0,1,0,1,0},
    {1,0,1,0,1}
  };
  
  setDisplay(temp);
}

void displayChessboardReverse() {
  int temp[][5] = {
    {0,1,0,1,0},
    {1,0,1,0,1},
    {0,1,0,1,0},
    {1,0,1,0,1},
    {0,1,0,1,0}
  };
  
  setDisplay(temp);
}

void displayFaceHappy() {
  int temp[][5] = {
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,0,0,0,0},
    {1,0,0,0,1},
    {0,1,1,1,0}
  };
  
  setDisplay(temp);
}

void displayFaceNormal() {
  int temp[][5] = {
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,0,0,0,0},
    {0,1,1,1,0},
    {0,0,0,0,0}
  };
  
  setDisplay(temp);
}

void displayFaceSad() {
  int temp[][5] = {
    {0,1,0,1,0},
    {1,0,0,0,1},
    {0,0,0,0,0},
    {0,1,1,1,0},
    {1,0,0,0,1}
  };
  
  setDisplay(temp);
}

void displayFaceUnhappy() {
  int temp[][5] = {
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,0,0,0,0},
    {0,1,1,1,0},
    {1,0,0,0,1}
  };
  
  setDisplay(temp);
}

void displayFaceEvil() {
  int temp[][5] = {
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,0,0,0},
    {1,0,0,0,1},
    {0,1,1,1,0}
  };
  
  setDisplay(temp);
}

void displayFaceAngry() {
  int temp[][5] = {
    {1,0,0,0,1},
    {0,1,0,1,0},
    {0,0,0,0,0},
    {0,1,1,1,0},
    {1,0,0,0,1}
  };
  
  setDisplay(temp);
}

void displayFaceEcstatic() {
  int temp[][5] = {
    {0,1,0,1,0},
    {0,1,0,1,0},
    {0,0,0,0,0},
    {1,1,1,1,1},
    {0,1,1,1,0}
  };
  
  setDisplay(temp);
}

void displayRoadHor() {
  int temp[][5] = {
    {1,0,1,0,1},
    {1,0,0,0,1},
    {1,0,1,0,1},
    {1,0,0,0,1},
    {1,0,1,0,1}
  };
  
  setDisplay(temp);
}

void displayRoadVer() {
  int temp[][5] = {
    {1,1,1,1,1},
    {0,0,0,0,0},
    {1,0,1,0,1},
    {0,0,0,0,0},
    {1,1,1,1,1}
  };
  
  setDisplay(temp);
}

void displayArrowUp() {
  int temp[][5] = {
    {0,0,1,0,0},
    {0,1,1,1,0},
    {1,0,1,0,1},
    {0,0,1,0,0},
    {0,0,1,0,0}
  };
  
  setDisplay(temp);
}
void displayArrowUpRight() {
  int temp[][5] = {
    {0,1,1,1,1},
    {0,0,0,1,1},
    {0,0,1,0,1},
    {0,1,0,0,1},
    {1,0,0,0,0}
  };
  
  setDisplay(temp);
}
void displayArrowRight() {
  int temp[][5] = {
    {0,0,1,0,0},
    {0,0,0,1,0},
    {1,1,1,1,1},
    {0,0,0,1,0},
    {0,0,1,0,0}
  };
  
  setDisplay(temp);
}
void displayArrowDownRight() {
  int temp[][5] = {
    {1,0,0,0,0},
    {0,1,0,0,1},
    {0,0,1,0,1},
    {0,0,0,1,1},
    {0,1,1,1,1}
  };
  
  setDisplay(temp);
}
void displayArrowDown() {
  int temp[][5] = {
    {0,0,1,0,0},
    {0,0,1,0,0},
    {1,0,1,0,1},
    {0,1,1,1,0},
    {0,0,1,0,0}
  };
  
  setDisplay(temp);
}
void displayArrowDownLeft() {
  int temp[][5] = {
    {0,0,0,0,1},
    {1,0,0,1,0},
    {1,0,1,0,0},
    {1,1,0,0,0},
    {1,1,1,1,0}
  };
  
  setDisplay(temp);
}
void displayArrowLeft() {
  int temp[][5] = {
    {0,0,1,0,0},
    {0,1,0,0,0},
    {1,1,1,1,1},
    {0,1,0,0,0},
    {0,0,1,0,0}
  };
  
  setDisplay(temp);
}
void displayArrowUpLeft() {
  int temp[][5] = {
    {1,1,1,1,0},
    {1,1,0,0,0},
    {1,0,1,0,0},
    {1,0,0,1,0},
    {0,0,0,0,1}
  };
  
  setDisplay(temp);
}
