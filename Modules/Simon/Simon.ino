const int MAX_LEVEL = 5;
int controlSequence[MAX_LEVEL];
int userSequence[MAX_LEVEL];
int controlIndex = 0;
int level = 1;
int strikes = 0;
char test[] = {'A', 'Z', 'E', 'R'};
char controlChar = ' ';
char receivedChar = ' ';
bool newData = false;
String serial = "";

void setup()
{
  Serial.begin(9600);
  randomSeed(analogRead(0));
  populateControl();
  generateSerial();
  Serial.println(serial);
  strikes = random(0,2);
  Serial.println(strikes);
  playSequence();
  controlChar = controlSequence[controlIndex];
}

void loop()
{
  while(checkLevel())
  { 
    recvOneChar();
    showNewData();
  }  
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
    
    check();
    newData = false;
  }
}

void populateControl()
{
  for(int i = 0; i < MAX_LEVEL; i++)
  {
    controlSequence[i] = test[random(0, 4)];
  }
  Serial.print(char (controlSequence[0]));
  Serial.print(char (controlSequence[1]));
  Serial.print(char (controlSequence[2]));
  Serial.print(char (controlSequence[3]));
  Serial.println(char (controlSequence[4]));
}

void check()
{
  applyChange();
  if(controlChar == receivedChar)
  {
    controlIndex++;
    controlChar = controlSequence[controlIndex];
    if(controlIndex >= level)
    {
      controlIndex = 0;
      controlChar = controlSequence[controlIndex];
      level++;
      playSequence();
    }
  }
  else 
  {
    strikes++;
    controlIndex = 0;
    controlChar = controlSequence[controlIndex];
    playSequence();
  }
}

void playSequence()
{
  for(int i = 0; i < level; i++)
  {
    char cch = controlSequence[i];
    Serial.println(cch);
    delay(1000);
  }
}

bool checkLevel()
{
  if(level > MAX_LEVEL)
  {
    return false;
  }
  return true;
}

String generateSerial()
{
  for(int i = 0; i < 6; i++)
  {
    if(random(50) > 25)
    {
      serial += char(random(65,90));
    }
    else
    {
      serial += char(random(48,57));
    }
  }
}

bool hasVowel()
{
  bool vowel = false;
  char vowels[] = {'A', 'E', 'I', 'O', 'U'};
  for(int i = 0; i < sizeof(serial); i++)
  {
    for(int y = 0; y < sizeof(vowels); y++)
    {
      if(serial[i] == vowels[y])
      {     
        vowel = true;
      }
    }
  }
  return vowel;
}

void applyChange()
{
  if(hasVowel())
  {
    if(strikes == 0)
    {
      Serial.println("Has Vowel, strike 0");
      if(controlChar == 'A') controlChar = 'Z';
      else if(controlChar == 'Z') controlChar = 'A';
      else if(controlChar == 'E') controlChar = 'R';
      else if(controlChar == 'R') controlChar = 'E';
    }
    else if(strikes == 1)
    {
      if(controlChar == 'A') controlChar = 'R';
      else if(controlChar == 'Z') controlChar = 'E';
      else if(controlChar == 'E') controlChar = 'Z';
      else if(controlChar == 'R') controlChar = 'A';
    }
    else
    {
      if(controlChar == 'A') controlChar = 'E';
      else if(controlChar == 'Z') controlChar = 'A';
      else if(controlChar == 'E') controlChar = 'R';
      else if(controlChar == 'R') controlChar = 'Z';
    }
  }
  else
  {
    if(strikes == 0)
    {
      if(controlChar == 'A') controlChar = 'Z';
      else if(controlChar == 'Z') controlChar = 'R';
      else if(controlChar == 'E') controlChar = 'E';
      else if(controlChar == 'R') controlChar = 'A';
    }
    else if(strikes == 1)
    {
      if(controlChar == 'A') controlChar = 'A';
      else if(controlChar == 'Z') controlChar = 'Z';
      else if(controlChar == 'E') controlChar = 'R';
      else if(controlChar == 'R') controlChar = 'E';
    }
    else
    {
      if(controlChar == 'A') controlChar = 'R';
      else if(controlChar == 'Z') controlChar = 'E';
      else if(controlChar == 'E') controlChar = 'Z';
      else if(controlChar == 'R') controlChar = 'A';
    }
  }
}

