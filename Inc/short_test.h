#ifndef _SHORT_TEST_H
#define _SHORT_TEST_H

#include "stm32l0xx_hal.h"
#include "cat9555.h"
#include "ads1115.h"
#include "elec_sw.h"
#include "delay.h"
#include "test_seq.h"

/*------------------- Short Test---------------*/
#define ExtAdcCh1Sel(ch) (UserExtPort.ExtAdc1(&UserI2c1, ch))
#define ExtAdcCh2Sel(ch) (UserExtPort.ExtAdc2(&UserI2c1, ch))

void ShortInit(void);
unsigned char ShortForceSet(unsigned char ch1, unsigned char ch2, unsigned char port);
unsigned char ShortSenseSet(unsigned char ch1, unsigned char ch2, unsigned char port);
unsigned char ShortEnableSet(uint8_t IsEn);

extern TestCycle Short_TestCycle;
// Test only
void ShortTestFunc(void);

#endif	/* _SHORT_TEST_H */
