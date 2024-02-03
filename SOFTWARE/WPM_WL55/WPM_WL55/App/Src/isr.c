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
	// Flag for interrupt routines to be handled in the main loop: APP_Run();
	ISR_interrupt_flag = 1;
}
