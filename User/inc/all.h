//#ifndef _ALL_H
//#define _ALL_H

//#include "stm32f10x.h"                  // Device header

//#define  Motor_is_run  ( ((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0)) || ((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1)) )

//#define  Valve_on    GPIO_SetBits(GPIOB,GPIO_Pin_12);    //PB12 ����
//#define  Valve_off   GPIO_ResetBits(GPIOB,GPIO_Pin_12);  //PB12


//#define Full_speed 255;

//#define  Pump_on    GPIO_SetBits(GPIOB,GPIO_Pin_13);   
//#define  Pump_off   GPIO_ResetBits(GPIOB,GPIO_Pin_13); 

//unsigned char JUMP_TO_6[] =    {0x06,0x80,0x03,0x00,0x06,0x59,0xE6};//����6ҳ
//unsigned char JUMP_TO_8[] =    {0x06,0x80,0x03,0x00,0x08,0xD8,0x22};//����8ҳ
//unsigned char JUMP_TO_10[] =   {0x06,0x80,0x03,0x00,0x0A,0x59,0xE3};//����10ҳ

//unsigned char Query_page_number[] =   {0x05,0x81,0x03,0x02,0xA0,0xD9};//��03�Ĵ���2���ֽ�--03ҳ��Ĵ���

// 

//volatile unsigned char POS_Check_enable;
//volatile unsigned char  while_loop_exit;
//volatile u32 Each_run_gap_pulse_value;
//volatile unsigned char SHOT_MARK; 
//volatile unsigned char  Suction_Ready;
//volatile unsigned int  Suction_Valve_on_time;
//volatile unsigned char  Self_check_finish;
//volatile unsigned char  EN1_CHN0;

//volatile unsigned char time_40uS_count; 
//volatile unsigned char time_1mS_count;
//volatile unsigned char time_10mS_count; 
//volatile unsigned char time_100mS_count; 
//volatile unsigned char SHOT_Delay_100mS; 


//volatile unsigned char  Self_check_finish;











//#endif
