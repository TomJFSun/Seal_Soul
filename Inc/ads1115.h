#ifndef _ADS1115_H
#define _ADS1115_H


unsigned char ADS1115_GetADC(i2c_interface* pI2C,unsigned char channel,unsigned short* pValue);

#endif	//_ADS1115_H
