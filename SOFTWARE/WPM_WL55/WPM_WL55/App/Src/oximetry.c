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

int32_t buffer_AC2_red[MOVING_AVERAGE_PERIOD] = {0};
circular_buffer_t circular_AC2_red =
{
		.buffer = buffer_AC2_red,
		.head = 0,
		.tail = 0,
		.length = MOVING_AVERAGE_PERIOD
};

int32_t buffer_AC2_infrared[MOVING_AVERAGE_PERIOD] = {0};
circular_buffer_t circular_AC2_infrared =
{
		.buffer = buffer_AC2_infrared,
		.head = 0,
		.tail = 0,
		.length = MOVING_AVERAGE_PERIOD
};

float buffer_ratio[MOVING_AVERAGE_PERIOD] = {0};
circular_buffer_t circular_ratio =
{
		.buffer = buffer_ratio,
		.head = 0,
		.tail = 0,
		.length = MOVING_AVERAGE_PERIOD
};

uint32_t DC_red = 0;
uint32_t DC_infrared = 0;

uint32_t RMS_AC_red = 0;
uint32_t RMS_AC_infrared = 0;

uint32_t ox_spo2 = 0;

void OXIMETRY_Init(void)
{
	MAX30102_Reset();
	MAX30102_ConfigProximityDetect();
}

float aux1 = 0;
float aux2 = 0;
float ratio = 0;

void OXIMETRY_GetRawData(OXIMETRY_raw_data_t * data)
{


	MAX30102_GetDataMulti(&MAX30102_measurements);

	AUX_CircularBufferPush(&circular_red     , MAX30102_measurements.red     );
	AUX_CircularBufferPush(&circular_infrared, MAX30102_measurements.infrared);

	DC_red 		= (uint32_t)AUX_Average((uint32_t *)circular_red.buffer     , MOVING_AVERAGE_PERIOD);
	DC_infrared = (uint32_t)AUX_Average((uint32_t *)circular_infrared.buffer, MOVING_AVERAGE_PERIOD);

	AUX_CircularBufferPush(&circular_AC2_red     , (int32_t)pow((float)((int32_t)(MAX30102_measurements.red      - DC_red     )), 2));
	AUX_CircularBufferPush(&circular_AC2_infrared, (int32_t)pow((float)((int32_t)(MAX30102_measurements.infrared - DC_infrared)), 2));

	RMS_AC_red 	    = (uint32_t) sqrt(AUX_Average((uint32_t *)circular_AC2_red.buffer     , MOVING_AVERAGE_PERIOD));
	RMS_AC_infrared = (uint32_t) sqrt(AUX_Average((uint32_t *)circular_AC2_infrared.buffer, MOVING_AVERAGE_PERIOD));

	aux1 = ((float)RMS_AC_red/(float)DC_red);
	aux2 = ((float)RMS_AC_infrared/(float)DC_infrared);

	AUX_CircularBufferPush(&circular_ratio, (aux1/aux2));

	ratio = AUX_Average((uint32_t *)circular_ratio.buffer, MOVING_AVERAGE_PERIOD);

	ox_spo2 = (uint32_t)(104.0 - 17.0 * ratio);

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
		heart_rate = -1;
	}

	data->spo2 = spo2;
	data->heart_rate = heart_rate;
}
