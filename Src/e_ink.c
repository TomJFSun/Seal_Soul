//name:e_ink.c
//by:yangjinjiang
//date:2016/11/16
//version:v1.00

#include "e_ink.h"
#include "delay.h"


void E_INK_WriteByte(unsigned char value)
{
	unsigned char i=8;
	while(i)
	{
		E_INK_SCL_LOW();
		if(value&0x80)
		{
			E_INK_SDA_HIGH();
		}
		else
		{
			E_INK_SDA_LOW();
		}
		E_INK_SCL_HIGH();
		value <<= 1;
		i--;
	}
}


void E_INK_WriteCommand(unsigned char cmd)
{
	E_INK_DC_LOW();
	E_INK_WriteByte(cmd);
}

void E_INK_WriteData(unsigned char dat)
{
	E_INK_DC_HIGH();	
	E_INK_WriteByte(dat);
}

	


void E_INK_WaitBusy(void)
{	
	unsigned short delaycount = 0;
	do
	{
		E_INK_WriteCommand(0x71); 
		delay_ms(10);
		delaycount++;
		if(delaycount > 800)
		{
			break;
		}
	}
	while(!E_INK_BUSY_STATE());   
	delay_ms(100);
}






const unsigned char lut_vcom0[] =
{
0x00	,0x17	,0x00	,0x00	,0x00	,0x02,		
0x00	,0x17	,0x17	,0x00	,0x00	,0x02,		
0x00	,0x0A	,0x01	,0x00	,0x00	,0x01,		
0x00	,0x0E	,0x0E	,0x00	,0x00	,0x02,		
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,		
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,		
0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,0x00	,0x00,

};
const unsigned char lut_ww[] ={
0x40	,0x17	,0x00	,0x00	,0x00	,0x02,
0x90	,0x17	,0x17	,0x00	,0x00	,0x02,
0x40	,0x0A	,0x01	,0x00	,0x00	,0x01,
0xA0	,0x0E	,0x0E	,0x00	,0x00	,0x02,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,

};
const unsigned char lut_bw[] ={
0x40	,0x17	,0x00	,0x00	,0x00	,0x02,
0x90	,0x17	,0x17	,0x00	,0x00	,0x02,
0x40	,0x0A	,0x01	,0x00	,0x00	,0x01,
0xA0	,0x0E	,0x0E	,0x00	,0x00	,0x02,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
	  
};

const unsigned char lut_bb[] ={
0x80	,0x17	,0x00	,0x00	,0x00	,0x02,
0x90	,0x17	,0x17	,0x00	,0x00	,0x02,
0x80	,0x0A	,0x01	,0x00	,0x00	,0x01,
0x50	,0x0E	,0x0E	,0x00	,0x00	,0x02,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
			 
};

const unsigned char lut_wb[] ={
0x80	,0x17	,0x00	,0x00	,0x00	,0x02,
0x90	,0x17	,0x17	,0x00	,0x00	,0x02,
0x80	,0x0A	,0x01	,0x00	,0x00	,0x01,
0x50	,0x0E	,0x0E	,0x00	,0x00	,0x02,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
0x00	,0x00	,0x00	,0x00	,0x00	,0x00,
			
};

void E_INK_lut(void)
{
	unsigned int count;
	
	//E_INK_CS_LOW();

	E_INK_WriteCommand(0x20);
	for(count=0;count<44;count++)	 
	{
		E_INK_WriteData(lut_vcom0[count]);
	}

	E_INK_WriteCommand(0x21);
	for(count=0;count<42;count++)	     
	{
		E_INK_WriteData(lut_ww[count]);
	}   
	
	E_INK_WriteCommand(0x22);
	for(count=0;count<42;count++)	     
	{
		E_INK_WriteData(lut_bw[count]);
	} 

	E_INK_WriteCommand(0x23);
	for(count=0;count<42;count++)	     
	{
		E_INK_WriteData(lut_wb[count]);
	} 


	E_INK_WriteCommand(0x24);
	for(count=0;count<42;count++)	     
	{
		E_INK_WriteData(lut_bb[count]);
	} 

	//E_INK_CS_HIGH();	
}	



void E_INK_DeInit(void)
{
	E_INK_CS_LOW();
	//power off Sequence
	E_INK_WriteCommand(0x50);
	E_INK_WriteData(0x17);		//border floating	

	E_INK_WriteCommand(0X82);  		//VCOM to 0V
	E_INK_WriteCommand(0X00);  		//

	delay_ms(10);	  	

	E_INK_WriteCommand(0x01);   		//VG&VS to 0V fast
	E_INK_WriteData (0x00);		
	E_INK_WriteData (0x00);		
	E_INK_WriteData (0x00);		      
	E_INK_WriteData (0x00);		
	E_INK_WriteData (0x00);

	delay_ms(10);

	E_INK_WriteCommand(0x02);  		//power off
	E_INK_WaitBusy();
	E_INK_WriteCommand(0x07);		  	//deep sleep
	E_INK_WriteData(0xA5);
	E_INK_CS_HIGH();	
}


void E_INK_Init(void)
{
	E_INK_RST_LOW();
	delay_ms(10);
	E_INK_RST_HIGH();
	delay_ms(100);
	E_INK_CS_LOW();
	/*
	E_INK_WriteCommand(0x01); 
	E_INK_WriteData (0x03);	     //设置高低电压       
	E_INK_WriteData (0x00);
	E_INK_WriteData (0x2b);
	E_INK_WriteData (0x2b);
	E_INK_WriteData (0xff);

	E_INK_WriteCommand(0x06);         //boost设定
	E_INK_WriteData (0x17);
	E_INK_WriteData (0x17);
	E_INK_WriteData (0x17);       //07 0f 17 1f 27 2F 37 2f

	E_INK_WriteCommand(0x04);  
	E_INK_WaitBusy();

	E_INK_WriteCommand(0x00);
	//E_INK_WriteData(0xbf);		// KW-BF   KWR-AF	BWROTP 0f
	E_INK_WriteData(0x3f);

	E_INK_WriteCommand(0x30);			//PLL设定
	E_INK_WriteData (0x3c);      	// 3A 100HZ   29 150Hz 39 200HZ	31 171HZ

	E_INK_WriteCommand(0x61);			//像素设定
	E_INK_WriteData (0x01); 
	E_INK_WriteData (0x90);       //128	 
	E_INK_WriteData (0x01);		//
	E_INK_WriteData (0x2c);

	E_INK_WriteCommand(0x82);			//vcom设定
	E_INK_WriteData (0x12);

	E_INK_WriteCommand(0X50);
	E_INK_WriteData(0x97);		//VBDF 17|D7 VBDW 97 VBDB 57		VBDF F7 VBDW 77 VBDB 37  VBDR B7
	*/
	
	E_INK_WriteCommand(0x01); 
	E_INK_WriteData (0x03);	     //设置高低电压       
	E_INK_WriteData (0x00);	
	
	E_INK_WriteCommand(0x06);         //boost设定
	E_INK_WriteData (0x07);
	E_INK_WriteData (0x07);
	E_INK_WriteData (0x07);       //07 0f 17 1f 27 2F 37 2f	
	
	E_INK_WriteCommand(0x04);  
	E_INK_WaitBusy();

	E_INK_WriteCommand(0x00);
	E_INK_WriteData(0x0f);
	
	E_INK_WriteCommand(0X50);
	E_INK_WriteData(0x97);		//VBDF 17|D7 VBDW 97 VBDB 57		VBDF F7 VBDW 77 VBDB 37  VBDR B7	
	
	E_INK_WriteCommand(0x30);			//PLL设定
	E_INK_WriteData (0x39);      	// 3A 100HZ   29 150Hz 39 200HZ	31 171HZ	
	
	E_INK_WriteCommand(0x61);			//像素设定
	E_INK_WriteData (0x01); 
	E_INK_WriteData (0x90);       //128	 
	E_INK_WriteData (0x01);		//
	E_INK_WriteData (0x2c);	
	
	E_INK_WriteCommand(0x82);			//vcom设定
	E_INK_WriteData (0x12);



	E_INK_CS_HIGH();
}




void E_INK_Partial_Window(unsigned short x_start,unsigned short x_end,unsigned short y_start,unsigned short y_end)
{
	E_INK_WriteCommand(0x90);
	
	x_start &= ~0x7;
	
	E_INK_WriteData(x_start>>8);
	E_INK_WriteData(x_start&0xff);
	
	x_end |= 0x7;
	
	E_INK_WriteData(x_end>>8);
	E_INK_WriteData(x_end&0xff);
	
	
	E_INK_WriteData(y_start>>8);
	E_INK_WriteData(y_start&0xff);
	E_INK_WriteData(y_end>>8);
	E_INK_WriteData(y_end&0xff);
	
	E_INK_WriteData(0x00);
	E_INK_WriteCommand(0x91);	
}





