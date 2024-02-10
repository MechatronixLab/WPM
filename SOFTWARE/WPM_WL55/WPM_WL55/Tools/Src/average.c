/*
 * average.c
 *
 *  Created on: Feb 9, 2024
 *      Author: Eng. André A. M. Araújo
 */

// TODO:
// gist.github.com/bmccormack/d12f4bf0c96423d03f82

#include "average.h"

uint32_t AVERAGE_ComputeMovingAverage(uint32_t * array, uint16_t length)
{
	uint16_t index = 0;
	uint64_t  average = 0;

	for (index = 0; index < length; index++)
	{
		average += array[index];
	}
	average /= length;

	return (uint32_t) average;
}

