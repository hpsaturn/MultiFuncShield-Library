#ifndef I2C_h_
#define I2C_h_


#include "Arduino.h"
#include "II2C.h"
#include <Wire.h>

// This class provides a wrapper for the Wire library.
class I2C : public II2C
{
  public:
  
  void initialize(TwoWire *wire);
  byte writeByte(byte devAddress, byte data, byte holdBus = false);
  byte writeBytes(byte devAddress, byte *data, byte dataSize);
  byte readByte(byte devAddress, byte *data);
  byte readBytes(byte devAddress, byte *data, byte dataSize);
  
  private:
  TwoWire *wire;
};

extern I2C I2C1;

#endif
