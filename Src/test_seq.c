/***
	File name:Test_Seq.c
	Create by:yangjinjiang
	date:2016/11/05
	version:v1.00
***/

#include "main.h"
#include "test_seq.h"
#include "stm32l0xx_hal.h"
#include "cat9555.h"
#include "ads1115.h"
#include "elec_sw.h"
#include "test_seq.h"
#include "usart.h"
#include "delay.h"

#define ExtAdcCh1Sel(ch) (UserExtPort.ExtAdc1(&UserI2c1, ch))
#define ExtAdcCh2Sel(ch) (UserExtPort.ExtAdc2(&UserI2c1, ch))

/*------------------- Short Test---------------*/

void ShortInit(void);
unsigned char ShortForceSet(unsigned char ch1, unsigned char ch2, unsigned char port);
unsigned char ShortSenseSet(unsigned char ch1, unsigned char ch2, unsigned char port);
unsigned char ShortEnableSet(uint8_t IsEn);
unsigned long ResCalc(void);




TestCycle Short_TestCycle ={
	ShortInit,			/*Init*/
	ShortForceSet,	/*ForceSet*/
	ShortSenseSet,	/*SenseSet*/
	ShortEnableSet,	/*EnaleSet*/		
	ResCalc,				/*ResCalc*/	
};


/**
 * @function name:	ShortInit
 * @brief	Init AMUX Matrix to switch to NC
 * @param	void
 * @return	void
 * @author	Tom Sum
 * @date	Dec. 4th, 2016
**/
void ShortInit(void)
{
	// Disable enable pin for all switchs
	AmuxDisableAll();
	// Reset AMUX to NC(S7)
	VoltageEnable(48);
	ResistanceEnable(48);
	ExtAdcCh1Sel(48);
	ExtAdcCh2Sel(48);
}

/**
 * @function name:	ShortForceSet
 * @brief	AMUX Matrix for force end to switch to USBC pins
 * @param	ch1, ch2 uint_8 2x pin of USBC selected (0-23)
 * @param	port -- 0: USBC_1, 1: USBC_2
 * @return	0 -- sel success, >1 -- sel fail
 * @author	Tom Sum
 * @date	Dec. 4th, 2016
**/
unsigned char ShortForceSet(unsigned char ch1, unsigned char ch2, unsigned char port)
{
	unsigned char raw_ch1, raw_ch2, tmp_ch;
	if(ch1 > 23 || ch2 >23 || port>1)	return 1;	// Params error
	if(ch1 == ch2) return 2;						// Set error
	raw_ch1 = ch1 + port*24;	//ch1 += port*24
	raw_ch2 = ch2 + port*24;	//ch2 += port*24
	if(raw_ch1 > raw_ch2)					// raw_ch1 = min(ch1, ch2) raw_ch2 = max(ch1, ch2)
	{
		tmp_ch = raw_ch1;
		raw_ch1 = raw_ch2;
		raw_ch2 = tmp_ch;
	}
	//USART_printf("Ch1 %d, Ch2 %d", raw_ch1, raw_ch2);
	VoltageEnable(raw_ch1);
	ResistanceEnable(raw_ch2);
	return 0;
}


/**
 * @function name:	ShortSenseSet
 * @brief	AMUX Matrix for force end to switch to USBC pins
 * @param	ch1, ch2 uint_8 2x pin of USBC selected
 * @param	port -- 0: USBC_1, 1: USBC_2
 * @return	0 -- sel success, >1 -- sel fail
 * @author	Tom Sum
 * @date	Dec. 4th, 2016
**/
unsigned char ShortSenseSet(unsigned char ch1, unsigned char ch2, unsigned char port)
{
	unsigned char raw_ch1, raw_ch2, tmp_ch;
	if(ch1 > 23 || ch2 >23 || port>1)	return 1;	// Params error
	if(ch1 == ch2) return 2;						// Set error
	raw_ch1 = ch1 + ((port<<4)+(port<<3));	//ch1 += port*24
	raw_ch2 = ch2 + ((port<<4)+(port<<3));	//ch2 += port*24
	if(raw_ch1 > raw_ch2)					// raw_ch1 = min(ch1, ch2) raw_ch2 = max(ch1, ch2)
	{
		tmp_ch = raw_ch1;
		raw_ch1 = raw_ch2;
		raw_ch2 = tmp_ch;
	}
	ExtAdcCh1Sel(raw_ch1);
	ExtAdcCh2Sel(raw_ch2);
	return 0;
}

unsigned char ShortEnableSet(uint8_t IsEn)
{
	if(IsEn == 0)
		AmuxDisableAll();
	else
		AmuxEnableAll();
}

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
uint32_t DividerResVal(uint8_t sel)
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
uint32_t SRCResVal(unsigned char sel)
{
	unsigned short AdcVal=0;
	unsigned long VolVal=0;
	unsigned long res;

	if (sel <4 || sel >6) return 0xff; // error
	MeasuringSwitch(sel);
	//delay_ms(500);
	ADS1115_GetADC(&UserI2c1, 0, (uint16_t *)&AdcVal);
	VolVal = (uint32_t)AdcVal * ADC_FULL_SCALE *10 >>15;
	VolVal = VolVal *10 / INA1_GAIN;
	//USART_printf("CURR:Vol: %d\r\nSel: %d\r\nADC: %d\r\n", VolVal, sel,AdcVal);
	if( VolVal < 5)	return 0;//50uA* 100Ω = 5mV
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
unsigned long ResCalc(void)
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
	res = DividerResVal(_10K);
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

/**
 * @function name:	TestFunc
 * @brief	test only
 * @param	void
 * @return	void
 * @author	Tom Sum
 * @date	Dec. 8th, 2016
**/
void TestFunc(void)
{
		uint16_t AdcVal;
		uint32_t VolVal, Res;
		uint8_t i=0;
		static uint16_t Index=0;
		//USART_printf("Test Index %d\r\n", Index++);
		/*for(i=0; i<23;i++)
		{
			
			Short_TestCycle.Init();
			Short_TestCycle.ForceSet(i, i+1, 1);
			Short_TestCycle.SenseSet(i, i+1, 1);
			Short_TestCycle.EnaleSet(1);
			Res = Short_TestCycle.ResCalc();
			//ADS1115_GetADC(&UserI2c1, 1, &AdcVal);
			//VolVal = (uint32_t)AdcVal * ADC_FULL_SCALE >> 15;
			//VolVal = VolVal*10 / INA2_GAIN ;
			USART_printf("CH(%d, %d) -- Res: %d Ohm\r\n", i, i+1, Res);
		}*/
		Short_TestCycle.Init();
		Short_TestCycle.ForceSet(0, 4, 1);
		Short_TestCycle.SenseSet(0, 4, 1);
		Short_TestCycle.EnaleSet(1);
		Res = Short_TestCycle.ResCalc();
		//ADS1115_GetADC(&UserI2c1, 1, &AdcVal);
		//VolVal = (uint32_t)AdcVal * ADC_FULL_SCALE >> 15;
		//VolVal = VolVal*10 / INA2_GAIN ;
		USART_printf("CH(%d, %d) -- Res: %d Ohm\r\n", i, i+1, Res);
}


