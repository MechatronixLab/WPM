/*
 * max30102.c
 *
 *  Created on: Nov 10, 2023
 *      Author: André A. M. Araújo
 */

////////////////////////////////////////////////////////////////////////////////

#include "max30102.h"

//MAX30102_data_t MAX30102_measurements;

void	MAX30102_Read	(uint8_t register_address, uint8_t data_size, uint8_t * I2C_buffer)
{
	I2C_buffer[0] = register_address;

	HAL_I2C_Master_Transmit(&MAX3010_I2C_HANDLE, MAX30102_DEVICE_ADDRESS, I2C_buffer,         1, MAX30102_I2C_TIMEOUT);
	HAL_I2C_Master_Receive (&MAX3010_I2C_HANDLE, MAX30102_DEVICE_ADDRESS, I2C_buffer, data_size, MAX30102_I2C_TIMEOUT);
}

void	MAX30102_Write	(uint8_t register_address, uint8_t data)
{
	uint8_t I2C_buffer[2];

	I2C_buffer[0] = register_address;
	I2C_buffer[1] = data;

	HAL_I2C_Master_Transmit(&MAX3010_I2C_HANDLE, MAX30102_DEVICE_ADDRESS, I2C_buffer,         2, MAX30102_I2C_TIMEOUT);
}

void	MAX30102_Update	(uint8_t register_address, uint8_t mask, uint8_t data)
{
	uint8_t I2C_buffer[2];
	uint8_t old_data = 0;
	uint8_t new_data = 0;

	// Reads data on register address
	MAX30102_Read(register_address, 1, I2C_buffer);

	// Masks device data to modify only required bits
	old_data = I2C_buffer[0];
	new_data = (old_data & mask) | data;

	// Writes updated data to register
	MAX30102_Write(register_address, new_data);
}

void	MAX30102_Reset(void)
{
	MAX30102_Update(MAX30102_MODE_CONFIG, 0xBF, 0x40);
	HAL_Delay(MAX30102_I2C_TIMEOUT);
}

// Configuration routine detailed on:
// analog.com/media/en/technical-documentation/user-guides/
//   max3010x-ev-kits-recommended-configurations-and-operating-profiles.pdf
void	MAX30102_ConfigProximityDetect(void)
{
	MAX30102_Write(MAX30102_INTERRUPT_STATUS_3, 0xD0);	// Enable PPG_RDY and PROX_INT

	MAX30102_Write(0x03, 0x00);
	MAX30102_Write(0x04, 0x00);
	MAX30102_Write(0x05, 0x00);
	MAX30102_Write(0x06, 0x00);

	MAX30102_Write(0x08, 0x4F);	// Rollover Enabled

	MAX30102_Write(0x09, 0x07);	// Multi LED mode

	MAX30102_Write(0x0A, 0x77);	// RGE 16384 nA, 100 Hz, 410.75 us (18-bit res.)

	MAX30102_Write(0x0C,  100);	// LED1: 10.0 mA
	MAX30102_Write(0x0D,  100);	// LED2: 10.0 mA

	MAX30102_Write(0x10, 0x24);	// Proximity LED PA

	MAX30102_Write(0x11, 0x21);	// Slot 2 = IR, Slot 1 = RED

	MAX30102_Write(0x30, 0x20);
}

void 	MAX30102_GetDataMulti(MAX30102_data_t * measurements)
{
	uint8_t I2C_buffer[6];

	MAX30102_Read(MAX30102_FIFO_WRITE_POINTER, 1, I2C_buffer);

//	fifo_write_pointer = I2C_buffer[0];

	MAX30102_Read(MAX30102_FIFO_DATA, 6, I2C_buffer);

	measurements->red 	   = ((I2C_buffer[0] & 0x03) << 16)	// 18-bit
					    	 | I2C_buffer[1] <<  8
					    	 | I2C_buffer[2];

	measurements->infrared = ((I2C_buffer[3] & 0x03) << 16)	// 18-bit
					    	 | I2C_buffer[4] <<  8
					         | I2C_buffer[5];
}

int16_t MAX30102_GetTemperature(void)
{
	uint8_t I2C_buffer[2];
	uint16_t temperature = 0;

	MAX30102_Write(MAX30102_DIE_TEMPERATURE_CONFIG, 0x01);

	HAL_Delay(30);	// Datasheet states 29ms for T ADC acquisition time

	MAX30102_Read(MAX30102_DIE_TEMPERATURE_INTEGER, 2, I2C_buffer);

	temperature = I2C_buffer[0];

	return temperature;
}

int16_t MAX30102_GetPartID(void)
{
	uint8_t I2C_buffer[2];
	uint16_t part_ID = 0;

	MAX30102_Read(MAX30102_REVISION_ID, 2, I2C_buffer);

	part_ID = (I2C_buffer[0] << 8) + I2C_buffer[1];

	return part_ID;
}
