#include "I2C.h"

I2C I2C1;
  
void I2C::initialize(TwoWire *wireInstance)
{
  wire = wireInstance;
}

// --------------------------------------------------------------------------------
byte I2C::writeByte(byte devAddress, byte data, byte holdBus)
{
  byte retval = 1;

  wire->beginTransmission(devAddress);
  if (!wire->write(data))
  {
    retval = 0;
  }
  wire->endTransmission(!holdBus);
  
  return retval;
}


// --------------------------------------------------------------------------------
byte I2C::writeBytes(byte devAddress, byte *data, byte dataSize)
{
  byte retval = 1;
  
  wire->beginTransmission(devAddress);

  if (!wire->write(data, dataSize))
  {
    retval = 0;
  }
  wire->endTransmission();
  return retval;
}


// --------------------------------------------------------------------------------
byte I2C::readByte(byte devAddress, byte *data)
{
  byte retval = 1;
  wire->requestFrom((int)devAddress, (int) 1, (int)true);
  if (wire->available())
  {
    *data = wire->read();
  }
  else
  {
    retval = 0;
  }
  return retval;
}


// --------------------------------------------------------------------------------
byte I2C::readBytes(byte devAddress, byte *data, byte dataSize)
{
  byte retval = 1;
  wire->requestFrom((int)devAddress, (int)dataSize, (int)true);
  
  int i=0;
  for (; wire->available() && i<dataSize; i++)
  {
    data[i] = wire->read();
  }
  
  if (i != dataSize)
  {
    retval = 0;
  }
  return retval;
}
