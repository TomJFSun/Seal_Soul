
#ifndef _CAT9555_H
#define _CAT9555_H

#include "gpio_i2c.h"


typedef unsigned char (*extport_init)(i2c_interface* pI2C);
typedef unsigned char (*extport_channel)(i2c_interface* pI2C,unsigned char channel);


typedef struct{
	extport_init			Init;
	extport_channel		ExtAdc1;
	extport_channel		ExtAdc2;
	extport_channel		MeasuringSwtch;
	
}cat9555_interface;

extern cat9555_interface UserExtPort;

#endif		//_CAT9555_H


