#include "stm32l0xx_hal.h"
#include "spiflash.h"	 



/*

void SPIx_Init(SPI_TypeDef* SPIx)
{
	SPIx->CR1 |= 0<<10;//全双工模式	
	SPIx->CR1 |= 1<<9; //软件nss管理
	SPIx->CR1 |= 1<<8;  

	SPIx->CR1 |= 1<<2; //SPI主机
	SPIx->CR1 |= 0<<11;//8bit数据格式	

	SPIx->CR1 |= 1<<1; //CPOL=0时空闲模式下SCK为1 
	SPIx->CR1 |= 1<<0; //第一个时钟的下降沿,CPHA=1 CPOL=1
	  
	SPIx->CR1 |= 0<<3; //0---/2,1--/4,2---/8,3---/16
	SPIx->CR1 |= 0<<7; //MSBfirst   
	SPIx->CR1 |= 1<<6; //SPI设备使能
} 


void SPI_FLASH_Init(void)
{
	SPIx_Init(SPI2);	
}
*/


//SPIx 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
unsigned char SPIx_ReadWriteByte(SPI_TypeDef* SPIx,unsigned char TxData)
{		
	unsigned char retry=0;				 
	while((SPIx->SR&1<<1)==0)//等待发送区空	
	{
		retry++;
		if(retry>200)return 0;
	}			  
	SPIx->DR=TxData;	 	  //发送一个byte 
	retry=0;
	while((SPIx->SR&1<<0)==0) //等待接收完一个byte  
	{
		retry++;
		if(retry>200)return 0;
	}	  						    
	return SPIx->DR;          //返回收到的数据				    
}


unsigned char SPI_Write_Byte(unsigned char data)
{
	return SPIx_ReadWriteByte(SPI2,data);
}

unsigned char SPI_Read_Byte(void)
{
	return (SPI_Write_Byte(0xFF));
}


void FLASH_CS_0(void)
{
	GPIOB->ODR &= ~(1<<12);	
}

void FLASH_CS_1(void)
{
	GPIOB->ODR |= (1<<12);	
}


unsigned long W25X_GetChipID(void)
{
	unsigned long nID = 0;
	
	FLASH_CS_0();

	SPI_Write_Byte(W25X_JedecDeviceID);
	nID = SPI_Read_Byte();
	nID <<= 8;
	nID |= SPI_Read_Byte();
	nID <<= 8;
	nID |= SPI_Read_Byte();
	
	FLASH_CS_1();

	return nID;
}


unsigned char W25X_Read_StatusReg(void)
{
	unsigned char u8 = 0;
	FLASH_CS_0();
	SPI_Write_Byte(W25X_ReadStatusReg);
	u8 = SPI_Read_Byte();
	FLASH_CS_1();	
	return u8;
}



void W25X_Write_StatusReg(unsigned char reg)
{
	FLASH_CS_0();
	SPI_Write_Byte(W25X_WriteStatusReg);
	SPI_Write_Byte(reg);
	FLASH_CS_1();
}



void W25X_Write_Enable(void)
{
	FLASH_CS_0();
	SPI_Write_Byte(W25X_WriteEnable);
	FLASH_CS_1();
}



void W25X_Write_Disable(void)
{
	FLASH_CS_0();
	SPI_Write_Byte(W25X_WriteDisable);
	FLASH_CS_1();
}



void W25X_Wait_Busy(void)
{	
	while(W25X_Read_StatusReg() == 0x03)
		W25X_Read_StatusReg();
}



void W25X_Erase_Sector(unsigned long nDest)
{
//	nDest *= FLASH_SECTOR_SIZE;
	
	FLASH_CS_0();			
	W25X_Write_Enable();
	FLASH_CS_0();
	SPI_Write_Byte(W25X_SectorErase);
	SPI_Write_Byte((unsigned char)((nDest & 0xFFFFFF) >> 16));
	SPI_Write_Byte((unsigned char)((nDest & 0xFFFF) >> 8));
	SPI_Write_Byte((unsigned char)nDest & 0xFF);
	FLASH_CS_1();
	W25X_Wait_Busy();
}



void W25X_Erase_Block(unsigned long nDest)
{
	nDest *= FLASH_BLOCK_SIZE;
	
	FLASH_CS_0();			
	W25X_Write_Enable();
	FLASH_CS_0();
	SPI_Write_Byte(W25X_SectorErase);
	SPI_Write_Byte((unsigned char)(nDest >> 16));
	SPI_Write_Byte((unsigned char)(nDest >> 8));
	SPI_Write_Byte((unsigned char)nDest & 0xFF);
	FLASH_CS_1();
	W25X_Wait_Busy();
}


void W25X_Erase_Chip(void)
{
	FLASH_CS_0();
	W25X_Write_Enable();
	FLASH_CS_0();
	W25X_Wait_Busy();
	FLASH_CS_0();
	SPI_Write_Byte(W25X_ChipErase);
	FLASH_CS_1();
	W25X_Wait_Busy();
}


void W25X_Read_Bytes(unsigned long nDest, unsigned char* pBuffer, unsigned short nBytes)
{	
	unsigned short i;
	
	FLASH_CS_0();
	SPI_Write_Byte(W25X_ReadData);
	SPI_Write_Byte((unsigned char)(nDest >> 16));
	SPI_Write_Byte((unsigned char)(nDest >> 8));
	SPI_Write_Byte((unsigned char)nDest);
	for(i=0;i<nBytes;i++)
	{
		pBuffer[i] = SPI_Read_Byte();
	}
	
	FLASH_CS_1();
	W25X_Wait_Busy();
}


void W25X_Read_Sector(unsigned long nSector, unsigned char* pBuffer)
{
	uint16_t i;
	
	//扇区号转为地址
	//nSector *= FLASH_SECTOR_SIZE;
	
	FLASH_CS_0();
	SPI_Write_Byte(W25X_ReadData);
	SPI_Write_Byte((unsigned char)(nSector >> 16));
	SPI_Write_Byte((unsigned char)(nSector>> 8));
	SPI_Write_Byte((unsigned char) nSector);
	
	for(i=0;i<FLASH_SECTOR_SIZE;i++)
	{	pBuffer[i] = SPI_Read_Byte();
	}
	FLASH_CS_1();
	//W25X_Wait_Busy();
}




void W25X_Write_Bytes(unsigned long nSector,unsigned char* pBuffer, unsigned short nBytes)
{
	/*
	u16 i;

	for(i=0;i<nBytes;i++)	
	{	
		W25X_Write_Enable(); 
		
		FLASH_CS_0();		
		SPI_Write_Byte(W25X_PageProgram);
		SPI_Write_Byte((u8)(((nSector+i) & 0xFFFFFF) >> 16));  // 发送3个字节的地址信息
		SPI_Write_Byte((u8)(((nSector+i) & 0xFFFF) >> 8));
		SPI_Write_Byte((u8)(nSector+i) & 0xFF);

	//	for(i=0;i<nBytes;i++)
		SPI_Write_Byte(pBuffer[i]);
		
		FLASH_CS_1();
	
		W25X_Wait_Busy();
	}
*/

	unsigned short times;
	unsigned short endbytes;
	unsigned short i;
	unsigned long addr;
	unsigned char* pTemp;
	
	if(nBytes<=FLASH_PAGE_SIZE)
	{
		W25X_Write_Sector(nSector,pBuffer,nBytes);		
	}
	else
	{
		addr = nSector;
		pTemp = pBuffer;
		
		times = nBytes/FLASH_PAGE_SIZE;
		endbytes = nBytes%FLASH_PAGE_SIZE;
		for(i=0;i<times;i++)
		{
			W25X_Write_Sector(addr,pTemp,FLASH_PAGE_SIZE);		
			addr	+= FLASH_PAGE_SIZE;
			pTemp += FLASH_PAGE_SIZE;	
		}
		if(endbytes)
		{
			W25X_Write_Sector(addr,pTemp,endbytes);		
		}
	}


}


void W25X_Write_Sector(unsigned long nSector, unsigned char* pBuffer, unsigned short nBytes)
{
	unsigned short i;
	
	if(nBytes<=FLASH_PAGE_SIZE)
	{
		W25X_Write_Enable(); 
		FLASH_CS_0();		
		SPI_Write_Byte(W25X_PageProgram);
		SPI_Write_Byte((unsigned char)(((nSector) & 0xFFFFFF) >> 16));  // 发送3个字节的地址信息
		SPI_Write_Byte((unsigned char)(((nSector) & 0xFFFF) >> 8));
		SPI_Write_Byte((unsigned char)(nSector) & 0xFF);

		for(i=0;i<nBytes;i++)
		SPI_Write_Byte(pBuffer[i]);
		
		FLASH_CS_1();
	
		W25X_Wait_Busy();		
	}
}

