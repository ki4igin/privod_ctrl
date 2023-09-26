#include "privod.h"
#include "stm32g4xx_ll_tim.h"

void privod_offset(struct privod *s, int32_t offset_deg)
{
    struct tim *tim;

    if (offset_deg > 0) {
        tim = &s->tim_pos;
    } else if (offset_deg < 0) {
        tim = &s->tim_neg;
    } else {
        return;
    }

    LL_TIM_SetCounter(tim->inst, 0);
    *tim->ccr = offset_deg * s->k_deg2pulse;
    LL_TIM_EnableCounter(tim->inst);
}
