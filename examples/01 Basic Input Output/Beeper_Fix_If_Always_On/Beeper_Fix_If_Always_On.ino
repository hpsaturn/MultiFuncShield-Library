#include <MultiFuncShield.h>

void setup() {
  // put your setup code here, to run once:
  
  MFS.setBeeperReversePolarity(true);  // try setting to true if your beeper is always on by default with KNARCO brand boards

  MFS.initialize(&Timer1);    // initialize multi-function shield library
  
  // 4 short beeps, repeated 3 times.
  MFS.beep(5,    // beep for 50 milliseconds
           5,    // silent for 50 milliseconds
           4,    // repeat above cycle 4 times
           3,    // loop 3 times
           50    // wait 500 milliseconds between loop
           );
}

void loop() {
  // put your main code here, to run repeatedly:

}
