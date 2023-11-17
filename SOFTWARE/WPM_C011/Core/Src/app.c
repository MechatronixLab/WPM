/*
 * app.c
 *
 *  Created on: Nov 10, 2023
 *      Author: André A. M. Araújo
 */

#include "app.h"

#include "main.h"
#include "tim.h"

#include "adconverter.h"
#include "console.h"
#include "max30102.h"
#include "oled_ssd1306.h"

#include <stdio.h>

uint16_t MAX30102_temperature = 0;
uint16_t MAX30102_id = 0;

int16_t  STM32C0_temperature = 0;

char 	string_buffer[80];

uint8_t i = 0;

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
	OLED_DrawLineV(63, 0, 63);

	HAL_ADCEx_Calibration_Start(&hadc1);									// Rotina de calibração do ADC
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buffer, ADC_ACTIVE_CHANNELS);	// Inicia operação do ADC com DMA para canais ativos
	HAL_TIM_Base_Start_IT(&htim3);											// Inicia base de tempo para coversões A/D (100 ms)

	OLED_Clear();

	while(1)
	{
		if (flag_ADC_EOC)
		{
			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);

			for (i = 0; i < ADC_ACTIVE_CHANNELS; i++)	// Conversão das leituras do ADC em tensão (mV)
			{
				adc_mV[i] = 3300 * adc_buffer[i] / 4095;
			}

			sprintf(string_buffer, "VR: %4d mV", adc_mV[0]);
			OLED_SetCursor(0, 3);
			OLED_DrawString((uint8_t *)font5x7, string_buffer);

			sprintf(string_buffer, "VT: %4d mV", adc_mV[1]);
			OLED_SetCursor(0, 4);
			OLED_DrawString((uint8_t *)font5x7, string_buffer);

			STM32C0_temperature  = (adc_mV[1] - 684) * 100 / 253;
			MAX30102_temperature = MAX30102_GetTemperature();


			sprintf(string_buffer, "STM32C011: %3d oC", STM32C0_temperature);
			OLED_SetCursor(0, 0);
			OLED_DrawString((uint8_t *)font5x7, string_buffer);


			sprintf(string_buffer, "MAX30102 : %3d oC", MAX30102_temperature);
			OLED_SetCursor(0, 1);
			OLED_DrawString((uint8_t *)font5x7, string_buffer);



			sprintf(string_buffer, "MAX30102 T: %d oC \r\n", MAX30102_temperature);
			CONSOLE_tx(string_buffer);

			flag_ADC_EOC = 0;

			HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);
		}
	}
}
