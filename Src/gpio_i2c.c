
//name:gpio_i2c.c
//by:yangjinjiang
//date:2016/11/03
//version:v1.00

#include "stm32l0xx_hal.h"
#include "gpio_i2c.h"


void I2C_Init(void);
unsigned char I2C_WriteData(unsigned char Device,unsigned char Register,unsigned char* pBuffer,unsigned int NumByte);
unsigned char I2C_ReadData(unsigned char Device,unsigned char Register,unsigned char* pBuffer,unsigned int NumByte);



#define I2C_PORT_SCL1		(GPIOB)
#define SCL1_PIN				(GPIO_PIN_8)

#define I2C_PORT_SDA1		(GPIOB)
#define SDA1_PIN				(GPIO_PIN_9)


#define	GPIO_I2C1_SDA_OUTPUT	GPIOB->MODER |=  (1<<18)
#define	GPIO_I2C1_SDA_INPUT		GPIOB->MODER &= ~(3<<18)


i2c_interface UserI2c1 = {
	I2C_Init,
	I2C_ReadData,
	I2C_WriteData,
};


void SCL_0(void)
{
	I2C_PORT_SCL1->BRR = SCL1_PIN;
}


void SCL_1(void)
{
	//I2C_PORT_SCL1->ODR |=  SCL1_PIN;
	I2C_PORT_SCL1->BSRR = SCL1_PIN;
}


void SDA_0(void)
{
	//I2C_PORT_SDA1->ODR &= ~SDA1_PIN;
	I2C_PORT_SDA1->BRR = SDA1_PIN;
}


void SDA_1(void)
{
	I2C_PORT_SDA1->BSRR = SDA1_PIN;
}


unsigned char SDA_DATA(void)
{
	if(I2C_PORT_SDA1->IDR & SDA1_PIN)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


void I2C_Init(void)
{

	GPIOB->MODER |=  (1<<16);
	GPIOB->MODER |=  (1<<18);

	GPIOB->OSPEEDR |=  (2<<16);
	GPIOB->OSPEEDR |=  (2<<18);	

	GPIOB->PUPDR &= ~(3<<16);
	//GPIOB->PUPDR |=  (1<<16);			//Pull-up
	GPIOB->PUPDR &= ~(3<<18);
	//GPIOB->PUPDR |=  (1<<18);			//Pull-up

	GPIOB->ODR |=  GPIO_PIN_8;
	GPIOB->ODR |=  GPIO_PIN_9;	

}


void I2C_Delay(void)
{
	//消耗80个时钟周期
	unsigned char conut = 20;

	while(conut != 0)
	{
		conut--;
	}

}

void I2C_Start(void)
{
	SDA_1();
	SCL_1();
	I2C_Delay();	
	SDA_0();
	I2C_Delay();
	SCL_0();
	I2C_Delay();	
}


void I2C_Stop(void)
{
	SDA_0();
	SCL_0();
	I2C_Delay();
	SCL_1();
	I2C_Delay();
	SDA_1();
	I2C_Delay();
}


void I2C_SendAck(void)
{
	SDA_0();
	SCL_1();
	I2C_Delay();
	SCL_0();
	I2C_Delay();	
}


void I2C_SendNoAck(void)
{
	SDA_1();
	SCL_1();
	I2C_Delay();
	SCL_0();
	I2C_Delay();	
}



unsigned char I2C_WaitAck(void)
{

	unsigned char Ack;
	SDA_1();
	SCL_1();  
	GPIO_I2C1_SDA_INPUT;
	I2C_Delay();
	Ack = SDA_DATA();
	SCL_0();
	GPIO_I2C1_SDA_OUTPUT;	
	I2C_Delay();
	if(Ack)
		return 0;
	return 1;

}




unsigned char I2C_SendByte(unsigned char dat)
{
	unsigned char i;

	for(i=0;i<8;i++)
	{
		if(dat & 0x80)
		{
			SDA_1();
		}
		else 
		{
			SDA_0();
		}
		SCL_1();
		I2C_Delay();
		SCL_0(); 
		dat <<= 1;		
		I2C_Delay();		
	}
	return I2C_WaitAck();

}

void I2C_RcvDat(unsigned char *pRdDat)
{
	unsigned char i;

	
	SDA_1();
	GPIO_I2C1_SDA_INPUT;
	for(i=0;i<8;i++)
	{
		SCL_1();
		I2C_Delay(); 
		*pRdDat<<=1;
		if(SDA_DATA())
		{
			*pRdDat|=1;
		}
		SCL_0();
		I2C_Delay();
	}
	GPIO_I2C1_SDA_OUTPUT;	
}


void I2C_ReceiveBytes(unsigned char *pBuffer,unsigned char bytes)
{
	unsigned char i;

	for(i=0;i<bytes;i++)
	{
		I2C_RcvDat(pBuffer+i);

		if(i==bytes-1)
		{
			I2C_SendNoAck();
		}
		else
		{
			I2C_SendAck();	
		}
	}
}


unsigned char I2C_WriteData(unsigned char DeviceAddr, unsigned char RegisterAddr,unsigned char* pBuffer,unsigned int NumByte)
{
	unsigned char ret = 0;
	unsigned char i;

	I2C_Start();
	
	if(I2C_SendByte(DeviceAddr) == 0)
	{
		goto write_end;		
	}
	if(I2C_SendByte(RegisterAddr) == 0)
	{
		goto write_end;		
	}
	for(i=0;i<NumByte;i++)
	{
		if(I2C_SendByte(pBuffer[i]) == 0)
		{
			goto write_end;
		}	
	}
	ret = 1;
write_end:
	I2C_Stop();
	return ret;
}




unsigned char I2C_ReadData(unsigned char DeviceAddr, unsigned char RegisterAddr,unsigned char* pBuffer,unsigned int NumByte)
{
	unsigned char ret = 1;

	I2C_Start();
	
	if(I2C_SendByte(DeviceAddr) == 0)
	{
		ret = 0;
		goto read_end;
	}
	if(I2C_SendByte(RegisterAddr) == 0)
	{
		ret = 0;
		goto read_end;
	}			
	I2C_Start();
	if(I2C_SendByte(DeviceAddr|1) == 0)
	{
		ret = 0;
		goto read_end;
	}
	I2C_ReceiveBytes(pBuffer,NumByte);

read_end:
	I2C_Stop(); 
	return ret;
}




