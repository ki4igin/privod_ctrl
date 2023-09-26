#include "motor.h"
#include "privod.h"
#include "stm32g4xx_ll_tim.h"

struct privod az = {
    .tim_pos = {
        .inst = TIM15,
        .ccr = &TIM15->CCR2,
    },
    .tim_neg = {
        .inst = TIM15,
        .ccr = &TIM15->CCR1,
    },
    .k_deg2pulse = 20,
};

struct privod el = {
    .tim_pos = {
        .inst = TIM3,
        .ccr = &TIM3->CCR1,
    },
    .tim_neg = {
        .inst = TIM2,
        .ccr = &TIM2->CCR3,
    },
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

void motor_az_set_k(uint32_t k_deg2pulse)
{
    az.k_deg2pulse = k_deg2pulse;
}

void motor_el_set_k(uint32_t k_deg2pulse)
{
    el.k_deg2pulse = k_deg2pulse;
}