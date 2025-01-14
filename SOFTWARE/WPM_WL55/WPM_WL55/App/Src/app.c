/*
 * app.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "app.h"

void APP_Init(void)
{
	CONSOLE_Init();
	DISPLAY_Init();
	IMU_Init();
	OXIMETRY_Init();
	LORA_RadioInit();
	//LORA_FSM_Init();	// TODO: Can I remove this? - YES (for TX; not sure for LoRa RX)
	ISR_StartInterruptTimer();
	BUZZER_SetVolume(1);

	APP_Run();
}

void APP_Run(void)
{
	char string_buffer[128];

	uint8_t	 interrupt_counter = (1000/(TIM16_ARR + 1)) - 1; // To print whole screen on first run

	IMU_data_t 		imu_data      = {0};
	OXIMETRY_data_t oximetry_data = {0};

	while(1)
	{	//LORA_Process();
		if (ISR_interrupt_flag)
		{
			ISR_interrupt_flag = 0;
			interrupt_counter++;

			IMU_GetData(&imu_data);

			OXIMETRY_ProcessDataWPM(&oximetry_data);
			DISPLAY_DrawPleth(&oximetry_data);

			sprintf(string_buffer, "deg/s: X%4d, Y%4d, Z%4d, m/ss: X%4d, Y%4d, Z%4d, T:%3d.%02doC, OXIMETRY: RED%6lu, INFRARED:%6lu \r\n",
									imu_data.angular_rate[IMU_X],
									imu_data.angular_rate[IMU_Y],
									imu_data.angular_rate[IMU_Z],
									imu_data.acceleration[IMU_X],
									imu_data.acceleration[IMU_Y],
									imu_data.acceleration[IMU_Z],
									imu_data.temperature / 100,
								abs(imu_data.temperature % 100),
									oximetry_data.red,
									oximetry_data.infrared);
			CLI_Write(string_buffer);

//			sprintf(string_buffer,
//					"AC_R:%6lu, DRDTR:%6ld, -:%6ld, AC_IR:%6lu, DIRDT:%6ld, -:%6ld, RATIO:%d, SpO2:%6d, %6d \r\n",
//					oximetry_data.RMS_AC_red,
//					oximetry_data.dred_dt, 0L,
//					oximetry_data.RMS_AC_infrared,
//					oximetry_data.dinfrared_dt, 0L,
//					oximetry_data.ratio, oximetry_data.spo2, oximetry_data.heart_rate);
//			CLI_Write(string_buffer);

			if (oximetry_data.heart_beat)
			{
				BUZZER_On();
				BSP_LED_On(LED_RED);
			}
			else
			{
				BUZZER_Off();
				BSP_LED_Off(LED_RED);
			}

			if (interrupt_counter == (1000/(TIM16_ARR + 1)))	// 1 Hz
			{
				BSP_LED_On(LED_GREEN);

				interrupt_counter = 0;

				// OXIMETRY_ProcessDataMaxim(&oximetry_data);
				// This algorithm from MAXIM did not work well. I suppose it
				// needs sample rate of 100Hz or more to work well.
				// However, the display update algorithms need to be improved
				// in order to reduce drawing times and to allow higher
				// oximetry sample rate.

				if (oximetry_data.valid_heart_rate)
				{
					sprintf(string_buffer, "SpO2:%3d.%1d%%",
							               (uint16_t)oximetry_data.spo2 / 10,
										   (uint16_t)oximetry_data.spo2 % 10);
					OLED_SetCursor(0, 0);
					GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

					sprintf(string_buffer, "HR:%3dbpm",
										   (uint16_t)oximetry_data.heart_rate);
					OLED_SetCursor(73, 0);
					GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

					sprintf(string_buffer, "PInd:%3d.%1d%%",
										   (uint16_t)oximetry_data.perfusion_index / 10,
										   (uint16_t)oximetry_data.perfusion_index % 10);
					OLED_SetCursor(0, 2);
					GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);
				}
				else
				{
					sprintf(string_buffer, "SpO2:-----%%");
					OLED_SetCursor(0, 0);
					GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

					sprintf(string_buffer, "HR:---bpm");
					OLED_SetCursor(73, 0);
					GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

					sprintf(string_buffer, "PInd:-----%%");
					OLED_SetCursor(0, 2);
					GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);
				}

				sprintf(string_buffer, "T:%3ld.%1ld\177C",
									   (oximetry_data.temperature >> 16) & 0xFF,
							          ((oximetry_data.temperature & 0x0000FFFF)/1000)%1000);
				OLED_SetCursor(73, 2);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				// Data transmission via LoRa //////////////////////////////////
				sprintf(string_buffer, "SpO2:%3d.%1d%%, HR:%3dbpm, PInd:%3d.%1d%%, T:%3ld.%1ldoC",
									   (uint16_t)oximetry_data.spo2 / 10,
									   (uint16_t)oximetry_data.spo2 % 10,
									   (uint16_t)oximetry_data.heart_rate,
									   (uint16_t)oximetry_data.perfusion_index / 10,
									   (uint16_t)oximetry_data.perfusion_index % 10,
									   (oximetry_data.temperature >> 16) & 0xFF,
									  ((oximetry_data.temperature & 0x0000FFFF)/1000)%1000);
				LORA_Tx(string_buffer);

				BSP_LED_Off(LED_GREEN);
			}
		}
	}
}
