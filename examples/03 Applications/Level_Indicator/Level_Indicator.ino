#define _SOFTI2C_H
#include <SoftI2CMaster.h>
#include <Wire.h>
#include <TimerOne.h>
#include <MultiFuncShield.h>

#include "SoftwareI2C.h"
#include "I2C.h"
#include "MPU6050.h"

#define SOFTWARE_I2C

void calibrate();

MPU6050 MPU;

const float radToDeg = 180.0 / 3.1415926535897932384626433832795;
int xOffset=0, yOffset=0;
float zScaleOffset = 1; // multiply Z axis with this value to get as close to 1g as possible.


void setup() {
  // put your setup code here, to run once:
  Timer1.initialize();

#if defined (SOFTWARE_I2C)
  // Use software I2C
  // Uno and Leonardo, use pin 5 for SCL and 6 for SDA. Mega2560, use pin 5 for SCL and pin A5 for SDA.
  SoftI2C1.initialize();
  MPU.initialize(&SoftI2C1, MPU_DEFAULT_ADDRESS << 1, ACCEL_FS_2, GYRO_FS_250, DLPF_BW_5);
#else
  // Use hardware I2C
  Wire.begin();
  I2C1.initialize(&Wire);
  MPU.initialize(&I2C1, MPU_DEFAULT_ADDRESS, ACCEL_FS_2, GYRO_FS_250, DLPF_BW_5);
#endif

  MFS.initialize(&Timer1);
}

void loop() {
  // put your main code here, to run repeatedly:

  byte btn = MFS.getButton();
  
  if (btn == BUTTON_1_LONG_PRESSED)
  {
    calibrate();
  }
  
  MPU.getAccelRaw();
  
  MPU.accel_X_Raw -= xOffset;
  MPU.accel_Y_Raw -= yOffset;
  
  float angle;
  
  if (MPU.accel_Z_Raw == 0)
  {
    angle = 90;
  }
  else
  {
    angle = atan((float)MPU.accel_Y_Raw / (MPU.accel_Z_Raw * zScaleOffset)) * radToDeg;  // calculate for y axis
    //angle = atan((float)MPU.accel_X_Raw / (MPU.accel_Z_Raw * zScaleOffset)) * radToDeg;    // calculate for X axis
  }
  MFS.write(angle, 1);
  delay(200);
}


void calibrate()
{
  MFS.write("    ");
  MFS.writeLeds(LED_1, ON);
  MFS.blinkLeds(LED_1, ON); 
  
  // discard first few sensor readings.
  for (int i=0; i<10; i++)
  {
    MPU.getAccelRaw();
    delay(10);
  }
  
  int xValues[5], yValues[5], zValues[5];
  
  for (int i=0; i<5; i++)
  {
    MPU.getAccelRaw();
    xValues[i] = MPU.accel_X_Raw;
    yValues[i] = MPU.accel_Y_Raw;
    zValues[i] = MPU.accel_Z_Raw;
    delay(300);
  }
  xOffset = MedianOf5(xValues[0], xValues[1], xValues[2], xValues[3], xValues[4]);
  yOffset = MedianOf5(yValues[0], yValues[1], yValues[2], yValues[3], yValues[4]);

  zScaleOffset = (float)MPU.accelScaleValue / MedianOf5(zValues[0], zValues[1], zValues[2], zValues[3], zValues[4]);
  
  MFS.blinkLeds(LED_1, OFF);
  
  // clear the input button buffer by reading it and discarding value.
  for (int i=0; i<10; i++)
  {
    MFS.getButton();
  }
}
