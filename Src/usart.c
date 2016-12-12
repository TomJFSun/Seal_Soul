
//name:usart.c
//by:yangjinjiang
//date:2016/11/05
//version:v1.00

#include "stm32l0xx_hal.h"
#include "usart.h"
#include <stdarg.h>

UART_HandleTypeDef UartHandle;
unsigned char UartTxBuffer[256];


void USART_Init(void)
{

  UartHandle.Instance = UARTPORT;
  UartHandle.Init.BaudRate = 115200;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits = UART_STOPBITS_1;
  UartHandle.Init.Parity = UART_PARITY_NONE;
  UartHandle.Init.Mode = UART_MODE_TX_RX;
  UartHandle.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
  UartHandle.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  UartHandle.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  HAL_UART_Init(&UartHandle);

}



unsigned char itoh(long n,unsigned char* p)
{
	unsigned char buf[8];
	unsigned char i,j;	
	
	i=0;
	do
	{
		buf[i] = n&0x0f;
		if(buf[i] > 9)
		{
			buf[i] += 'a'-10;
		}
		else
		{
			buf[i] += '0';
		}
		i++;		
	}
	while((n>>=4)>0);	
	
	for(j=0;j<i;j++)
	{
		p[j] = buf[i-j-1];	
	}
	return i;
}

unsigned char itoa(long n,unsigned char* p)
{
	unsigned char i,j;
	unsigned char buf[10];
	unsigned char flag = 0;
	
	if(n < 0)
	{
		n = -n;
		flag = 1;
	}
	i=0;
	do
	{
		 buf[i++]=n%10+'0';
	}
	while((n/=10)>0);
	
	if(flag)
	{
		*p = '-';
		p++;
	}
	for(j=0;j<i;j++)
	{
		p[j] = buf[i-j-1];	
	}
	if(flag)
	{
		i++;
	}
	return i;
}


void USART_printf(unsigned char *Data,...)
{
	int d;   
	unsigned char bytes;
	unsigned char* pBuffer;
	unsigned short count;

	va_list ap;
	va_start(ap, Data);
	
	pBuffer = UartTxBuffer;
	count = 0;

	while(*Data != 0)
	{				                          
		if(*Data == '%')
		{
			switch(*++Data)
			{				
			case 'd':
				d = va_arg(ap, int);
				bytes = itoa(d,pBuffer);
				pBuffer += bytes;
				count += bytes;
				Data++;
				break;
			
			case 'x':
				d = va_arg(ap, int);
				bytes = itoh(d,pBuffer);
				pBuffer += bytes;
				count += bytes;
				Data++;
				break;			
			
			
			default:
				Data++;
				break;
			}		 
		}
		else
		{
			*pBuffer++ = *Data++;
			count++;
		}
	}
	HAL_UART_Transmit(&UartHandle,UartTxBuffer,count,500);
}
