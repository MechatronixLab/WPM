/*
 * app.c
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "app.h"

extern UART_HandleTypeDef huart2;

static pingPongFSM_t fsm;
static char uartBuff[100];

void APP_Init(void)
{
	uint8_t 	i = 0;
	uint16_t	dt = 100;

	CLI_NewLine();
	CLI_Write("Wearable Patient Monitor \r\n");
	CLI_Write("Version: 0.0.1 \r\n");
	CLI_NewLine();

	for (i = 0; i < 6; i++)
	{
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		HAL_Delay(dt);
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		HAL_Delay(dt);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(dt);
	}

	LORA_RadioInit();

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

	APP_Run();
}

void APP_Run(void)
{
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
