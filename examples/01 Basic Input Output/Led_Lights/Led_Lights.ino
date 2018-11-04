#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
  // put your setup code here, to run once:
  
  Timer1.initialize();
  MFS.initialize(&Timer1);    // initialize multi-function shield library
  
  MFS.writeLeds(LED_ALL, ON);
  delay(2000);
  MFS.blinkLeds(LED_1 | LED_2, ON);
  delay(2000);
  MFS.blinkLeds(LED_1 | LED_2, OFF);
  
  MFS.blinkLeds(LED_3 | LED_4, ON);
  delay(2000);
  MFS.blinkLeds(LED_ALL, ON);
  delay(2000);
  MFS.blinkLeds(LED_ALL, OFF);
  MFS.writeLeds(LED_ALL, OFF);
}

void loop() {
  // put your main code here, to run repeatedly:

}
