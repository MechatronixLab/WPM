/*
 * auxiliary.c
 *
 *  Created on: Feb 17, 2024
 *      Author: André A. M. Araújo
 */

#include "auxiliary.h"

// Moving Averages Algorithm ///////////////////////////////////////////////////

float AUX_Average(uint32_t * array, uint16_t length)
{
	uint16_t index = 0;
	float  average = 0;

	for (index = 0; index < length; index++)
	{
		average += array[index];
	}
	average /= length;

	return average;
}

// Circular Buffer Algorithm ///////////////////////////////////////////////////

// https://embedjournal.com/implementing-circular-buffer-embedded-c/

uint8_t	AUX_CircularBufferFull(circular_buffer_t * c)
{
    if ((c->head + 1) == c->tail)  // if the head + 1 == tail, buffer is full
        return 1;
    else
    	return 0;
}

uint8_t	AUX_CircularBufferEmpty(circular_buffer_t * c)
{
    if (c->head == c->tail)  		// if the head == tail, buffer is empty
        return 1;
    else
    	return 0;
}

void AUX_CircularBufferPush(circular_buffer_t * c, uint32_t data)
{
    uint16_t next;

    next = c->head + 1;  // next is where head will point to after this write.
    if (next >= c->length)
        next = 0;

    c->buffer[c->head] = data;  // Load data and then move
    c->head = next;             // head to next data offset.
}

void 	AUX_CircularBufferPop (circular_buffer_t * c, uint32_t * data)
{
	uint16_t next;

	next = c->tail + 1;  // next is where tail will point to after this read.
    if(next >= c->length)
        next = 0;

    *data = c->buffer[c->tail];  // Read data and then move
    c->tail = next;              // tail to next offset.
}

// Map Algorithm ///////////////////////////////////////////////////////////////

int32_t AUX_Map(int32_t x, int32_t in_min, int32_t in_max, int32_t out_min, int32_t out_max)
{
  return (int32_t) ((1.0 * x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min);
}
