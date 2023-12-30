/*
 * app.h
 *
 *  Created on: Dec 30, 2023
 *      Author: Andre
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "main.h"
#include "usart.h"

#define LEDS_GPIO_PORT	GPIOB
#define	LED1_PIN		GPIO_PIN_15
#define	LED2_PIN		GPIO_PIN_9
#define	LED3_PIN		GPIO_PIN_11

void APP_Init(void);
void APP_Run(void);

#endif /* INC_APP_H_ */
