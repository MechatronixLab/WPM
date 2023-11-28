/*
 * wsen-isds.c
 *
 *  Created on: Nov 24, 2023
 *      Author: Andre
 */

#include "wsen-isds.h"

ISDS_data_t ISDS_measurements;

uint8_t ISDS_CommunicationCheck(void)
{
	uint8_t I2C_buffer[1];
	uint8_t status = 0;

	I2C_buffer[0] = ISDS_DEVICE_ID;

	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);
	HAL_I2C_Master_Receive (&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);

	if (I2C_buffer[0] == 0x6A)
	{
		status = 0;
	}
	else
	{
		status = 0xFF;
	}

	return status;
}

uint8_t	ISDS_SoftReset(void)
{
	uint8_t I2C_buffer[2];

	I2C_buffer[0] = ISDS_CTRL3_C;
	I2C_buffer[1] = 0x01;

	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);

	HAL_Delay(1);

	I2C_buffer[0] = ISDS_CTRL3_C;
	I2C_buffer[1] = 0x80;

	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);

	HAL_Delay(20);

	return ISDS_CommunicationCheck();
}

void	ISDS_Init(void)
{
	uint8_t I2C_buffer[2];

	// Sensor in power down mode
	// Enable high performance mode
	// Select output data rate 208 Hz
	I2C_buffer[0] = ISDS_CTRL1_XL;
	I2C_buffer[1] = 0x54;
	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);

	I2C_buffer[0] = ISDS_CTRL2_G;
	I2C_buffer[1] = 0x5C;
	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);

//	I2C_buffer[0] = ISDS_CTRL6_C;
//	I2C_buffer[1] = 0x8;
//	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);
//
//	I2C_buffer[0] = ISDS_CTRL7_G;
//	I2C_buffer[1] = 0x;
//	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);
//
	// Enable block data update
	// Enable automatic address increment
	I2C_buffer[0] = ISDS_CTRL3_C;
	I2C_buffer[1] = 0x04;
	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);
//
//	// Select bandwidth: ODR/2 Hz
//	// Select full scale: +/- 16 g, +/- 2000 dps
//	I2C_buffer[0] = ISDS_CTRL1_XL;
//	I2C_buffer[1] = 0x;
//	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);
//
//	I2C_buffer[0] = ISDS_CTRL8_XL;
//	I2C_buffer[1] = 0x;
//	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);
//
//	I2C_buffer[0] = ISDS_CTRL6_C;
//	I2C_buffer[1] = 0x;
//	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);
//
//	I2C_buffer[0] = ISDS_CTRL2_G;
//	I2C_buffer[1] = 0x;
//	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);

	// Read XLDA and GDA bit in status register
	I2C_buffer[0] = ISDS_STATUS_REG;

	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);
	HAL_I2C_Master_Receive (&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);

	// If XLDA and GDA == 0, no data

	// Else

	// Request data from output register G_X_OUT_L, etc

	// Concatenate bytes into 16bit var

	// Multiply by sensitivity

	// Output in g and dps

	// repeat


}

int16_t	ISDS_GetTemperature(void)
{
	int16_t temperature = 0;

	uint8_t I2C_buffer[2];

	I2C_buffer[0] = ISDS_T_OUT_L;

	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);
	HAL_I2C_Master_Receive (&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 2, ISDS_I2C_TIMEOUT);

//	temperature  = I2C_buffer[0];
//
//	I2C_buffer[0] = ISDS_T_OUT_H;
//
//	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);
//	HAL_I2C_Master_Receive (&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);
//
//	temperature |= I2C_buffer[0] << 8;

	temperature = (int16_t) ( (I2C_buffer[1] << 8)  + I2C_buffer[0] );
	//temperature = (int16_t) ((float) temperature * 0.390625f + 25.0f);

	return temperature;
}

void 	ISDS_GetData(ISDS_data_t * measurements)
{
	uint8_t I2C_buffer[14];

	I2C_buffer[0] = ISDS_T_OUT_L;

	HAL_I2C_Master_Transmit(&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 1, ISDS_I2C_TIMEOUT);
	HAL_I2C_Master_Receive (&hi2c1, ISDS_DEVICE_ADDRESS, I2C_buffer, 14, ISDS_I2C_TIMEOUT);

	measurements->temperature 				= (int16_t) ((I2C_buffer[ 1] << 8) | I2C_buffer[ 0] );
	measurements->temperature = (int16_t) ((float) measurements->temperature * 0.390625f + 25.0f);

	measurements->angular_rate[ISDS_X_AXIS] = (int16_t) ((I2C_buffer[ 3] << 8) | I2C_buffer[ 2]) * 70 / 1000;	// mdps
	measurements->angular_rate[ISDS_Y_AXIS] = (int16_t) ((I2C_buffer[ 5] << 8) | I2C_buffer[ 4]) * 70 / 1000;	// mdps
	measurements->angular_rate[ISDS_Z_AXIS] = (int16_t) ((I2C_buffer[ 7] << 8) | I2C_buffer[ 6]) * 70 / 1000;	// mdps

	measurements->acceleration[ISDS_X_AXIS] = (int16_t) ((I2C_buffer[ 9] << 8) | I2C_buffer[ 8]) * 488 / 1000;	// mg
	measurements->acceleration[ISDS_Y_AXIS] = (int16_t) ((I2C_buffer[11] << 8) | I2C_buffer[10]) * 488 / 1000;	// mg
	measurements->acceleration[ISDS_Z_AXIS] = (int16_t) ((I2C_buffer[13] << 8) | I2C_buffer[12]) * 488 / 1000;	// mg
}























