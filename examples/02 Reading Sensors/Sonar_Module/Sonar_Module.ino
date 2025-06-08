#include <MultiFuncShield.h>

const int TrigPin = 5;
const int EchoPin = 6;


void setup() {
  // put your setup code here, to run once:

  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  
  Timer1.initialize();
  MFS.initialize();
  
  // initialize with low pass filter: SMOOTHING_NONE, SMOOTHING_MODERATE or SMOOTHING_STRONG
  MFS.initSonar(SMOOTHING_MODERATE);
}


void loop() {
  // put your main code here, to run repeatedly:

  MFS.write((int)MFS.getSonarDataCm(TrigPin, EchoPin));
  
  delay(100);
}
