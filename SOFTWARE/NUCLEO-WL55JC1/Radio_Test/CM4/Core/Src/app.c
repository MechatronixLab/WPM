/*
 * app.c
 *
 *  Created on: Dec 30, 2023
 *      Author: Andre
 */

#include "app.h"

#include <string.h>

void APP_Init(void)
{
	static GPIO_InitTypeDef  GPIO_InitStruct;

	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	GPIO_InitStruct.Pin = LED1_PIN;
	HAL_GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = LED2_PIN;
	HAL_GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = LED3_PIN;
	HAL_GPIO_Init(LEDS_GPIO_PORT, &GPIO_InitStruct);
}

void APP_Run(void)
{
	uint8_t tx_buffer[] = "Test \n";

	APP_Init();

	while(1)
	{
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_9);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_15);

		HAL_UART_Transmit(&huart2, tx_buffer, strlen((char *)tx_buffer), 100);

		HAL_Delay(250);
	}
}
