#ifndef _MOTOR_H
#define _MOTOR_H

#include "stm32f10x.h"                  // Device header

#define Fuya_ON        (GPIO_SetBits(GPIOB,GPIO_Pin_13))
#define Fuya_OFF       (GPIO_ResetBits(GPIOB,GPIO_Pin_13))
#define Fuya_State     (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13) == 1)
#define Foot_State     (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == 1)


#define Valve_ON       GPIO_SetBits(GPIOB,GPIO_Pin_12)
#define Valve_OFF      GPIO_ResetBits(GPIOB,GPIO_Pin_12)



//��ת
#define Motor_RR_F     TIM4->CCR3=0;     TIM4->CCR4=255;      //����
#define Motor_RR_M     TIM4->CCR3=0;     TIM4->CCR4=76;      //����
#define Motor_RR_S     TIM4->CCR3=0;     TIM4->CCR4=60;      //����
//��ת
#define Motor_LL_F     TIM4->CCR3=255;   TIM4->CCR4=0;   //����
#define Motor_LL_M     TIM4->CCR3=76;   TIM4->CCR4=0;   //����
#define Motor_LL_S     TIM4->CCR3=60;   TIM4->CCR4=0;   //����


#define Motor_STOP     TIM4->CCR3=255;  TIM4->CCR4=255;//ͣת
#define Motor_RUN     ( ((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==1)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==0)) || ((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_8)==0)&&(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)==1)) )


#define Signal_A    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define Signal_B    GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define around      4000    //������ƽ�-   ��Ϊ61535


extern	u16 fuya_grade;
extern	u16 fuya_time;
extern	u8 Fuya_wait;
extern  u8 Valve_flag;
extern  u16 g_s16LeftMotorPulse;
extern  u8 Motor_Run_Flag;
extern  u8 Motor_Runing;
extern  u8 Motor_timeflag;
extern  u8 Mortor_trend;


void Motor_Init(void);
void Motor_OFF(void);
void Motor_L(void);
void Motor_R(void);

void Fuya_Init(void);
void Foot_Init(void);
void Valve_Init(void);

void Get_fuya_grade_time(void);
void Volue_on(void);
void TIM2_Encoder_Init(void);  //��ʱ��2������ģʽ����
void Motor_Run(void);        //���������
void Motor_Stuck(void);      //�����תִ��
void Motor_Blocked(void);    //�������Կ�

void Motor_Work(void);      //�ƽ�������

#endif
