/*
 * wsen-isds.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Andre
 */

#ifndef INC_WSEN_ISDS_H_
#define INC_WSEN_ISDS_H_

#include "i2c.h"

#define ISDS_I2C_HANDLE			hi2c3
#define ISDS_DEVICE_ADDRESS		(0x6B << 1)

#define ISDS_I2C_TIMEOUT		50U

#define ISDS_X_AXIS				0U
#define ISDS_Y_AXIS				1U
#define ISDS_Z_AXIS				2U

// Register Map

					// RESERVED	0x00 - 0x05
#define ISDS_FIFO_CTRL1			0x06
#define ISDS_FIFO_CTRL2			0x07
#define ISDS_FIFO_TIMER_EN				0x80
#define ISDS_FIFO_TEMP_EN				0x08
#define ISDS_FIFO_CTRL3			0x08
#define ISDS_FIFO_CTRL4			0x09
#define ISDS_FIFO_CTRL5			0x0A
#define ISDS_DRDY_PULSE_CFG		0x0B
					// RESERVED	0x0C
#define ISDS_INT0_CTRL			0x0D
#define ISDS_INT1_CTRL			0x0E
#define ISDS_DEVICE_ID			0x0F
#define ISDS_CTRL1_XL			0x10
#define ISDS_CTRL2_G			0x11
#define ISDS_CTRL3_C			0x12
#define ISDS_CTRL4_C			0x13
#define ISDS_CTRL5_C			0x14
#define ISDS_CTRL6_C			0x15
#define ISDS_CTRL7_G			0x16
#define ISDS_CTRL8_XL			0x17
#define ISDS_CTRL9_XL			0x18
#define ISDS_CTRL10_C			0x19
#define ISDS_MASTER_CONFIG		0x1A
#define ISDS_WAKE_IP_SRC		0x1B
#define ISDS_TAP_SRC			0x1C
#define ISDS_D6D_SRC			0x1D
#define ISDS_STATUS_REG			0x1E
					// RESERVED	0x1F
#define ISDS_T_OUT_L			0x20
#define ISDS_T_OUT_H			0x21
#define ISDS_G_X_OUT_L			0x22
#define ISDS_G_X_OUT_H			0x23
#define ISDS_G_Y_OUT_L			0x24
#define ISDS_G_Y_OUT_H			0x25
#define ISDS_G_Z_OUT_L			0x26
#define ISDS_G_Z_OUT_H			0x27
#define ISDS_XL_X_OUT_L			0x28
#define ISDS_XL_X_OUT_H			0x29
#define ISDS_XL_Y_OUT_L			0x2A
#define ISDS_XL_Y_OUT_H			0x2B
#define ISDS_XL_Z_OUT_L			0x2C
#define ISDS_XL_Z_OUT_H			0x2D
					// RESERVED	0x2E - 0x39
#define ISDS_FIFO_STATUS1		0x3A
#define ISDS_FIFO_STATUS2		0x3B
#define ISDS_FIFO_STATUS3		0x3C
#define ISDS_FIFO_STATUS4		0x3D
#define ISDS_FIFO_DATA_OUT_L	0x3E
#define ISDS_FIFO_DATA_OUT_H	0x3F
					// RESERVED	0x40 - 0x52
#define ISDS_FUNC_SRC1			0x53
					// RESERVED	0x54 - 0x57
#define ISDS_TAP_CFG			0x58
#define ISDS_TAP_THS_6D			0x59
#define ISDS_INT_DUR2			0x5A
#define ISDS_WAKE_UP_THS		0x5B
#define ISDS_WAKE_UP_DUR		0x5C
#define ISDS_FREE_FALL			0x5D
#define ISDS_MD1_CFG			0x5E
#define ISDS_MD2_CFG			0x5F
					// RESERVED	0x60 - 0x72
#define ISDS_X_OFS_USR			0x73
#define ISDS_Y_OFS_USR			0x74
#define ISDS_Z_OFS_USR			0x75
					// RESERVED	0x76 - 0x7F

typedef struct
{
	int16_t acceleration[3];
	int16_t angular_rate[3];
	int16_t temperature;
} ISDS_data_t;

extern ISDS_data_t ISDS_measurements;





uint8_t ISDS_CommunicationCheck(void);

uint8_t	ISDS_SoftReset(void);

void	ISDS_Init(void);

int16_t	ISDS_GetTemperature(void);

void 	ISDS_GetData(ISDS_data_t * measurements);


#endif /* INC_WSEN_ISDS_H_ */
