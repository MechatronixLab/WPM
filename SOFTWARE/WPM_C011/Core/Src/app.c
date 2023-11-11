/*
 * app.c
 *
 *  Created on: Nov 10, 2023
 *      Author: André A. M. Araújo
 */

#include "app.h"
#include "console.h"
#include "max30102.h"

#include <stdio.h>

uint16_t	MAX30102_temperature = 0;
uint16_t	MAX30102_id = 0;

char string_buffer[80];

void APP_init(void)
{
	CONSOLE_tx("Wearable Patient Monitor V 0.0.1 \r\n");

	MAX30102_id = MAX30102_GetPartID();

	sprintf(string_buffer, "MAX30102 - Revision: %3d, ID: 0x%02x \r\n",
							(MAX30102_id >> 8), (MAX30102_id & 0x00FF));
	CONSOLE_tx(string_buffer);

	//MAX30102_EnableTemperature();

	while(1)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);

		MAX30102_temperature = MAX30102_GetTemperature();

		sprintf(string_buffer, "MAX30102_temperature: %d oC \r\n", MAX30102_temperature);
		CONSOLE_tx(string_buffer);

		HAL_Delay(250);

		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
		HAL_Delay(250);
	}
}