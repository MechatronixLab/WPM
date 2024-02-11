/*
 * oximetry.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "oximetry.h"

static MAX30102_data_t MAX30102_measurements;

int32_t buffer_red[MOVING_AVERAGE_PERIOD] = {0};
circular_buffer_t circular_red =
{
		.buffer = buffer_red,
		.head = 0,
		.tail = 0,
		.length = MOVING_AVERAGE_PERIOD
};

int32_t buffer_infrared[MOVING_AVERAGE_PERIOD] = {0};
circular_buffer_t circular_infrared =
{
		.buffer = buffer_infrared,
		.head = 0,
		.tail = 0,
		.length = MOVING_AVERAGE_PERIOD
};

int32_t buffer_AC_red[MOVING_AVERAGE_PERIOD] = {0};
circular_buffer_t circular_AC_red =
{
		.buffer = buffer_AC_red,
		.head = 0,
		.tail = 0,
		.length = MOVING_AVERAGE_PERIOD
};

int32_t buffer_AC_infrared[MOVING_AVERAGE_PERIOD] = {0};
circular_buffer_t circular_AC_infrared =
{
		.buffer = buffer_AC_infrared,
		.head = 0,
		.tail = 0,
		.length = MOVING_AVERAGE_PERIOD
};

uint32_t average_red = 0;
uint32_t average_infrared = 0;

uint32_t RMS_AC_red = 0;
uint32_t RMS_AC_infrared = 0;

void OXIMETRY_Init(void)
{
	MAX30102_Reset();
	MAX30102_ConfigProximityDetect();
}

void OXIMETRY_GetRawData(OXIMETRY_raw_data_t * data)
{
	MAX30102_GetDataMulti(&MAX30102_measurements);

	CIRCULAR_Push(&circular_red     , MAX30102_measurements.red     );
	CIRCULAR_Push(&circular_infrared, MAX30102_measurements.infrared);

//	average_red = AVERAGE_avg((uint32_t *)circular_red.buffer, MOVING_AVERAGE_PERIOD);
//	average_infrared = AVERAGE_avg((uint32_t *)circular_infrared.buffer, MOVING_AVERAGE_PERIOD);
//
//	CIRCULAR_Push(&circular_AC_red, pow((float)(MAX30102_measurements.red - average_red), 2));
//	CIRCULAR_Push(&circular_AC_infrared, pow((float)(MAX30102_measurements.infrared - average_infrared), 2));
//
//	RMS_AC_red = (uint32_t) sqrt(AVERAGE_avg((uint32_t *)circular_AC_red.buffer, MOVING_AVERAGE_PERIOD));
//	RMS_AC_infrared = (uint32_t) sqrt(AVERAGE_avg((uint32_t *)circular_AC_infrared.buffer, MOVING_AVERAGE_PERIOD));

	data->red      = MAX30102_measurements.red;
	data->infrared = MAX30102_measurements.infrared;
	// TODO: get temperature (need to request conversion before hand, as it takes 30 ms to convert).
}

void OXIMETRY_ProcessData(OXIMETRY_data_t * data)
{
	int32_t spo2;
	int8_t  spo2_valid;

	int32_t heart_rate;
	int8_t  heart_rate_valid;

	MAXIM_HeartRate_SpO2((uint32_t *)circular_infrared.buffer,
						           OXIMETRY_NUMBER_OF_SAMPLES,
						 (uint32_t *)circular_red.buffer,
						 &spo2      , &spo2_valid,
						 &heart_rate, &heart_rate_valid);

	if (!spo2_valid)
	{
		spo2 = -1;
	}
	if(!heart_rate_valid)
	{
		heart_rate = 1;
	}

	data->spo2 = spo2;
	data->heart_rate = heart_rate;
}
