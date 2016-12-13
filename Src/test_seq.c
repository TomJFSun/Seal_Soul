/***
	File name:Test_Seq.c
	Create by:Tom
	date:2016/12/04
	version:v1.00
***/
#include "test_seq.h"
#include "short_test.h"



// Define Threshold (default)
#ifdef _REF3V3
	#define	Threshold1	300
	#define	Threshold2	550
	#define	Threshold3	762
	#define	Threshold4	943
	#define	Threshold5	1100
	#define	Threshold6	1238
	#define	Threshold7	1359
	#define	Threshold8	1467
	#define	Threshold9	1563
	#define	Threshold10	1650

#elif _REF2V5

	#define	Threshold1	227
	#define	Threshold2	417
	#define	Threshold3	577
	#define	Threshold4	714
	#define	Threshold5	833
	#define	Threshold6	938
	#define	Threshold7	1029
	#define	Threshold8	1111
	#define	Threshold9	1842
	#define	Threshold10	1250
	
#endif

#define	INA1_GAIN	200 // unit: 0.1G
#define INA2_GAIN	10	// unit: 0.1G
#define ADC_FULL_SCALE	6144	// FullScale, Unit: mV

#define _10M 0x03
#define _1M 0x02
#define _100K 0x01
#define _10K 0x00

#define _50UA 0x06 
#define _500UA 0x05
#define _5MA 0x04

/**
 * @function name:	DividerVaule
 * @brief	Calculate Resistor (rough)
 * @param	Vin -- Voltage input (mV)
 * @return	Res value, unit: 1Ω 
 * @author	Tom Sum
 * @date	Dec. 5th, 2016
**/
static uint32_t DividerResVal(uint8_t sel)
{
	uint32_t VolVal=0, res=0;
	uint16_t AdcVal;
	if (sel > 3) return 0xff; // error
	//USART_printf("DivideResVal\r\n");
	MeasuringSwitch(sel);
	delay_ms(5);
	ADS1115_GetADC(&UserI2c1, 1, &AdcVal);
	VolVal = (uint32_t)AdcVal * ADC_FULL_SCALE >> 15;
	VolVal = VolVal*10 / INA2_GAIN ;
	//USART_printf("DIV:Vol: %d Sel: %d\r\n", VolVal, sel);
	//USART_printf("Vol: %d Sel: %d\r\n", VolVal, sel);
	if( VolVal < Threshold1 ) return 0;
	else if( VolVal < Threshold2 ) res = 1;
	else if( VolVal < Threshold3 ) res = 2;
	else if( VolVal < Threshold4 ) res = 3;
	else if( VolVal < Threshold5 ) res = 4;
	else if( VolVal < Threshold6 ) res = 5;
	else if( VolVal < Threshold7 ) res = 6;
	else if( VolVal < Threshold8 ) res = 7;
	else if( VolVal < Threshold9 ) res = 8;
	else if( VolVal < Threshold10) res = 9;
	else res = 10;

	if( sel == _10M )				res *= 1000000;
	else if( sel == _1M )		res *= 100000;
	else if( sel == _100K )	res *= 10000;
	else if( sel == _10K)		res *= 1000;
	return res*10;
}

/**
 * @function name:	SRCResVal
 * @brief	Calculate Resistor (accurate)
 * @param	Vin -- Voltage input (mV)
 * @return	Res value, unit: 0.1Ω
 * @author	Tom Sum
 * @date	Dec. 5th, 2016
**/
static uint32_t SRCResVal(unsigned char sel)
{
	unsigned short AdcVal=0;
	unsigned long VolVal=0;
	unsigned long res;

	if (sel <4 || sel >6) return 0xff; // error
	MeasuringSwitch(sel);
	//delay_ms(500);
	ADS1115_GetADC(&UserI2c1, 0, (uint16_t *)&AdcVal);
	VolVal = (uint32_t)AdcVal * ADC_FULL_SCALE *10 >>15;	//unit: 0.1 mV
	VolVal = VolVal *10 / INA1_GAIN;
	//USART_printf("CURR:Vol: %d\r\nSel: %d\r\nADC: %d\r\n", VolVal, sel,AdcVal);
	if( VolVal < 50)	return 0;//50uA* 100Ω = 5mV
	if( sel == _50UA )
	{
		res = VolVal * 20;				//VolVal*1000/50
	}
	else if( sel == _500UA)
	{
		res = VolVal * 2;					//VolVal * 1000/500
	}
	else if( sel == _5MA)
	{
		res = VolVal /5;					//VolVal * 1000/5000;
	}
	return res;	
}


/**
 * @function name:	ResCalc
 * @brief	Res calculation in short test
 * @param	CalParam -- Vector of calibration params
 * @return	Res value 0.1Ω
 * @author	Tom Sum
 * @date	Dec. 4th, 2016
**/
unsigned long ResCalc(void* pParam)
{
	unsigned long res=0;
	// set res switch from 10kΩ to 10Ω to detect proper scale
	/* resister divider */
	// Select 10M scale
	res = DividerResVal(_10M);
	if(res >0) return res; // unit: 0.1Ω

	// Select 1M scale
	res = DividerResVal(_1M);
	if(res >0) return res;

	// Select 100k scale
	res = DividerResVal(_100K);
	if(res >0) return res;

	// Select 10k scale
	//res = DividerResVal(_10K);
	if(res >0) return res;

	// set res switch from 10kΩ to 10Ω to detect proper scale
	/* current source */
	// Select 50uA scale 100Ω - 1k
	res = SRCResVal(_50UA);
	if(res != 0) return res;

	// Select 50uA scale 10Ω - 100Ω
	res = SRCResVal(_500UA);
	if(res != 0) return res;

	// Select 500uA scale 1Ω - 10Ω
	res = SRCResVal(_5MA);
	return res; 
}




