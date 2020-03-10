// Possible values
String buttonColors[] = {"BLUE", "WHITE", "YELLOW", "RED"};
String buttonTexts[] = {"Abort", "Detonate", "Hold"};
String stripColors[] = {"BLUE", "WHITE", "YELLOW", "RED", "GREEN"};
String indicatorTexts[] = {"CAR", "FRK", "SND", "IND"};
// Init values
unsigned long time;
int timer = 10000; 
bool buttonPush = false;
String buttonColor = "";
String buttonText = "";
String indicator = "";
bool isIndicator = false;
int batteries = 0;
String reference = "";

void setup()
{
  // Init serial and random seed
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  // Applying values
  buttonText = buttonTexts[random(0, 3)];
  buttonColor = buttonColors[random(0, 4)];
  reference = stripColors[random(0, 5)];
  indicator = indicatorTexts[random(0, 4)];
  batteries = random(0, 4);
  if(random(0, 100) >= 50)
  {
    isIndicator = true;  
  }
  else
  {
    isIndicator = false;
  }

  // Print for testing
  Serial.println("<--------| |-------->");  
  Serial.print("Button Color : ");  
  Serial.println(buttonColor);
  Serial.print("Button Text : ");  
  Serial.println(buttonText);
  Serial.print("Strip Color : ");  
  Serial.println(reference);
  Serial.print("Batteries : ");  
  Serial.println(batteries);
  Serial.print("Indicator : ");  
  Serial.println(isIndicator);
  Serial.print("Indicator text : ");  
  Serial.println(indicator);
}

void loop()
{
  time = millis();
  if(timer > time)
  {
    //Serial.println("Time: On");  
  }
  else
  {
    Serial.println("Time: Out");
  }
}
