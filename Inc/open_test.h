#ifndef _OPEN_TEST_H
#define _OPEN_TEST_H

#include "stm32l0xx_hal.h"
#include "cat9555.h"
#include "ads1115.h"
#include "elec_sw.h"
#include "delay.h"
#include "test_seq.h"

/*------------------- Short Test---------------*/
#define ExtAdcCh1Sel(ch) (UserExtPort.ExtAdc1(&UserI2c1, ch))
#define ExtAdcCh2Sel(ch) (UserExtPort.ExtAdc2(&UserI2c1, ch))

void OpenInit(void);
unsigned char OpenForceSet(unsigned char ch1, unsigned char ch2, unsigned char port);
unsigned char OpenSenseSet(unsigned char ch1, unsigned char ch2, unsigned char port);
unsigned char OpenEnableSet(uint8_t IsEn);

extern TestCycle Open_TestCycle;
// Test only
void OpenTestFunc(void);

#endif	/* _OPEN_TEST_H */