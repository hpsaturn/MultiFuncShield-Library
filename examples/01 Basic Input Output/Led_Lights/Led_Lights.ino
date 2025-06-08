#include <MultiFuncShield.h>

/*

For more information and help, please visit https://www.cohesivecomputing.co.uk/hackatronics/arduino-multi-function-shield/part-1/

*/

void setup() {
  // put your setup code here, to run once:
  
  MFS.initialize();    // initialize multi-function shield library
  
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
