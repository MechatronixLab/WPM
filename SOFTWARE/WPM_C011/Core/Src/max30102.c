/*
 * max30102.c
 *
 *  Created on: Nov 10, 2023
 *      Author: André A. M. Araújo
 */

///////////////////////////////////////////////////////////////////////////////

#include "max30102.h"

void 	MAX30102_EnableTemperature(void)
{
	uint8_t I2C_buffer[1];

	I2C_buffer[0] = MAX30102_DIE_TEMPERATURE_CONFIG;

	HAL_I2C_Master_Transmit(&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 1, 5);
}

int16_t MAX30102_GetTemperature(void)
{
	uint8_t I2C_buffer[2];
	uint16_t temperature = 0;

	I2C_buffer[0] = MAX30102_DIE_TEMPERATURE_INTEGER;

	HAL_I2C_Master_Transmit(&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 1, 5);
	HAL_I2C_Master_Receive (&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 2, 5);

	temperature = I2C_buffer[0];

	return temperature;
}

int16_t MAX30102_GetPartID(void)
{
	uint8_t I2C_buffer[2];
	uint16_t part_ID = 0;

	I2C_buffer[0] = MAX30102_REVISION_ID;

	HAL_I2C_Master_Transmit(&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 1, 5);
	HAL_I2C_Master_Receive (&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 2, 5);

	part_ID = (I2C_buffer[0] << 8) + I2C_buffer[1];

	return part_ID;
}
