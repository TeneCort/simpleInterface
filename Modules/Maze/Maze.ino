int matrix[11][11]; // 2D matrix that contains the states of each position (player, empty, wall)
int maxWidth = 10; // values of the visible spots width
int maxHeight = 10; // values of the visible spots height
int cWidth = 0; // current width position in matrix
int cHeight = 0; // current height position in matrix
bool newData = false;
char receivedChar;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  initMaze();
  chooseWalls();
  printMaze();
}

void loop()
{
  recvOneChar();
  showNewData();
  checkWin();
}

// Sends a "win" message, to be changed later in a function that passes the win state 
// to the master controller
void checkWin()
{
  if(cHeight == 6 && cWidth == 8)
  {
    Serial.println("Win");
    // WE SHOULD EMMIT A STRIKE
  }
}

void showNewData()
{
  if (newData == true)
  {
    // Movement & update function are here so that they get blocked after reading input
    movementInput(receivedChar);
    printMaze();
    newData = false;
  }
}

void recvOneChar()
{
  if (Serial.available() > 0)
  {
    receivedChar = Serial.read();
    newData = true;
  }
}

// This will change when the hardware will be installed
void printMaze()
{
  debug();
  for (int i = 0; i <= maxWidth; i++)
  {
    for (int j = 0; j <= maxHeight; j++)
    {
      if (j == 0 || j % 2 == 0 )
      {
        if (i == 0 || i % 2 == 0)
        {
          if (j == maxHeight)
          {
            Serial.println(matrix[i][j]);
          }
          else
          {
            Serial.print(matrix[i][j]);
          }
        }
      }
    }
  }
}

// Sets the default values in the matrix and instanciates the starting position
void initMaze()
{
  for (int i = 0; i <= maxWidth; i++)
  {
    for (int j = 0; j <= maxHeight; j++)
    {
      matrix[i][j] = 0;
    }
  }
  matrix[cHeight][cWidth] = 1;
}

// Returns true if we move to an non occupied space
bool checkPath(int height, int width)
{
  if (matrix[height][width] == 0)
  {
    return true;
  }
  // We should probably remove that later
  else if (matrix[height][width] == 3)
  {
    return true;
  }
  else
  {
    Serial.println("LOOSER");
    return false;
    // WE SHOULD EMMIT A STRIKE
  }
}

// Sets the old position to it's initial value (0) after a move has been completed
void updateMaze(int oldH, int oldW, int newH, int newW)
{
  matrix[oldH][oldW] = 0;
  matrix[newH][newW] = 1;
}

// Sets the position to default, can be used at start of a round or when we hit a wall
void resetPosition()
{
  cHeight = 0;
  cWidth = 0;
}

// Using the keyboard, we can move around the maze
// Movement works as following: first we move 1 step, then we check if we are on a wall
// As long as we are not on a wall, the position move once more with the same vector/direction
void movementInput(char moveKey)
{
  // We set current position in variables so we know what to reset once we have moved
  int oH = cHeight;
  int oW = cWidth;

  if (moveKey == 'A')
  {
    if (cWidth > 0)
    {
      cWidth -= 1;
      if (checkPath(cHeight, cWidth))
      {
        cWidth -= 1;
      }
      else
      {
        resetPosition();
      }
    }
    else
    {
      cWidth = 0;
    }
  }
  if (moveKey == 'R')
  {
    if (cWidth < 10)
    {
      cWidth += 1;
      if (checkPath(cHeight, cWidth))
      {
        cWidth += 1;
      }
      else
      {
        resetPosition();
      }
    }
    else
    {
      cWidth = 10;
    }
  }
  if (moveKey == 'Z')
  {
    if (cHeight > 0)
    {
      cHeight -= 1;
      if (checkPath(cHeight, cWidth))
      {
        cHeight -= 1;
      }
      else
      {
        resetPosition();
      }
    }
    else
    {
      cHeight = 0;
    }
  }
  if (moveKey == 'E')
  {
    if (cHeight < 10)
    {
      cHeight += 1;
      if (checkPath(cHeight, cWidth))
      {
        cHeight += 1;
      }
      else
      {
        resetPosition();
      }
    }
    else
    {
      cHeight = 10;
    }
  }
  updateMaze(oH, oW, cHeight, cWidth);
}

// Maybe rework this, as in displaying the indicators when the player is located at the starting position?
void wallsIndicators(int option)
{
  if(option == 1)
  {
    matrix[2][0] = 3;
    matrix[4][10] = 3;
  }
  else if(option == 2)
  {
    matrix[2][8] = 3;
    matrix[6][2] = 3;
  }
}

// Uses the random seed to initalise a preset of walls
void chooseWalls()
{
  int i = random(1, 3);
  if(i == 1)
  {
    populateWallsOne();
  }
  else if(i == 2)
  {
    populateWallsTwo();
  }
}

// Ugly hardcoded motherfukers
void populateWallsOne()
{
  wallsIndicators(1);
  matrix[0][5] = 2;

  for (int i = 1; i < 11; i++)
  {
    if ( i != 4)
    {
      if (i != 6)
      {
        matrix[1][i] = 2;
      }
    }
  }

  matrix[2][1] = 2;
  matrix[2][5] = 2;

  for (int i = 1; i < 10; i++)
  {
    if (i != 2)
    {
      matrix[3][i] = 2;
    }
  }

  matrix[4][1] = 2;
  matrix[4][5] = 2;

  for (int i = 1; i < 10; i++)
  {
    if (i != 4)
    {
      if (i != 6)
      {
        matrix[5][i] = 2;
        matrix[9][i] = 2;
      }
    }
  }

  matrix[6][1] = 2;
  matrix[6][7] = 2;

  for (int i = 1; i < 10; i++)
  {
    matrix[7][i] = 2;
  }

  matrix[8][5] = 2;
  matrix[8][9] = 2;

  matrix[10][3] = 2;
  matrix[10][7] = 2;
}

// Ugly hardcoded motherfukers
void populateWallsTwo()
{
  wallsIndicators(2);
  
  matrix[0][5] = 2;

  for (int i = 0; i < 11; i++)
  {
    if (i != 2)
    {
      if (i != 6)
      {
        if (i != 8)
        {
          matrix[1][i] = 2;
        }
      }
    }
  }

  matrix[2][3] = 2;
  matrix[2][7] = 2;

  for (int i = 1; i < 10; i++)
  {
    if (i != 4)
    {
      matrix[3][i] = 2;
    }
  }

  matrix[4][1] = 2;
  matrix[4][5] = 2;

  for (int i = 1; i < 10; i++)
  {
    if (i != 2)
    {
      if (i != 6)
      {
        matrix[5][i] = 2;
      }
    }
  }

  matrix[6][3] = 2;
  matrix[6][7] = 2;
  matrix[6][9] = 2;

  for (int i = 1; i < 10; i++)
  {
    if (i != 4)
    {
      if (i != 8)
      {
        matrix[7][i] = 2;
      }
    }
  }

  matrix[8][1] = 2;
  matrix[8][3] = 2;
  matrix[8][5] = 2;
  matrix[8][9] = 2;

  for (int i = 1; i < 10; i++)
  {
    if (i != 2)
    {
      if (i != 4)
      {
        if (i != 6)
        {
          matrix[9][i] = 2;
        }
      }
    }
  }

  matrix[10][1] = 2;
  matrix[10][5] = 2;
}

// Helps visualising in the serial monitor
void debug()
{
  Serial.println("--------------------------------------------");
}

