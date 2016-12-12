

#ifndef _KEY_H
#define _KEY_H


#define		KEY1_DOWN			(1<<1)
#define		KEY1_UP				(1<<2)

#define 	KEY_PORT			(GPIOC)
#define 	KEY1_PIN			(GPIO_PIN_13)

extern unsigned char KeyDown2SFlag;

void KeyInit(void);
void EXTI_Key_IRQHandle(void);
void KeyProcess(void);



#endif


