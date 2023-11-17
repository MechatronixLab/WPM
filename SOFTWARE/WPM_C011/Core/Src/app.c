/*
 * app.c
 *
 *  Created on: Nov 10, 2023
 *      Author: André A. M. Araújo
 */

#include "app.h"
#include "console.h"
#include "display_oled.h"
#include "max30102.h"


#include <stdio.h>

uint16_t MAX30102_temperature = 0;
uint16_t MAX30102_id = 0;

char 	string_buffer[80];

void APP_Run(void)
{
	CONSOLE_tx("Wearable Patient Monitor V 0.0.1 \r\n");

	MAX30102_id = MAX30102_GetPartID();

	sprintf(string_buffer, "MAX30102 - Revision: %3d, ID: 0x%02x \r\n",
						   (MAX30102_id >> 8), (MAX30102_id & 0x00FF));
	CONSOLE_tx(string_buffer);

	OLED_Init();
	OLED_SetCursor(64, 0);
	OLED_DrawString((uint8_t *)font5x7, "WPM-C011.001");

	sprintf(string_buffer, "MAX30102 R%d", (MAX30102_id >> 8));
	OLED_SetCursor(64, 1);
	OLED_DrawString((uint8_t *)font5x7, string_buffer);

	MAX30102_Reset();
	MAX30102_ConfigProximityDetect();

	OLED_Clear();
	OLED_DrawLine(  0,  0, 127, 63);

	OLED_Clear();
	OLED_DrawLine(  0,  0, 127,  0);
	OLED_DrawLineH(0, 2, 128);

	OLED_Clear();
	OLED_DrawLine(127,  0,   0, 63);

	OLED_Clear();
	OLED_DrawLine(127,  0,   0, 63);

//	OLED_DrawLine(  0, 31, 127, 31);
//	OLED_DrawLine( 63,  0,  63, 63);
//	OLED_DrawLine(  0, 63, 127,  0);

	while(1)
	{
		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);

		MAX30102_temperature = MAX30102_GetTemperature();

		sprintf(string_buffer, "MAX30102 Temperature: %d oC \r\n", MAX30102_temperature);
		CONSOLE_tx(string_buffer);

		sprintf(string_buffer, "%d oC", MAX30102_temperature);
		OLED_SetCursor(64, 2);
		OLED_DrawString((uint8_t *)font5x7, string_buffer);

		HAL_Delay(500);

		OLED_LightBG();

		HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
		HAL_Delay(500);

		OLED_DarkBG();
	}
}
