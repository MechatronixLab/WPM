/*
 * app.c
 *
 *  Created on: Nov 10, 2023
 *      Author: André A. M. Araújo
 */

#include "app.h"
#include "console.h"
#include "max30102.h"

void APP_init(void)
{
	CONSOLE_tx("Wearable Patient Monitor V 0.0.1 \r\n");

	while(1)
	{
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(50);
	}
}
