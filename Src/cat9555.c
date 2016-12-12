//name:cat9555.c
//by:yangjinjiang
//date:2016/11/16
//version:v1.00

//Modified by Tom Sum
//Date : Dec. 04, 2016
//Brief: Modified ExtAdcChannelx function to switch channel to NC

#include "cat9555.h"

#define CAT9555_ADDR 		0x40


#define CMD_PORT_IN0	 		0x00
#define CMD_PORT_IN1	 		0x01
#define CMD_PORT_OUT0	 		0x02
#define CMD_PORT_OUT1	 		0x03
#define CMD_REVERSAL0	 		0x04
#define CMD_REVERSAL1	 		0x05
#define CMD_CONFIG0	 			0x06
#define CMD_CONFIG1	 			0x07

static unsigned short ExtRegData = 0;

unsigned char CAT9555Init(i2c_interface* pI2C);
unsigned char ExtAdcChannel1(i2c_interface* pI2C,unsigned char channel);
unsigned char ExtAdcChannel2(i2c_interface* pI2C,unsigned char channel);
unsigned char MeasuringSwitch(i2c_interface* pI2C,unsigned char channel);



cat9555_interface UserExtPort = {
	CAT9555Init,
	ExtAdcChannel1,
	ExtAdcChannel2,
	MeasuringSwitch,
};


unsigned char ExtPortOut(i2c_interface* pI2C)
{
	unsigned char buf[2];
	
	buf[1] = ExtRegData>>8;
	buf[0] = ExtRegData&0xff;
	
	return pI2C->Write(CAT9555_ADDR,CMD_PORT_OUT0,buf,2);		
}


unsigned char CAT9555Init(i2c_interface* pI2C)
{
	unsigned char buf[2];
	
	buf[0] = 0x00;
	buf[1] = 0x00;	
	
	if(pI2C->Write(CAT9555_ADDR,CMD_CONFIG0,buf,2) == 0)
		return 0;
	
	ExtRegData = 0;
	
	return ExtPortOut(pI2C);
}





#define	CAT9555PORT		ExtRegData

#define	IO_0_0				(1<<0)
#define	IO_0_1				(1<<1)
#define	IO_0_2				(1<<2)
#define	IO_0_3				(1<<3)
#define	IO_0_4				(1<<4)
#define	IO_0_5				(1<<5)
#define	IO_0_6				(1<<6)
#define	IO_0_7				(1<<7)


#define	IO_1_0				(1<<8)
#define	IO_1_1				(1<<9)
#define	IO_1_2				(1<<10)
#define	IO_1_3				(1<<11)
#define	IO_1_4				(1<<12)
#define	IO_1_5				(1<<13)
#define	IO_1_6				(1<<14)
#define	IO_1_7				(1<<15)



#define U2_1A0_PORT				CAT9555PORT
#define U2_1A0_PIN				IO_1_0
#define	U2_1A0_HIGH()			CAT9555PORT |= 	U2_1A0_PIN
#define	U2_1A0_LOW()			CAT9555PORT &= ~U2_1A0_PIN

#define U2_1A1_PORT				CAT9555PORT
#define U2_1A1_PIN				IO_0_7
#define	U2_1A1_HIGH()			CAT9555PORT |= 	U2_1A1_PIN
#define	U2_1A1_LOW()			CAT9555PORT &= ~U2_1A1_PIN

#define U2_1A2_PORT				CAT9555PORT
#define U2_1A2_PIN				IO_0_6
#define	U2_1A2_HIGH()			CAT9555PORT |= 	U2_1A2_PIN
#define	U2_1A2_LOW()			CAT9555PORT &= ~U2_1A2_PIN




//input 0-7
void U2_1_Channel(unsigned char sel)
{
	switch(sel)
	{
		case 0:
			U2_1A2_LOW();
			U2_1A1_LOW();
			U2_1A0_LOW();
			break;
		
		case 1:
			U2_1A2_LOW();
			U2_1A1_LOW();
			U2_1A0_HIGH();
			break;
		
		case 2:
			U2_1A2_LOW();
			U2_1A1_HIGH();
			U2_1A0_LOW();
			break;
		
		case 3:
			U2_1A2_LOW();
			U2_1A1_HIGH();
			U2_1A0_HIGH();
			break;

		case 4:
			U2_1A2_HIGH();
			U2_1A1_LOW();
			U2_1A0_LOW();
			break;
		
		case 5:
			U2_1A2_HIGH();
			U2_1A1_LOW();
			U2_1A0_HIGH();
			break;
		
		case 6:
			U2_1A2_HIGH();
			U2_1A1_HIGH();
			U2_1A0_LOW();
			break;
		
		case 7:
			U2_1A2_HIGH();
			U2_1A1_HIGH();
			U2_1A0_HIGH();
			break;			
	}
}
//==================================================
#define U2_2A0_PORT				CAT9555PORT
#define U2_2A0_PIN				IO_1_3
#define	U2_2A0_HIGH()			CAT9555PORT |= 	U2_2A0_PIN
#define	U2_2A0_LOW()			CAT9555PORT &= ~U2_2A0_PIN

#define U2_2A1_PORT				CAT9555PORT
#define U2_2A1_PIN				IO_1_2
#define	U2_2A1_HIGH()			CAT9555PORT |= 	U2_2A1_PIN
#define	U2_2A1_LOW()			CAT9555PORT &= ~U2_2A1_PIN

#define U2_2A2_PORT				CAT9555PORT
#define U2_2A2_PIN				IO_1_1
#define	U2_2A2_HIGH()			CAT9555PORT |= 	U2_2A2_PIN
#define	U2_2A2_LOW()			CAT9555PORT &= ~U2_2A2_PIN




//input 0-7
void U2_2_Channel(unsigned char sel)
{
	switch(sel)
	{
		case 0:
			U2_2A2_LOW();
			U2_2A1_LOW();
			U2_2A0_LOW();
			break;
		
		case 1:
			U2_2A2_LOW();
			U2_2A1_LOW();
			U2_2A0_HIGH();
			break;
		
		case 2:
			U2_2A2_LOW();
			U2_2A1_HIGH();
			U2_2A0_LOW();
			break;
		
		case 3:
			U2_2A2_LOW();
			U2_2A1_HIGH();
			U2_2A0_HIGH();
			break;

		case 4:
			U2_2A2_HIGH();
			U2_2A1_LOW();
			U2_2A0_LOW();
			break;
		
		case 5:
			U2_2A2_HIGH();
			U2_2A1_LOW();
			U2_2A0_HIGH();
			break;
		
		case 6:
			U2_2A2_HIGH();
			U2_2A1_HIGH();
			U2_2A0_LOW();
			break;
		
		case 7:
			U2_2A2_HIGH();
			U2_2A1_HIGH();
			U2_2A0_HIGH();
			break;			
	}
}



//==================================================

#define U1_1A0_PORT				CAT9555PORT
#define U1_1A0_PIN				IO_0_2
#define	U1_1A0_HIGH()			CAT9555PORT |= 	U1_1A0_PIN
#define	U1_1A0_LOW()			CAT9555PORT &= ~U1_1A0_PIN

#define U1_1A1_PORT				CAT9555PORT
#define U1_1A1_PIN				IO_0_1
#define	U1_1A1_HIGH()			CAT9555PORT |= 	U1_1A1_PIN
#define	U1_1A1_LOW()			CAT9555PORT &= ~U1_1A1_PIN

#define U1_1A2_PORT				CAT9555PORT
#define U1_1A2_PIN				IO_0_0
#define	U1_1A2_HIGH()			CAT9555PORT |= 	U1_1A2_PIN
#define	U1_1A2_LOW()			CAT9555PORT &= ~U1_1A2_PIN


//input 0-5
void U1_1_Channel(unsigned char sel)
{
	switch(sel)
	{
		case 0:
			U1_1A2_LOW();
			U1_1A1_LOW();
			U1_1A0_LOW();
			break;
		
		case 1:
			U1_1A2_LOW();
			U1_1A1_LOW();
			U1_1A0_HIGH();
			break;
		
		case 2:
			U1_1A2_LOW();
			U1_1A1_HIGH();
			U1_1A0_LOW();
			break;
		
		case 3:
			U1_1A2_LOW();
			U1_1A1_HIGH();
			U1_1A0_HIGH();
			break;

		case 4:
			U1_1A2_HIGH();
			U1_1A1_LOW();
			U1_1A0_LOW();
			break;
		
		case 5:
			U1_1A2_HIGH();
			U1_1A1_LOW();
			U1_1A0_HIGH();
			break;			
	}
}


//==================================================

#define U1_2A0_PORT				CAT9555PORT
#define U1_2A0_PIN				IO_0_5
#define	U1_2A0_HIGH()			CAT9555PORT |= 	U1_2A0_PIN
#define	U1_2A0_LOW()			CAT9555PORT &= ~U1_2A0_PIN

#define U1_2A1_PORT				CAT9555PORT
#define U1_2A1_PIN				IO_0_4
#define	U1_2A1_HIGH()			CAT9555PORT |= 	U1_2A1_PIN
#define	U1_2A1_LOW()			CAT9555PORT &= ~U1_2A1_PIN

#define U1_2A2_PORT				CAT9555PORT
#define U1_2A2_PIN				IO_0_3
#define	U1_2A2_HIGH()			CAT9555PORT |= 	U1_2A2_PIN
#define	U1_2A2_LOW()			CAT9555PORT &= ~U1_2A2_PIN


//input 0-5
void U1_2_Channel(unsigned char sel)
{
	switch(sel)
	{
		case 0:
			U1_2A2_LOW();
			U1_2A1_LOW();
			U1_2A0_LOW();
			break;
		
		case 1:
			U1_2A2_LOW();
			U1_2A1_LOW();
			U1_2A0_HIGH();
			break;
		
		case 2:
			U1_2A2_LOW();
			U1_2A1_HIGH();
			U1_2A0_LOW();
			break;
		
		case 3:
			U1_2A2_LOW();
			U1_2A1_HIGH();
			U1_2A0_HIGH();
			break;

		case 4:
			U1_2A2_HIGH();
			U1_2A1_LOW();
			U1_2A0_LOW();
			break;
		
		case 5:
			U1_2A2_HIGH();
			U1_2A1_LOW();
			U1_2A0_HIGH();
			break;			
	}
}



//channel select(0-47)
unsigned char ExtAdcChannel1(i2c_interface* pI2C,unsigned char channel)
{
	if(channel > 47)	// swith to NC
	{
		U2_1_Channel(0);
		U1_1_Channel(6);
		return 0;
	}
	U2_1_Channel(channel%8);
	U1_1_Channel(channel/8);
		
	return ExtPortOut(pI2C);
}


//channel select(0-47)
unsigned char ExtAdcChannel2(i2c_interface* pI2C,unsigned char channel)
{	
	if(channel > 47)	// switch to NC 
	{
		U2_2_Channel(0);
		U1_2_Channel(6);
		return 0;
	}
	U2_2_Channel(channel%8);
	U1_2_Channel(channel/8);
		
	return ExtPortOut(pI2C);
}












