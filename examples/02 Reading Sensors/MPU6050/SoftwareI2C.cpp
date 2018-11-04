#if defined(__AVR_ATmega328P__)
  // digital pin 5
  #define SCL_PIN  5
  #define SCL_PORT PORTD
  // digital pin 6
  #define SDA_PIN  6
  #define SDA_PORT PORTD
  
#elif defined(__AVR_ATmega32U4__)
  // digital pin 5
  #define SCL_PIN  6
  #define SCL_PORT PORTC
  // digital pin 6
  #define SDA_PIN  7
  #define SDA_PORT PORTD

#elif defined(__AVR_ATmega2560__)
  // digital pin 5
  #define SCL_PIN  3
  #define SCL_PORT PORTE
  // Analog pin 5
  #define SDA_PIN  5
  #define SDA_PORT PORTF 
  
#endif

//#define I2C_NOINTERRUPT  1
#define I2C_TIMEOUT      20

#include "SoftwareI2C.h"
#include <SoftI2CMaster.h>

SoftI2C SoftI2C1;


void SoftI2C::initialize()
{
  i2c_init();
}


// --------------------------------------------------------------------------------
byte SoftI2C::writeByte(byte devAddress, byte data, byte holdBus)
{
  if (!i2c_start(devAddress | I2C_WRITE))
  {
    return 0;
  }
  if (!i2c_write(data)) 
  {
    i2c_stop();
    return 0;
  }
  
  i2c_stop();
  
  return 1;
}


// --------------------------------------------------------------------------------
byte SoftI2C::writeBytes(byte devAddress, byte *data, byte dataSize)
{
  if (!i2c_start(devAddress | I2C_WRITE))
  {
    return 0;
  }
  
  for (int i=0; i < dataSize; i++)
  {
    if (!i2c_write(data[i])) 
    {
      i2c_stop();
      return 0;
    }
  }
  
  i2c_stop();
  
  return 1;
}


// --------------------------------------------------------------------------------
byte SoftI2C::readByte(byte devAddress, byte *data)
{
  if (!i2c_start(devAddress | I2C_READ))
  {
    return 0;
  }
  
  *data = i2c_read(true);
  
  i2c_stop();
  
  return 1;
}


// --------------------------------------------------------------------------------
byte SoftI2C::readBytes(byte devAddress, byte *data, byte dataSize)
{
  if (dataSize == 0)
  {
    return 0;
  }
  
  if (!i2c_start(devAddress | I2C_READ))
  {
    return 0;
  }
  
  int i=0;
  for (; i < dataSize-1; i++)
  {
    data[i] = i2c_read(false);
  }

  data[i] = i2c_read(true);  
  
  i2c_stop();
  
  return 1;
}



