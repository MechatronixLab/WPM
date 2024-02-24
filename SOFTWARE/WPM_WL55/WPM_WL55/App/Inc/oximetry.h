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

#include <math.h>

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

extern int32_t buffer_red[MOVING_AVERAGE_PERIOD];
extern int32_t buffer_infrared[MOVING_AVERAGE_PERIOD];
extern int32_t buffer_AC2_red[MOVING_AVERAGE_PERIOD];
extern int32_t buffer_AC2_infrared[MOVING_AVERAGE_PERIOD];

extern uint32_t DC_red;
extern uint32_t DC_infrared;

extern uint32_t RMS_AC_red;
extern uint32_t RMS_AC_infrared;

extern uint32_t ox_spo2;

extern 	float aux1, aux2, ratio;

void OXIMETRY_Init(void);
void OXIMETRY_GetRawData(OXIMETRY_raw_data_t * data);
void OXIMETRY_ProcessData(OXIMETRY_data_t * data);

// TODO:
// Map MAX30102 registers and bit fields
// Recreate Init function accepting configuration parameters as arguments

#endif /* INC_OXIMETRY_H_ */
