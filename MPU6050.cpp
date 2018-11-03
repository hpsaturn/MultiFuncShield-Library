#include "MPU6050.h"

const unsigned int accelScaleValues[4] = {16384, 8192, 4096, 2048};
const float gyroScaleValues[4] = {131.072, 65.536, 32.768, 16.384};

void MPU6050::initialize(II2C *i2cInstance, byte addr, byte accelScale, byte gyroScale, byte dlpf)
{
  _devAddr = addr;
  i2c = i2cInstance;

  if (accelScale > 3)
  {
    accelScale = 3;
  }
  accelScaleValue = accelScaleValues[accelScale];
  
  if (gyroScale > 3)
  {
    gyroScale = 3;
  }
  gyroScaleValue = gyroScaleValues[gyroScale];

  if (dlpf > 7)
  {
    dlpf = 7;
  }  

  // Disable sleep
  i2c->writeBit(_devAddr, RA_PWR_MGMT_1, PWR1_SLEEP_BIT, 0);
  
  //Sets sample rate to 8000/1+7 = 1000Hz
  i2c->writeRegister(addr, RA_SMPLRT_DIV, 0x07);
  
  //Disable FSync, 256Hz DLPF
  i2c->writeRegister(addr, RA_CONFIG, 0x00);
  //Disable gyro self tests, scale of 500 degrees/s
  i2c->writeRegister(addr, RA_GYRO_CONFIG, 0x08);
  //Disable accel self tests, scale of +-2g, no DHPF
  i2c->writeRegister(addr, RA_ACCEL_CONFIG, 0x00);
  //Freefall threshold of |0mg|
  i2c->writeRegister(addr, RA_FF_THR, 0x00);
  //Freefall duration limit of 0
  i2c->writeRegister(addr, RA_FF_DUR, 0x00);
  //Motion threshold of 0mg
  i2c->writeRegister(addr, RA_MOT_THR, 0x00);
  //Motion duration of 0s
  i2c->writeRegister(addr, RA_MOT_DUR, 0x00);
  //Zero motion threshold
  i2c->writeRegister(addr, RA_ZRMOT_THR, 0x00);
  //Zero motion duration threshold
  i2c->writeRegister(addr, RA_ZRMOT_DUR, 0x00);
  //Disable sensor output to FIFO buffer
  i2c->writeRegister(addr, RA_FIFO_EN, 0x00);
  
  // set clock source
  i2c->writeBits(addr, RA_PWR_MGMT_1, PWR1_CLKSEL_BIT, PWR1_CLKSEL_LENGTH, CLOCK_PLL_XGYRO);
  // set Gyro scale
  i2c->writeBits(addr, RA_GYRO_CONFIG, GCONFIG_FS_SEL_BIT, GCONFIG_FS_SEL_LENGTH, gyroScale);
  // set Accel scale
  i2c->writeBits(addr, RA_ACCEL_CONFIG, ACONFIG_AFS_SEL_BIT, ACONFIG_AFS_SEL_LENGTH, accelScale);
  // set low pass filter
  i2c->writeBits(addr, RA_CONFIG, CFG_DLPF_CFG_BIT, CFG_DLPF_CFG_LENGTH, dlpf);
}


// --------------------------------------------------------------------------------
void MPU6050::getAccelRaw()
{
  byte buffer[6];
  
  i2c->readRegister(_devAddr, RA_ACCEL_XOUT_H, buffer, sizeof(buffer));
  accel_X_Raw = (int)((buffer[0]) << 8) | buffer[1];
  accel_Y_Raw = (int)((buffer[2]) << 8) | buffer[3];
  accel_Z_Raw = (int)((buffer[4]) << 8) | buffer[5];
}


// --------------------------------------------------------------------------------
void MPU6050::getGyroRaw()
{
  byte buffer[6];
  
  i2c->readRegister(_devAddr, RA_GYRO_XOUT_H, buffer, sizeof(buffer));
  gyro_X_Raw = (int)((buffer[0]) << 8) | buffer[1];
  gyro_Y_Raw = (int)((buffer[2]) << 8) | buffer[3];
  gyro_Z_Raw = (int)((buffer[4]) << 8) | buffer[5];
}


// --------------------------------------------------------------------------------
int MPU6050::getTemp10th()
{
  byte buffer[2];
  
  i2c->readRegister(_devAddr, RA_TEMP_OUT_H, buffer, sizeof(buffer));
  return ((long)(((int)((buffer[0]) << 8) | buffer[1]) + 12412) * 241) >> 13;
}

