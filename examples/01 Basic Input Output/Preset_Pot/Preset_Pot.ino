#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
  // put your setup code here, to run once:

  Timer1.initialize();
  MFS.initialize(&Timer1);    // initialize multi-function shield library
}

void loop() {
  // put your main code here, to run repeatedly:

  MFS.write(analogRead(POT_PIN));
  
  delay(100);
}
