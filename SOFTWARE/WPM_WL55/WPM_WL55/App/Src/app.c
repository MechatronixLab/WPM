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
	LORA_FSM_Init();	// TODO: Can I remove this?

	ISR_StartInterruptTimer();

	APP_Run();
}

void APP_Run(void)
{
	char string_buffer[128];

	uint32_t LORA_TX_counter = 0;
	uint8_t	 interrupt_counter = 0;

//	uint16_t MAX30102_temperature = 0;

//	int16_t	ISDS_temperature = 0;

	IMU_data_t imu_data = {0};
	OXIMETRY_raw_data_t oximetry_raw_data = {0};
	OXIMETRY_data_t oximetry_data = {0};

	while(1)
	{	//LORA_Process();
		if (ISR_interrupt_flag)
		{
			ISR_interrupt_flag = 0;
			interrupt_counter++;

			IMU_GetData(&imu_data);
			OXIMETRY_GetRawData(&oximetry_raw_data);

			// TODO: oxim get raw data

			sprintf(string_buffer, "%4d, %4d, %4d, %4d, %4d, %4d, %3d.%02d oC, R %6lu, IR %6lu \r\n",
								imu_data.angular_rate[IMU_X],
								imu_data.angular_rate[IMU_Y],
								imu_data.angular_rate[IMU_Z],
								imu_data.acceleration[IMU_X],
								imu_data.acceleration[IMU_Y],
								imu_data.acceleration[IMU_Z],
								imu_data.temperature / 100,
							abs(imu_data.temperature % 100),
								oximetry_raw_data.red,
								oximetry_raw_data.infrared);
			CLI_Write(string_buffer);




//			sprintf(string_buffer,
//					"R:%6lu, AVG_R:%6lu, AC_R:%6ld, IR:%6lu, AVG_IR:%6lu, AC_IR:%6ld, AC_R:%6ld, AC_IR:%6ld, %d \r\n",
//					MAX30102_measurements.red,
//					average_red,
//					RMS_AC_red,
//					MAX30102_measurements.infrared,
//					average_infrared,
//					RMS_AC_infrared,
//					RMS_AC_red, RMS_AC_infrared, 0);
//			CLI_Write(string_buffer);


			if (interrupt_counter == 50)	// 1 Hz
			{
				BSP_LED_On(LED_GREEN);

				interrupt_counter = 0;

//				MAX30102_temperature = MAX30102_GetTemperature();	// Takes 30ms
//				sprintf(string_buffer, "%3d oC", MAX30102_temperature);
//				OLED_SetCursor(66, 3);
//				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				OXIMETRY_ProcessData(&oximetry_data);

				if (oximetry_data.spo2 > 0)
				{
					sprintf(string_buffer, "SpO2:%3d%% ", (uint16_t)oximetry_data.spo2);
				}
				else
				{
					sprintf(string_buffer, "SpO2:---%% ");
				}
				OLED_SetCursor(0, 0);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				if (oximetry_data.heart_rate > 0)
				{
					sprintf(string_buffer, "HR:%3dbpm ", (uint16_t)oximetry_data.heart_rate);
				}
				else
				{
					sprintf(string_buffer, "HR:---bpm ");
				}
				OLED_SetCursor(64, 0);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				sprintf(string_buffer, "T:%3d.%02doC",
										imu_data.temperature / 100,
									abs(imu_data.temperature % 100));
				OLED_SetCursor(0, 1);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				LORA_TX_counter++;
				sprintf(string_buffer, "TX:%5lu", LORA_TX_counter);
				LORA_Tx(string_buffer);
				OLED_SetCursor(64, 1);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				BSP_LED_Off(LED_GREEN);
			}
		}
	}
}
