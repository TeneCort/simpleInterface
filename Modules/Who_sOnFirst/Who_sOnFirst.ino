const String pReady[14] PROGMEM = {"YES", "OKAY", "WHAT", "MIDDLE", "LEFT", "PRESS", "RIGHT", "BLANK", "READY", "NO", "FIRST", "UHHH", "NOTHING", "WAIT"};
const String pFirst[14] PROGMEM = {"LEFT", "OKAY", "YES", "MIDDLE", "NO", "RIGHT", "NOTHING", "UHHH", "WAIT", "READY", "BLANK", "WHAT", "PRESS", "FIRST"};
const String pBlank[] PROGMEM = {"WAIT", "RIGHT", "OKAY", "MIDDLE", "BLANK", "PRESS", "READY", "NOTHING", "NO", "WHAT", "LEFT", "UHHH", "YES", "FIRST"};
//const String pNo[] PROGMEM = {"BLANK", "UHHH", "WAIT", "FIRST", "WHAT", "READY", "RIGHT", "YES", "NOTHING", "LEFT", "PRESS", "OKAY", "NO", "MIDDLE"};

String displayTextsArray[] = {"YES", "FIRST", "DISPLAY",
                        "OKAY", "SAYS", "NOTHING",
                        "----", "BLANK", "NO",
                        "LED", "LEAD", "READ",
                        "RED", "REED", "LEED",
                        "HOLD ON", "YOU", "YOU ARE",
                        "YOUR", "YOU'RE", "UR",
                        "THERE", "THEY'RE", "THEIR",
                        "THEY ARE", "SEE", "C",
                        "CEE"
                        };
String buttonTextsArray[] = {"READY", "FIRST", "NO",
                        "BLANK", "NOTHING", "YES",
                        "WHAT", "UHHH", "LEFT",
                        "RIGHT", "MIDDLE", "OKAY",
                        "WAIT", "PRESS", "YOU",
                        "YOU ARE", "YOUR", "YOU'RE",
                        "UR", "U", "UH HUH",
                        "WHAT?", "DONE", "NEXT",
                        "HOLD", "SURE", "LIKE"
                        };
String buttonTexts[6];  
String displayText = "";         
char receivedChar = ' ';
bool newData = false;
int level = 0;

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  displayText = displayTextsArray[random(0, sizeof(displayTextsArray) / sizeof(displayTextsArray[0]))];
  allocateButtonTexts();
  Serial.println(displayText);
  Serial.println(activeLabel(displayText));
}

void loop()
{
  while(level < 3)
  {
    
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

void showNewData()
{
  if (newData == true)
  {
    newData = false;
  }
}

void allocateButtonTexts()
{
  int iterator = 0;
  while(iterator < 6)
  {
    String candidate = getCandidate();
    if(iterator == 0)
    {
      Serial.println(candidate);
      buttonTexts[iterator] = candidate;
      iterator ++;
    }
    else
    {
      if(!hasDuplicate(iterator, candidate))
      {
        Serial.println(candidate);
        buttonTexts[iterator] = candidate;
        iterator ++;
      } 
    }
  }
}

String getCandidate()
{
  String candidate = buttonTextsArray[random(sizeof(buttonTextsArray) / sizeof(buttonTextsArray[0]))];
  return candidate;
}

bool hasDuplicate(int iterations, String cString)
{ 
  for(int y = 0; y < iterations; y++)
  {
    if(buttonTexts[y] == cString)
    {
      return true;
    }
  }
  return false;
}

int activeLabel(String label)
{
  if(label == "UR")
  {
    return 0;
  }
  else if(label == "FIRST" || label == "OKAY" || label == "C")
  {
    return 1;
  }
  else if(label == "NOTHING" || label == "LED" || label == "THEY ARE" || label == "YES")
  {
    return 2;
  }
  else if(label == "BLANK" || label == "READ" || label == "RED" || label == "YOU" || label == "YOUR" || label == "YOU'RE" || label == "THEIR")
  {
    return 3;
  }
  else if(label == "----" || label == "REED" || label == "LEED" || label == "THEY'RE")
  {
    return 4;
  }
  else if(label == "DISPLAY" || label == "SAYS" || label == "NO" || label == "LEAD" ||  label == "HOLD ON" || label == "YOU ARE" || label == "THERE" || label == "SEE" || label == "CEE")
  {
    return 5;
  }
  else
  {
    return NULL;
  }
}
