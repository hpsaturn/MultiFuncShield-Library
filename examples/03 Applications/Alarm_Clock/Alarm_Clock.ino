#include <TimerOne.h>
#include <Wire.h>
#include <MultiFuncShield.h>

/*

  24h Alarm Clock sample

  button 1  : hold to set time or alarm
  button 2  : press to view alarm time or cancel alarm if in progress
  button 3  : increment hour / minute when setting (alarm) time. Hold to toggle alarm setting.
  
  LED1  : on = alarm enabled
*/

volatile unsigned int clockMilliSeconds = 0;
volatile byte clockSeconds = 0;
volatile byte clockMinutes = 0;
volatile byte clockHours = 12;
volatile byte clockEnabled = 1;

byte alarmMinutes = 30;
byte alarmHours = 6;
volatile byte alarmEnabled = false;

byte alarmTogglePressed = false;


enum displayModeValues
{
  MODE_CLOCK_TIME,
  MODE_CLOCK_TIME_SET_HOUR,
  MODE_CLOCK_TIME_SET_MINUTE,
  MODE_ALARM_TIME,
  MODE_ALARM_TIME_SET_HOUR,
  MODE_ALARM_TIME_SET_MINUTE
};

byte displayMode = MODE_CLOCK_TIME;

//--------------------------------------------------------------------------------------------------
void setup()
{
  Timer1.initialize();
  MFS.userInterrupt = clockISR;
  MFS.initialize(&Timer1);
  
  MFS.blinkDisplay(DIGIT_ALL);
  //MFS.beep(500);
}


void loop()
{
  // put your main code here, to run repeatedly:
  
  byte btn = MFS.getButton();
  
  switch (displayMode)
  {
    case MODE_CLOCK_TIME:
        displayTime(clockHours, clockMinutes);
        
        if (btn == BUTTON_2_PRESSED)
        {
          MFS.beep(0);  // cancel the alarm.
          displayMode = MODE_ALARM_TIME;
        }
        else if (btn == BUTTON_1_LONG_PRESSED)
        {
          MFS.blinkDisplay(DIGIT_ALL, OFF);
          MFS.blinkDisplay(DIGIT_1 | DIGIT_2);
          displayMode = MODE_CLOCK_TIME_SET_HOUR;
          clockEnabled = false;
          clockMilliSeconds = 0;
          clockSeconds = 0;
        }
        else if (btn == BUTTON_3_LONG_PRESSED && !alarmTogglePressed)
        {
          alarmTogglePressed = true;
          alarmEnabled = !alarmEnabled;
          MFS.writeLeds(LED_1, alarmEnabled);
        }
        else if (btn == BUTTON_3_LONG_RELEASE)
        {
          alarmTogglePressed = false;
        }
        break;
        
    case MODE_CLOCK_TIME_SET_HOUR:
        if (btn == BUTTON_1_PRESSED)
        {
          MFS.blinkDisplay(DIGIT_1 | DIGIT_2, OFF);
          MFS.blinkDisplay(DIGIT_3 | DIGIT_4);
          displayMode = MODE_CLOCK_TIME_SET_MINUTE;
        }
        else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED)
        {
          clockHours++;
          if (clockHours >= 24)
          {
            clockHours = 0;
          }
          displayTime(clockHours, clockMinutes);
        }
        break;
        
    case MODE_CLOCK_TIME_SET_MINUTE:
        if (btn == BUTTON_1_PRESSED)
        {
          MFS.blinkDisplay(DIGIT_3 | DIGIT_4, OFF);
          displayMode = MODE_CLOCK_TIME;
          clockEnabled = true;
        }
        else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED)
        {
          clockMinutes++;
          if (clockMinutes >= 60)
          {
            clockMinutes = 0;
          }
          displayTime(clockHours, clockMinutes);
        }
        break;
        
    case MODE_ALARM_TIME:
        displayTime(alarmHours, alarmMinutes);

        if (btn == BUTTON_2_SHORT_RELEASE || btn == BUTTON_2_LONG_RELEASE)
        {
          displayMode = MODE_CLOCK_TIME;
        }
        else if (btn == BUTTON_1_LONG_PRESSED)
        {
          MFS.blinkDisplay(DIGIT_ALL, OFF);
          MFS.blinkDisplay(DIGIT_1 | DIGIT_2);
          displayMode = MODE_ALARM_TIME_SET_HOUR;
          alarmEnabled = false;
        }
        break;
        
    case MODE_ALARM_TIME_SET_HOUR:
        if (btn == BUTTON_1_PRESSED)
        {
          MFS.blinkDisplay(DIGIT_1 | DIGIT_2, OFF);
          MFS.blinkDisplay(DIGIT_3 | DIGIT_4);
          displayMode = MODE_ALARM_TIME_SET_MINUTE;
        }
        else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED)
        {
          alarmHours++;
          if (alarmHours >= 24)
          {
            alarmHours = 0;
          }
          displayTime(alarmHours, alarmMinutes);
        }
        break;
        
    case MODE_ALARM_TIME_SET_MINUTE:
        if (btn == BUTTON_1_PRESSED)
        {
          MFS.blinkDisplay(DIGIT_3 | DIGIT_4, OFF);
          displayMode = MODE_CLOCK_TIME;
          alarmEnabled = true;
          MFS.writeLeds(LED_1, ON);
        }
        else if (btn == BUTTON_3_PRESSED || btn == BUTTON_3_LONG_PRESSED)
        {
          alarmMinutes++;
          if (alarmMinutes >= 60)
          {
            alarmMinutes = 0;
          }
          displayTime(alarmHours, alarmMinutes);
        }
        break;      
  }
}


void displayTime (byte hours, byte minutes)
{
  char time[5];
  
  sprintf(time, "%03d", (hours * 100) + minutes);
  MFS.write(time, 1);
}

//--------------------------------------------------------------------------------------------------
void clockISR ()
{
  // Perform ripple count for all time components.
  if (clockEnabled)
  {
    clockMilliSeconds++;
    if (clockMilliSeconds >= 1000)
    {
      clockMilliSeconds = 0;
      
      clockSeconds++;
      if (clockSeconds >= 60)
      {
        clockSeconds = 0;
        
        clockMinutes++;
        if (clockMinutes >= 60)
        {
          clockMinutes = 0;
          
          clockHours++;
          if (clockHours >= 24)
          {
            clockHours = 0;
          }
        }
             
        // If current time coincides with alarm time, and alarm is enabled, engage the alarm.
        if (alarmEnabled && (clockMinutes == alarmMinutes) && (clockHours == alarmHours))
        {
          MFS.beep(
                    10,  // on period
                     5,  // off period
                     4,  // number of cycles
                   100,  // number of loop cycles
                    50   // delay between loop cycles
                   );
        }
      }
    }
  }
}

