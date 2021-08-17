#ifndef II2C_h_
#define II2C_h_

// This class defines an interface for I2C implementation.
class II2C
{
  public:
  
  virtual byte writeByte(byte devAddress, byte data, byte holdBus = false);
  virtual byte writeBytes(byte devAddress, byte *data, byte dataSize);
  virtual byte readByte(byte devAddress, byte *data);
  virtual byte readBytes(byte devAddress, byte *data, byte dataSize);
  
  // --------------------------------------------------------------------------
  
  byte writeRegister(byte devAddress, byte reg, byte data)
  {
    byte cmd[2] = {reg, data};
  
    return writeBytes(devAddress, cmd, sizeof(cmd));
  };
  
  
  byte readRegister(byte devAddress, byte reg, byte *data, byte dataSize = 1)
  {
    if (!writeByte(devAddress, reg, true))
    {
      return 0;
    }
    if (!readBytes(devAddress, data, dataSize))
    {
      return 0;
    }
    return 1;
  };
  
  
  byte writeBits(byte devAddress, byte regAddr, byte bitStart, byte bitLength, byte data)
  {
    byte b;
    if (!readRegister(devAddress, regAddr, &b))
    {
      return 0;
    }
    
    byte mask = (byte)(((1 << bitLength) - 1) << (bitStart - bitLength + 1));
    data <<= (bitStart - bitLength + 1);   // shift data into correct position
    data &= mask;                       // zero all non-important bits in data
    b &= (byte)~(mask);                 // zero all important bits in existing byte
    b |= data;                          // combine data with existing byte
    
    if (!writeRegister(devAddress, regAddr, b))
    {
      return 0;
    }
    return 1;
  };
  
  
  byte writeBit(int devAddress, byte regAddr, byte bitNum, byte data)
  {
    byte b;
    if (!readRegister(devAddress, regAddr, &b))
    {
      return 0;
    }
    
    b = (byte)((data != 0) ? (b | (1 << bitNum)) : (b & ~(1 << bitNum)));
    
    if (!writeRegister(devAddress, regAddr, b))
    {
      return 0;
    }
    return 1;
  };
};

#endif

