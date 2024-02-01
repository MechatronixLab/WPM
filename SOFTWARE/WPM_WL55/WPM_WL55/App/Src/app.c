/*
 * app.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "app.h"

extern UART_HandleTypeDef huart2;



void APP_Init(void)
{
	  pingPongFSM_t fsm;
	  char uartBuff[100];


	/*** GPIO Configuration (for debugging) ***/
	  /* DEBUG_SUBGHZSPI_NSSOUT = PA4
	   * DEBUG_SUBGHZSPI_SCKOUT = PA5
	   * DEBUG_SUBGHZSPI_MISOOUT = PA6
	   * DEBUG_SUBGHZSPI_MOSIOUT = PA7
	   * DEBUG_RF_HSE32RDY = PA10
	   * DEBUG_RF_NRESET = PA11
	   * DEBUG_RF_SMPSRDY = PB2
	   * DEBUG_RF_DTB1 = PB3 <---- Conflicts with RF_IRQ0
	   * DEBUG_RF_LDORDY = PB4
	   * RF_BUSY = PA12
	   * RF_IRQ0 = PB3
	   * RF_IRQ1 = PB5
	   * RF_IRQ2 = PB8
	   */

	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  // Enable GPIO Clocks
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  // DEBUG_SUBGHZSPI_{NSSOUT, SCKOUT, MSIOOUT, MOSIOUT} pins
	  GPIO_InitStruct.Pin = GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
	  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	  GPIO_InitStruct.Alternate = GPIO_AF13_DEBUG_SUBGHZSPI;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  // DEBUG_RF_{HSE32RDY, NRESET} pins
	  GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
	  GPIO_InitStruct.Alternate = GPIO_AF13_DEBUG_RF;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  // DEBUG_RF_{SMPSRDY, LDORDY} pins
	  GPIO_InitStruct.Pin = GPIO_PIN_2 | GPIO_PIN_4;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  // RF_BUSY pin
	  GPIO_InitStruct.Pin = GPIO_PIN_12;
	  GPIO_InitStruct.Alternate = GPIO_AF6_RF_BUSY;
	  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	  // RF_{IRQ0, IRQ1, IRQ2} pins
	  GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_8;
	  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	  strcpy(uartBuff, "\n\rPING PONG\r\nAPP_VERSION=0.0.1\r\n---------------\r\n");
	HAL_UART_Transmit(&huart2, (uint8_t *)uartBuff, strlen(uartBuff), HAL_MAX_DELAY);
	sprintf(uartBuff, "LORA_MODULATION\r\nLORA_BW=%d Hz\r\nLORA_SF=%d\r\n", (1 << LORA_BANDWIDTH) * 125, LORA_SPREADING_FACTOR);
	HAL_UART_Transmit(&huart2, (uint8_t *)uartBuff, strlen(uartBuff), HAL_MAX_DELAY);
	radioInit();

	// get random number
	uint32_t rnd = 0;
	SUBGRF_SetDioIrqParams(IRQ_RADIO_NONE, IRQ_RADIO_NONE, IRQ_RADIO_NONE, IRQ_RADIO_NONE);
	rnd = SUBGRF_GetRandom();

	fsm.state = STATE_NULL;
	fsm.subState = SSTATE_NULL;
	fsm.rxTimeout = 3000; // 3000 ms
	fsm.rxMargin = 200;   // 200 ms
	fsm.randomDelay = rnd >> 22; // [0, 1023] ms
	sprintf(uartBuff, "rand=%lu\r\n", fsm.randomDelay);
	HAL_UART_Transmit(&huart2, (uint8_t *)uartBuff, strlen(uartBuff), HAL_MAX_DELAY);

	HAL_Delay(fsm.randomDelay);
	SUBGRF_SetDioIrqParams( IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT | IRQ_CRC_ERROR,
						  IRQ_RX_DONE | IRQ_RX_TX_TIMEOUT | IRQ_CRC_ERROR,
						  IRQ_RADIO_NONE,
						  IRQ_RADIO_NONE );
	SUBGRF_SetSwitch(RFO_LP, RFSWITCH_RX);
	SUBGRF_SetRx(fsm.rxTimeout << 6);
	fsm.state = STATE_MASTER;
	fsm.subState = SSTATE_RX;

	while(1)
	{
		//    eventReceptor = NULL;
		//    while (eventReceptor == NULL);
		//    eventReceptor(&fsm);

		if (eventReceptor != NULL)
		{
			BSP_LED_On(LED_GREEN);

			eventReceptor(&fsm);
			eventReceptor = NULL;

			BSP_LED_Off(LED_GREEN);
		}

		BSP_LED_Toggle(LED_BLUE);
		HAL_Delay(250);
	}
}
