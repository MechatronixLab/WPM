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
	int32_t * const buffer;
	uint16_t	head;
	uint16_t 	tail;
	const uint16_t length;
}circular_buffer_t;

uint8_t	CIRCULAR_Full (circular_buffer_t * c);
uint8_t CIRCULAR_Empty(circular_buffer_t * c);
void 	CIRCULAR_Push (circular_buffer_t * c, uint32_t data);
void 	CIRCULAR_Pop  (circular_buffer_t * c, uint32_t * data);

#endif /* INC_CIRCULAR_BUFFER_H_ */
