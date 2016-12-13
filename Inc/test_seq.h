#ifndef _TEST_SEQ_H
#define _TEST_SEQ_H

#include "stm32l0xx_hal.h"
#include "cat9555.h"
#include "ads1115.h"
#include "elec_sw.h"
#include "usart.h"
#include "delay.h"


typedef void (*Init)(void);
typedef unsigned char(*Set)(unsigned char ch1, unsigned char ch2, unsigned char port);
typedef unsigned char(*CES)(unsigned char );
typedef unsigned long (*Calc)(void*);


typedef struct{
	Init	Init;
	Set		ForceSet;
	Set		SenseSet;
	CES		EnaleSet;
	Calc	ResCalc;
}TestCycle;


unsigned long ResCalc(void*);


//extern TestCycle Open_TestCycle;

#endif		//_TEST_SEQ_H

