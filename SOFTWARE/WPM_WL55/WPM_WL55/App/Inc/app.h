/*
 * app.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_APP_H_
#define INC_APP_H_

#include "main.h"

// App
#include "cli.h"
#include "lora.h"
#include "isr.h"
#include "graphics.h"
#include "max30102.h"
#include "oled_ssd1306.h"
#include "wsen-isds.h"
#include "version.h"

// Tools
#include "average.h"
#include "circular_buffer.h"

void APP_Init(void);
void APP_Run (void);

#endif /* INC_APP_H_ */
