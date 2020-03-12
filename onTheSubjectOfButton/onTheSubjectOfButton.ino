// constants won't change. They're used here to set pin numbers:
const int SENSOR_PIN = 7; // the Arduino's input pin that connects to the sensor's SIGNAL pin

// Hardware values
int lastState = LOW;      // the previous state from the input pin
int currentState;         // the current reading from the input pin

// Possible values
String buttonColors[] = {"BLUE", "WHITE", "YELLOW", "RED"};
String buttonTexts[] = {"Abort", "Detonate", "Hold"};
String stripColors[] = {"BLUE", "WHITE", "YELLOW", "RED", "GREEN"};
String indicatorTexts[] = {"CAR", "FRK", "SND", "IND"};

// Init values
unsigned long time;
bool buttonPush = false;
bool isIndicator = false;
String buttonColor = "";
String buttonText = "";
String indicator = "";
String reference = "";
int batteries = 0;
int timer = 0;
int strikes = 0;
int interval = 1000;

// Serial activators
bool isActive = false;
bool moduleListener = false;
bool durationListener = false;

void setup()
{
  // initialize the Arduino's pin as an input
  pinMode(SENSOR_PIN, INPUT);

  // Init serial and random seed
  Serial.begin(9600);
  randomSeed(analogRead(0));

  randomizer();

  // Print for testing
  Serial.println("<--------| |-------->");
  Serial.print("Button Color : ");
  Serial.println(buttonColor);
  Serial.print("Button Text : ");
  Serial.println(buttonText);
  Serial.print("Batteries : ");
  Serial.println(batteries);
  Serial.print("Indicator : ");
  Serial.println(isIndicator);
  Serial.print("Indicator text : ");
  Serial.println(indicator);
}

void clockCounter()
{
  timer --;
  Serial.println(timer);
}

void loop()
{
  currentState = digitalRead(SENSOR_PIN);

  if (millis() > time + interval && timer > 0)
  { 
      clockCounter();
      time = millis();
  }

  if (buttonColor == "BLUE" && buttonText == "Abort")
  {
    // Hold and ref
    if (lastState == LOW && currentState == HIGH)
    {
      Serial.print("Strip Color : ");
      Serial.println(reference);
    }
  }

  else if (batteries > 1 && buttonText == "Detonate")
  {
    //Press and release
  }

  else if (buttonColor == "WHITE" && isIndicator == 1 && indicator == "CAR")
  {
    // Hold and ref
    if (lastState == LOW && currentState == HIGH)
    {
      Serial.print("Strip Color : ");
      Serial.println(reference);
    }
  }

  else if (batteries > 2 && isIndicator == 1 && indicator == "FRK")
  {
    // Press and release
  }

  else if (buttonColor == "YELLOW")
  {
    if (lastState == LOW && currentState == HIGH)
    {
      Serial.print("Strip Color : ");
      Serial.println(reference);
    }
  }

  else if (buttonColor == "RED" && buttonText == "Hold")
  {
    // Press and release
  }

  else if (batteries > 2 && isIndicator == 1 && indicator == "FRK")
  {
    // Press and release
  }

  else
  {
    // Press and release
  }

  if (lastState == LOW && currentState == HIGH)
  {
    Serial.println("The sensor is touched");
  }
  if (lastState == HIGH && currentState == LOW)
  {
    Serial.println("The sensor is untouched");
    win();
  }

  // save the the last state
  lastState = currentState;

  // Communication part
  if (Serial.available())
  {
    char c = Serial.read();

    if (c == 'R')
    {
      moduleListener = false;
      durationListener = false;
    }
    
    // Module Listener
    if (c == 'M')
    {
      moduleListener = true;
      durationListener = false;
    }
    if (moduleListener && c == '1')
    {
      isActive = true;
      Serial.println("I'm active!");
      moduleListener = false;
    }

    // when Module Listener is active, check duration and apply
    if (isActive)
    {
      if (c == 'D')
      {
        durationListener = true;
        moduleListener = false;
      }
      if (durationListener && c != 'D')
      {
        timer = (c - 48) * 60;
        Serial.print("My duration is : ");
        Serial.print(timer * 60);
        durationListener = false;
      }
    }
  }
}

void win()
{
  Serial.print("W");
  Serial.print("1");
}

void randomizer()
{
  // Applying values
  buttonText = buttonTexts[random(0, 3)];
  buttonColor = buttonColors[random(0, 4)];
  reference = stripColors[random(0, 5)];
  indicator = indicatorTexts[random(0, 4)];
  batteries = random(0, 4);
  isIndicator = false;
  if (random(0, 100) >= 50)
  {
    isIndicator = true;
  }
}
