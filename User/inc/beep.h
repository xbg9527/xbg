#ifndef _BEEP_H
#define _BEEP_H

#include "stm32f10x.h"                  // Device header

#define BEEP_ON         (GPIO_SetBits(GPIOB,GPIO_Pin_5))
#define BEEP_OFF        (GPIO_ResetBits(GPIOB,GPIO_Pin_5))
#define BEEP_OVERTURN   (GPIO_ToggleBits(GPIOB,GPIO_Pin_5))




void Beep_Init(void);
void Sound_buzzer_di_di(void);
void Sound_buzzer_du_di(void);
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);



#endif
