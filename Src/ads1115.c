//name:ads1115.c
//by:yangjinjiang
//date:2016/11/14
//version:v1.00

#include "gpio_i2c.h"




#define ADS1115_ADDR 0x90 




unsigned char ADS1115_GetADC(i2c_interface* pI2C,unsigned char channel,unsigned short* pValue)
{
	unsigned char select;
	unsigned char buf[2];
	unsigned char ret;
	
	if(channel > 3)
		return 0;

	select = 0xc0+(channel<<4);
	buf[0] = select;
	buf[1] = 0xE3;

	ret = pI2C->Write(ADS1115_ADDR,0x01,buf,2);
	if(ret == 0)
		return 0;
	delay_ms(2);
	ret = pI2C->Read(ADS1115_ADDR,0x00,buf,2);
	*pValue = buf[0]<<8 | buf[1];
	
	return ret;
}



