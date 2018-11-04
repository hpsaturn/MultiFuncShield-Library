#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Timer1.initialize();
  MFS.initialize(&Timer1);    // initialize multi-function shield library
}


void loop() {
  // put your main code here, to run repeatedly:

  byte btn = MFS.getButton(); // Normally it is sufficient to compare the return
                              // value to predefined macros, e.g. BUTTON_1_PRESSED,
                              // BUTTON_1_LONG_PRESSED etc.
  
  if (btn)
  {
    byte buttonNumber = btn & B00111111;
    byte buttonAction = btn & B11000000;
    
    Serial.print("BUTTON_");
    Serial.write(buttonNumber + '0');
    Serial.print("_");
    
    if (buttonAction == BUTTON_PRESSED_IND)
    {
      Serial.println("PRESSED");
    }
    else if (buttonAction == BUTTON_SHORT_RELEASE_IND)
    {
      Serial.println("SHORT_RELEASE");
    }
    else if (buttonAction == BUTTON_LONG_PRESSED_IND)
    {
      Serial.println("LONG_PRESSED");
    }
    else if (buttonAction == BUTTON_LONG_RELEASE_IND)
    {
      Serial.println("LONG_RELEASE");
    }
  }
}
