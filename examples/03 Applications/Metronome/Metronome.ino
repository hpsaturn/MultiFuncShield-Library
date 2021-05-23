#include <I2C.h>
#include <II2C.h>
#include <MPU6050.h>
#include <MultiFuncShield.h>
#include <avr/eeprom.h>


typedef struct Config {
  char appNameAndVersion[16];
  byte  signature;    // must be between 2 to 8
  unsigned int tempo; // must be between 60 to 240
};

enum MetronomeDisplayModeValues
{
  DISPLAY_TIMER,
  DISPLAY_SIGNATURE,
  DISPLAY_TEMPO
};

enum MetronomeStatusValues
{
  METRO_OFF,
  METRO_ON
};

Config currentConfig;
byte beatCounter;
byte displayMode = DISPLAY_TIMER;
byte statusMode = METRO_OFF;
const byte led[] = {13,12,11,10};


void setup() {
  // put your setup code here, to run once:
  
  loadConfig();
  MFS.initialize();
  MFS.write(beatCounter);
}


void loop() {
  const unsigned int oldTempo = currentConfig.tempo;
  const byte oldSignature = currentConfig.signature;
  const byte btn = MFS.getButton();

  switch (displayMode)
  {
    case DISPLAY_TIMER:
      if (btn == BUTTON_1_PRESSED)
      {
        if (statusMode == METRO_OFF)
        {
          statusMode = METRO_ON;          // Turn metronome on, if off.
        }
        else if (statusMode == METRO_ON)
        {
          statusMode = METRO_OFF;         // Turn metronome off, if on.
          beatCounter = 0;
          MFS.write(beatCounter);
          clearLeds();
        }
      }
      else if (btn == BUTTON_2_PRESSED)
      {
        displayMode = DISPLAY_TEMPO;
        MFS.write((int)currentConfig.tempo);
        MFS.blinkDisplay(DIGIT_ALL, ON);
      }
      else if (btn == BUTTON_3_PRESSED)
      {
        displayMode = DISPLAY_SIGNATURE;
        displaySignature(currentConfig.signature);
        MFS.blinkDisplay(DIGIT_ALL, ON);
      }
      break;
    case DISPLAY_SIGNATURE:
      if (btn == BUTTON_1_PRESSED)
      {
        displayMode = DISPLAY_TIMER;
        MFS.write(beatCounter);
        MFS.blinkDisplay(DIGIT_ALL, OFF);
        saveConfig();                       // Write config to eeprom.
      }
      else if (btn == BUTTON_2_PRESSED)
      {
        currentConfig.signature--;          // Change to lower time signature
        if (currentConfig.signature <2)
        {
          currentConfig.signature = 2;
        }
      }
      else if (btn == BUTTON_3_PRESSED)
      {
        currentConfig.signature++;          // Change to higher time signature
        if (currentConfig.signature > 8)
        {
          currentConfig.signature = 8;
        }
      }

      if (oldSignature != currentConfig.signature)
      {
        displaySignature(currentConfig.signature);
      }
      break;
      
    case DISPLAY_TEMPO:
      if (btn == BUTTON_1_PRESSED)
      {
        displayMode = DISPLAY_TIMER;
        MFS.write(beatCounter);
        MFS.blinkDisplay(DIGIT_ALL, OFF);
        saveConfig();                       // Write config to eeprom.
      }
      else if (btn == BUTTON_2_PRESSED)
      {
        currentConfig.tempo--;              // Reduce tempo by 1
      }
      else if (btn == BUTTON_3_PRESSED)
      {
        currentConfig.tempo++;              // Increase tempo by 1
      }
      else if (btn == BUTTON_2_LONG_PRESSED)
      {
        currentConfig.tempo = ((currentConfig.tempo-2) / 2) * 2;    // Reduce tempo to next even number
      }
      else if (btn == BUTTON_3_LONG_PRESSED)
      {
        currentConfig.tempo = ((currentConfig.tempo+2) / 2) * 2;    // Increase tempo to next even number
      }

      if (oldTempo != currentConfig.tempo)
      {
        if (currentConfig.tempo < 60)
        {
          currentConfig.tempo = 60;
        }
        else if (currentConfig.tempo > 240)
        {
          currentConfig.tempo = 240;
        }
        MFS.write((int)currentConfig.tempo);
      }
      break;
  }

  switch (statusMode)
  {
    case METRO_OFF:
      break;
    case METRO_ON:
      // Has millisecond countdown timer reached 0?
      if (MFS.getTimer() == 0)
      {
        // Reset countdown timer.
        MFS.setTimer(240000 / (currentConfig.tempo * (currentConfig.signature <= 4 ? 4 : 8)));
        if (beatCounter < 1 || beatCounter >= currentConfig.signature)
        {
        // Sound beeper every time beat counter is reset.
          MFS.beep(2);
          beatCounter = 1;
        }
        else
        {
          // bump beat counter
          beatCounter++;
        }

        if (displayMode == DISPLAY_TIMER)
        {
          MFS.write(beatCounter);
        }
      }
      break;
  }

  if (beatCounter != 0)
  {
    clearLeds();
    digitalWrite(led[(beatCounter-1) & 3], beatCounter == 1 ? 0 : millis() & 7);  // use crude PWM to change brightness
  }
}


// -------------------------------------------------------------
float displaySignature(byte signature)
{
  float sig = (float)signature;

  if (signature <= 4)
  {
    sig = sig + 0.4;
  }
  else
  {
    sig = sig + 0.8;
  }
  MFS.write(sig);
}


// -------------------------------------------------------------
void clearLeds()
{
  for (int i=0; i < sizeof(led); i++)
  {
    digitalWrite(led[i], 1);
  }
}


// -------------------------------------------------------------
const char appNameAndVersion[] = "Metronome V1.0";

void loadConfig()
{
  // Attempt to load config from EEPROM
  eeprom_read_block(&currentConfig, (void *)0, sizeof (Config));

  if (strcmp(currentConfig.appNameAndVersion, appNameAndVersion) != 0)
  {
    // Config not found in eeprom, so set default values here.
    strcpy(currentConfig.appNameAndVersion, appNameAndVersion);
    currentConfig.signature = 4;
    currentConfig.tempo = 80;
  }
}

void saveConfig()
{
  eeprom_write_block(&currentConfig, (void *)0, sizeof (Config));
}
