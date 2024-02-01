/*
 * lora.h
 *
 *  Created on: Feb 1, 2024
 *      Author: Eng. André A. M. Araújo
 */

#ifndef INC_LORA_H_
#define INC_LORA_H_

#include "main.h"
#include "subghz.h"
#include "usart.h"

#include "radio_driver.h"
#include "stm32wlxx_nucleo.h"

#include <string.h>
#include <stdio.h>

#include "cli.h"

#define LORA_RF_FREQUENCY		915000000	// 915 MHz
#define LORA_TX_POWER         	14	      	// dBm
#define LORA_BANDWIDTH      	2      		// Maps to const RadioLoRaBandwidths_t Bandwidths; 500 kHz
#define LORA_SPREADING_FACTOR 	11			// SF
#define LORA_CODINGRATE       	1			// 4/5
#define LORA_PREAMBLE_LENGTH  	8     	  	// Same for Tx and Rx
#define LORA_SYMBOL_TIMEOUT    	5      	 	// Symbols

typedef enum
{
  STATE_NULL,
  STATE_MASTER,
  STATE_SLAVE
} state_t;

typedef enum
{
  SSTATE_NULL,
  SSTATE_RX,
  SSTATE_TX
} substate_t;

typedef struct
{
  state_t state;
  substate_t subState;
  uint32_t rxTimeout;
  uint32_t rxMargin;
  uint32_t randomDelay;
  char rxBuffer[RX_BUFFER_SIZE];
  uint8_t rxSize;
} pingPongFSM_t;

void LORA_RadioInit(void);
void LORA_RadioIRQ(RadioIrqMasks_t radioIrq);
void eventTxDone(pingPongFSM_t *const fsm);
void eventRxDone(pingPongFSM_t *const fsm);
void eventTxTimeout(pingPongFSM_t *const fsm);
void eventRxTimeout(pingPongFSM_t *const fsm);
void eventRxError(pingPongFSM_t *const fsm);
void enterMasterRx(pingPongFSM_t *const fsm);
void enterSlaveRx(pingPongFSM_t *const fsm);
void enterMasterTx(pingPongFSM_t *const fsm);
void enterSlaveTx(pingPongFSM_t *const fsm);
void transitionRxDone(pingPongFSM_t *const fsm);

void LORA_FSM_Init(void);
void LORA_Process(void);

void LORA_Tx(char * lora_tx_buffer);

#endif /* INC_LORA_H_ */
