int stage = 1; // keeps tracks of the stage
int screenDisplay = 0; // The number used as screen display, user defines what key to press based on this
int positions[5]; // Array that saves the position of each key pressed during stages
int labels[5]; // Array that saves the label of each key pressed during stages
int buttonLabels[5]; // Array that saves the label of each key at each round
bool newData; // Bool that changes states each time there is user input
char test[] = {'A', 'Z', 'E', 'R'}; // Array wich keys are meant to be pressed
char receivedChar; // Variable that stores the last key pressed

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  Serial.println("---------------");
  getDisplay();
  allocateButtonLabels();
}

void loop()
{
  recvOneChar();
  
  if(stage == 1)
  {
    stageOne(screenDisplay);
  }
  else if(stage == 2)
  {
    stageTwo(screenDisplay);
  }
  else if(stage == 3)
  {
    stageThree(screenDisplay);
  }
  else if(stage == 4)
  {
    stageFour(screenDisplay);
  }
  else if(stage == 5)
  {
    stageFive(screenDisplay);
  }
  showNewData();
}

void recvOneChar()
{
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    newData = true;
  }
}

void showNewData()
{
  if (newData == true) {
    newData = false;
  }
}

// This function generates a random number between, 1 and 4 that serves as the display number.
// Will be displayed on screen.
int getDisplay()
{
  screenDisplay = random(1, 5);
  Serial.println(screenDisplay);
  return screenDisplay;
}

// Called after each successful stage.
// This function sets that round's key position and label in their respective arrays.
// The round is passed as an index.
void redistribute(int roundIndex, int posVal, int labelValIndex)
{
  positions[roundIndex] = posVal;
  labels[roundIndex] = labelValIndex;
  getDisplay();
  allocateButtonLabels();
  stage++;
}

// Called when the user makes a wrong move.
// Sets the stage to 1 and resets the display and key labels
void resetStage()
{
  Serial.println("LOOSER");
  getDisplay();
  allocateButtonLabels();
  stage = 1;
  // WE SHOULD EMMIT A STRIKE
}

// Called when the user completes the 5th stage.
void isWinner()
{
  Serial.println("WINNER");
  // WE SHOULD EMMIT A WIN
}

// Since the key doesn't know directly wich label is assigned to,
// this function correlates the pressed key with it's respective value in the array. 
int positionLabelCorrelation(char pos)
{
  if(pos == 'A')
  {
    return buttonLabels[0];
  }
  else if(pos == 'Z')
  {
    return buttonLabels[1];
  }
  else if(pos == 'E')
  {
    return buttonLabels[2];
  }
  else if(pos == 'R')
  {
    return buttonLabels[3];
  }
}

// Since the key doesn't know directly wich position is assigned to,
// this function correlates the pressed key with it's respective position. 
int charToPosition(char pressedChar)
{
  if(pressedChar == 'A')
  {
    return 1;
  }
  else if(pressedChar == 'Z')
  {
    return 2;
  }
  else if(pressedChar == 'E')
  {
    return 3;
  }
  else if(pressedChar == 'R')
  {
    return 4;
  }
}

bool stageOne(int disp)
{
  if(newData == true && disp == 1)
  {
    if(newData == true && receivedChar == 'Z')
    {
      redistribute(0, 2, positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 2)
  {
    if(receivedChar == 'Z')
    {
      redistribute(0, 2, positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 3)
  {
    if(receivedChar == 'E')
    {
      redistribute(0, 3, positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 4)
  {
    if(receivedChar == 'R')
    {
      redistribute(0, 4, positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
}

bool stageTwo(int disp)
{
  if(newData == true && disp == 1)
  {
    if(receivedChar == findPosition(4))
    {
      redistribute(1, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 2)
  {
    if(receivedChar == test[positions[0] - 1])
    {
      redistribute(1, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 3)
  {
    if(receivedChar == 'A')
    {
      redistribute(1, 3, positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 4)
  {
    if(receivedChar == test[positions[0] - 1])
    {
      redistribute(1, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
}

bool stageThree(int disp)
{
  if(newData == true && disp == 1)
  {
    if(positionLabelCorrelation(receivedChar) == labels[1])
    {
      redistribute(2, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 2)
  {
    if(positionLabelCorrelation(receivedChar) == labels[0])
    {
      redistribute(2, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 3)
  {
    if(receivedChar == 'E')
    {
      redistribute(2, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 4)
  {
    if(receivedChar == findPosition(4))
    {
      redistribute(2, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
}

bool stageFour(int disp)
{
  if(newData == true && disp == 1)
  {
   if(receivedChar == test[positions[0] - 1])
    {
      redistribute(3, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 2)
  {
    if(receivedChar == 'A')
    {
      redistribute(3, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 3)
  {
    if(receivedChar == test[positions[1] - 1])
    {
      redistribute(3, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 4)
  {
    if(receivedChar == test[positions[1] - 1])
    {
      redistribute(3, charToPosition(receivedChar), positionLabelCorrelation(receivedChar));
    }
    else
    {
      resetStage();
    }
  }
}

bool stageFive(int disp)
{
  if(newData == true && disp == 1)
  {
    if(positionLabelCorrelation(receivedChar) == labels[0])
    {
      isWinner();
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 2)
  {
    if(positionLabelCorrelation(receivedChar) == labels[1])
    {
      isWinner();
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 3)
  {
    if(positionLabelCorrelation(receivedChar) == labels[3])
    {
      isWinner();
    }
    else
    {
      resetStage();
    }
  }
  else if(newData == true && disp == 4)
  {
    if(positionLabelCorrelation(receivedChar) == labels[2])
    {
      isWinner();
    }
    else
    {
      resetStage();
    }
  }
}

// Function that takes as argument the wanted label,
// then checks which key is corresponding to it and return that key.
char findPosition(int wantedLabel)
{
  for(int i = 0; i < 4; i++)
  {
    if(buttonLabels[i] == wantedLabel)
    {
      return test[i];
    }
  }
}


// Function that displays the labels on each key
void showLabels()
{
  for(int i = 0; i < 4; i++)
  {
    Serial.print(buttonLabels[i]);
  }
  Serial.println(' ');
}

// Function that sets the number labels randomly from getCandidate()
// then controls if there are any duplicates with the help of hasDuplicate()
void allocateButtonLabels()
{
  int iterator = 0;
  while(iterator < 4)
  {
    int candidate = getCandidate();
    if(iterator == 0)
    {
      buttonLabels[iterator] = candidate;
      iterator ++;
    }
    else
    {
      if(!hasDuplicate(iterator, candidate))
      {
        buttonLabels[iterator] = candidate;
        iterator ++;
      } 
    }
  }
  showLabels();
}

// Returns a random number from 1 to 4
int getCandidate()
{
  int candidate = random(1, 5);
  return candidate;
}

// Returns true or false if a number exists or not in an array.
// takes the size of the array and the number that is searched for duplicate as arguments
bool hasDuplicate(int iterations, int cInt)
{ 
  for(int y = 0; y < iterations; y++)
  {
    if(buttonLabels[y] == cInt)
    {
      return true;
    }
  }
  return false;
}
