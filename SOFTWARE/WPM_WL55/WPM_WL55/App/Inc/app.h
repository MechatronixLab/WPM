/*
 * app.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_APP_H_
#define INC_APP_H_

// STM32 ///////////////////////////////////////////////////////////////////////
#include "main.h"

// App /////////////////////////////////////////////////////////////////////////
#include "isr.h"

// Display
#include "graphics.h"	// TODO: Ideally, should be called from "display.h" only
#include "display.h"

// Buzzer
#include "buzzer.h"

// Sensors
#include "imu.h"
#include "oximetry.h"

// LoRa
#include "lora.h"

// Console
#include "console.h"

// Version
#include "version.h"

// Standard Libraries //////////////////////////////////////////////////////////
#include <math.h>

// Function Prototypes /////////////////////////////////////////////////////////
void APP_Init(void);
void APP_Run (void);

#endif /* INC_APP_H_ */
