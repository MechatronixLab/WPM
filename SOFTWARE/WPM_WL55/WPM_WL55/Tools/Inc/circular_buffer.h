/*
 * circular_buffer.h
 *
 *  Created on: Feb 9, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_CIRCULAR_BUFFER_H_
#define INC_CIRCULAR_BUFFER_H_

#include "main.h"

// https://embedjournal.com/implementing-circular-buffer-embedded-c/

typedef struct
{
	uint32_t * const buffer;
	uint8_t	 head;
	uint8_t  tail;
	const uint8_t buffer_size;
}circular_buffer_t;

uint8_t	AVG_CircularBufferFull (circular_buffer_t * c);
uint8_t AVG_CircularBufferEmpty(circular_buffer_t * c);
void 	AVG_CircularBufferPush (circular_buffer_t * c, uint32_t data);
void 	AVG_CircularBufferPop  (circular_buffer_t * c, uint32_t * data);

#endif /* INC_CIRCULAR_BUFFER_H_ */
