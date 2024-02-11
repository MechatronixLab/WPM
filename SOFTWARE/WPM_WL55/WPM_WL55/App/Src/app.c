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

	LORA_RadioInit();
	LORA_FSM_Init();	// TODO: Can I remove this?

	// TODO: move to imu.c


	// TODO: move to oximetry.c
	MAX30102_Reset();
	MAX30102_ConfigProximityDetect();

	ISR_StartInterruptTimer();

	APP_Run();
}

void APP_Run(void)
{
	uint32_t LORA_TX_counter = 0;
	uint8_t	 interrupt_counter = 0;
	char string_buffer[128];

//	uint16_t MAX30102_temperature = 0;

	int16_t	ISDS_temperature = 0;

	IMU_data_t IMU_data = {0};


	MAX30102_data_t MAX30102_measurements;

	int32_t buffer_red[MOVING_AVERAGE_PERIOD] = {0};
	circular_buffer_t circular_red =
	{
			.buffer = buffer_red,
			.head = 0,
			.tail = 0,
			.length = MOVING_AVERAGE_PERIOD
	};

	int32_t buffer_infrared[MOVING_AVERAGE_PERIOD] = {0};
	circular_buffer_t circular_infrared =
	{
			.buffer = buffer_infrared,
			.head = 0,
			.tail = 0,
			.length = MOVING_AVERAGE_PERIOD
	};

	int32_t buffer_AC_red[MOVING_AVERAGE_PERIOD] = {0};
	circular_buffer_t circular_AC_red =
	{
			.buffer = buffer_AC_red,
			.head = 0,
			.tail = 0,
			.length = MOVING_AVERAGE_PERIOD
	};

	int32_t buffer_AC_infrared[MOVING_AVERAGE_PERIOD] = {0};
	circular_buffer_t circular_AC_infrared =
	{
			.buffer = buffer_AC_infrared,
			.head = 0,
			.tail = 0,
			.length = MOVING_AVERAGE_PERIOD
	};

	uint32_t average_red = 0;
	uint32_t average_infrared = 0;

	uint32_t RMS_AC_red = 0;
	uint32_t RMS_AC_infrared = 0;

	int32_t spo2;
	int8_t  spo2_valid;
	int32_t heart_rate;
	int8_t  heart_rate_valid;

	while(1)
	{	//LORA_Process();
		if (ISR_interrupt_flag)
		{
			ISR_interrupt_flag = 0;
			interrupt_counter++;

			IMU_GetData(&IMU_data);

			MAX30102_GetDataMulti(&MAX30102_measurements);

			sprintf(string_buffer, "%4d, %4d, %4d, %4d, %4d, %4d, %3d.%02d oC, R %6lu, IR %6lu \r\n",
								IMU_data.angular_rate[IMU_X],
								IMU_data.angular_rate[IMU_Y],
								IMU_data.angular_rate[IMU_Z],
								IMU_data.acceleration[IMU_X],
								IMU_data.acceleration[IMU_Y],
								IMU_data.acceleration[IMU_Z],
								IMU_data.temperature / 100,
							abs(IMU_data.temperature % 100),
								MAX30102_measurements.red,
								MAX30102_measurements.infrared);
			CLI_Write(string_buffer);

			CIRCULAR_Push(&circular_red, MAX30102_measurements.red);
			CIRCULAR_Push(&circular_infrared, MAX30102_measurements.infrared);

			average_red = AVERAGE_avg((uint32_t *)circular_red.buffer, MOVING_AVERAGE_PERIOD);
			average_infrared = AVERAGE_avg((uint32_t *)circular_infrared.buffer, MOVING_AVERAGE_PERIOD);

			CIRCULAR_Push(&circular_AC_red, pow((float)(MAX30102_measurements.red - average_red), 2));
			CIRCULAR_Push(&circular_AC_infrared, pow((float)(MAX30102_measurements.infrared - average_infrared), 2));

			RMS_AC_red = (uint32_t) sqrt(AVERAGE_avg((uint32_t *)circular_AC_red.buffer, MOVING_AVERAGE_PERIOD));
			RMS_AC_infrared = (uint32_t) sqrt(AVERAGE_avg((uint32_t *)circular_AC_infrared.buffer, MOVING_AVERAGE_PERIOD));


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
				interrupt_counter = 0;

//				sprintf(string_buffer, "%3d.%02d oC",
//										ISDS_measurements.temperature / 100,
//									abs(ISDS_measurements.temperature % 100));

				BSP_LED_On(LED_GREEN);
				MAXIM_HeartRate_SpO2((uint32_t *)circular_infrared.buffer, MOVING_AVERAGE_PERIOD,
						             (uint32_t *)circular_red.buffer,
									 &spo2, &spo2_valid,
									 &heart_rate, &heart_rate_valid);

				BSP_LED_Off(LED_GREEN);

				ISDS_temperature = ISDS_GetTemperature();
				sprintf(string_buffer, "%3d.%02d oC",
										ISDS_temperature / 100,
									abs(ISDS_temperature % 100));
				OLED_SetCursor(66, 2);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

//				MAX30102_temperature = MAX30102_GetTemperature();	// Takes 30ms
//				sprintf(string_buffer, "%3d oC", MAX30102_temperature);
//				OLED_SetCursor(66, 3);
//				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				if (spo2_valid)
				{
					sprintf(string_buffer, "SpO2:%3d%% ", (uint16_t)spo2);
				}
				else
				{
					sprintf(string_buffer, "SpO2:---%% ");
				}
				OLED_SetCursor(66, 4);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				if (heart_rate_valid)
				{
					sprintf(string_buffer, "HR:%3dbpm ", (uint16_t)heart_rate);
				}
				else
				{
					sprintf(string_buffer, "HR:---bpm ");
				}
				OLED_SetCursor(66, 5);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);

				sprintf(string_buffer, "TX: %lu", LORA_TX_counter);
				LORA_Tx(string_buffer);
				LORA_TX_counter++;

				OLED_SetCursor(66, 7);
				GFX_DrawString((uint8_t *)GFX_font_5x7, string_buffer);
			}
		}
	}
}
