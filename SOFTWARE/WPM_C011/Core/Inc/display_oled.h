/*
 * display_oled.h
 *
 *  Created on: Nov 11, 2023
 *      Author: Andre
 */

#ifndef INC_DISPLAY_OLED_H_
#define INC_DISPLAY_OLED_H_

#include "i2c.h"

#define SSD1306_REG_CMD 	0x80
#define SSD1306_REG_DATA 	0x40
#define SSD1306_ADDR	   (0x3C << 1)

extern const uint8_t font5x7[];

void OLED_SendCommand(uint8_t cmd);
void OLED_SendData(uint8_t data);
void OLED_SetCursor(uint8_t x, uint8_t y);
void OLED_Clear(void);
void OLED_Init(void);

void OLED_DrawChar(uint8_t * font, uint8_t character);
void OLED_DrawString(uint8_t * font, char * string);
void OLED_DrawLogo(void);
void OLED_DrawFrame(uint8_t * frame_buf);

#endif /* INC_DISPLAY_OLED_H_ */
