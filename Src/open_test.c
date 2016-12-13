#include "open_test.h"


TestCycle Open_TestCycle ={
	OpenInit,				/*Init*/
	OpenForceSet,		/*ForceSet*/
	OpenSenseSet,		/*SenseSet*/
	OpenEnableSet,	/*EnaleSet*/		
	ResCalc,				/*ResCalc*/	
};

/**
 * @function name:	OpenInit
 * @brief	Init AMUX Matrix to switch to NC
 * @param	void
 * @return	void
 * @author	Tom Sum
 * @date	Dec. 4th, 2016
**/
void OpenInit(void)
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
 * @function name:	OpenForceSet
 * @brief	AMUX Matrix for force end to switch to USBC pins
 * @param	Port0_ch, Port1_ch 2x pin of USBC selected (0-23)
 * @param	opt -- reserved
 * @return	0 -- sel success, >1 -- sel fail
 * @author	Tom Sum
 * @date	Dec. 13th, 2016
**/
unsigned char OpenForceSet(unsigned char Port0_ch, unsigned char Port1_ch, unsigned char opt)
{
	unsigned char raw_ch1, raw_ch2, tmp_ch;
	if(Port0_ch > 23 || Port1_ch >23)	return 1;	// Params error
	if(Port0_ch == Port1_ch) return 2;					// Set error
	raw_ch1 = Port0_ch;
	raw_ch2 = Port1_ch + 24;
	VoltageEnable(raw_ch1);
	ResistanceEnable(raw_ch2);
	return 0;
}

/**
 * @function name:	OpenSenseSet
 * @brief	AMUX Matrix for force end to switch to USBC pins
 * @param	Port0_ch, Port1_ch -- 2x pin of USBC selected
 * @param	opt -- Reserved
 * @return 0 -- sel success, >1 -- sel fail
 * @author	Tom Sum
 * @date	Dec. 13th, 2016
**/
unsigned char OpenSenseSet(unsigned char Port0_ch, unsigned char Port1_ch, unsigned char opt)
{
	unsigned char raw_ch1, raw_ch2, tmp_ch;
	if(Port0_ch > 23 || Port1_ch >23 )	return 1;	// Params error
	if(Port0_ch == Port1_ch) return 2;						// Set error
	raw_ch1 = Port0_ch;
	raw_ch2 = Port1_ch + 24;
	
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

unsigned char OpenEnableSet(uint8_t IsEn)
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
 * @function name:	OpenTestFunc
 * @brief	test only
 * @param	void
 * @return	void
 * @author	Tom Sum
 * @date	Dec. 13th, 2016
**/
void OpenTestFunc(void)
{
		uint16_t AdcVal;
		uint32_t VolVal, Res;
		uint8_t i=0;
		uint8_t Port0_ch = 1, Port1_ch = 22;
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
	
		Open_TestCycle.Init();
		Open_TestCycle.ForceSet(Port0_ch, Port1_ch, 0);	//A2 -- B11
		Open_TestCycle.SenseSet(Port0_ch, Port1_ch, 0);
		Open_TestCycle.EnaleSet(1);
		Res = Open_TestCycle.ResCalc((void*)0);
		//ADS1115_GetADC(&UserI2c1, 1, &AdcVal);
		//VolVal = (uint32_t)AdcVal * ADC_FULL_SCALE >> 15;
		//VolVal = VolVal*10 / INA2_GAIN ;
		USART_printf("Open: L: ch%d, R: ch%d -- Res: %d.%d Ohm\r\n", Port0_ch, Port1_ch, Res/10, Res%10);
		delay_ms(100);
}