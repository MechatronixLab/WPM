/*
 * adconverter.h
 *
 *  Created on: Nov 17, 2023
 *      Author: Andre
 */

#ifndef INC_ADCONVERTER_H_
#define INC_ADCONVERTER_H_

#include "adc.h"

#define	ADC_ACTIVE_CHANNELS	2	// Número de canais do ADC ativos

extern volatile uint8_t flag_ADC_EOC;

extern uint16_t adc_buffer[2];
extern uint16_t adc_mV[2];

#endif /* INC_ADCONVERTER_H_ */
