#ifndef _NVIC_H
#define _NVIC_H

#include "stm32f10x.h"                  // Device header

extern u8 usart1_buff[30];
extern u8 usart2_buff[30];

extern u8 src_flag;
extern u8 Motor_Flag;

extern u32 timer1_flag[5];
extern u16 Adc_Fuya;
extern u16 Motor_speed;
extern u32 TIM_CC1;
extern u16 TIM_CC2;
extern u8 Stuck_in;



#endif
