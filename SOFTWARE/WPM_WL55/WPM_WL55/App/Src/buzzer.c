/*
 * buzzer.c
 *
 *  Created on: Feb 18, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "buzzer.h"

void BUZZER_On(void)
{
	HAL_TIM_PWM_Start(&BUZZER_TIMER_HANDLE, BUZZER_PWM_CHANNEL);
}

void BUZZER_Off(void)
{
	HAL_TIM_PWM_Stop(&BUZZER_TIMER_HANDLE, BUZZER_PWM_CHANNEL);
}

void BUZZER_SetVolume(uint8_t volume)
{
	__HAL_TIM_SET_COMPARE(&BUZZER_TIMER_HANDLE, BUZZER_PWM_CHANNEL, volume);
}

//void BUZZER_SetTone(uint16_t frequency)
//{
//	;
//}
