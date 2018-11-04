#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();
  MFS.initialize(&Timer1);
  
  MFS.initPulseInCounter(
      BUTTON_1_PIN,      // use button 1 as means of generating pulses.
      1500,              // the number of milliseconds to wait for a pulse, before resetting pulse in period to 0.
      LOW                // trigger pulse on LOW input.
  );
}


void loop() {
  // put your main code here, to run repeatedly:

  // Get the period of the most recent pulse (in milliseconds).
  // NOTE: pulse measurements are actually performed using interrupts.
  unsigned int pulsePeriodMs = MFS.getPulseInPeriod();
  
  if (pulsePeriodMs == 0)
  {
    MFS.write(0.0, 1);
  }
  else
  {
    MFS.write(1000.0 / pulsePeriodMs, 1);  // calculate pulses per second. Display to 1 decimal place.
  }
}
