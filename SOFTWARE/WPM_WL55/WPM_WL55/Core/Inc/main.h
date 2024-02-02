/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wlxx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LED1_Pin GPIO_PIN_15
#define LED1_GPIO_Port GPIOB
#define IRQ0_Pin GPIO_PIN_3
#define IRQ0_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_9
#define LED2_GPIO_Port GPIOB
#define IRQ1_Pin GPIO_PIN_5
#define IRQ1_GPIO_Port GPIOB
#define IRQ2_Pin GPIO_PIN_8
#define IRQ2_GPIO_Port GPIOB
#define FE_CTRL3_Pin GPIO_PIN_3
#define FE_CTRL3_GPIO_Port GPIOC
#define B1_Pin GPIO_PIN_0
#define B1_GPIO_Port GPIOA
#define FE_CTRL2_Pin GPIO_PIN_5
#define FE_CTRL2_GPIO_Port GPIOC
#define OLED_RESET_Pin GPIO_PIN_1
#define OLED_RESET_GPIO_Port GPIOB
#define FE_CTRL1_Pin GPIO_PIN_4
#define FE_CTRL1_GPIO_Port GPIOC
#define B3_Pin GPIO_PIN_6
#define B3_GPIO_Port GPIOC
#define B2_Pin GPIO_PIN_1
#define B2_GPIO_Port GPIOA
#define LED3_Pin GPIO_PIN_11
#define LED3_GPIO_Port GPIOB
#define T_VCP_RX_Pin GPIO_PIN_3
#define T_VCP_RX_GPIO_Port GPIOA
#define T_VCP_RXA2_Pin GPIO_PIN_2
#define T_VCP_RXA2_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
