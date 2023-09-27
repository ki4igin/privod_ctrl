
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "stm32g4xx_ll_usart.h"
#include "gpio.h"
#include "motor.h"
#include "tim.h"

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* Private user code ---------------------------------------------------------*/

enum __attribute__((packed)) cmd_id {
    CMD_RESET = 1,
    CMD_TEST = 2,
    CMD_LED_TOGGLE,
    CMD_AZ_SET_K,
    CMD_EL_SET_K,
    CMD_STOP,
    CMD_AZ_STOP,
    CMD_EL_STOP,
    CMD_AZ_OFFSET,
    CMD_EL_OFFSET,
    CMD_AZ_GET_POS,
    CMD_EL_GET_POS,
    CMD_SET_ORIGIN,
};

struct cmd {
    uint16_t id;
    int16_t arg;
};

union {
    struct cmd cmd;
    uint8_t data[4];
} uart_buf_rx = {0};

static void uart_send_word(struct cmd cmd)
{
    uint8_t *buf = (uint8_t *)&cmd;
    for (uint32_t i = 0; i < 4; i++) {
        LL_USART_TransmitData8(USART2, *buf++);
    }
}

static void cmd_work(struct cmd cmd)
{
    switch (cmd.id) {
    case CMD_RESET: {
        NVIC_SystemReset();
    } break;
    case CMD_STOP: {
        motor_stop();
    } break;
    case CMD_AZ_STOP: {
        motor_az_stop();
    } break;
    case CMD_EL_STOP: {
        motor_el_stop();
    } break;
    case CMD_LED_TOGGLE: {
        gpio_led_toggle();
    } break;
    case CMD_AZ_OFFSET: {
        motor_az_offset(cmd.arg);
    } break;
    case CMD_EL_OFFSET: {
        motor_el_offset(cmd.arg);
    } break;
    case CMD_AZ_SET_K: {
        motor_az_set_k(cmd.arg);
    } break;
    case CMD_EL_SET_K: {
        motor_el_set_k(cmd.arg);
    } break;
    case CMD_AZ_GET_POS: {
        cmd.arg = motor_az_get_pos();
        uart_send_word(cmd);
    } break;
    case CMD_EL_GET_POS: {
        cmd.arg = motor_el_get_pos();
        uart_send_word(cmd);
    } break;
    case CMD_SET_ORIGIN: {
        motor_origin();
    } break;

    default:
        break;
    }
}

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{
    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

    /* System interrupt init*/
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    /** Disable the internal Pull-Up in Dead Battery pins of UCPD peripheral
     */
    LL_PWR_DisableUCPDDeadBattery();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_USART2_UART_Init();
    MX_TIM6_Init();

    LL_TIM_EnableIT_UPDATE(TIM6);
    LL_TIM_EnableCounter(TIM6);

    /* Infinite loop */

    while (1) {
        if (LL_USART_IsActiveFlag_RXFT(USART2)) {
            for (uint32_t i = 0; i < 4; i++) {
                uart_buf_rx.data[i] = LL_USART_ReceiveData8(USART2);
            }
            cmd_work(uart_buf_rx.cmd);
        }
        if (LL_USART_IsActiveFlag_RTO(USART2)) {
            LL_USART_ClearFlag_RTO(USART2);
            while (LL_USART_IsActiveFlag_RXNE(USART2)) {
                uint32_t t = LL_USART_ReceiveData8(USART2);
                (void)t;
            }
        }

        // LL_mDelay(1000);
        // gpio_led_toggle();
    }
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config(void)
{
    LL_FLASH_SetLatency(LL_FLASH_LATENCY_3);
    while (LL_FLASH_GetLatency() != LL_FLASH_LATENCY_3) {
    }
    LL_PWR_SetRegulVoltageScaling(LL_PWR_REGU_VOLTAGE_SCALE1);
    LL_RCC_HSE_Enable();
    /* Wait till HSE is ready */
    while (LL_RCC_HSE_IsReady() != 1) {
    }

    LL_RCC_PLL_ConfigDomain_SYS(LL_RCC_PLLSOURCE_HSE, LL_RCC_PLLM_DIV_3, 25, LL_RCC_PLLR_DIV_2);
    LL_RCC_PLL_EnableDomain_SYS();
    LL_RCC_PLL_Enable();
    /* Wait till PLL is ready */
    while (LL_RCC_PLL_IsReady() != 1) {
    }

    LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_PLL);
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_2);
    /* Wait till System clock is ready */
    while (LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_PLL) {
    }

    /* Insure 1us transition state at intermediate medium speed clock*/
    for (__IO uint32_t i = (170 >> 1); i != 0; i--) {
        ;
    }

    /* Set AHB prescaler*/
    LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
    LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_4);
    LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_4);

    LL_Init1msTick(100000000);

    LL_SetSystemCoreClock(100000000);
}

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
    }
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
       ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
}
#endif /* USE_FULL_ASSERT */
