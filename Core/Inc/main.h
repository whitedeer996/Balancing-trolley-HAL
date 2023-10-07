/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
extern float yaw_used;
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
#define MPU6050_SCK_Pin GPIO_PIN_13
#define MPU6050_SCK_GPIO_Port GPIOC
#define TB6612EN_Pin GPIO_PIN_1
#define TB6612EN_GPIO_Port GPIOC
#define TestKey_Pin GPIO_PIN_0
#define TestKey_GPIO_Port GPIOA
#define OledINT_Pin GPIO_PIN_4
#define OledINT_GPIO_Port GPIOC
#define OledINT_EXTI_IRQn EXTI4_IRQn
#define TB6612BIN2_Pin GPIO_PIN_5
#define TB6612BIN2_GPIO_Port GPIOC
#define MPU6050_SDA_Pin GPIO_PIN_12
#define MPU6050_SDA_GPIO_Port GPIOB
#define TB6612AIN2_Pin GPIO_PIN_9
#define TB6612AIN2_GPIO_Port GPIOC
#define TB6612BIN1_Pin GPIO_PIN_8
#define TB6612BIN1_GPIO_Port GPIOA
#define TB6612AIN1_Pin GPIO_PIN_15
#define TB6612AIN1_GPIO_Port GPIOA
#define TestLed_Pin GPIO_PIN_2
#define TestLed_GPIO_Port GPIOD
#define OledClk_Pin GPIO_PIN_8
#define OledClk_GPIO_Port GPIOB
#define OledData_Pin GPIO_PIN_9
#define OledData_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
