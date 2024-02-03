/*
 * oled_ssd1306.c
 *
 *  Created on: Feb 2, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include <oled_ssd1306.h>

// TODO: map device commands in the .h file

void OLED_SendCommand(uint8_t command)
{
	uint8_t I2C_buffer[2];

	I2C_buffer[0] = SSD1306_REGISTER_COMMAND;
	I2C_buffer[1] = command;
	HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_DEVICE_ADDRESS, I2C_buffer, 2, SSD1306_I2C_TIMEOUT);
}

void OLED_SendData(uint8_t data)
{
	uint8_t I2C_buffer[2];

	I2C_buffer[0] = SSD1306_REGISTER_DATA;
	I2C_buffer[1] = data;
	HAL_I2C_Master_Transmit(&SSD1306_I2C_HANDLE, SSD1306_DEVICE_ADDRESS, I2C_buffer, 2, SSD1306_I2C_TIMEOUT);
}

void OLED_SetCursor(uint8_t x, uint8_t page)
{
	OLED_SendCommand(0x00 + ( x       & 0x0F));
	OLED_SendCommand(0x10 + ((x >> 4) & 0x0F));

	OLED_SendCommand(0xB0 + page);
}

void OLED_SetPixel(uint8_t x, uint8_t y)
{
	OLED_SetCursor(x, (y / 8));
	OLED_SendData(0x01 << (y % 8));
}

void OLED_Clear(void)
{
	uint8_t page 	= 0;
	uint8_t column  = 0;

	for (page = 0; page < 8; page++)
	{
		OLED_SetCursor(0, page);

		for (column = 0; column < 128; column++)
		{
			OLED_SendData(0x00);
		}
	}
}

void OLED_Sleep(void)
{
	OLED_SendCommand(0xAE); 	// Turn off screen
}

void OLED_WakeUp(void)
{
	OLED_SendCommand(0xAF); 	// Turn on screen
}

void OLED_DarkBG(void)
{
	OLED_SendCommand(0xA6);		// Dark background (Normal Display)
}

void OLED_LightBG(void)
{
	OLED_SendCommand(0xA7);		// Light background (Inverse Display)
}

void OLED_Init(void)
{
	HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, 0);
	HAL_Delay(100);
	HAL_GPIO_WritePin(OLED_RESET_GPIO_Port, OLED_RESET_Pin, 1);

	OLED_WakeUp(); 				// Turn on display
	OLED_DarkBG();				// Normal mode (dark background)
	OLED_SendCommand(0x20);		// Set memory addressing mode
	OLED_SendCommand(0x02);			// Set Page Mode
	OLED_SendCommand(0x8D);		// Charge pump
	OLED_SendCommand(0x14);			// Charge pump
	OLED_SendCommand(0x81);		// Set contrast
	OLED_SendCommand( 127);			// Default
	OLED_SendCommand(0xC8);		// Pages Remapping
	OLED_SendCommand(0xA1);		// Columns Remapping

	OLED_Clear();
}


