#ifndef SOFTI2C_h_
#define SOFTI2C_h_

#include "Arduino.h"
#include "II2C.h"

// This class provides a wrapper for the software I2C library.
class SoftI2C : public II2C
{
  public:
  
  void initialize();
  byte writeByte(byte devAddress, byte data, byte holdBus = false);
  byte writeBytes(byte devAddress, byte *data, byte dataSize);
  byte readByte(byte devAddress, byte *data);
  byte readBytes(byte devAddress, byte *data, byte dataSize);
};


extern SoftI2C SoftI2C1;

#endif
