#ifndef __PRIVOD_H__
#define __PRIVOD_H__

#include "stm32g4xx.h"

struct privod {
    struct tim {
        TIM_TypeDef *const inst;
        volatile uint32_t *const ccr;
    } tim_pos, tim_neg;

    uint32_t k_deg2pulse;
};

void privod_offset(struct privod *s, int32_t offset_deg);

#endif