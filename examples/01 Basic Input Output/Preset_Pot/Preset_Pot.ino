#include <MultiFuncShield.h>

void setup() {
  // put your setup code here, to run once:

  MFS.initialize();    // initialize multi-function shield library
}

void loop() {
  // put your main code here, to run repeatedly:

  MFS.write(analogRead(POT_PIN));
  
  delay(100);
}
