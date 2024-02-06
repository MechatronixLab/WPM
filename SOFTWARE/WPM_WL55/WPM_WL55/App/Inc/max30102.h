/*
 * max30102.h
 *
 *  Created on: Nov 10, 2023
 *      Author: André A. M. Araújo
 */

// Device datasheet:
// analog.com/media/en/technical-documentation/data-sheets/MAX30102.pdf

#ifndef INC_MAX30102_H_
#define INC_MAX30102_H_

#include "i2c.h"

#define MAX3010_I2C_HANDLE		hi2c3	// Change here if using other I2C
#define MAX30102_DEVICE_ADDRESS	0xAE	// 0x57 << 1
#define MAX30102_I2C_TIMEOUT	50

// Register Maps

// Status
#define MAX30102_INTERRUPT_STATUS_1			0x00
#define MAX30102_INTERRUPT_STATUS_2			0x01
#define MAX30102_INTERRUPT_STATUS_3			0x02
#define MAX30102_INTERRUPT_STATUS_4			0x03

// FIFO
#define MAX30102_FIFO_WRITE_POINTER			0x04
#define MAX30102_FIFO_OVERFLOW_COUNTER		0x05
#define MAX30102_FIFO_READ_POINTER			0x06
#define MAX30102_FIFO_DATA					0x07

// Configuration
#define MAX30102_FIFO_CONFIG				0x08
#define MAX30102_MODE_CONFIG				0x09
#define MAX30102_SPO2_CONFIG				0x0A
								// RESERVED	0x0B
#define MAX30102_LED_PULSE_AMPLITUDE_1		0x0C
#define MAX30102_LED_PULSE_AMPLITUDE_2		0x0D
								// RESERVED	0x0E - 0x0F
#define MAX30102_MULTI_LED_MODE_CONTROL_12	0x11
#define MAX30102_MULTI_LED_MODE_CONTROL_34	0x12
								// RESERVED	0x13 - 0x1E

// Die Temperature
#define MAX30102_DIE_TEMPERATURE_INTEGER	0x1F
#define MAX30102_DIE_TEMPERATURE_FRACTION	0x20
#define MAX30102_DIE_TEMPERATURE_CONFIG		0x21
								// RESERVED	0x22 - 0x2F

// Part ID
#define MAX30102_REVISION_ID				0xFE
#define MAX30102_PART_ID					0xFF		// 0x15

void	MAX30102_Read  	(uint8_t register_address, uint8_t data_size, uint8_t * I2C_buffer);
void	MAX30102_Write 	(uint8_t register_address, uint8_t data);
void	MAX30102_Update	(uint8_t register_address, uint8_t mask, uint8_t data);

void	MAX30102_Reset(void);

void	MAX30102_ConfigProximityDetect(void);

void 	MAX30102_GetDataMulti(uint8_t * I2C_buffer);

int16_t MAX30102_GetTemperature(void);

int16_t MAX30102_GetPartID(void);

#endif /* INC_MAX30102_H_ */
