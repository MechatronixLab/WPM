/*
 * oled_ssd1306.h
 *
 *  Created on: Feb 2, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_OLED_SSD1306_H_
#define INC_OLED_SSD1306_H_

#include "gpio.h"
#include "i2c.h"

#define SSD1306_DEVICE_ADDRESS	   (0x3C << 1)

#define SSD1306_I2C_TIMEOUT			  50

#define SSD1306_REGISTER_COMMAND	0x80
#define SSD1306_REGISTER_DATA		0x40

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

#endif /* INC_OLED_SSD1306_H_ */
