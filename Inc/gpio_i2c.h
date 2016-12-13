

#ifndef _GPIO_I2C_H
#define _GPIO_I2C_H


typedef void (*i2c_init)(void);
typedef unsigned char (*i2c_rw)(unsigned char DeviceAddr, unsigned char RegisterAddr,unsigned char* pBuffer,unsigned int NumByte);


typedef struct{
	i2c_init	Init;
	i2c_rw		Read;
	i2c_rw		Write;
}i2c_interface;

extern i2c_interface UserI2c1;



#endif		//_GPIO_I2C_H


