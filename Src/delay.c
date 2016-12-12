

#include "stm32l0xx_hal.h"


void delay_us(unsigned char us)
{
	unsigned short count = SystemCoreClock/1000000/3*us;

	while(count != 0)
	{
		count--;
	}	
}


void delay_1ms(void)
{
	unsigned short count = SystemCoreClock/1000/3;

	while(count != 0)
	{
		count--;
	}	
}




void delay_ms(unsigned short ms)
{
	while(ms)
	{
		delay_1ms();
		ms--;
	}
}





