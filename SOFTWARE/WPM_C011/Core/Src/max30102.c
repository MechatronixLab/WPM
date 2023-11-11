/*
 * max30102.c
 *
 *  Created on: Nov 10, 2023
 *      Author: André A. M. Araújo
 */

///////////////////////////////////////////////////////////////////////////////

#include "max30102.h"

void	MAX30102_ReadRegister(uint8_t register_address, uint8_t * I2C_buffer)
{
	I2C_buffer[0] = register_address;

	HAL_I2C_Master_Transmit(&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 1, MAX30102_I2C_TIMEOUT);
	HAL_I2C_Master_Receive (&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 1, MAX30102_I2C_TIMEOUT);
}

void	MAX30102_ReadRegisters(uint8_t register_address, uint8_t data_size, uint8_t * I2C_buffer)
{
	I2C_buffer[0] = register_address;

	HAL_I2C_Master_Transmit(&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 1, MAX30102_I2C_TIMEOUT);
	HAL_I2C_Master_Receive (&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, data_size, MAX30102_I2C_TIMEOUT);
}

void	MAX30102_WriteRegister(uint8_t register_address, uint8_t data)
{
	uint8_t I2C_buffer[2];

	I2C_buffer[0] = register_address;
	I2C_buffer[1] = data;

	HAL_I2C_Master_Transmit(&hi2c1, MAX30102_DEVICE_ADDRESS, I2C_buffer, 2, MAX30102_I2C_TIMEOUT);
}

void	MAX30102_UpdateRegister(uint8_t register_address, uint8_t mask, uint8_t data)
{
	uint8_t I2C_buffer[2];
	uint8_t old_data = 0;
	uint8_t new_data = 0;

	// Reads data on register address
	MAX30102_ReadRegister(register_address, I2C_buffer);

	// Masks device data to modify only required bits
	old_data = I2C_buffer[0];
	new_data = (old_data & mask) | data;

	// Writes updated data to register
	MAX30102_WriteRegister(register_address, new_data);
}

void	MAX30102_Reset(void)
{

}

int16_t MAX30102_GetTemperature(void)
{
	uint8_t I2C_buffer[2];
	uint16_t temperature = 0;

	MAX30102_WriteRegister(MAX30102_DIE_TEMPERATURE_CONFIG, 0x01);

	HAL_Delay(50);	// Datasheet states 29ms for T ADC acquisition time

	MAX30102_ReadRegisters(MAX30102_DIE_TEMPERATURE_INTEGER, 2, I2C_buffer);

	temperature = I2C_buffer[0];

	return temperature;
}

int16_t MAX30102_GetPartID(void)
{
	uint8_t I2C_buffer[2];
	uint16_t part_ID = 0;

	MAX30102_ReadRegisters(MAX30102_REVISION_ID, 2, I2C_buffer);

	part_ID = (I2C_buffer[0] << 8) + I2C_buffer[1];

	return part_ID;
}
