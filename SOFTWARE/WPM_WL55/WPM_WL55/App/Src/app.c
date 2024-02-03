/*
 * app.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "app.h"

extern UART_HandleTypeDef huart2;



void APP_Init(void)
{
	uint8_t 	i = 0;
	uint16_t	dt = 100;

	CLI_NewLine();
	CLI_Write("------------------------ \r\n");
	CLI_Write("Wearable Patient Monitor \r\n");
	CLI_Write("Version: 0.0.1 \r\n");
	CLI_Write("------------------------ \r\n");
	CLI_NewLine();

	OLED_Init();
	GFX_DrawLogo();
	OLED_SetCursor(66, 0);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "WPM-WL55");
	OLED_SetCursor(66, 1);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "V: 0.0.1");

	for (i = 0; i < 6; i++)	// Sweep LEDs thrice
	{
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		HAL_Delay(dt);
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		HAL_Delay(dt);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(dt);
	}

	LORA_RadioInit();
	LORA_FSM_Init();

	ISR_StartInterruptTimer();

	APP_Run();
}

void APP_Run(void)
{
	uint32_t counter = 0;
	char string_buffer[64];

	while(1)
	{	//LORA_Process();
		BSP_LED_On(LED_BLUE);

		sprintf(string_buffer, "TX: %lu", counter);

		LORA_Tx(string_buffer);

		OLED_SetCursor(66, 2);
		GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

		HAL_Delay(250);
		BSP_LED_Off(LED_BLUE);
		HAL_Delay(750);

		counter++;
	}
}
