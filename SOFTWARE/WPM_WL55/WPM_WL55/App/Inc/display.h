/*
 * display.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "oled_ssd1306.h"
#include "graphics.h"

#include "main.h"

#include "oximetry.h"

void DISPLAY_Init(void);

void DISPLAY_DrawPleth(OXIMETRY_data_t * data);

#endif /* INC_DISPLAY_H_ */
