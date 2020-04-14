char setA[8] = {'a', 'f', 'e', 'd', 'c', 'b', 'g'};
char setB[8] = {'h', 'a', 'g', 'i', 'j', 'f', 'k'};
char setC[8] = {'l', 'm', 'i', 'n', 'o', 'c', 'j'};
char setD[8] = {'p', 'q', 'r', 'e', 'n', 'k', 's'};
char setE[8] = {'t', 's', 'r', 'u', 'q', 'v', 'w'};
char setF[8] = {'p', 'h', 'x', 'y', 't', 'z', 'a'};

char activeSet[8];
char keys[5];
char submittedKeys[5];

int submitIndex = 0;

char receivedChar;
bool newData = false;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  selectSet();
  populateKeys(keys);
  Serial.println(keys);
}

void loop()
{
  recvOneChar();
  showNewData();
}

void showNewData()
{
  if (newData == true)
  {
    //Serial.println(mapCharToKey(receivedChar));
    applySubmitsToArray(mapCharToKey(receivedChar));
    //Serial.println(submittedKeys);
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

bool checkIndexes()
{
  if (submitIndex >= 4)
  {
    int currIndex = 0;
    int prevIndex = 0;
    for(int i = 0; i < 4; i++)
    {
      char can = submittedKeys[i];
      for(int y = 0; y < 7; y++)
      {
        char con = activeSet[y];
        if(can == con)
        {
          currIndex = y;
        }
        if( i != 0)
        {
          if(currIndex < prevIndex)
          {
            Serial.println("you Loose");
            return false;
          }
        }
        prevIndex = currIndex;
      }
    }
    Serial.println("you Win");
    return true;
  }
}

// Function that takes a char value as input, if the iterator value (global) is less than 4,
// it stores that input value in SubmittedKeys[] at the iterator index and calls checkIndexes().
void applySubmitsToArray(char c)
{
  if (submitIndex < 4)
  {
    submittedKeys[submitIndex] = c;
    submitIndex++;
  }
  checkIndexes();
}

// Function that take a char as an argument, if the char is one of the predefined it returns the 
// value of the keys[] index it's mapped to
char mapCharToKey(char c)
{
  if ( c == 'a')
  {
    return keys[0];
  }
  else if ( c == 'z')
  {
    return keys[1];
  }
  else if ( c == 'e')
  {
    return keys[2];
  }
  else if ( c == 'r')
  {
    return keys[3];
  }
}

// Function that takes a chr[] array and populates it
// with random unique char values returned from getCandidate()
void populateKeys(char k[])
{
  int iterator = 0;
  while (iterator < 4)
  {
    char candidate = getCandidate();
    if (!hasDuplicate(k, 5, candidate))
    {
      k[iterator] = candidate;
      iterator++;
    }
  }
}

// Returns a random char from char[] array
char getCandidate()
{
  char candidate = activeSet[random(0, 8)];
  return candidate;
}

// Returns true or false if a char exists or not in an array.
// takes an char array, it's size and the char value to search for a duplicate as arguments
bool hasDuplicate(char set[], int iterations, char cChar)
{
  for (int y = 0; y < iterations; y++)
  {
    if (set[y] == cChar)
    {
      return true;
    }
  }
  return false;
}

// Copies the values of each index in array A to the same index of the array B
// The arrays must have a size of 7 slots
void copyArray(char A[], char B[])
{
  for (int i = 0; i < 8; i++)
  {
    B[i] = A[i];
  }
}

// Function that pick an random value from 1 to 6 then pick a case for that given value
// each case calls the copyArray() function and passes one of the predefined char arrays to it
// with the empty array to be copied.
char selectSet()
{
  int r = random(1, 7);
  switch (r)
  {
    case 1:
      copyArray(setA, activeSet);
      break;
    case 2:
      copyArray(setB, activeSet);
      break;
    case 3:
      copyArray(setC, activeSet);
      break;
    case 4:
      copyArray(setD, activeSet);
      break;
    case 5:
      copyArray(setE, activeSet);
      break;
    case 6:
      copyArray(setF, activeSet);
      break;
    default:
      copyArray(setA, activeSet);
      break;
  }
}
