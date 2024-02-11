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


#include "isr.h"

// Display
#include "oled_ssd1306.h"
#include "graphics.h"
#include "display.h"

// Sensors
#include "oximetry.h"
//#include "max30102.h"
// Third Party Libraries
// #include "maxim_algorithm.h"

#include "imu.h"
//#include "wsen-isds.h"

// LoRa
#include "lora.h"

// Console
//#include "cli.h"
#include "console.h"

// Version
#include "version.h"

// Tools
#include "average.h"
#include "circular_buffer.h"



// Standard Libraries
#include <math.h>

void APP_Init(void);
void APP_Run (void);

#endif /* INC_APP_H_ */
