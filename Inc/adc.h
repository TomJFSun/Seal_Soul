#ifndef _ADC_H
#define _ADC_H


typedef unsigned char (*adc_init)(void);
typedef unsigned int (*adc_getadc)(unsigned int AdcChannel);

typedef struct{
	adc_init			Init;
	adc_getadc		GetAdc;
	
}adc_interface;

extern adc_interface UserAdc;
extern unsigned short McuAdcPer;

#endif	//_ADC_H
