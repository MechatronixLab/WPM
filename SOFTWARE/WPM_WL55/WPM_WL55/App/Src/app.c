/*
 * app.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "app.h"

int32_t map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
  return (int32_t) ((x - 1.0 * in_min) * (1.0 * out_max - 1.0 * out_min) / (1.0 * in_max - 1.0 * in_min) + 1.0 * out_min);
}

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



	uint32_t pleth_min = 1 << 19;
	uint32_t pleth_max = 0x00000000;
	uint8_t pleth_x = 0;

	uint8_t graph_min = 32;
	uint8_t graph_max = 63;
	uint16_t graph_x = 0;
	uint8_t graph_y = 0;

	uint8_t graph_x_prev = 0;
	uint8_t graph_y_prev = 0;





	while(1)
	{	//LORA_Process();
		if (ISR_interrupt_flag)
		{
			ISR_interrupt_flag = 0;
			interrupt_counter++;

			IMU_GetData(&imu_data);
			OXIMETRY_GetRawData(&oximetry_raw_data);

			// TODO: oxim get raw data


			if (oximetry_raw_data.red < 1000)
			{
				oximetry_raw_data.red = 1;
			}

			if (oximetry_raw_data.red < pleth_min)
			{
				pleth_min = oximetry_raw_data.red;
			}

			if (oximetry_raw_data.red > pleth_max)
			{
				pleth_max = oximetry_raw_data.red;
			}


//			if (pleth_x = 0)
//			{
//				graph_min =
//
//			}

			graph_y = (uint8_t) map(oximetry_raw_data.red, pleth_min, pleth_max, graph_min, graph_max);
			if (graph_y == 0)
			{
				graph_y = 63;
			}

//			OLED_SetPixel(graph_x, graph_y);

//			GFX_DrawLine(graph_x_prev, graph_y_prev, graph_x, graph_y);
			GFX_DrawLine(graph_x, graph_y, graph_x, 63);

			graph_x_prev = graph_x;
			graph_y_prev = graph_y;

			graph_x++;
			if (graph_x > (SCREEN_WIDTH - 1))
			{
				graph_x = 0;
				graph_x_prev = 63;
				pleth_min = 1 << 19;
				pleth_max = 0x00000000;
				GFX_ClearFrame(GFX_frame_buffer);
			}

			sprintf(string_buffer, "%4d, %4d, %4d, %4d, %4d, %4d, %3d.%02d oC, R %6lu, IR %6lu \r\n",
								graph_x,
								graph_y,
								0,
								imu_data.acceleration[IMU_X],
								imu_data.acceleration[IMU_Y],
								imu_data.acceleration[IMU_Z],
								imu_data.temperature / 100,
							abs(imu_data.temperature % 100),
								oximetry_raw_data.red,
								oximetry_raw_data.infrared);
			CLI_Write(string_buffer);


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
//					"R:%6lu, AVG_R:%6lu, AC_R:%6ld, IR:%6lu, AVG_IR:%6lu, AC_IR:%6ld, AC_R:%6ld, AC_IR:%6ld, %d \r\n",
//					MAX30102_measurements.red,
//					average_red,
//					RMS_AC_red,
//					MAX30102_measurements.infrared,
//					average_infrared,
//					RMS_AC_infrared,
//					RMS_AC_red, RMS_AC_infrared, 0);
//			CLI_Write(string_buffer);


			if (interrupt_counter == (1000/(TIM16_ARR + 1)))	// 1 Hz
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
