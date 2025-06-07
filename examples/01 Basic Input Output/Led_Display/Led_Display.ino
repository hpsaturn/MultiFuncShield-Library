#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
  // put your setup code here, to run once:
  
  Timer1.initialize();
  MFS.initialize(&Timer1);    // initialize multi-function shield library
  MFS.setDisplayBrightness(3); // set display brightness. 0 = max, 3 = min. 
  
  MFS.write("Hi");
  delay(2000);
  MFS.write(-273);
  delay(2000);
  MFS.write(3.141, 2);  // display to 2 decimal places.
  delay(2000);
}

int counter=0;
byte ended = false;

void loop() {
  // put your main code here, to run repeatedly:

  if (counter < 200)
  {
    MFS.write((int)counter);
    counter++;
  }
  else if (!ended)
  {
    ended = true;
    MFS.write("End");
    MFS.blinkDisplay(DIGIT_ALL, ON);
  }
  delay(50);
}
