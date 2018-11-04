#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();
  MFS.initialize(&Timer1);
  
  MFS.initPulseInCounter(BUTTON_1_PIN);  // use button 1 as means of generating pulses.
}


void loop() {
  // put your main code here, to run repeatedly:
  
  // Basically, we count the number of pulses with 3 secconds to get a per second reading.
  
  if (MFS.getTimer() == 0)  // has countdown timer reached 0?
  {  
    int count = MFS.getPulseInTotalCount();

    if (count > 0)
    {
      MFS.write((float)count / 3.0, 1); // display counts per second
    }
    else
    {
      MFS.write(0);
    }
    
    MFS.setTimer(3000);  // set countdown timer to 3 seconds
    MFS.resetPulseInTotalCount();
  }
}
