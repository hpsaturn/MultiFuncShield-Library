#include <MultiFuncShield.h>

/*

For more information and help, please visit https://www.cohesivecomputing.co.uk/hackatronics/arduino-multi-function-shield/part-1/

*/

void setup() {
  // put your setup code here, to run once:

  MFS.initialize();    // initialize multi-function shield library
  
  // NOTE beep control is performed in the background, i.e. beep() is non blocking.
  
  // short beep for 200 milliseconds
  MFS.beep();
  
  delay(1000);
  
  // 4 short beeps, repeated 3 times.
  MFS.beep(5,    // beep for 50 milliseconds
           5,    // silent for 75 milliseconds
           4,    // repeat above cycle 4 times
           3,    // loop 3 times
           50    // wait 500 milliseconds between loop
           );
}

void loop() {
  // put your main code here, to run repeatedly:

}
