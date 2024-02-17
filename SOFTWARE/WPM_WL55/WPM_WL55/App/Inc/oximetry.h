/*
 * oximetry.h
 *
 *  Created on: Feb 10, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_OXIMETRY_H_
#define INC_OXIMETRY_H_

#include "max30102.h"
#include "maxim_algorithm.h"

#include "auxiliary.h"

#define	OXIMETRY_NUMBER_OF_SAMPLES	MAXIM_BUFFER_SIZE

typedef struct
{
	uint32_t red;
	uint32_t infrared;
	uint16_t temperature;
} OXIMETRY_raw_data_t;

typedef struct
{
	 int32_t spo2;
	 int32_t heart_rate;
	uint16_t temperature;
} OXIMETRY_data_t;

void OXIMETRY_Init(void);
void OXIMETRY_GetRawData(OXIMETRY_raw_data_t * data);
void OXIMETRY_ProcessData(OXIMETRY_data_t * data);

// TODO:
// Map MAX30102 registers and bit fields
// Recreate Init function accepting configuration parameters as arguments

#endif /* INC_OXIMETRY_H_ */
