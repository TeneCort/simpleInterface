// Array containing the possible passwords
String passwords[] = {"about", "after", "again", "below", "could", "every", "first", "found", "great", "house", "large", "learn", "never", "other", "place", "plant", "point", "right", "small", "sound", "spell", "still", "still", "study", "their", "there", "these", "thing", "think", "three", "water", "where", "which", "world", "would", "write"};

String password; // The password String will be stored here

// Array containing the possible characters to be mixed with the password
char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

char slotA[6]; // Arrays that will contain the char values for each slot
char slotB[6];
char slotC[6];
char slotD[6];
char slotE[6];

char receivedChar;

int slotIndexes[] = {0, 0, 0, 0, 0}; // Array that stores which slot index is to be displayed

char swapA; // Variables that will store the characters to be swaped in it's respective function
char swapB;

bool newData = false;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  choosePassword();
  initAndShuffleSlots();
  displaySlots();
}

void loop()
{
  showNewData();
  recvOneChar();
}

void showNewData()
{
  if (newData == true)
  {
    slotInput(receivedChar);
    checkResult(receivedChar);
    displaySlots();
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

// Function that is called while passing a char value as an argument,
// if the char is equals to the "submit" key, the concatResult function is called and 
// it's return string value is checked against the password String variable.
// It proceeds to notify the user if the submit was correct or no. 
void checkResult(char C)
{
  if (C == 'w')
  {
    Serial.print("submit : ");
    Serial.println(concatResult());
    if (concatResult() == password)
    {
      Serial.println("You win!");
    }
    else
    {
      Serial.println("You loose!");
    }
  }
}

// Function that concatenates the active index of each slot array into a string and returns that string
String concatResult()
{
  String valueToControl;
  valueToControl += slotA[slotIndexes[0]];
  valueToControl += slotB[slotIndexes[1]];
  valueToControl += slotC[slotIndexes[2]];
  valueToControl += slotD[slotIndexes[3]];
  valueToControl += slotE[slotIndexes[4]];
  return valueToControl;
}

// Function that takes a char value as an argument. If the char value is mapped to a slot change input,
// it increments/decrements the value of the indexes array. The indexes array contains the current
// position of each slot to be displayed
void slotInput(char C) {
  if (C == 'a')
  {
    if (slotIndexes[0] > 3)
    {
      slotIndexes[0] = 0;
    }
    else
    {
      slotIndexes[0]++;
    }
  }
  else if (C == 'z')
  {
    if (slotIndexes[1] > 3)
    {
      slotIndexes[1] = 0;
    }
    else
    {
      slotIndexes[1]++;
    }
  }
  else if (C == 'e')
  {
    if (slotIndexes[2] > 3)
    {
      slotIndexes[2] = 0;
    }
    else
    {
      slotIndexes[2]++;
    }
  }
  else if (C == 'r')
  {
    if (slotIndexes[3] > 3)
    {
      slotIndexes[3] = 0;
    }
    else
    {
      slotIndexes[3]++;
    }
  }
  else if (C == 't')
  {
    if (slotIndexes[4] > 3)
    {
      slotIndexes[4] = 0;
    }
    else
    {
      slotIndexes[4]++;
    }
  }
  else if (C == 'q')
  {
    if (slotIndexes[0] < 1)
    {
      slotIndexes[0] = 4;
    }
    else
    {
      slotIndexes[0]--;
    }
  }
  else if (C == 's')
  {
    if (slotIndexes[1] < 1)
    {
      slotIndexes[1] = 4;
    }
    else
    {
      slotIndexes[1]--;
    }
  }
  else if (C == 'd')
  {
    if (slotIndexes[2] < 1)
    {
      slotIndexes[2] = 4;
    }
    else
    {
      slotIndexes[2]--;
    }
  }
  else if (C == 'f')
  {
    if (slotIndexes[3] < 1)
    {
      slotIndexes[3] = 4;
    }
    else
    {
      slotIndexes[3]--;
    }
  }
  else if (C == 'g')
  {
    if (slotIndexes[4] < 1)
    {
      slotIndexes[4] = 4;
    }
    else
    {
      slotIndexes[4]--;
    }
  }
}

//function that displays the current index for each slot
void displaySlots()
{
  Serial.println("----------------");
  Serial.print(slotA[slotIndexes[0]]);
  Serial.print(" ");
  Serial.print(slotB[slotIndexes[1]]);
  Serial.print(" ");
  Serial.print(slotC[slotIndexes[2]]);
  Serial.print(" ");
  Serial.print(slotD[slotIndexes[3]]);
  Serial.print(" ");
  Serial.println(slotE[slotIndexes[4]]);
}

// Function that takes a chr array[] and and initial char value, then populates the rest of it
// with random unique char values
void populateSlots(char slot[], char pwdChar)
{
  slot[0] = pwdChar;
  int iterator = 1;
  while (iterator < 5)
  {
    char candidate = getCandidate();
    if (!hasDuplicate(slot, 5, candidate))
    {
      slot[iterator] = candidate;
      iterator++;
    }
  }
}

// Function that chooses a random String out of the passwords[] array
void choosePassword()
{
  int i = random(0, 36);
  password = passwords[i];
}

// Function that receives an char array and it's length as arguments and shuffles the values
// by calling the swapper function and passing and incremental index and a random index
void shuffler(char table[], int tableL)
{
  for (int i = 0; i < tableL - 1; i++)
  {
    int y = random((i + 1), tableL);
    swapper(table[i], table[y]);
    table[i] = swapA;
    table[y] = swapB;
  }
}

// Function that receives 2 chars as arguments and swaps them
char swapper(char a, char b)
{
  char t = a;
  swapA = b;
  swapB = t;
}

// Returns a random char from alphabet array
char getCandidate()
{
  char candidate = alphabet[random(0, 26)];
  return candidate;
}

// Returns true or false if a char exists or not in an array.
// takes an char array, it's size and the char value to search for a duplicate as arguments
bool hasDuplicate(char slot[], int iterations, char cChar)
{
  for (int y = 0; y < iterations; y++)
  {
    if (slot[y] == cChar)
    {
      return true;
    }
  }
  return false;
}

// Function that calls the necessary function to initialise the module parameters
void initAndShuffleSlots()
{
  populateSlots(slotA, password[0]);
  populateSlots(slotB, password[1]);
  populateSlots(slotC, password[2]);
  populateSlots(slotD, password[3]);
  populateSlots(slotE, password[4]);
  shuffler(slotA, 5);
  shuffler(slotB, 5);
  shuffler(slotC, 5);
  shuffler(slotD, 5);
  shuffler(slotE, 5);
}

void debug()
{
  Serial.println(password);
  Serial.println(slotA);
  Serial.println(slotB);
  Serial.println(slotC);
  Serial.println(slotD);
  Serial.println(slotE);
}

