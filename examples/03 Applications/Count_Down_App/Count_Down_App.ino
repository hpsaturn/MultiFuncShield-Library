#include <EEPROMex.h>
#include <MultiFuncShield.h>

#define TIMER_VALUE_MAX 99

enum CountDownModeValues
{
  COUNTING_STOPPED,
  COUNTING
};

byte countDownMode = COUNTING_STOPPED;

byte tenths = 0;
char seconds = 0;
char minutes = 0;

void saveTimer(char minutes, char seconds) {
  EEPROM.writeByte(0, seconds);
  EEPROM.writeByte(sizeof(byte), minutes);
}

void loadTimer() {
  seconds = EEPROM.readByte(0);
  minutes = EEPROM.readByte(sizeof(byte));
  if((seconds+minutes)<0){
    seconds=0;
    minutes=0;
  }
}

void checkStopConditions(byte btn) {

  if (btn == BUTTON_1_SHORT_RELEASE && (minutes + seconds) > 0) {
    countDownMode = COUNTING; // start the timer
    MFS.beep(6, 2, 3);  // beep 3 times, 600 milliseconds on / 200 off
    saveTimer(minutes,seconds);
  }
  else if (btn == BUTTON_1_LONG_PRESSED) {
    tenths  = 0; // reset the timer
    seconds = 0;
    minutes = 0;
    MFS.beep(8, 10, 1);  // beep 1 times, 800 milliseconds on / 1000 off
  }
  else if (btn == BUTTON_2_PRESSED || btn == BUTTON_2_LONG_PRESSED) {
    minutes++;
    if (minutes > TIMER_VALUE_MAX) minutes = 0;
  }
  else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED) {
    seconds += 1; // continue counting down
    if (seconds >= 60) seconds = 0;
  }

}

void checkCountDownConditions (byte btn) {

  if (btn == BUTTON_1_SHORT_RELEASE || btn == BUTTON_1_LONG_RELEASE) {
    countDownMode = COUNTING_STOPPED; // stop the timer
    MFS.beep(6, 2, 2);  // beep 6 times, 200 milliseconds on / 200 off
  }
  else { 

    tenths++; // continue counting down

    if (tenths == 10) {

      tenths = 0;
      seconds--;

      if (seconds < 0 && minutes > 0) {
        seconds = 59;
        minutes--;
      }

      if (minutes == 0 && seconds == 0) {
        // timer has reached 0, so sound the alarm
        MFS.beep(50, 50, 3);  // beep 3 times, 500 milliseconds on / 500 off
        countDownMode = COUNTING_STOPPED;
      }

    }

    delay(100);

  }

}

void display (char min, char sec){
  // display minutes and seconds sepated with a point
  MFS.write((float)((minutes*100 + seconds)/100.0),2);
}

void setup() {
  // put your setup code here, to run once:
  MFS.initialize();    // initialize multifunction shield library
  MFS.write(0);
  loadTimer();
}

void loop() {

  byte btn = MFS.getButton();
  
  switch (countDownMode)
  {
    case COUNTING_STOPPED:
        checkStopConditions(btn);
        MFS.blinkDisplay(DIGIT_1 | DIGIT_2 | DIGIT_3 | DIGIT_4);
        break;
        
    case COUNTING:
        checkCountDownConditions(btn);
        MFS.blinkDisplay(DIGIT_1 | DIGIT_2 | DIGIT_3 | DIGIT_4, OFF);
        break;
  }

  display(minutes,seconds);

}
