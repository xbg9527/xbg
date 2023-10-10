#ifndef _GPIO_H
#define _GPIO_H

#include "stm32f10x.h"                  // Device header

#define  Pump_on    GPIO_SetBits(GPIOB,GPIO_Pin_13);
#define  Pump_off   GPIO_ResetBits(GPIOB,GPIO_Pin_13);




void RCC_Configuration(void);
void GPIO_Configuration(void);

#endif
