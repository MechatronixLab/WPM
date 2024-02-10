/*
 * circular_buffer.c
 *
 *  Created on: Feb 9, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "circular_buffer.h"

uint8_t	AVG_CircularBufferFull(circular_buffer_t * c)
{
    if ((c->head + 1) == c->tail)  // if the head + 1 == tail, buffer is full
        return 1;
    else
    	return 0;
}

uint8_t	AVG_CircularBufferEmpty(circular_buffer_t * c)
{
    if (c->head == c->tail)  		// if the head == tail, buffer is empty
        return 1;
    else
    	return 0;
}

void AVG_CircularBufferPush(circular_buffer_t * c, uint32_t data)
{
    uint8_t next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->buffer_size)
        next = 0;

    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
}

void 	AVG_CircularBufferPop (circular_buffer_t * c, uint32_t * data)
{
	uint8_t next;

	next = c->tail + 1;  // next is where tail will point to after this read.
    if(next >= c->buffer_size)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
}
