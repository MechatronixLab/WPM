/*
 * wsen-isds.c
 *
 *  Created on: Nov 24, 2023
 *      Author: Andre
 */

#include "wsen-isds.h"

uint8_t ISDS_CommunicationCheck(void)
{
	uint8_t I2C_buffer[1];
	uint8_t status = 0;

	I2C_buffer[0] = ISDS_DEVICE_ID;

	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);
	HAL_I2C_Master_Receive (&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);

	if (I2C_buffer[0] == 0x6A)
	{
		status = 1;
	}
	else
	{
		status = 0;
	}

	return status;
}

