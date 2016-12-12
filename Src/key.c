//name:key.c
//by:yangjinjiang
//date:2016/11/05
//version:v1.00

#include "stm32l0xx_hal.h"
#include "key.h"



unsigned char KeyValue = 0;
unsigned char Key1DownFlag = 0;
unsigned short Key1DownCount = 0;
unsigned char KeyDemoOnOff = 0;
unsigned char KeyDown2SFlag = 0;

extern unsigned char TimeFlag_10ms;

void KeyInit(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct;
	
  //Configure GPIO pins : PC13
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;//GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);	
	
	
  HAL_NVIC_SetPriority(EXTI4_15_IRQn,3,0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);	
	
}


void EXTI_Key_IRQHandle(void)
{
	if((KEY_PORT->IDR & KEY1_PIN) == 0)
	{
		EXTI->PR = KEY1_PIN;
		KeyValue |= KEY1_DOWN;
		Key1DownFlag = 1;
	}
	else
	{
		EXTI->PR = KEY1_PIN;
		KeyValue |= KEY1_UP;
		Key1DownFlag = 0;	

	}
}



#include "pwm_tim2.h"

unsigned char SmoothState = 0;

unsigned char SmoothRgb[3];
unsigned char SmoothCount=0;
unsigned int SmoothDelay=0;


void SetRGB(unsigned char* rgb_data)
{
	UserPWM.SetR(rgb_data[0]);
	UserPWM.SetG(rgb_data[1]);
	UserPWM.SetB(rgb_data[2]);	
}


//R-G-B demo

void ModeSmooothProcess(void)
{
	switch(SmoothState)
	{
	case 0:
		if(SmoothCount<0xff)
		{
			SmoothRgb[0] = 0xff-SmoothCount;
			SmoothRgb[1]	= SmoothCount;
			SmoothRgb[2]	= 0;
			SetRGB(SmoothRgb);
			SmoothCount++;
		}
		else
		{
			SmoothCount = 0;				
			SmoothDelay = 0;
			SmoothState++;
		}
		break;
	case 1:
		if(SmoothCount<0xff)
		{
			SmoothRgb[0] = 0;
			SmoothRgb[1]	= 0xff-SmoothCount;
			SmoothRgb[2]	= SmoothCount;
			SetRGB(SmoothRgb);
			SmoothCount++;
		}
		else
		{
			SmoothCount = 0;				
			SmoothDelay = 0;
			SmoothState++;
		}
		break;
	case 2:
		if(SmoothCount<0xff)
		{
			SmoothRgb[0] = SmoothCount;
			SmoothRgb[1]	= 0;
			SmoothRgb[2]	= 0xff-SmoothCount;
			SetRGB(SmoothRgb);
			SmoothCount++;
		}
		else
		{
			SmoothCount = 0;				
			SmoothDelay = 0;
			SmoothState = 0;
		}
		break;
	}
}





void KeyProcess(void)
{
	if(KeyValue & KEY1_DOWN && KeyValue & KEY1_UP)
	{
		KeyValue &= ~(KEY1_DOWN);	
		KeyValue &= ~(KEY1_UP);
		Key1DownCount = 0;	
		if(KeyDemoOnOff == 0)
		{
			KeyDemoOnOff = 1;
		}
		else
		{
			KeyDemoOnOff = 0;
			UserPWM.SetR(0);
			UserPWM.SetG(0);
			UserPWM.SetB(0);
		}		
	}
	if(TimeFlag_10ms)
	{
		TimeFlag_10ms = 0;
		if(Key1DownFlag)
		{
			Key1DownCount++;
		}				
		if(KeyDemoOnOff)
		{
			ModeSmooothProcess();
		}
	}	
	if(Key1DownFlag)
	{
		if(Key1DownCount >= 200)			//2s
		{
			KeyDown2SFlag = 1;
		}
	}
}






