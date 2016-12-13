#ifndef _SPI_FLASH_H_
#define _SPI_FLASH_H_




//Flash相关参数
//#define FLASH_PAGE_SIZE			256
#define FLASH_SECTOR_SIZE		4096
//#define FLASH_SECTOR_COUNT		256
#define FLASH_BLOCK_SIZE		65536
#define FLASH_PAGES_PER_SECTOR	FLASH_SECTOR_SIZE/FLASH_PAGE_SIZE

/****************************************
	W25X32	命令
****************************************/
#define W25X32_CHIPID				0xEF3016

#define W25X_WriteEnable			0x06
#define W25X_WriteDisable			0x04
#define W25X_ReadStatusReg			0x05
#define W25X_WriteStatusReg			0x01
#define W25X_ReadData				0x03
#define W25X_FastReadData			0x0B
#define W25X_FastReadDual			0x3B
#define W25X_PageProgram			0x02
#define W25X_BlockErase				0xD8
#define W25X_SectorErase			0x20
#define W25X_ChipErase				0xC7
#define W25X_SetPowerDown			0xB9
#define W25X_SetReleasePowerDown	0xAB
#define W25X_DeviceID				0xAB
#define W25X_ManufactDeviceID		0x90
#define W25X_JedecDeviceID			0x9F



void SPI_FLASH_Init(void);


unsigned long W25X_GetChipID(void);
unsigned char W25X_Read_StatusReg(void);
void W25X_Write_StatusReg(unsigned char reg);
void W25X_Write_Enable(void);
void W25X_Write_Disable(void);
void W25X_Erase_Chip(void);
void W25X_Erase_Sector(unsigned long nDest);
void W25X_Erase_Block(unsigned long nDest);
void W25X_Wait_Busy(void);
void W25X_PowerDown(void);
void W25X_ReleasePowerDown(void);
void W25X_Read_Bytes(unsigned long nDest, unsigned char* pBuffer, unsigned short nBytes);
void W25X_Write_Bytes(unsigned long nDest,unsigned char* pBuffer, unsigned short nBytes);
void W25X_Read_Sector(unsigned long nSector, unsigned char* pBuffer);
void W25X_Write_Sector(unsigned long nSector, unsigned char* pBuffer, unsigned short nBytes);


#endif

