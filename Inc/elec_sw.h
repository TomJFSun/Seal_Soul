/**
File name: elec_sw.h
Created by : Tom Sun
Date:	Dec. 4th, 2016
Description: head file of amux matrix except the sel pin connected to CAT9555(I2C to GPIO expander)
**/
#ifndef _ELEC_SW_H
#define _ELEC_SW_H

#include "stm32l0xx_hal.h"

// External fuctions declearation 
void AmuxEnableAll(void);
void AmuxDisableAll(void);
unsigned char VoltageEnable(unsigned char);
unsigned char ResistanceEnable(unsigned char channel);
unsigned char MeasuringSwitch(unsigned char channel);

#endif	/*_ELEC_SW_H*/
