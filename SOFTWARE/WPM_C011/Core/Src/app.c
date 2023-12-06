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
#include "graphics.h"
#include "max30102.h"
#include "oled_ssd1306.h"
#include "wsen-isds.h"

#include <stdio.h>

uint16_t MAX30102_temperature = 0;
uint16_t MAX30102_id = 0;

int16_t  STM32C0_temperature = 0;
int16_t  ISDS_temperature = 0;


char 	string_buffer[128];

uint16_t i = 0;

uint8_t screen_counter = 0;

void APP_Run(void)
{
	CONSOLE_tx("Wearable Patient Monitor V 0.0.1 \r\n");

	MAX30102_id = MAX30102_GetPartID();

	sprintf(string_buffer, "MAX30102 - Revision: %3d, ID: 0x%02x \r\n",
						   (MAX30102_id >> 8), (MAX30102_id & 0x00FF));
	CONSOLE_tx(string_buffer);

	OLED_Init();
	GFX_DrawLogo();

	OLED_SetCursor(64, 0);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "WPM-C011.001");

	sprintf(string_buffer, "MAX30102 R%d", (MAX30102_id >> 8));
	OLED_SetCursor(64, 1);
	GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

	MAX30102_Reset();
	MAX30102_ConfigProximityDetect();

	OLED_Clear();

//	for (i = 0; i < 1024; i++)
//	{
//		OLED_frame_buffer[i] = i & 0xFF;
//	}
//	OLED_DrawFrame(OLED_frame_buffer);
//
//	GFX_DrawLine(   0,   0, 127,   7);
//	GFX_DrawLine(   0,   0, 127,  15);
//	GFX_DrawLine(   0,   0, 127,  31);
//	GFX_DrawLine(   0,   0, 127,  63);
//
//	GFX_DrawLine(   0,   0,  64,  63);
//
//	GFX_DrawLine(   0,  32,  32,  63);
//
//	GFX_ClearFrame(GFX_frame_buffer);
//	OLED_Clear();
//
//	GFX_DrawLine(  32,  32,  63,  63);
//	GFX_DrawLine(   0,  32,  32,  63);
//
//
//
//	GFX_DrawLine(  0,  0, 127,  0);
//	GFX_DrawHorizontalLine(0, 2, 128);
//	GFX_DrawVerticalLine(63, 0, 63);

//	GFX_DrawLine(  0,  0, 128,  0);
//	GFX_DrawLine(  0,  0,   0, 63);
//	GFX_DrawLine(127,  0,   0, 63);
//	GFX_DrawLine(  0, 63, 128,  0);
//
//	GFX_DrawLine(  0,  0,  64, 64);
//
//	GFX_DrawRectangle(15, 15, (128-32), (64-32));

	GFX_ClearFrame(GFX_frame_buffer);
	OLED_Clear();

	GFX_DrawLine(63, 31, 127, 31);
	GFX_DrawLine(63, 31, 127, 47);
	GFX_DrawLine(63, 31, 127, 63);
	GFX_DrawLine(63, 31,  95, 63);
	GFX_DrawLine(63, 31,  63, 63);
	GFX_DrawLine(63, 31,  31, 63);
	GFX_DrawLine(63, 31,   0, 63);
	GFX_DrawLine(63, 31,   0, 47);
	GFX_DrawLine(63, 31,   0, 31);
	GFX_DrawLine(63, 31,   0, 15);
	GFX_DrawLine(63, 31,   0,  0);
	GFX_DrawLine(63, 31,  31,  0);
	GFX_DrawLine(63, 31,  63,  0);
	GFX_DrawLine(63, 31,  95,  0);
	GFX_DrawLine(63, 31, 127,  0);
	GFX_DrawLine(63, 31, 127, 15);

	GFX_ClearFrame(GFX_frame_buffer);
	OLED_Clear();

	GFX_DrawTriangle(24, 12, 96, 48, 32, 60);

	HAL_ADCEx_Calibration_Start(&hadc1);									// Rotina de calibração do ADC
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_buffer, ADC_ACTIVE_CHANNELS);	// Inicia operação do ADC com DMA para canais ativos
	HAL_TIM_Base_Start_IT(&htim3);											// Inicia base de tempo para coversões A/D (100 ms)

	OLED_Clear();

	if (ISDS_SoftReset() == 0)
	{
		OLED_SetCursor(0, 2);
		GFX_DrawString((uint8_t *)GFX_font_5x7, "ISDS Status: OK");

		ISDS_Init();

	}
	else
	{
		OLED_SetCursor(0, 2);
		GFX_DrawString((uint8_t *)GFX_font_5x7, "ISDS Status: FAIL");
	}

	while(1)
	{
		if (flag_ADC_EOC)
		{
			ISDS_GetData(&ISDS_measurements);

			//sprintf(string_buffer, "Angular Rate: x: %4d, y: %4d, z: %4d, Acceleration: x: %4d, y: %4d, z: %4d, Temperature: %3d.%02d oC \r\n",
			sprintf(string_buffer, "%4d, %4d, %4d, %4d, %4d, %4d, %3d.%02d oC \r\n",
									ISDS_measurements.angular_rate[ISDS_X_AXIS],
									ISDS_measurements.angular_rate[ISDS_Y_AXIS],
									ISDS_measurements.angular_rate[ISDS_Z_AXIS],
									ISDS_measurements.acceleration[ISDS_X_AXIS],
									ISDS_measurements.acceleration[ISDS_Y_AXIS],
									ISDS_measurements.acceleration[ISDS_Z_AXIS],
									ISDS_measurements.temperature / 100,
								abs(ISDS_measurements.temperature % 100));
			CONSOLE_tx(string_buffer);

			screen_counter++;

			if (screen_counter == 100)	// 40ms
			{
				screen_counter = 0;


				for (i = 0; i < ADC_ACTIVE_CHANNELS; i++)	// Conversão das leituras do ADC em tensão (mV)
				{
					adc_mV[i] = 3300 * adc_buffer[i] / 4095;
				}

				STM32C0_temperature  = (adc_mV[1] - 684) * 100 / 253;


				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1);
				MAX30102_temperature = MAX30102_GetTemperature();
				HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0);

				sprintf(string_buffer, "VR: %4d mV", adc_mV[0]);
				OLED_SetCursor(0, 3);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				sprintf(string_buffer, "VT: %4d mV", adc_mV[1]);
				OLED_SetCursor(0, 4);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				sprintf(string_buffer, "STM32C011: %3d oC", STM32C0_temperature);
				OLED_SetCursor(0, 0);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				sprintf(string_buffer, "MAX30102 : %3d oC", MAX30102_temperature);
				OLED_SetCursor(0, 1);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				sprintf(string_buffer, "WSEN-ISDS: %3d.%2d oC",
										ISDS_measurements.temperature/100,
										ISDS_measurements.temperature%100);
				OLED_SetCursor(0, 2);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);
			}

			flag_ADC_EOC = 0;
		}
	}
}
