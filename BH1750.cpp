
#include "BH1750.h"

#define BH1750_I2C_ADDRESS (0x23)

void BH1750::begin(void)
{
  Wire.begin();
}

int BH1750::read(uint16_t *p_value)
{

  int i=0;
  int address = BH1750_I2C_ADDRESS ;
  byte buff[2];

  Wire.beginTransmission(address);
  Wire.write(0x10);
  Wire.endTransmission();
  delay(200);

  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while(Wire.available()) {
    buff[i] = Wire.read();
    i++;
  }
  Wire.endTransmission();

  if (i != 2) {
    return false ;
  }

  *p_value = ((buff[0]<<8)|buff[1])/1.2;
  return 0 ;
}




