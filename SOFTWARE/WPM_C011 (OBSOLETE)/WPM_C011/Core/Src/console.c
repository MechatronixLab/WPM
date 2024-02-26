/*
 * console.c
 *
 *  Created on: Nov 11, 2023
 *      Author: André A. M. Araújo
 */

#include "console.h"

void CONSOLE_tx(char * string)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)string, strlen(string), HAL_MAX_DELAY);
}
