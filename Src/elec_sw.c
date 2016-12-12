//name:elec_sw.c
//by:yangjinjiang
//date:2016/11/15
//version:v1.00

// Modified by Tom Sun
// Add amux IC enable pin control
// Date: Ded. 4th, 2016

#include "stm32l0xx_hal.h"
#include "elec_sw.h"

/*-----------------Define AMUX IC EN pin set --------------------*/
//define SW_EN_ALL -> PA2 OUTPUT PP
#define	SW_EN_ALL_PORT			(GPIOA)
#define	SW_EN_ALL_PIN				(GPIO_PIN_2)
#define SW_EN_ALL_HIGH()		(SW_EN_ALL_PORT->BSRR = SW_EN_ALL_PIN)
#define	SW_EN_ALL_LOW()			(SW_EN_ALL_PORT->BRR  = SW_EN_ALL_PIN)
/*-----------------Define AMUX IC EN pin set --------------------*/

#define U3_1A0_PORT				GPIOB
#define U3_1A0_PIN				GPIO_PIN_5
#define U3_1A0_HIGH()			U3_1A0_PORT->BSRR = U3_1A0_PIN
#define U3_1A0_LOW()			U3_1A0_PORT->BRR  = U3_1A0_PIN

#define U3_1A1_PORT				GPIOB
#define U3_1A1_PIN				GPIO_PIN_6
#define U3_1A1_HIGH()			U3_1A1_PORT->BSRR = U3_1A1_PIN
#define U3_1A1_LOW()			U3_1A1_PORT->BRR  = U3_1A1_PIN

#define U3_1A2_PORT				GPIOB
#define U3_1A2_PIN				GPIO_PIN_7
#define U3_1A2_HIGH()			U3_1A2_PORT->BSRR = U3_1A2_PIN
#define U3_1A2_LOW()			U3_1A2_PORT->BRR  = U3_1A2_PIN


#define U4_1A0_PORT				GPIOB
#define U4_1A0_PIN				GPIO_PIN_0
#define U4_1A0_HIGH()			U4_1A0_PORT->BSRR = U4_1A0_PIN
#define U4_1A0_LOW()			U4_1A0_PORT->BRR  = U4_1A0_PIN

#define U4_1A1_PORT				GPIOB
#define U4_1A1_PIN				GPIO_PIN_1
#define U4_1A1_HIGH()			U4_1A1_PORT->BSRR = U4_1A1_PIN
#define U4_1A1_LOW()			U4_1A1_PORT->BRR  = U4_1A1_PIN

#define U4_1A2_PORT				GPIOB
#define U4_1A2_PIN				GPIO_PIN_2
#define U4_1A2_HIGH()			U4_1A2_PORT->BSRR = U4_1A2_PIN
#define U4_1A2_LOW()			U4_1A2_PORT->BRR  = U4_1A2_PIN


/**
 * @function name:	AmuxEnableAll
 * @brief	Enable all mux ICs enable pin
 * @param	void
 * @return	void
 * @author	Tom Sum
 * @date	Dec. 4th, 2016
**/
void AmuxEnableAll(void)
{
	SW_EN_ALL_HIGH();
}

/**
 * @function name:	AmuxDisableAll
 * @brief	Disable all mux ICs enable pin
 * @param	void
 * @return	void
 * @author	Tom Sum
 * @date	Dec. 4th, 2016
**/
void AmuxDisableAll(void)
{
	SW_EN_ALL_LOW();
}


//input 0-7
void U3_1_Channel(unsigned char sel)
{
	switch(sel)
	{
		case 0:
			U3_1A2_LOW();
			U3_1A1_LOW();
			U3_1A0_LOW();
			break;
		
		case 1:
			U3_1A2_LOW();
			U3_1A1_LOW();
			U3_1A0_HIGH();
			break;
		
		case 2:
			U3_1A2_LOW();
			U3_1A1_HIGH();
			U3_1A0_LOW();
			break;
		
		case 3:
			U3_1A2_LOW();
			U3_1A1_HIGH();
			U3_1A0_HIGH();
			break;

		case 4:
			U3_1A2_HIGH();
			U3_1A1_LOW();
			U3_1A0_LOW();
			break;
		
		case 5:
			U3_1A2_HIGH();
			U3_1A1_LOW();
			U3_1A0_HIGH();
			break;
		
		case 6:
			U3_1A2_HIGH();
			U3_1A1_HIGH();
			U3_1A0_LOW();
			break;
		
		case 7:
			U3_1A2_HIGH();
			U3_1A1_HIGH();
			U3_1A0_HIGH();
			break;			
	}
}


//input 0-5
void U4_1_Channel(uint8_t sel)
{
	switch(sel)
	{
		case 0:
			U4_1A2_LOW();
			U4_1A1_LOW();
			U4_1A0_LOW();
			break;
		
		case 1:
			U4_1A2_LOW();
			U4_1A1_LOW();
			U4_1A0_HIGH();
			break;
		
		case 2:
			U4_1A2_LOW();
			U4_1A1_HIGH();
			U4_1A0_LOW();
			break;
		
		case 3:
			U4_1A2_LOW();
			U4_1A1_HIGH();
			U4_1A0_HIGH();
			break;

		case 4:
			U4_1A2_HIGH();
			U4_1A1_LOW();
			U4_1A0_LOW();
			break;
		
		case 5:
			U4_1A2_HIGH();
			U4_1A1_LOW();
			U4_1A0_HIGH();
			break;			
	}
}


//channel select(0-47)
unsigned char VoltageEnable(unsigned char channel)
{
	if(channel > 47)	// Switch to NC
	{
		U3_1_Channel(0);
		U4_1_Channel(7);	// AMUX NC pin
		return 0;
	}
	U3_1_Channel(channel%8);
	U4_1_Channel(channel/8);
	return 1;
}

//============================================================================

#define U3_3A0_PORT				GPIOC
#define U3_3A0_PIN				GPIO_PIN_1
#define U3_3A0_HIGH()			U3_3A0_PORT->BSRR = U3_3A0_PIN
#define U3_3A0_LOW()			U3_3A0_PORT->BRR  = U3_3A0_PIN

#define U3_3A1_PORT				GPIOC
#define U3_3A1_PIN				GPIO_PIN_2
#define U3_3A1_HIGH()			U3_3A1_PORT->BSRR = U3_3A1_PIN
#define U3_3A1_LOW()			U3_3A1_PORT->BRR  = U3_3A1_PIN

#define U3_3A2_PORT				GPIOC
#define U3_3A2_PIN				GPIO_PIN_3
#define U3_3A2_HIGH()			U3_3A2_PORT->BSRR = U3_3A2_PIN
#define U3_3A2_LOW()			U3_3A2_PORT->BRR  = U3_3A2_PIN


#define U4_2A0_PORT				GPIOC
#define U4_2A0_PIN				GPIO_PIN_6
#define U4_2A0_HIGH()			U4_2A0_PORT->BSRR = U4_2A0_PIN
#define U4_2A0_LOW()			U4_2A0_PORT->BRR  = U4_2A0_PIN

#define U4_2A1_PORT				GPIOB
#define U4_2A1_PIN				GPIO_PIN_4
#define U4_2A1_HIGH()			U4_2A1_PORT->BSRR = U4_2A1_PIN
#define U4_2A1_LOW()			U4_2A1_PORT->BRR  = U4_2A1_PIN

#define U4_2A2_PORT				GPIOB
#define U4_2A2_PIN				GPIO_PIN_3
#define U4_2A2_HIGH()			U4_2A2_PORT->BSRR = U4_2A2_PIN
#define U4_2A2_LOW()			U4_2A2_PORT->BRR  = U4_2A2_PIN


//input 0-7
void U3_3_Channel(unsigned char sel)
{
	switch(sel)
	{
		case 0:
			U3_3A2_LOW();
			U3_3A1_LOW();
			U3_3A0_LOW();
			break;
		
		case 1:
			U3_3A2_LOW();
			U3_3A1_LOW();
			U3_3A0_HIGH();
			break;
		
		case 2:
			U3_3A2_LOW();
			U3_3A1_HIGH();
			U3_3A0_LOW();
			break;
		
		case 3:
			U3_3A2_LOW();
			U3_3A1_HIGH();
			U3_3A0_HIGH();
			break;

		case 4:
			U3_3A2_HIGH();
			U3_3A1_LOW();
			U3_3A0_LOW();
			break;
		
		case 5:
			U3_3A2_HIGH();
			U3_3A1_LOW();
			U3_3A0_HIGH();
			break;
		
		case 6:
			U3_3A2_HIGH();
			U3_3A1_HIGH();
			U3_3A0_LOW();
			break;
		
		case 7:
			U3_3A2_HIGH();
			U3_3A1_HIGH();
			U3_3A0_HIGH();
			break;			
	}
}




//input 0-5
void U4_2_Channel(unsigned char sel)
{
	switch(sel)
	{
		case 0:
			U4_2A2_LOW();
			U4_2A1_LOW();
			U4_2A0_LOW();
			break;
		
		case 1:
			U4_2A2_LOW();
			U4_2A1_LOW();
			U4_2A0_HIGH();
			break;
		
		case 2:
			U4_2A2_LOW();
			U4_2A1_HIGH();
			U4_2A0_LOW();
			break;
		
		case 3:
			U4_2A2_LOW();
			U4_2A1_HIGH();
			U4_2A0_HIGH();
			break;

		case 4:
			U4_2A2_HIGH();
			U4_2A1_LOW();
			U4_2A0_LOW();
			break;
		
		case 5:
			U4_2A2_HIGH();
			U4_2A1_LOW();
			U4_2A0_HIGH();
			break;			
	}
}


//channel select(0-47)
unsigned char ResistanceEnable(unsigned char channel)
{
	if(channel > 47)	// Switch to NC
	{
		U3_3_Channel(0);
		U4_2_Channel(7);	// AMUX NC pin
		return 0;
	}
	U3_3_Channel(channel%8);
	U4_2_Channel(channel/8);
	return 1;
}



//==================================================

#define U5_1A0_PORT				GPIOC
#define U5_1A0_PIN				GPIO_PIN_12
#define	U5_1A0_HIGH()			U5_1A0_PORT->BSRR = U5_1A0_PIN
#define	U5_1A0_LOW()			U5_1A0_PORT->BRR  = U5_1A0_PIN

#define U5_1A1_PORT				GPIOC
#define U5_1A1_PIN				GPIO_PIN_11
#define	U5_1A1_HIGH()			U5_1A1_PORT->BSRR = U5_1A1_PIN
#define	U5_1A1_LOW()			U5_1A1_PORT->BRR  = U5_1A1_PIN

#define U5_1A2_PORT				GPIOC
#define U5_1A2_PIN				GPIO_PIN_10
#define	U5_1A2_HIGH()			U5_1A2_PORT->BSRR = U5_1A2_PIN
#define	U5_1A2_LOW()			U5_1A2_PORT->BRR  = U5_1A2_PIN



//input 0-7
void U5_1_Channel(unsigned char sel)
{
	switch(sel)
	{
		case 0:
			U5_1A2_LOW();
			U5_1A1_LOW();
			U5_1A0_LOW();
			break;
		
		case 1:
			U5_1A2_LOW();
			U5_1A1_LOW();
			U5_1A0_HIGH();
			break;
		
		case 2:
			U5_1A2_LOW();
			U5_1A1_HIGH();
			U5_1A0_LOW();
			break;
		
		case 3:
			U5_1A2_LOW();
			U5_1A1_HIGH();
			U5_1A0_HIGH();
			break;

		case 4:
			U5_1A2_HIGH();
			U5_1A1_LOW();
			U5_1A0_LOW();
			break;
		
		case 5:
			U5_1A2_HIGH();
			U5_1A1_LOW();
			U5_1A0_HIGH();
			break;
		
		case 6:
			U5_1A2_HIGH();
			U5_1A1_HIGH();
			U5_1A0_LOW();
			break;
		
		case 7:
			U5_1A2_HIGH();
			U5_1A1_HIGH();
			U5_1A0_HIGH();
			break;			
	}
}


//input 0-7
/**
 * @fuction name: MeasuringSwitch
 * @brief: 0-3: 10k, 100k, 1M, 10M
 * 		   4-7: 10O, 100O, 1k
**/
unsigned char MeasuringSwitch(unsigned char channel)
{
	U5_1_Channel(channel);
}















