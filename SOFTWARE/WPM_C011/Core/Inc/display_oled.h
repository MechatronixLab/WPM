/*
 * display_oled.h
 *
 *  Created on: Nov 11, 2023
 *      Author: Andre
 */

#ifndef INC_DISPLAY_OLED_H_
#define INC_DISPLAY_OLED_H_

#include "i2c.h"

#include <stdlib.h>

#define SSD1306_REGISTER_COMMAND	0x80
#define SSD1306_REGISTER_DATA		0x40
#define SSD1306_DEVICE_ADDRESS	   (0x3C << 1)

extern const uint8_t font5x7[];

void OLED_SendCommand(uint8_t command);
void OLED_SendData(uint8_t data);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_SetPixel(uint8_t x, uint8_t y);
void OLED_Clear(void);
void OLED_Init(void);

void OLED_Sleep(void);
void OLED_WakeUp(void);
void OLED_DarkBG(void);
void OLED_LightBG(void);

void OLED_DrawChar(uint8_t * font, uint8_t character);
void OLED_DrawString(uint8_t * font, char * string);
void OLED_DrawLogo(void);
void OLED_DrawFrame(uint8_t * frame_buffer);
void OLED_DrawLine(uint8_t xi, uint8_t yi, uint8_t xf, uint8_t yf);

#endif /* INC_DISPLAY_OLED_H_ */
