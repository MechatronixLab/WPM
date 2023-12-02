/*
 * graphics.h
 *
 *  Created on: Dec 2, 2023
 *      Author: Andre
 */

#ifndef INC_GRAPHICS_H_
#define INC_GRAPHICS_H_

#include "main.h"

#include "oled_ssd1306.h"

#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH		 128
#define SCREEN_HEIGHT	 	  64
#define SCREEN_AREA			(SCREEN_WIDTH * SCREEN_HEIGHT)
#define FRAME_BUFFER_SIZE	(SCREEN_AREA  / 8)

extern uint8_t GFX_frame_buffer[FRAME_BUFFER_SIZE];
extern const uint8_t GFX_font_5x7[];

void GFX_ClearFrame(uint8_t * frame_buffer);

void GFX_DrawChar(uint8_t * font, uint8_t character);
void GFX_DrawString(uint8_t * font, char * string);
void GFX_DrawLogo(void);
void GFX_DrawFrame(uint8_t * frame_buffer);
void GFX_DrawLine(uint8_t xi, uint8_t yi, uint8_t xf, uint8_t yf);

void GFX_DrawHorizontalLine(uint8_t xi, uint8_t yi, uint8_t width);
void GFX_DrawVerticalLine(uint8_t xi, uint8_t yi, uint8_t height);

#endif /* INC_GRAPHICS_H_ */
