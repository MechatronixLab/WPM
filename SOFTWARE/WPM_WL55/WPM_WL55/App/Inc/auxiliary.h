/*
 * auxiliary.h
 *
 *  Created on: Feb 17, 2024
 *      Author: André A. M. Araújo
 */

#ifndef INC_AUXILIARY_H_
#define INC_AUXILIARY_H_

#include "main.h"

// Moving Averages Algorithm ///////////////////////////////////////////////////

#define MOVING_AVERAGE_PERIOD	250

uint32_t AUX_Average(uint32_t * array, uint16_t length);

// Circular Buffer Algorithm ///////////////////////////////////////////////////

// https://embedjournal.com/implementing-circular-buffer-embedded-c/

typedef struct
{
	int32_t * const buffer;
	uint16_t	head;
	uint16_t 	tail;
	const uint16_t length;
}circular_buffer_t;

uint8_t	AUX_CircularBufferFull (circular_buffer_t * c);
uint8_t AUX_CircularBufferEmpty(circular_buffer_t * c);
void 	AUX_CircularBufferPush (circular_buffer_t * c, uint32_t data);
void 	AUX_CircularBufferPop  (circular_buffer_t * c, uint32_t * data);

// Map Algorithm ///////////////////////////////////////////////////////////////

int32_t AUX_Map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max);

#endif /* INC_AUXILIARY_H_ */
