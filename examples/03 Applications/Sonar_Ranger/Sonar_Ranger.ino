#include <MultiFuncShield.h>

/*

For more information and help, please visit https://www.cohesivecomputing.co.uk/hackatronics/arduino-multi-function-shield/part-3/

All our hackatronics projects are free for personal use, and there are many more
in the pipeline. If you find our projects helpful or useful, please consider making
a small donation to our hackatronics fund using the donate buttons on our web pages.
Thank you.

*/

const int TrigPin = 5;
const int EchoPin = 6;

enum sonarModeValues
{
  MODE_SONAR_OFF,
  MODE_SONAR_ON
};

byte sonarMode = MODE_SONAR_OFF;

void setup()
{
  //Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  
  MFS.initialize();
  MFS.write("off");
}

void loop()
{
  byte btn = MFS.getButton();
  
  switch (sonarMode)
  {
    case MODE_SONAR_OFF:
        if (btn == BUTTON_1_PRESSED)
        {
          sonarMode = MODE_SONAR_ON;
          MFS.beep(5, 95, 1,0,0);
          MFS.write("on");
        }
        break;
        
    case MODE_SONAR_ON:
        if (btn == BUTTON_1_PRESSED)
        {
          sonarMode = MODE_SONAR_OFF;
          MFS.beep(0);
          MFS.write("off");
          MFS.blinkDisplay(DIGIT_ALL, OFF);
          MFS.initSonar();
        }
        else
        {
          int distance = MFS.getSonarDataCm(TrigPin, EchoPin);
          //int distance = 5;
          if (distance != 0 && distance < 2000)
          { 
            int offPeriod = distance - 6;
            
            if (offPeriod < 0)
            {
              offPeriod = 0;
            }
            
            MFS.write(distance);
            MFS.setBeepOffPeriod(offPeriod);
            
            MFS.blinkDisplay(DIGIT_ALL, distance < 11);
          }
          delay(100);
        }
        break;
  }
}
