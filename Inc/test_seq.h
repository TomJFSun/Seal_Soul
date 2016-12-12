#ifndef _TEST_SEQ_H
#define _TEST_SEQ_H

typedef void (*Init)(void);
typedef unsigned char(*Set)(unsigned char ch1, unsigned char ch2, unsigned char port);
typedef unsigned char(*CES)(unsigned char );
typedef unsigned long (*Calc)(void);


typedef struct{
	Init	Init;
	Set		ForceSet;
	Set		SenseSet;
	CES		EnaleSet;
	Calc	ResCalc;
}TestCycle;

extern TestCycle Short_TestCycle;

// Test only
void TestFunc(void);

#endif		//_TEST_SEQ_H