#ifndef _TIMER_H
#define _TIMER_H

#include "stm32f10x.h"                  // Device header






void Delay_ms(u32 ms);
void Delay_us(u32 us);
void Tim1_IT_ms(u32 ms);
void TIM4_Motor_Pwm(void);


#endif
