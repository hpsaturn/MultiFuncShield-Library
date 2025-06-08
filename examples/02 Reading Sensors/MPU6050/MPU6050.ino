#include <Wire.h>
#include <MultiFuncShield.h>

#include "I2C.h"
#include "MPU6050.h"

//#define SOFTWARE_I2C

/*

For more information and help, please visit https://www.cohesivecomputing.co.uk/hackatronics/arduino-multi-function-shield/part-2/

*/

MPU6050 MPU;
void displayHeading(byte mode);


void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  // Use hardware I2C
  Wire.begin();
  I2C1.initialize(&Wire);
  MPU.initialize(&I2C1, MPU_DEFAULT_ADDRESS);

  MFS.initialize();
  MFS.write("Acc");
}


byte displayValues = true;
byte displayMode = 0;


void loop() {
  // put your main code here, to run repeatedly:

  byte btn = MFS.getButton();

  // Use button 1 to toggle reporting of sensor values.
  if (btn == BUTTON_1_PRESSED)
  {
    displayValues = !displayValues;
    
    if (displayValues)
    {
      displayHeading(displayMode);
    }
    else
    {
      MFS.write("Off");
    }
  }
  
  if (displayValues)
  {
    // Use button 2 to cycle though the display modes.
    if (btn == BUTTON_2_PRESSED)
    {
      displayMode++;
      
      if (displayMode == 3)
      {
        displayMode = 0;
      }
      
      displayHeading(displayMode);
    }
    
    if (displayMode == 0)
    {
      // display raw acceleration values.
      MPU.getAccelRaw();
      Serial.print((float)MPU.accel_X_Raw / MPU.accelScaleValue);
      Serial.print("\t");
      Serial.print((float)MPU.accel_Y_Raw / MPU.accelScaleValue);
      Serial.print("\t");
      Serial.print((float)MPU.accel_Z_Raw / MPU.accelScaleValue);
      Serial.print("\t\n");
    }
    else if (displayMode == 1)
    {
      // display raw gyrovalues
      MPU.getGyroRaw();
      Serial.print((float)MPU.gyro_X_Raw / MPU.gyroScaleValue);
      Serial.print("\t");
      Serial.print((float)MPU.gyro_Y_Raw / MPU.gyroScaleValue);
      Serial.print("\t");
      Serial.print((float)MPU.gyro_Z_Raw / MPU.gyroScaleValue);
      Serial.print("\t\n");
    }
    else if (displayMode == 2)
    {
      // display temperature value.
      Serial.println((float)MPU.getTemp10th() / 10);
    }
  }
  
  delay(50);
}


void displayHeading(byte mode)
{
  if (mode == 0)
  {
    Serial.println("Acceleration in g (1g = 9.8 m/s/s)");
    Serial.println("X\tY\tZ");
    MFS.write("Acc");
  }
  else if (mode == 1)
  {
    Serial.println("Gyro angular velocity in degrees / second");
    Serial.println("X\tY\tZ");
    MFS.write("Gyro");
  }
  else if (mode == 2)
  {
    Serial.println("Temperature in degrees celsius.");
    MFS.write("Te");
  }
}
