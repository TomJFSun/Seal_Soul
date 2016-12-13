#ifndef __USART_H
#define	__USART_H

#define		UARTPORT		USART1

void USART_Init(void);
void USART_printf(unsigned char *Data,...);

#endif //__USART_H
