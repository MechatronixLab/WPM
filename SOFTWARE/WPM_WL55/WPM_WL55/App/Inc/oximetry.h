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

#define OXIMETRY_SAMPLE_RATE		30u	// Hz

#define OXIMETRY_SPO2_AVERAGE		120 	// Samples
#define OXIMETRY_HR_AVERAGE			120 	// Samples

typedef struct
{
	uint32_t red;
	uint32_t infrared;
	uint32_t DC_red;
	uint32_t DC_infrared;
	uint32_t RMS_AC_red;
	uint32_t RMS_AC_infrared;
	 int32_t dred_dt;
	 int32_t dinfrared_dt;
	   float ratio;
	uint16_t spo2;
	 uint8_t valid_spo2;
	uint16_t heart_rate;
	 uint8_t heart_beep;
	 uint8_t valid_heart_rate;
	uint16_t temperature;
} OXIMETRY_data_t;

void OXIMETRY_Init(void);
void OXIMETRY_ProcessDataWPM(OXIMETRY_data_t * data);
void OXIMETRY_ProcessDataMaxim(OXIMETRY_data_t * data);

// TODO:
// Map MAX30102 registers and bit fields
// Recreate Init function accepting configuration parameters as arguments

#endif /* INC_OXIMETRY_H_ */
