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

#define OXIMETRY_SPO2_AVERAGE		240 // Samples
#define OXIMETRY_HR_AVERAGE			240 // Samples

typedef struct
{
	uint32_t red;				// Raw data from RED LED
	uint32_t infrared;			// Raw data from INFRARED LED
	uint32_t DC_red;			// Average RED LED level
	uint32_t DC_infrared;		// Average INFRARED LED level
	uint32_t RMS_AC_red;		// RMS of variable RED LED signal
	uint32_t RMS_AC_infrared;	// RMS of variable INFRARED LED signal
	 int32_t dred_dt;			// Derivative of RED LED signal with respect to time
	 int32_t dinfrared_dt;		// Derivative of INFRARED LED signal with respect to time
	uint32_t ratio;				// Ratio of Ratios
	uint16_t spo2;				// Peripheral oxygen saturation
	uint8_t  valid_spo2;		// Flag for valid SpO2 reading 			// TODO
	uint16_t perfusion_index;	// Perfusion Index
	uint16_t heart_rate;		// Heart rate
	uint8_t  heart_beat;		// Flag for heart beat detection
	uint8_t  valid_heart_rate;	// Flag for valid heart rate reading
	uint16_t temperature;		// Oximetry sensor temperature			// TODO
} OXIMETRY_data_t;

void OXIMETRY_Init(void);
void OXIMETRY_ProcessDataWPM  (OXIMETRY_data_t * data);
void OXIMETRY_ProcessDataMaxim(OXIMETRY_data_t * data);				// Not used

// TODO:
// Map MAX30102 registers and bit fields
// Recreate Init function accepting configuration parameters as arguments

#endif /* INC_OXIMETRY_H_ */
