#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"                  // Device header


//volatile unsigned char USART0_RX_Data[150]; 
//volatile unsigned char USART0_RX_Count;
//volatile unsigned char USART0_RX_Data_clean_delay_1mS;
extern unsigned char A0[];
extern unsigned char A1[];
extern unsigned char A2[];
extern unsigned char A3[];

extern unsigned char Z1[];
extern unsigned char Z2[];
extern unsigned char Z3[];
extern unsigned char Z4[];
extern unsigned char Z5[];
extern unsigned char Z6[];
extern unsigned char Z7[];
extern unsigned char Z8[];

extern unsigned char E1[];
extern unsigned char E2[];
extern unsigned char E3[];
extern unsigned char E4[];
extern unsigned char E5[];
extern unsigned char E6[];
extern unsigned char E7[];
extern unsigned char E8[];






extern u8 Cheak_page[];
extern u8 JUMP_TO_6[];
extern u8 JUMP_TO_8[];
extern u8 JUMP_TO_10[];








void Usart1_Init(u32 baud);
void Usart1_Send_Byte(u8 data);
void Usart1_Send_Str(u8 *str);
void Usart1_Send_array(unsigned char *data_array_Pointer );



void Usart2_Init(u32 baud);
void Usart2_Send_Byte(u8 data);
void Usart2_Send_Str(u8 *str);





void Usart2_Send_array(unsigned char *data_array_Pointer );
u8 Array_Comparison(u8 str1[],u8 str2[]);







#endif
