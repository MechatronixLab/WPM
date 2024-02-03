/*
 * isr.h
 *
 *  Created on: Feb 3, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_ISR_H_
#define INC_ISR_H_

#include "app.h"

extern TIM_HandleTypeDef htim16;

void ISR_StartInterruptTimer(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif /* INC_ISR_H_ */
