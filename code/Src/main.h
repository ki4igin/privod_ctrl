
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/

#include "stm32g4xx_ll_lpuart.h"
#include "stm32g4xx_ll_rcc.h"
#include "stm32g4xx_ll_bus.h"
#include "stm32g4xx_ll_crs.h"
#include "stm32g4xx_ll_system.h"
#include "stm32g4xx_ll_exti.h"
#include "stm32g4xx_ll_cortex.h"
#include "stm32g4xx_ll_utils.h"
#include "stm32g4xx_ll_pwr.h"
#include "stm32g4xx_ll_dma.h"
#include "stm32g4xx_ll_tim.h"
#include "stm32g4xx_ll_gpio.h"

#if defined(USE_FULL_ASSERT)
#include "stm32_assert.h"
#endif /* USE_FULL_ASSERT */

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* Private defines -----------------------------------------------------------*/
#define B1_Pin               LL_GPIO_PIN_13
#define B1_GPIO_Port         GPIOC
#define LPUART1_TX_Pin       LL_GPIO_PIN_2
#define LPUART1_TX_GPIO_Port GPIOA
#define LPUART1_RX_Pin       LL_GPIO_PIN_3
#define LPUART1_RX_GPIO_Port GPIOA
#define LD2_Pin              LL_GPIO_PIN_5
#define LD2_GPIO_Port        GPIOA
#define S4_Pin               LL_GPIO_PIN_10
#define S4_GPIO_Port         GPIOB
#define S1_Pin               LL_GPIO_PIN_14
#define S1_GPIO_Port         GPIOB
#define S3_Pin               LL_GPIO_PIN_15
#define S3_GPIO_Port         GPIOB
#define T_SWDIO_Pin          LL_GPIO_PIN_13
#define T_SWDIO_GPIO_Port    GPIOA
#define T_SWCLK_Pin          LL_GPIO_PIN_14
#define T_SWCLK_GPIO_Port    GPIOA
#define T_SWO_Pin            LL_GPIO_PIN_3
#define T_SWO_GPIO_Port      GPIOB
#define S2_Pin               LL_GPIO_PIN_4
#define S2_GPIO_Port         GPIOB
#ifndef NVIC_PRIORITYGROUP_0
#define NVIC_PRIORITYGROUP_0 ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority, \
                                                         4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1 ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority, \
                                                         3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2 ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority, \
                                                         2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3 ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority, \
                                                         1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4 ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority, \
                                                         0 bit  for subpriority */
#endif

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
