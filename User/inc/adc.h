#ifndef _ADC_H
#define _ADC_H

#include "stm32f10x.h"                  // Device header

#define ADC1_DR     (0x4001244C)
#define SendBuff_Size      5


void ADC_DMA_Init(void);
void Adc1_Ch9_Init(void);
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);


#endif
