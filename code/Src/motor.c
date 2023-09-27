#include "motor.h"
#include "main.h"
#include "privod.h"
#include "stm32g4xx_ll_gpio.h"

struct privod az = {
    .gpio_pos = {S1_GPIO_Port, S1_Pin},
    .gpio_neg = {S2_GPIO_Port, S2_Pin},
    .k_deg2pulse = 20,
};

struct privod el = {
    .gpio_pos = {S3_GPIO_Port, S3_Pin},
    .gpio_neg = {S4_GPIO_Port, S4_Pin},
    .k_deg2pulse = 20,
};

void motor_az_offset(int32_t offset_deg)
{
    privod_offset(&az, offset_deg);
}

void motor_el_offset(int32_t offset_deg)
{
    privod_offset(&el, offset_deg);
}

void motor_az_stop(void)
{
    privod_stop(&az);
}

void motor_el_stop(void)
{
    privod_stop(&el);
}

void motor_az_set_k(uint32_t k_deg2pulse)
{
    az.k_deg2pulse = k_deg2pulse;
}

void motor_el_set_k(uint32_t k_deg2pulse)
{
    el.k_deg2pulse = k_deg2pulse;
}

void motor_tick_ms(void)
{
    privod_mov_process(&az);
    privod_mov_process(&el);
}
