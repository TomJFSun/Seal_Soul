
//name:adc.c
//by:yangjinjiang
//date:2016/11/09
//version:v1.00

#include "stm32l0xx_hal.h"
#include "adc.h"



static ADC_HandleTypeDef hadc;

unsigned char ADC_Init(void);
unsigned int GetADC16BitValue(unsigned int AdcChannel);



adc_interface UserAdc = {
	ADC_Init,
	GetADC16BitValue,
};




unsigned char ADC_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;


  /*
   *  Instance                  = ADC1.
   *  OversamplingMode          = Enabled
   *  .Oversample.Ratio         = x128
   *  .Oversample.RightBitShift = 3 bit shift
   *  .Oversample.TriggeredMode = single trigger (each trigger, all the oversampling series are performed).
   *  ClockPrescaler            = PCLK clock with no division.
   *  LowPowerAutoPowerOff      = Disabled (For this exemple continuous mode is enabled with software start)
   *  LowPowerFrequencyMode     = Enabled (To be enabled only if ADC clock is lower than 2.8MHz) 
   *  LowPowerAutoWait          = Disabled (New conversion starts only when the previous conversion is completed)       
   *  Resolution                = 12 bit (increased to 16 bit with oversampler)
   *  SamplingTime              = 7.5 cycles od ADC clock.
   *  ScanConvMode              = Upward 
   *  DataAlign                 = Right
   *  ContinuousConvMode        = Enabled
   *  DiscontinuousConvMode     = Enabled
   *  ExternalTrigConvEdge      = None (Software start)
   *  EOCSelection              = End Of Conversion event
   *  DMAContinuousRequests     = Disabled
   */	
	
  hadc.Instance = ADC1;		
  hadc.Init.OversamplingMode         = ENABLE;
  hadc.Init.Oversample.Ratio         = ADC_OVERSAMPLING_RATIO_128;
  hadc.Init.Oversample.RightBitShift = ADC_RIGHTBITSHIFT_3;
  hadc.Init.Oversample.TriggeredMode = ADC_TRIGGEREDMODE_SINGLE_TRIGGER;

  hadc.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;
  hadc.Init.LowPowerAutoPowerOff  = DISABLE;
  hadc.Init.LowPowerFrequencyMode = ENABLE;
  hadc.Init.LowPowerAutoWait      = DISABLE;

  hadc.Init.Resolution            = ADC_RESOLUTION_12B;
  hadc.Init.SamplingTime          = ADC_SAMPLETIME_7CYCLES_5;
  hadc.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  hadc.Init.ContinuousConvMode    = DISABLE;//ENABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
  hadc.Init.DMAContinuousRequests = DISABLE;	


  if(HAL_ADC_Init(&hadc) != HAL_OK)
  {
		return 0;
  }




  sConfig.Channel = ADC_CHANNEL_0;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;

  if(HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
		return 0;
  }
	
  ADC->CCR |= ADC_CCR_LFMEN;
  ADC->CCR |= ADC_CCR_TSEN;	
	ADC->CCR |= ADC_CCR_VREFEN;	
	
	if(HAL_ADC_Start(&hadc) != HAL_OK)
	{
		return 0;
	}	
	
  HAL_ADCEx_Calibration_Start(&hadc, ADC_SINGLE_ENDED);	
/*	
Bits 31:30 CKMODE[1:0]: ADC clock mode
These bits are set and cleared by software to define how the analog ADC is clocked:
00: ADCCLK (Asynchronous clock mode), generated at product level (refer to RCC section)
01: PCLK/2 (Synchronous clock mode)
10: PCLK/4 (Synchronous clock mode)
11: PCLK (Synchronous clock mode). This configuration must be enabled only if PCLK has a 50%
duty clock cycle (APB prescaler configured inside the RCC must be bypassed and the system clock must by 50% duty cycle)
In all synchronous clock modes, there is no jitter in the delay from a timer trigger to the start of a conversion.
Note: Software is allowed to write these bits only when the ADC is disabled (ADCAL=0, ADSTART=0,
ADSTP=0, ADDIS=0 and ADEN=0).

Bits 29:10 Reserved, must be kept at reset value.

Bits 9 TOVS: Triggered Oversampling
This bit is set and cleared by software.
0: All oversampled conversions for a channel are done consecutively after a trigger
1: Each oversampled conversion for a channel needs a trigger
Note: Software is allowed to write this bit only when ADSTART=0 (which ensures that no conversion is ongoing).

Bits 8:5 OVSS[3:0]: Oversampling shift
This bit is set and cleared by software.
0000: No shift
0001: Shift 1-bit
0010: Shift 2-bits
0011: Shift 3-bits
0100: Shift 4-bits
0101: Shift 5-bits
0110: Shift 6-bits
0111: Shift 7-bits
1000: Shift 8-bits
Other codes reserved	

Bits 4:2 OVSR[2:0]: Oversampling ratio
This bit filed defines the number of oversampling ratio.
000: 2x
001: 4x
010: 8x
011: 16x
100: 32x
101: 64x
110: 128x
111: 256x

Bit 1 Reserved, must be kept at reset value.
Bit 0 OVSE: Oversampler Enable
This bit is set and cleared by software.
0: Oversampler disabled
1: Oversampler enabled
*/	
	//ADC1->CFGR2 |= (1<<30);
	//ADC1->CFGR2 |= (3<<5);
	//ADC1->CFGR2 |= (6<<2);
	//ADC1->CFGR2 |= (1<<0);	
	
/*	
ADC1->ISR = 0x803
ADC1->IER = 0x1c
ADC1->CR = 0x10000005
ADC1->CFGR1 = 0x2000
ADC1->CFGR2 = 0x40000079
ADC1->SMPR = 0x1
ADC1->TR = 0xfff0000
ADC1->CHSELR = 0x10
ADC1->CALFACT = 0x3c	
*/

	
/*			NO INTERRUPT
	
ADC1->ISR = 0x81f
ADC1->IER = 0x0
ADC1->CR = 0x10000005
ADC1->CFGR1 = 0x2000					//á?D?×a??
ADC1->CFGR2 = 0x40000079
ADC1->SMPR = 0x1
ADC1->TR = 0xfff0000
ADC1->CHSELR = 0x10
ADC1->CALFACT = 0x3c	
	
*/

	return 1;
}


//ADC精度12位，扩展值为16位
unsigned int GetADC16BitValue(unsigned int AdcChannel)
{
	unsigned short value;


	ADC1->CHSELR = AdcChannel;

	if(HAL_ADC_Start(&hadc) != HAL_OK)
	{
		return 0;
	}
	if(HAL_ADC_PollForConversion(&hadc, 50) != HAL_OK)
	{
		return 0;
	}
	value = HAL_ADC_GetValue(&hadc);

	HAL_ADC_Stop(&hadc);

	/*
	ADC1->ISR &= ~(1<<2);
	ADC1->ISR &= ~(1<<4);	
	
	ADC1->CR |=  (1<<4);			//ADC Stop
	ADC1->CR &= ~(1<<0);			//ADC disabled	
	

	while(ADC1->ISR &(1<<2) == 0);		//1: Channel conversion complete	
	
	
	ADC1->ISR &= ~(1<<0);
	ADC1->CR &=  ~(1<<4);			//	
	ADC1->CR |=  (1<<0);			//ADC Start
	while(ADC1->ISR &(1<<0) == 0);		//ADC ready

	while(ADC1->ISR &(1<<4) == 0);		//1: Overrun has occurred*/

	return value;//ADC1->DR;	
}

//datasheet page27



#define TEMP130_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FF8007E))
#define TEMP30_CAL_ADDR ((uint16_t*) ((uint32_t) 0x1FF8007A))
#define VDD_CALIB ((uint16_t) (300))
#define VDD_APPLI ((uint16_t) (330))
int32_t ComputeTemperature(uint32_t measure)
{
	int32_t temperature;
	
	temperature = ((measure/16 * VDD_APPLI / VDD_CALIB)- (int32_t) *TEMP30_CAL_ADDR );
	temperature = temperature * (int32_t)(130 - 30);
	temperature = temperature / (int32_t)(*TEMP130_CAL_ADDR - (int32_t) *TEMP30_CAL_ADDR );
		
	temperature = temperature + 30;
	return(temperature);
}







