/*
 * console.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "console.h"

static char console_buffer[64] = {0};

void CONSOLE_Init(void)
{
	sprintf(console_buffer,
			  "  |  Version: %d.%d.%d                            | \r\n",
			     V_MAJOR, V_MINOR, V_PATCH);

	CLI_NewLine();
	CLI_Write("   --------------------------------------------  \r\n");
	CLI_Write("  |                                            | \r\n");
	CLI_Write("  |  Wearable Patient Monitor                  | \r\n");
	CLI_Write("  |  WPM-WL55                                  | \r\n");
	CLI_Write(console_buffer);										// Version
	CLI_Write("  |                                            | \r\n");
	CLI_Write("  |  Developed by Eng. Andre A. M. Araujo      | \r\n");
	CLI_Write("  |  https://github.com/MechatronixLab/WPM     | \r\n");
	CLI_Write("  |                                            | \r\n");
	CLI_Write("  |  Elektor and ST Microelectronics           | \r\n");
	CLI_Write("  |  STM32 Wireless Innovation Design Contest  | \r\n");
	CLI_Write("  |  2024                                      | \r\n");
	CLI_Write("  |                                            | \r\n");
	CLI_Write("   --------------------------------------------  \r\n");

	CLI_NewLine();
}

