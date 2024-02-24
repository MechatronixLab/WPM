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

	APP_Run();
}

void APP_Run(void)
{
	char string_buffer[128];

	uint32_t LORA_TX_counter = 0;
	uint8_t	 interrupt_counter = 0;

	IMU_data_t imu_data = {0};
	//OXIMETRY_raw_data_t oximetry_raw_data = {0};
	OXIMETRY_data_t oximetry_data = {0};

	BUZZER_SetVolume(1);

	while(1)
	{	//LORA_Process();
		if (ISR_interrupt_flag)
		{
			ISR_interrupt_flag = 0;
			interrupt_counter++;

			IMU_GetData(&imu_data);

			OXIMETRY_ProcessDataWPM(&oximetry_data);
			DISPLAY_DrawPleth(&oximetry_data);

//			sprintf(string_buffer, "%4d, %4d, %4d, %4d, %4d, %4d, %3d.%02d oC, R %6lu, IR %6lu \r\n",
//								0,
//								0,
//								0,
//								imu_data.acceleration[IMU_X],
//								imu_data.acceleration[IMU_Y],
//								imu_data.acceleration[IMU_Z],
//								imu_data.temperature / 100,
//							abs(imu_data.temperature % 100),
//								oximetry_raw_data.red,
//								oximetry_raw_data.infrared);
//			CLI_Write(string_buffer);


//			sprintf(string_buffer, "%4d, %4d, %4d, %4d, %4d, %4d, %3d.%02d oC, R %6lu, IR %6lu \r\n",
//								imu_data.angular_rate[IMU_X],
//								imu_data.angular_rate[IMU_Y],
//								imu_data.angular_rate[IMU_Z],
//								imu_data.acceleration[IMU_X],
//								imu_data.acceleration[IMU_Y],
//								imu_data.acceleration[IMU_Z],
//								imu_data.temperature / 100,
//							abs(imu_data.temperature % 100),
//								oximetry_raw_data.red,
//								oximetry_raw_data.infrared);
//			CLI_Write(string_buffer);

//			sprintf(string_buffer,
//					"R:%6lu, DC_R:%6lu, AC_R:%6ld, IR:%6lu, DC_IR:%6lu, AC_IR:%6ld, RATIO:%f, SpO2:%6ld, %ld \r\n",
//					oximetry_raw_data.red,
//					DC_red,
//					RMS_AC_red,
//					oximetry_raw_data.infrared,
//					DC_infrared,
//					RMS_AC_infrared,
//					ratio, ox_spo2, 0L);
//			CLI_Write(string_buffer);


			sprintf(string_buffer,
					"AC_R:%6lu, DRDTR:%6ld, -:%6ld, AC_IR:%6lu, DIRDT:%6ld, -:%6ld, RATIO:%f, SpO2:%6ld, %d \r\n",
					oximetry_data.RMS_AC_red,
					oximetry_data.dred_dt, 0L,
					oximetry_data.RMS_AC_infrared,
					oximetry_data.dinfrared_dt, 0L,
					oximetry_data.ratio, oximetry_data.spo2, oximetry_data.heart_rate);
			CLI_Write(string_buffer);

			if (oximetry_data.heart_beep)
			{
				BUZZER_On();
			}
			else
			{
				BUZZER_Off();
			}


			if (interrupt_counter == (1000/(TIM16_ARR + 1)))	// 1 Hz
			{
				BSP_LED_On(LED_GREEN);

				interrupt_counter = 0;

//				MAX30102_temperature = MAX30102_GetTemperature();	// Takes 30ms
//				sprintf(string_buffer, "%3d oC", MAX30102_temperature);
//				OLED_SetCursor(66, 3);
//				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				//OXIMETRY_ProcessDataMaxim(&oximetry_data);

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

				HAL_Delay(5);
				BSP_LED_Off(LED_GREEN);
			}
		}
	}
}
