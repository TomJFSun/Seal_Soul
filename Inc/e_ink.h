#ifndef _E_INK_H
#define _E_INK_H

#include "stm32l0xx_hal.h"
/*
#define E_INK_CS_PORT				GPIOB
#define E_INK_CS_PIN				GPIO_PIN_6
#define E_INK_CS_HIGH()     E_INK_CS_PORT->ODR |=  (E_INK_CS_PIN)
#define E_INK_CS_LOW()      E_INK_CS_PORT->ODR &= ~(E_INK_CS_PIN)

#define E_INK_DC_PORT				GPIOB
#define E_INK_DC_PIN				GPIO_PIN_4
#define E_INK_DC_HIGH()     E_INK_DC_PORT->ODR |=  (E_INK_DC_PIN)
#define E_INK_DC_LOW()      E_INK_DC_PORT->ODR &= ~(E_INK_DC_PIN)

#define E_INK_RES_PORT			GPIOB
#define E_INK_RES_PIN				GPIO_PIN_5
#define E_INK_RST_HIGH()		E_INK_RES_PORT->ODR |=  (E_INK_RES_PIN)
#define E_INK_RST_LOW()			E_INK_RES_PORT->ODR &= ~(E_INK_RES_PIN)

#define E_INK_SCLK_PORT			GPIOB
#define E_INK_SCLK_PIN			GPIO_PIN_3
#define E_INK_SCL_HIGH()		E_INK_SCLK_PORT->ODR |=  (E_INK_SCLK_PIN)
#define E_INK_SCL_LOW()			E_INK_SCLK_PORT->ODR &= ~(E_INK_SCLK_PIN)

#define E_INK_SDAT_PORT			GPIOD
#define E_INK_SDAT_PIN			GPIO_PIN_2
#define E_INK_SDA_HIGH()		E_INK_SDAT_PORT->ODR |=  (E_INK_SDAT_PIN)
#define E_INK_SDA_LOW()			E_INK_SDAT_PORT->ODR &= ~(E_INK_SDAT_PIN)
*/

#define E_INK_CS_PORT				GPIOA
#define E_INK_CS_PIN				GPIO_PIN_11
#define E_INK_CS_HIGH()     E_INK_CS_PORT->BSRR = E_INK_CS_PIN
#define E_INK_CS_LOW()      E_INK_CS_PORT->BRR = E_INK_CS_PIN

#define E_INK_DC_PORT				GPIOC
#define E_INK_DC_PIN				GPIO_PIN_9
#define E_INK_DC_HIGH()     E_INK_DC_PORT->BSRR = E_INK_DC_PIN
#define E_INK_DC_LOW()      E_INK_DC_PORT->BRR = E_INK_DC_PIN

#define E_INK_RES_PORT			GPIOC
#define E_INK_RES_PIN				GPIO_PIN_8
#define E_INK_RST_HIGH()		E_INK_RES_PORT->BSRR = E_INK_RES_PIN
#define E_INK_RST_LOW()			E_INK_RES_PORT->BRR = E_INK_RES_PIN

#define E_INK_SCLK_PORT			GPIOB
#define E_INK_SCLK_PIN			GPIO_PIN_13
#define E_INK_SCL_HIGH()		E_INK_SCLK_PORT->BSRR = E_INK_SCLK_PIN
#define E_INK_SCL_LOW()			E_INK_SCLK_PORT->BRR = E_INK_SCLK_PIN

#define E_INK_SDAT_PORT			GPIOB
#define E_INK_SDAT_PIN			GPIO_PIN_15
#define E_INK_SDA_HIGH()		E_INK_SDAT_PORT->BSRR = E_INK_SDAT_PIN
#define E_INK_SDA_LOW()			E_INK_SDAT_PORT->BRR = E_INK_SDAT_PIN

#define E_INK_BUSY_PORT			GPIOC
#define E_INK_BUSY_PIN			GPIO_PIN_7
#define E_INK_BUSY_STATE()	HAL_GPIO_ReadPin(E_INK_BUSY_PORT,E_INK_BUSY_PIN)

//#define E_INK_BUSY_STATE()	E_INK_BUSY_PORT->IDR & E_INK_BUSY_PIN



void E_INK_Init(void);
void E_INK_DeInit(void);

void E_INK_Clear(void);

void E_INK_WriteCommand(unsigned char cmd);
void E_INK_WriteData(unsigned char dat);
void E_INK_lut(void);
void E_INK_WaitBusy(void);
void E_INK_Partial_Window(unsigned short x_start,unsigned short x_end,unsigned short y_start,unsigned short y_end);

#endif	//_E_INK_H
