#include <MultiFuncShield.h>

// NOTE: make sure jumper J1 is removed from shield, and that LM35 is inserted correctly.

void setup() {
  // put your setup code here, to run once:
  MFS.initialize();
  
  // Initialize using a low pass filter.
  // Choose either: SMOOTHING_NONE, SMOOTHING_MODERATE or SMOOTHING_STRONG
  MFS.initLM35(SMOOTHING_MODERATE);
}

void loop() {
  // put your main code here, to run repeatedly:

  int tempCentigrade = MFS.getLM35Data(); // get centigrade in 1/10 of degree.
  
  MFS.write((float)tempCentigrade / 10, 1);  // display temp to 1 decimal place.
  
  delay(100);
}
