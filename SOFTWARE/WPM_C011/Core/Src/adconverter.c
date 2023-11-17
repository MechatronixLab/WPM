/*
 * adconverter.c
 *
 *  Created on: Nov 17, 2023
 *      Author: Andre
 */

#include "adconverter.h"

volatile uint8_t flag_ADC_EOC = 0;	// Flag para sinalização de que um conjunto de conversões A/D foi finalizado
									// EOC: End Of Conversions

uint16_t adc_buffer[2];	// Vetor para armazenar convesões A/D (12 bits: 0 a 4095)
uint16_t adc_mV[2];		// Vetor para armazenar tensões no ADC (0 a 3300 mV)

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{	// Interrupção que ocorre quando um conjunto de conversões é finalizado
	flag_ADC_EOC = 1;								// Seta flag para tratamento no main()
	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);	// Altera estado do LED1 para indicar funionamento do ADC
}

