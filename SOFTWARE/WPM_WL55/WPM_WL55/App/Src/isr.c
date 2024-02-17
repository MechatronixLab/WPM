/*
 * isr.c
 *
 *  Created on: Feb 3, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "isr.h"

uint8_t	ISR_interrupt_flag = 0;

void ISR_StartInterruptTimer(void)
{
	HAL_TIM_Base_Start_IT(&htim16);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim16)
	{	// Flag for interrupt routines to be handled in the main loop: APP_Run();
		ISR_interrupt_flag = 1;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (GPIO_Pin == B1_Pin)
	{
		BSP_LED_Toggle(LED_BLUE);
	}

	else if (GPIO_Pin == B2_Pin)
	{
		BSP_LED_Toggle(LED_GREEN);
	}

	else if (GPIO_Pin == B3_Pin)
	{
		BSP_LED_Toggle(LED_RED);
	}
}
