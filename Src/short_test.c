#include "short_test.h"


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
	/*if(raw_ch1 > raw_ch2)					// raw_ch1 = min(ch1, ch2) raw_ch2 = max(ch1, ch2)
	{
		tmp_ch = raw_ch1;
		raw_ch1 = raw_ch2;
		raw_ch2 = tmp_ch;
	}*/
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
	/*if(raw_ch1 > raw_ch2)					// raw_ch1 = min(ch1, ch2) raw_ch2 = max(ch1, ch2)
	{
		tmp_ch = raw_ch1;
		raw_ch1 = raw_ch2;
		raw_ch2 = tmp_ch;
	}*/
	ExtAdcCh1Sel(raw_ch1);
	ExtAdcCh2Sel(raw_ch2);
	return 0;
}

unsigned char ShortEnableSet(uint8_t IsEn)
{
	if(IsEn == 0)
	{
		AmuxDisableAll();
		return 1;
	}
	else
	{
		AmuxEnableAll();
		return 0;
	}
}

/**
 * @function name:	ShortTestFunc
 * @brief	test only
 * @param	void
 * @return	void
 * @author	Tom Sum
 * @date	Dec. 8th, 2016
**/
void ShortTestFunc(void)
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
		Short_TestCycle.ForceSet(0, 12, 0);
		Short_TestCycle.SenseSet(0, 12, 0);
		Short_TestCycle.EnaleSet(1);
		Res = Short_TestCycle.ResCalc((void*)0);
		//ADS1115_GetADC(&UserI2c1, 1, &AdcVal);
		//VolVal = (uint32_t)AdcVal * ADC_FULL_SCALE >> 15;
		//VolVal = VolVal*10 / INA2_GAIN ;
		USART_printf("Port %d: CH(%d, %d) -- Res: %d Ohm\r\n", 0, 12, 0, Res);
		delay_ms(100);
}