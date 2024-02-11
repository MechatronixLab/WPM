/*
 * imu.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "imu.h"

static ISDS_data_t ISDS_measurements;

void IMU_Init(void)
{
	if(ISDS_CommunicationCheck() == 0)
	{
		ISDS_SoftReset();
		ISDS_Init();
	}
	else
	{
		CLI_Write("Error communicating with IMU! \r\n");
	}
}

void IMU_GetData(IMU_data_t * data)
{
	ISDS_GetData(&ISDS_measurements);

	data->acceleration[IMU_X] = ISDS_measurements.acceleration[ISDS_X_AXIS];
	data->acceleration[IMU_Y] = ISDS_measurements.acceleration[ISDS_Y_AXIS];
	data->acceleration[IMU_Z] = ISDS_measurements.acceleration[ISDS_Z_AXIS];

	data->angular_rate[IMU_X] = ISDS_measurements.angular_rate[ISDS_X_AXIS];
	data->angular_rate[IMU_Y] = ISDS_measurements.angular_rate[ISDS_Y_AXIS];
	data->angular_rate[IMU_Z] = ISDS_measurements.angular_rate[ISDS_Z_AXIS];

	data->temperature = ISDS_measurements.temperature;
}
