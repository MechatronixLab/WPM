/*
 * oximetry.c
 *
 *  Created on: Feb 10, 2024
 *      Author: Eng. André A. M. Araújo
 */

#include "oximetry.h"

static int32_t buffer_red[OXIMETRY_SPO2_AVERAGE] = {0};
circular_buffer_t circular_red =
{
		.buffer = buffer_red,
		.head = 0,
		.tail = 0,
		.length = OXIMETRY_SPO2_AVERAGE
};

static int32_t buffer_infrared[OXIMETRY_SPO2_AVERAGE] = {0};
circular_buffer_t circular_infrared =
{
		.buffer = buffer_infrared,
		.head = 0,
		.tail = 0,
		.length = OXIMETRY_SPO2_AVERAGE
};

static int32_t buffer_AC2_red[OXIMETRY_SPO2_AVERAGE] = {0};
circular_buffer_t circular_AC2_red =
{
		.buffer = buffer_AC2_red,
		.head = 0,
		.tail = 0,
		.length = OXIMETRY_SPO2_AVERAGE
};

static int32_t buffer_AC2_infrared[OXIMETRY_SPO2_AVERAGE] = {0};
circular_buffer_t circular_AC2_infrared =
{
		.buffer = buffer_AC2_infrared,
		.head = 0,
		.tail = 0,
		.length = OXIMETRY_SPO2_AVERAGE
};

static float buffer_ratio[OXIMETRY_SPO2_AVERAGE] = {0};
circular_buffer_t circular_ratio =
{
		.buffer = buffer_ratio,
		.head = 0,
		.tail = 0,
		.length = OXIMETRY_SPO2_AVERAGE
};

static int32_t buffer_pulse_counter[OXIMETRY_HR_AVERAGE] = {0};
circular_buffer_t circular_pulse_counter =
{
		.buffer = buffer_pulse_counter,
		.head = 0,
		.tail = 0,
		.length = OXIMETRY_HR_AVERAGE
};

static int32_t buffer_pulse[OXIMETRY_HR_AVERAGE] = {0};
circular_buffer_t circular_pulse =
{
		.buffer = buffer_pulse,
		.head = 0,
		.tail = 0,
		.length = OXIMETRY_HR_AVERAGE
};

void OXIMETRY_Init(void)
{
	MAX30102_Reset();
	MAX30102_ConfigProximityDetect();
}

void OXIMETRY_ProcessDataWPM(OXIMETRY_data_t * data)
{
	static int32_t previous_red = 0;
	static int32_t previous_infrared = 0;

	static uint8_t peak_counter = 0;
	static uint8_t pulse_detected = 0;

	uint8_t pulse_counter = 0;

	float aux1 = 0;
	float aux2 = 0;

	static MAX30102_data_t max30102_data = {0};

	MAX30102_GetDataMulti(&max30102_data);

	data->red 	   = max30102_data.red     ;
	data->infrared = max30102_data.infrared;

	AUX_CircularBufferPush(&circular_red     , data->red     );
	AUX_CircularBufferPush(&circular_infrared, data->infrared);

	data->DC_red 	  = (uint32_t)AUX_Average((uint32_t *)circular_red.buffer     , OXIMETRY_SPO2_AVERAGE);
	data->DC_infrared = (uint32_t)AUX_Average((uint32_t *)circular_infrared.buffer, OXIMETRY_SPO2_AVERAGE);

	AUX_CircularBufferPush(&circular_AC2_red     , (int32_t)pow((float)((int32_t)(data->red      - data->DC_red     )), 2));
	AUX_CircularBufferPush(&circular_AC2_infrared, (int32_t)pow((float)((int32_t)(data->infrared - data->DC_infrared)), 2));

	data->RMS_AC_red 	  = (uint32_t) sqrt(AUX_Average((uint32_t *)circular_AC2_red.buffer     , OXIMETRY_SPO2_AVERAGE));
	data->RMS_AC_infrared = (uint32_t) sqrt(AUX_Average((uint32_t *)circular_AC2_infrared.buffer, OXIMETRY_SPO2_AVERAGE));

	aux1 = ((float)data->RMS_AC_red/(float)data->DC_red);
	aux2 = ((float)data->RMS_AC_infrared/(float)data->DC_infrared);

	AUX_CircularBufferPush(&circular_ratio, (uint32_t)(1000*aux1/aux2));

	data->ratio = AUX_Average((uint32_t *)circular_ratio.buffer, OXIMETRY_SPO2_AVERAGE);

	data->spo2  = (uint16_t)(1040.0 - (170.0 * data->ratio)/1000.0);

	data->dred_dt 	   = ((int32_t)data->red      - previous_red     ) * OXIMETRY_SAMPLE_RATE;
	data->dinfrared_dt = ((int32_t)data->infrared - previous_infrared) * OXIMETRY_SAMPLE_RATE;

	if (data->dred_dt < 0)
	{
		peak_counter++;

		if (data->dred_dt < -1000)
		{
			data->heart_beep = 1;
			BSP_LED_On(2);
		}
	}
	else
	{
		peak_counter = 0;
		data->heart_beep = 0;
		BSP_LED_Off(2);
	}

	if (peak_counter >= 4)
	{
		pulse_detected = OXIMETRY_HR_AVERAGE;
		peak_counter = 0;
	}

	AUX_CircularBufferPush(&circular_pulse_counter, pulse_detected);

	pulse_detected = 0;

	pulse_counter = AUX_Average((uint32_t *)circular_pulse_counter.buffer, OXIMETRY_HR_AVERAGE);

	AUX_CircularBufferPush(&circular_pulse, (pulse_counter * 60)/(OXIMETRY_HR_AVERAGE/OXIMETRY_SAMPLE_RATE));	// TODO: remove magic numbers: pulse * 60[s/min] / avergaing_time[s]

	data->heart_rate = AUX_Average((uint32_t *)circular_pulse.buffer, OXIMETRY_HR_AVERAGE);

	previous_red      = data->red;
	previous_infrared = data->infrared;

	// TODO: get temperature (need to request conversion before hand, as it takes 30 ms to convert).
}

void OXIMETRY_ProcessDataMaxim(OXIMETRY_data_t * data)
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
