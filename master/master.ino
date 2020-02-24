#include <Wire.h>

#define SLAVE_ADDRESS 0x12

int dataReceived = 0;
int modules[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
int activeModules[] = {};
int activeModuleIndex = 0;

void setup() {
    activeModuleIndex = 0;
    Serial.begin(9600);
    Wire.begin(SLAVE_ADDRESS);
    Wire.onReceive(receiveData);
    Wire.onRequest(sendData);
}

void loop() {
    delay(100);
}

void receiveData(int byteCount)
{
    while(Wire.available())
    {
        dataReceived = Wire.read();
        
        if(dataReceived < 100)
        {
          Serial.print("Durée du script : ");
          Serial.println(dataReceived);
        }
        
        if(dataReceived > 100 && dataReceived < 200)
        {
          activeModules[activeModuleIndex] = dataReceived - 100;
          activeModuleIndex++;
          Serial.print("Module actif : ");
          Serial.println(dataReceived - 100);
        }
    }               
}

void sendData()
{
    int envoi = dataReceived;
    if(dataReceived < 100)
    {
      Wire.write(envoi);
    }
    
    if(dataReceived > 100 && dataReceived < 200)
    {
      Wire.write(envoi);
    }
    
    if(dataReceived == 200)
    {
      activeModuleIndex--;
      Serial.print("Modules remaining ");
      Serial.println(activeModuleIndex);
      Wire.write(activeModuleIndex);
    }
    
}

void checkModules()
{
  
}
