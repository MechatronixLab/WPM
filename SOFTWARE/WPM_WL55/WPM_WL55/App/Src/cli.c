/*
 * cli.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "cli.h"

void CLI_Write(char * buffer)
{
	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
}

void CLI_NewLine(void)
{
	CLI_Write("\r\n");
}
