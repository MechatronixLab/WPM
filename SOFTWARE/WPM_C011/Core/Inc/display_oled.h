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

void OLED_command(uint8_t cmd);
void OLED_data(uint8_t data);
void OLED_cursor(uint8_t x, uint8_t y);
void OLED_clear(void);
void OLED_logo(void);
void OLED_frame(uint8_t * frame_buf);
void OLED_init(void);
void OLED_char(uint8_t * font, uint8_t character);
void OLED_string(uint8_t * font, char * string);

#endif /* INC_DISPLAY_OLED_H_ */
