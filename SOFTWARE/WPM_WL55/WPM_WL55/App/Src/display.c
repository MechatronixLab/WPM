/*
 * display.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "display.h"

// Mechatronix Lab Logo
//
// 	To convert a bitmap to an array, use this website and the following configurations:
// 		http://javl.github.io/image2cpp/
//			Code output format: Arduino code
//			Draw mode: 			Vertical - 1 bit per pixel
//
//	Then, copy array contents from the page to this array:
static const uint8_t MECHATRONIX_LAB_LOGO_64x64[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0c, 0xfe, 0xfe, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0xfe, 0xfe, 0x0c, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x80, 0xe0, 0x78, 0x3e, 0x0f, 0x03, 0x00, 0x00, 0x80, 0xc0, 0x80, 0x00, 0x00, 0x80, 0xc0, 0xe0,
	0xe0, 0xc0, 0x80, 0x00, 0x00, 0x80, 0xc0, 0x80, 0x00, 0x00, 0x03, 0x0f, 0x3c, 0x78, 0xe0, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0x3c, 0x1e,
	0x87, 0x01, 0x20, 0x70, 0xe0, 0xc4, 0xce, 0xfc, 0x78, 0x79, 0xff, 0xff, 0x1f, 0x0f, 0x1f, 0x7f,
	0x7f, 0x1f, 0x0f, 0x1f, 0xff, 0xff, 0x79, 0x78, 0xfc, 0xce, 0xc4, 0xe0, 0x70, 0x20, 0x01, 0x87,
	0x1e, 0x7c, 0xf0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0x78, 0x3e, 0x0f, 0x03, 0x00, 0x00, 0x01,
	0xf3, 0xff, 0xfe, 0xfe, 0xff, 0xcf, 0xcf, 0x0f, 0x04, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0xf8, 0xfc,
	0xfe, 0xfe, 0xfe, 0xf0, 0xe0, 0x00, 0x00, 0x04, 0x0f, 0xcf, 0xcf, 0xff, 0xfe, 0xfe, 0xff, 0xf3,
	0xe1, 0xc0, 0x80, 0x03, 0x0f, 0x3c, 0x78, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xc0, 0xf0, 0x3c, 0x1e, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60,
	0x77, 0x3f, 0x1f, 0xbf, 0xff, 0xf9, 0xf9, 0xf8, 0x10, 0x00, 0x80, 0x81, 0x07, 0x0f, 0x0f, 0x0f,
	0x0f, 0x0f, 0x0f, 0x07, 0x81, 0x80, 0x00, 0x10, 0xf8, 0xf9, 0xf9, 0xff, 0xbf, 0x1f, 0x3f, 0x77,
	0x63, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x1e, 0x7c, 0xf0, 0xc0, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x7e, 0xff, 0x81, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x03, 0x03, 0x01, 0x18, 0x1d, 0x0f, 0xc7, 0xef, 0x7f, 0x3f, 0x7c, 0xf8, 0xfc, 0xff,
	0xff, 0xfc, 0xf8, 0x7c, 0x3f, 0x7f, 0xef, 0xc7, 0x0f, 0x1d, 0x18, 0x01, 0x03, 0x03, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x83, 0xff, 0x7e, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x03, 0x07, 0x0e, 0x1c, 0x38, 0x30, 0x70, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
	0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x61, 0x63,
	0x63, 0x61, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60,
	0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x70, 0x30, 0x38, 0x1c, 0x0e, 0x07, 0x03, 0x00, 0x00, 0x00
};

static const uint8_t ST_LOGO_64x32[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf8, 0xf8, 0xfc, 0xfc, 0x7e,
	0x7e, 0x3e, 0x3e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
	0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x06, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xe0, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xc3, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x10, 0x38, 0x78, 0x78, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8,
	0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x78, 0x18, 0x00, 0x00, 0x00, 0x00, 0x80,
	0xe0, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0xf8, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xc0, 0xf0, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
	0xfc, 0xf8, 0xf0, 0xe0, 0xe0, 0xc0, 0x80, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x07, 0x01, 0x00, 0x00, 0x00, 0xc0, 0xf0, 0xfc, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
	0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x00, 0x00, 0x40, 0x40, 0x60, 0x70, 0x7f, 0x7f, 0x7f,
	0x7f, 0x7f, 0x3f, 0x0f, 0x03, 0x00, 0x00, 0x00, 0x00, 0x60, 0x7c, 0x7f, 0x7f, 0x7f, 0x7f, 0x3f,
	0x3f, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t ELEKTOR_LOGO_64x32[] =
{
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x80,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xe0, 0xf8, 0x3c, 0x0e, 0x03, 0x03, 0x01, 0x61, 0x30, 0x30, 0x30, 0x30, 0x01, 0x01, 0x03,
	0x03, 0x86, 0x9e, 0xf8, 0xe0, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0,
	0x80, 0x00, 0x00, 0xfc, 0xfc, 0x00, 0x80, 0xc0, 0xc0, 0x00, 0x00, 0xc0, 0xf0, 0xf0, 0xc0, 0xc0,
	0x00, 0x00, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x00, 0x00, 0xc0, 0xc0, 0x80, 0xc0, 0x40, 0x00,
	0x00, 0x07, 0x1f, 0x3c, 0x70, 0xc0, 0xc0, 0x80, 0x80, 0x04, 0x0e, 0x0e, 0x0e, 0x8f, 0x87, 0x87,
	0xc3, 0xe1, 0x79, 0x1f, 0x07, 0x00, 0x00, 0x3f, 0x3f, 0x00, 0x06, 0x0f, 0x1e, 0x32, 0x32, 0x12,
	0x1b, 0x02, 0x00, 0x3f, 0x3f, 0x07, 0x0f, 0x3d, 0x30, 0x00, 0x00, 0x00, 0x1f, 0x3f, 0x30, 0x10,
	0x00, 0x07, 0x1f, 0x18, 0x30, 0x30, 0x18, 0x1f, 0x07, 0x00, 0x3f, 0x3f, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void DISPLAY_Init(void)
{
	uint16_t dt = 10;
	uint8_t i = 0;

	OLED_Init();
	GFX_DrawLogo( 0, 0,64,64, (uint8_t *) MECHATRONIX_LAB_LOGO_64x64);
	OLED_SetCursor(64, 0);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "WEARABLE  ");
	OLED_SetCursor(64, 1);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "PATIENT   ");
	OLED_SetCursor(64, 2);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "MONITOR   ");
	OLED_SetCursor(64, 6);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "ENG. ANDRE");
	OLED_SetCursor(64, 7);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "A.M.ARAUJO");

	for (i = 0; i < 6; i++)	// Sweep LEDs thrice
	{
		HAL_GPIO_TogglePin(LED3_GPIO_Port, LED3_Pin);
		HAL_Delay(dt);
		HAL_GPIO_TogglePin(LED2_GPIO_Port, LED2_Pin);
		HAL_Delay(dt);
		HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
		HAL_Delay(dt);
	}

	HAL_Delay(14 * dt);

	OLED_SetCursor(64, 0);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "WPM-WL55  ");
	OLED_SetCursor(64, 1);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "V: 0.0.1  ");
	OLED_SetCursor(64, 2);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "2024.02.29");

	HAL_Delay(20 * dt);

	OLED_Clear();

	OLED_SetCursor(0, 0);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "STM32     ");
	OLED_SetCursor(0, 1);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "WIRELESS  ");
	OLED_SetCursor(0, 2);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "INNOVATION");
	OLED_SetCursor(0, 3);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "DESIGN    ");
	OLED_SetCursor(0, 4);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "CONTEST   ");
	OLED_SetCursor(0, 7);
	GFX_DrawString((uint8_t *)GFX_font_5x7, "2024      ");

	GFX_DrawLogo(64, 0,64,32, (uint8_t *) ST_LOGO_64x32);
	GFX_DrawLogo(64, 4,64,32, (uint8_t *) ELEKTOR_LOGO_64x32);

	HAL_Delay(20 * dt);

	OLED_Clear();
}

void DISPLAY_DrawPleth(OXIMETRY_raw_data_t * data)
{

	static uint8_t graph_min;
	static uint8_t graph_max;

	static uint32_t red_min = 0xFFFFFFFF;
	static uint32_t red_max = 0x00000000;

	static uint8_t graph_x = 0;

	if (data->red > red_max)
	{
		red_max = data->red;
	}

	if (data->red < red_min)
	{
		red_min = data->red;
	}

	graph_min = (uint8_t) data->red / red_min;





}
