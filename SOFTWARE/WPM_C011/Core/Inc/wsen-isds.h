/*
 * wsen-isds.h
 *
 *  Created on: Nov 24, 2023
 *      Author: Andre
 */

#ifndef INC_WSEN_ISDS_H_
#define INC_WSEN_ISDS_H_

#include "i2c.h"

#define ISDS_DEVICE_ADDRESS		(0x6B << 1)

#define ISDS_I2C_TIMEOUT		50U

uint8_t ISDS_CommunicationCheck(void);

#endif /* INC_WSEN_ISDS_H_ */
