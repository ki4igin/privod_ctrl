#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32g4xx.h"

void motor_az_offset(int32_t offset_deg);
void motor_el_offset(int32_t offset_deg);
void motor_az_stop(void);
void motor_el_stop(void);
void motor_stop(void);
void motor_az_set_k(uint32_t k_deg2pulse);
void motor_el_set_k(uint32_t k_deg2pulse);
void motor_tick_ms(void);
int32_t motor_az_get_pos(void);
int32_t motor_el_get_pos(void);
void motor_origin(void);

#endif