
//name:battery.c
//by:yangjinjiang
//date:2016/11/09
//version:v1.00

#include "stm32l0xx_hal.h"
#include "adc.h"


#define	BAT_PULLUP_RES				100000
#define	BAT_PULLDOWN_RES			100000
#define	ADC_MAX								65520
#define	MCUWORK_VOL						3300


#define BAT_CHANNEL			ADC_CHANNEL_4


#define	VREFINT_CAL_ADDR			((uint16_t*) ((uint32_t)0x1FF80078))



/*
 OCV??????? 550mA??????????? 
  100%----4.20V 100%----4.20V 
  90%-----4.06V 90%-----3.97V 
  80%-----3.98V 80%-----3.87V 
  70%-----3.92V 70%-----3.79V
  60%-----3.87V 60%-----3.73V 
  50%-----3.82V 50%-----3.68V 
  40%-----3.79V 40%-----3.65V 
  30%-----3.77V 30%-----3.62V 
  20%-----3.74V 20%-----3.58V 
  10%-----3.68V 10%-----3.51V 
  5%------3.45V 5%------3.42V 
  0%------3.00V 0%------3.00V 


*/


const static unsigned short BAT_TABLE[][2] = {
	4170,99,
	4150,98,
	4130,97,
	4115,96,
	4100,95,
	4095,94,
	4090,93,
	4080,92,
	4070,91,	
	4060,90,
	4050,89,
	4040,88,
	4030,87,
	4025,86,
	4020,85,
	4015,84,	
	4010,83,
	4000,82,
	3990,81,
	3980,80,
	3975,79,		
	3970,78,		
	3960,77,
	3955,76,
	3950,75,
	3945,74,	
	3940,73,
	3935,72,
	3930,71,	
	3920,70,
	3915,69,
	3910,68,
	3905,67,
	3900,66,
	3895,65,
	3890,64,
	3885,63,
	3880,62,	
	3875,61,
	3870,60,
	3865,59,
	3860,58,
	3855,57,
	3850,56,
	3845,55,
	3840,54,
	3835,53,
	3830,52,
	3825,51,
	3820,50,
	3815,48,
	3810,46,	
	3805,45,
	3800,43,
	3795,42,
	3790,40,
	3780,35,	
	3770,30,
	3755,25,
	3740,20,
	3710,15,
	3680,10,
	3640,8,
	3600,6,
	3550,4,
	3500,2,
	3450,0,
};


unsigned char GetBatLevel(unsigned short value)
{
	unsigned char i;
	unsigned char ret;

	ret = 0;
	
	for(i=0;i<sizeof(BAT_TABLE)/4;i++)
	{

		if(value >= BAT_TABLE[i][0])
		{
			ret = BAT_TABLE[i][1];
			break;
		}
	}
	return ret;
}

unsigned short GetBatVoltage(adc_interface *pAdc)
{
	unsigned int Voltage;					//3500-4200
	
	Voltage = pAdc->GetAdc(BAT_CHANNEL);
	Voltage = Voltage*((BAT_PULLUP_RES+BAT_PULLDOWN_RES)/BAT_PULLDOWN_RES)*MCUWORK_VOL/ADC_MAX;
	
	//Voltage = Voltage*1053/1000;	
	return (unsigned short)Voltage;
}
	
unsigned short GetDCVoltage(adc_interface *pAdc)
{
	unsigned int Voltage;
	
	Voltage = pAdc->GetAdc(ADC_CHANNEL_1);
	Voltage = Voltage*2*MCUWORK_VOL/ADC_MAX;
		
	return (unsigned short)Voltage;
}


unsigned char BatDisplayLevel(adc_interface *pAdc)
{
	unsigned char per;
	
	if(GetDCVoltage(pAdc) >= 4300)
	{
		return 6;
	}
	per = GetBatLevel(GetBatVoltage(pAdc));
	
	if(per >= 85)
	{
		return 5;
	}
	if(per >= 70)
	{
		return 4;
	}
	if(per >= 50)
	{
		return 3;
	}	
	if(per >= 30)
	{
		return 2;
	}
	if(per >= 10)
	{
		return 1;
	}
	return 0;
}

/*
unsigned short GetVref(adc_interface *pAdc)
{
	unsigned int Voltage;	
	unsigned short *pVerf;
	
	pVerf = VREFINT_CAL_ADDR;
	Voltage = pAdc->GetAdc(ADC_CHANNEL_17);	
	
	//1670-----1200	
	USART2_printf("aaaa = %d,%d\r\n",*pVerf,Voltage);		

	Voltage = 3000*(*pVerf*16)/Voltage;	
	
	return (unsigned short)Voltage;
}
*/

