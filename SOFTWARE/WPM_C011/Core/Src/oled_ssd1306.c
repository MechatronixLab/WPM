/*
 * display_oled.c
 *
 *  Created on: Nov 11, 2023
 *      Author: Andre
 */

#include <oled_ssd1306.h>

uint8_t OLED_frame_buffer[1024] = {0};

// TODO: map device commands in the .h file

// https://lexus2k.github.io/ssd1306/group___l_c_d___f_o_n_t_s.html#ga7f8ff37e85ff2ea4e4dfe68a555028ad
const uint8_t font5x7[] =
{
	0x00, 0x05, 0x07, 0x20,
	0x00, 0x00, 0x00, 0x00, 0x00, // sp
	0x00, 0x00, 0x5F, 0x00, 0x00, // !
	0x00, 0x03, 0x00, 0x03, 0x00, // "
	0x14, 0x3E, 0x14, 0x3E, 0x14, // #
	0x24, 0x2A, 0x7F, 0x2A, 0x12, // $
	0x43, 0x33, 0x08, 0x66, 0x61, // %
	0x36, 0x49, 0x55, 0x22, 0x50, // &
	0x00, 0x05, 0x03, 0x00, 0x00, // '
	0x00, 0x1C, 0x22, 0x41, 0x00, // (
	0x00, 0x41, 0x22, 0x1C, 0x00, // )
	0x14, 0x08, 0x3E, 0x08, 0x14, // *
	0x08, 0x08, 0x3E, 0x08, 0x08, // +
	0x00, 0x50, 0x30, 0x00, 0x00, // ,
	0x08, 0x08, 0x08, 0x08, 0x08, // -
	0x00, 0x60, 0x60, 0x00, 0x00, // .
	0x20, 0x10, 0x08, 0x04, 0x02, // /
	0x3E, 0x51, 0x49, 0x45, 0x3E, // 0
	0x00, 0x04, 0x02, 0x7F, 0x00, // 1
	0x42, 0x61, 0x51, 0x49, 0x46, // 2
	0x22, 0x41, 0x49, 0x49, 0x36, // 3
	0x18, 0x14, 0x12, 0x7F, 0x10, // 4
	0x27, 0x45, 0x45, 0x45, 0x39, // 5
	0x3E, 0x49, 0x49, 0x49, 0x32, // 6
	0x01, 0x01, 0x71, 0x09, 0x07, // 7
	0x36, 0x49, 0x49, 0x49, 0x36, // 8
	0x26, 0x49, 0x49, 0x49, 0x3E, // 9
	0x00, 0x36, 0x36, 0x00, 0x00, // :
	0x00, 0x56, 0x36, 0x00, 0x00, // ;
	0x08, 0x14, 0x22, 0x41, 0x00, // <
	0x14, 0x14, 0x14, 0x14, 0x14, // =
	0x00, 0x41, 0x22, 0x14, 0x08, // >
	0x02, 0x01, 0x51, 0x09, 0x06, // ?
	0x3E, 0x41, 0x59, 0x55, 0x5E, // @
	0x7E, 0x09, 0x09, 0x09, 0x7E, // A
	0x7F, 0x49, 0x49, 0x49, 0x36, // B
	0x3E, 0x41, 0x41, 0x41, 0x22, // C
	0x7F, 0x41, 0x41, 0x41, 0x3E, // D
	0x7F, 0x49, 0x49, 0x49, 0x41, // E
	0x7F, 0x09, 0x09, 0x09, 0x01, // F
	0x3E, 0x41, 0x41, 0x49, 0x3A, // G
	0x7F, 0x08, 0x08, 0x08, 0x7F, // H
	0x00, 0x41, 0x7F, 0x41, 0x00, // I
	0x30, 0x40, 0x40, 0x40, 0x3F, // J
	0x7F, 0x08, 0x14, 0x22, 0x41, // K
	0x7F, 0x40, 0x40, 0x40, 0x40, // L
	0x7F, 0x02, 0x0C, 0x02, 0x7F, // M
	0x7F, 0x02, 0x04, 0x08, 0x7F, // N
	0x3E, 0x41, 0x41, 0x41, 0x3E, // O
	0x7F, 0x09, 0x09, 0x09, 0x06, // P
	0x1E, 0x21, 0x21, 0x21, 0x5E, // Q
	0x7F, 0x09, 0x09, 0x09, 0x76, // R
	0x26, 0x49, 0x49, 0x49, 0x32, // S
	0x01, 0x01, 0x7F, 0x01, 0x01, // T
	0x3F, 0x40, 0x40, 0x40, 0x3F, // U
	0x1F, 0x20, 0x40, 0x20, 0x1F, // V
	0x7F, 0x20, 0x10, 0x20, 0x7F, // W
	0x41, 0x22, 0x1C, 0x22, 0x41, // X
	0x07, 0x08, 0x70, 0x08, 0x07, // Y
	0x61, 0x51, 0x49, 0x45, 0x43, // Z
	0x00, 0x7F, 0x41, 0x00, 0x00, // [
	0x02, 0x04, 0x08, 0x10, 0x20, // 55
	0x00, 0x00, 0x41, 0x7F, 0x00, // ]
	0x04, 0x02, 0x01, 0x02, 0x04, // ^
	0x40, 0x40, 0x40, 0x40, 0x40, // _
	0x00, 0x01, 0x02, 0x04, 0x00, // `
	0x20, 0x54, 0x54, 0x54, 0x78, // a
	0x7F, 0x44, 0x44, 0x44, 0x38, // b
	0x38, 0x44, 0x44, 0x44, 0x44, // c
	0x38, 0x44, 0x44, 0x44, 0x7F, // d
	0x38, 0x54, 0x54, 0x54, 0x18, // e
	0x04, 0x04, 0x7E, 0x05, 0x05, // f
	0x08, 0x54, 0x54, 0x54, 0x3C, // g
	0x7F, 0x08, 0x04, 0x04, 0x78, // h
	0x00, 0x44, 0x7D, 0x40, 0x00, // i
	0x20, 0x40, 0x44, 0x3D, 0x00, // j
	0x7F, 0x10, 0x28, 0x44, 0x00, // k
	0x00, 0x41, 0x7F, 0x40, 0x00, // l
	0x7C, 0x04, 0x78, 0x04, 0x78, // m
	0x7C, 0x08, 0x04, 0x04, 0x78, // n
	0x38, 0x44, 0x44, 0x44, 0x38, // o
	0x7C, 0x14, 0x14, 0x14, 0x08, // p
	0x08, 0x14, 0x14, 0x14, 0x7C, // q
	0x00, 0x7C, 0x08, 0x04, 0x04, // r
	0x48, 0x54, 0x54, 0x54, 0x20, // s
	0x04, 0x04, 0x3F, 0x44, 0x44, // t
	0x3C, 0x40, 0x40, 0x20, 0x7C, // u
	0x1C, 0x20, 0x40, 0x20, 0x1C, // v
	0x3C, 0x40, 0x30, 0x40, 0x3C, // w
	0x44, 0x28, 0x10, 0x28, 0x44, // x
	0x0C, 0x50, 0x50, 0x50, 0x3C, // y
	0x44, 0x64, 0x54, 0x4C, 0x44, // z
	0x00, 0x08, 0x36, 0x41, 0x41, // {
	0x00, 0x00, 0x7F, 0x00, 0x00, // |
	0x41, 0x41, 0x36, 0x08, 0x00, // }
	0x02, 0x01, 0x02, 0x04, 0x02, // ~
	0x14, 0x14, 0x14, 0x14, 0x14, // horiz lines // DEL
	0x00 						  // This byte is required for italic type of font
};

// http://javl.github.io/image2cpp/
const uint8_t MECHATRONIX_LAB_LOGO[] =
{
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xf3, 0x01, 0x01, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1,
	0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0xe1, 0x01, 0x01, 0xf3, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x7f, 0x1f, 0x87, 0xc1, 0xf0, 0xfc, 0xff, 0xff, 0x7f, 0x3f, 0x7f, 0xff, 0xff, 0x7f, 0x3f, 0x1f,
	0x1f, 0x3f, 0x7f, 0xff, 0xff, 0x7f, 0x3f, 0x7f, 0xff, 0xff, 0xfc, 0xf0, 0xc3, 0x87, 0x1f, 0x7f,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0xc3, 0xe1,
	0x78, 0xfe, 0xdf, 0x8f, 0x1f, 0x3b, 0x31, 0x03, 0x87, 0x86, 0x00, 0x00, 0xe0, 0xf0, 0xe0, 0x80,
	0x80, 0xe0, 0xf0, 0xe0, 0x00, 0x00, 0x86, 0x87, 0x03, 0x31, 0x3b, 0x1f, 0x8f, 0xdf, 0xfe, 0x78,
	0xe1, 0x83, 0x0f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0x87, 0xc1, 0xf0, 0xfc, 0xff, 0xff, 0xfe,
	0x0c, 0x00, 0x01, 0x01, 0x00, 0x30, 0x30, 0xf0, 0xfb, 0xff, 0xff, 0x1f, 0x0f, 0x07, 0x07, 0x03,
	0x01, 0x01, 0x01, 0x0f, 0x1f, 0xff, 0xff, 0xfb, 0xf0, 0x30, 0x30, 0x00, 0x01, 0x01, 0x00, 0x0c,
	0x1e, 0x3f, 0x7f, 0xfc, 0xf0, 0xc3, 0x87, 0x1f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x3f, 0x0f, 0xc3, 0xe1, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x9f,
	0x88, 0xc0, 0xe0, 0x40, 0x00, 0x06, 0x06, 0x07, 0xef, 0xff, 0x7f, 0x7e, 0xf8, 0xf0, 0xf0, 0xf0,
	0xf0, 0xf0, 0xf0, 0xf8, 0x7e, 0x7f, 0xff, 0xef, 0x07, 0x06, 0x06, 0x00, 0x40, 0xe0, 0xc0, 0x88,
	0x9c, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xf8, 0xe1, 0x83, 0x0f, 0x3f, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x81, 0x00, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xfc, 0xfc, 0xfe, 0xe7, 0xe2, 0xf0, 0x38, 0x10, 0x80, 0xc0, 0x83, 0x07, 0x03, 0x00,
	0x00, 0x03, 0x07, 0x83, 0xc0, 0x80, 0x10, 0x38, 0xf0, 0xe2, 0xe7, 0xfe, 0xfc, 0xfc, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7c, 0x00, 0x81, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xfc, 0xf8, 0xf1, 0xe3, 0xc7, 0xcf, 0x8f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f,
	0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9e, 0x9c,
	0x9c, 0x9e, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f,
	0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x9f, 0x8f, 0xcf, 0xc7, 0xe3, 0xf1, 0xf8, 0xfc, 0xff, 0xff, 0xff
};

void OLED_SendCommand(uint8_t command)
{
	uint8_t I2C_buffer[2];

	I2C_buffer[0] = SSD1306_REGISTER_COMMAND;
	I2C_buffer[1] = command;
	HAL_I2C_Master_Transmit(&hi2c1, SSD1306_DEVICE_ADDRESS, I2C_buffer, 2, 1000);
}

void OLED_SendData(uint8_t data)
{
	uint8_t I2C_buffer[2];

	I2C_buffer[0] = SSD1306_REGISTER_DATA;
	I2C_buffer[1] = data;
	HAL_I2C_Master_Transmit(&hi2c1, SSD1306_DEVICE_ADDRESS, I2C_buffer, 2, 1000);
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
	OLED_DrawLogo();
}

void OLED_DrawChar(uint8_t * font, uint8_t character)
{
	uint8_t column	= 0;

	for (column = 0; column < 5; column++)
	{
		OLED_SendData(font[(character - 0x20)*5 + column + 0x04]);
	}
}

void OLED_DrawString(uint8_t * font, char * string)
{
	uint8_t index	= 0;

	while(string[index] != '\0')
	{
		OLED_DrawChar(font, string[index]);
		index++;
	}
}

void OLED_DrawLogo(void)
{
	uint8_t page 	= 0;
	uint8_t column  = 0;
	uint16_t pixel 	= 0;

	for (page = 0; page < 8; page++)
	{
		OLED_SetCursor(0, page);

		for (column = 0; column < 64; column++)
		{
			OLED_SendData(MECHATRONIX_LAB_LOGO[pixel++]);
		}
	}
}

void OLED_DrawFrame(uint8_t * frame_buffer)
{
	uint8_t page 	= 0;
	uint8_t column  = 0;
	uint16_t sector = 0;

	for (page = 0; page < 8; page++)
	{
		OLED_SetCursor(0, page);

		for (column = 0; column < 128; column++)
		{
			OLED_SendData(frame_buffer[sector++]);
		}
	}
}

void OLED_DrawLine(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1)
{
	// Based on Bresenham algorithm. Source:
	// http://www.phatcode.net/res/224/files/html/ch35/35-01.html
	uint8_t page = 0;

	int32_t x, y, dx, dy, dy2, dy2_dx2, error;

	x = x0;
	y = y0;

	dx = (x1 - x0);
	dy = (y1 - y0);

	dy2 = 2*dy;
	dy2_dx2 = dy2 - 2 * dx;
	error = dy2 - dx;

	if 		(dx ==  1)
	{
		OLED_DrawVerticalLine(x0, y0, dy);
	}
	else if (dy ==  1)
	{
		OLED_DrawHorizontalLine(x0, y0, dx);
	}
	else if (dx == dy)
	{
		// diagonal 45°
	}
	else if (abs(dx) >= dy)
	{
		OLED_frame_buffer[x + 128 * page] |= 0x01 << (y % 8);
		while (x < dx)
		{
			if (error > 0)
			{
				y++;
				error += dy2_dx2;
			}
			else
			{
				error += dy2;
			}

			x++;

			OLED_frame_buffer[x + 128 * (y / 8)] |= 0x01 << (y % 8);
		}
	}
	OLED_DrawFrame(OLED_frame_buffer);
}

void OLED_DrawHorizontalLine(uint8_t xi, uint8_t yi, uint8_t width)
{
	uint8_t counter = 0;

	for (counter = 0; counter < width; counter++)
	{
		OLED_SetPixel(xi, yi);
		xi++;
	}
}

void OLED_DrawVerticalLine(uint8_t xi, uint8_t yi, uint8_t height)
{
	uint8_t counter = 0;

	for (counter = 0; counter < height; counter++)
	{
		OLED_SetPixel(xi, yi);
		yi++;
	}
}
