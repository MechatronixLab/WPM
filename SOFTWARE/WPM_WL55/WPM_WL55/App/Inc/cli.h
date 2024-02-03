/*
 * cli.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_CLI_H_
#define INC_CLI_H_

#include "usart.h"

#include <string.h>

extern UART_HandleTypeDef 	huart2;

#define CLI_UART_HANDLE		huart2		// Change here if using other UART

void CLI_Write(char * buffer);
void CLI_NewLine(void);

#endif /* INC_CLI_H_ */
