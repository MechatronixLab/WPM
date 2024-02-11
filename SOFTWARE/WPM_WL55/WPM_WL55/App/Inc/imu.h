/*
 * imu.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_IMU_H_
#define INC_IMU_H_

#include "wsen-isds.h"

#include "cli.h"

#define IMU_X			0U
#define IMU_Y			1U
#define IMU_Z			2U

typedef struct
{
	int16_t acceleration[3];
	int16_t angular_rate[3];
	int16_t temperature;
} IMU_data_t;

void IMU_Init(void);
void IMU_GetData(IMU_data_t * data);

#endif /* INC_IMU_H_ */
