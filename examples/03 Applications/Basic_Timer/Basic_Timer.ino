#include <MultiFuncShield.h>


enum CountDownModeValues
{
  COUNTING_STOPPED,
  COUNTING
};

byte countDownMode = COUNTING_STOPPED;

byte tenths = 0;
char seconds = 0;
char minutes = 0;

void setup() {
  // put your setup code here, to run once:
  MFS.initialize();    // initialize multifunction shield library
  MFS.write(0);
  
  Serial.begin(9600);
}


void loop() {
  // put your main code here, to run repeatedly:

  byte btn = MFS.getButton();
  
  switch (countDownMode)
  {
    case COUNTING_STOPPED:
        if (btn == BUTTON_1_SHORT_RELEASE && (minutes + seconds) > 0)
        {
          // start the timer
          countDownMode = COUNTING;
        }
        else if (btn == BUTTON_1_LONG_PRESSED)
        {
          // reset the timer
          tenths = 0;
          seconds = 0;
          minutes = 0;
          MFS.write(minutes*100 + seconds);
        }
        else if (btn == BUTTON_2_PRESSED || btn == BUTTON_2_LONG_PRESSED)
        {
          minutes++;
          if (minutes > 60)
          {
            minutes = 0;
          }
          MFS.write(minutes*100 + seconds);
        }
        else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED)
        {
          seconds += 10;
          if (seconds >= 60)
          {
            seconds = 0;
          }
          MFS.write(minutes*100 + seconds);
        }
        break;
        
    case COUNTING:
        if (btn == BUTTON_1_SHORT_RELEASE || btn == BUTTON_1_LONG_RELEASE)
        {
          // stop the timer
          countDownMode = COUNTING_STOPPED;
        }
        else
        {
          // continue counting down
          tenths++;
          
          if (tenths == 10)
          {
            tenths = 0;
            seconds--;
            
            if (seconds < 0 && minutes > 0)
            {
              seconds = 59;
              minutes--;
            }
            
            if (minutes == 0 && seconds == 0)
            {
              // timer has reached 0, so sound the alarm
              MFS.beep(50, 50, 3);  // beep 3 times, 500 milliseconds on / 500 off
              countDownMode = COUNTING_STOPPED;
            }
            
            MFS.write(minutes*100 + seconds);
          }
          delay(100);
        }
        break;
  }
}
