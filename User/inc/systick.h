#ifndef _SYSTICK_H
#define _SYSTICK_H

#include "stm32f10x.h"                  // Device header




void Delay_ms_use_SysTick(int nms);
void Delay_us_use_SysTick(int nus);


#endif
