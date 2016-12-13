
//name:pwm_tim2.c
//by:yangjinjiang
//date:2016/11/02
//version:v1.00


#include "stm32l0xx_hal.h"
#include "pwm_tim2.h"


void PWM_TIM2_Init(void);
void SetR_Value(unsigned char value);
void SetG_Value(unsigned char value);
void SetB_Value(unsigned char value);


pwm_interface UserPWM = {
	PWM_TIM2_Init,
	SetR_Value,
	SetG_Value,
	SetB_Value,
};


void PWM_TIM2_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;
	TIM_HandleTypeDef htim2;	
	
	//PA15     ------> TIM2_CH1 	
	//PB10     ------> TIM2_CH3
	//PB11     ------> TIM2_CH4
	
	GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF2_TIM2;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Alternate = GPIO_AF5_TIM2;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	
	
  htim2.Instance = TIM2;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;	//4·ÖÆµ£¬4M	
  htim2.Init.Period = 100;
  htim2.Init.Prescaler = (400-1);
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	HAL_TIM_PWM_Init(&htim2);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
  HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);	
}


void SetR_Value(unsigned char value)
{
	if(value <= 100)
		TIM2->CCR1 = value;
}

void SetG_Value(unsigned char value)
{
	if(value <= 100)
		TIM2->CCR3 = value;
}

void SetB_Value(unsigned char value)
{
	if(value <= 100)
		TIM2->CCR4 = value;
}




