#ifndef __PRIVOD_H__
#define __PRIVOD_H__

#include "stm32g4xx.h"

struct gpio {
    GPIO_TypeDef *port;
    uint32_t pin;
};

struct privod {
    struct gpio gpio_pos;
    struct gpio gpio_neg;
    int32_t pos_ms;
    int32_t offset_ms;
    uint32_t k_deg2pulse;
};

inline static void privod_offset(struct privod *s, int32_t offset_deg)
{
    s->offset_ms += offset_deg * s->k_deg2pulse;
}

inline static int32_t privod_get_pos(struct privod *s)
{
    return s->pos_ms / s->k_deg2pulse;
}

inline static void privod_set_origin(struct privod *s)
{
    s->pos_ms = 0;
}

inline static void privod_mov_process(struct privod *s)
{
    if (s->offset_ms > 0) {
        LL_GPIO_ResetOutputPin(s->gpio_neg.port, s->gpio_neg.pin);
        LL_GPIO_SetOutputPin(s->gpio_pos.port, s->gpio_pos.pin);
        s->offset_ms--;
        s->pos_ms++;
    } else if (s->offset_ms < 0) {
        LL_GPIO_ResetOutputPin(s->gpio_pos.port, s->gpio_pos.pin);
        LL_GPIO_SetOutputPin(s->gpio_neg.port, s->gpio_neg.pin);
        s->offset_ms++;
        s->pos_ms--;
    } else {
        LL_GPIO_ResetOutputPin(s->gpio_neg.port, s->gpio_neg.pin);
        LL_GPIO_ResetOutputPin(s->gpio_pos.port, s->gpio_pos.pin);
    }
}

inline static void privod_stop(struct privod *s)
{
    s->offset_ms = 0;
}

#endif