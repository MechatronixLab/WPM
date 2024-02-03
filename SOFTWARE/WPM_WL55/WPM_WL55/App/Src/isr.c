/*
 * isr.c
 *
 *  Created on: Feb 3, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "isr.h"

void ISR_StartInterruptTimer(void)
{
	HAL_TIM_Base_Start_IT(&htim16);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	BSP_LED_Toggle(LED_RED);
}
