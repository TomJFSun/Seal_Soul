
#ifndef _PWM_TIM2_H
#define _PWM_TIM2_H

typedef void (*pwm_init)(void);
typedef void (*pwm_set)(unsigned char value);

typedef struct{
	pwm_init	Init;
	pwm_set		SetR;
	pwm_set		SetG;
	pwm_set		SetB;
	
}pwm_interface;

extern pwm_interface UserPWM;





#endif		//_PWM_TIM2_H


