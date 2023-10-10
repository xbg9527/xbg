#include "main.h"                  // Device header



/***********************************************
*������    ��Tim3_delay_ms
*��������  ����ʱ��3���뼶��ʱ����
*��������  ��u32 ms
*��������ֵ����
*��������  ��APB1  72M    7200��Ƶ  10��/ms
***********************************************/
void Delay_ms(u32 ms)
{
	//��ʱ����ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);                          //����Ӱ�ӼĴ���
	//���ö�ʱ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;    //���Բ�д
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ض���,���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = ms*10-1;                //����ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;              //��Ƶ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);            //�ڲ�����Ϊ���������¼�
	
	TIM_SelectOnePulseMode(TIM3, TIM_OPMode_Single);           //���������ģʽ
	

	//�����־λ
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3,ENABLE);
	//�ȴ��������
	while(!(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)));

}




/***********************************************
*������    ��Tim3_delay_us
*��������  ����ʱ��3΢�뼶��ʱ����
*��������  ��u32 us
*��������ֵ����
*��������  ��APB1  72M    36��Ƶ  2��/us
*********************************	**************/
void Delay_us(u32 us)
{
	//��ʱ����ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);                          //����Ӱ�ӼĴ���
	//���ö�ʱ��
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;    //���Բ�д
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//���ض���,���ϼ���
	TIM_TimeBaseInitStruct.TIM_Period = us*2-1;                //����ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;              //��Ƶ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);            //�ڲ�����Ϊ���������¼�
	
	TIM_SelectOnePulseMode(TIM3, TIM_OPMode_Single);           //���������ģʽ
	

	//�����־λ
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM3,ENABLE);
	//�ȴ��������
	while(!(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)));

}



/**************************************
*��������Tim1_IT_ms
*�������ܣ���ʱ��1���뼶�ж�
*����������u32 ms
*��������ֵ����
*����������
**************************************/
void Tim1_IT_ms(u32 ms)
{
	/*��ʱ������*/
	//�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//����ʱ����Ԫ����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;        //��������
	TIM_TimeBaseInitStruct.TIM_Period = 10 * ms - 1;                    //����ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;                      //7200��Ƶ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	//����������/���� �жϱ�־Wie
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	
	/*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn ;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
	
	//�����ж�ʹ��
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	//ʹ�ܼ�����
	TIM_Cmd(TIM1, ENABLE);
	
}










/********************************************************************
*������    ��TIM4_Motor_Pwm
*��������  ����ʱ��4ͨ��3��4���PWM
*��������  ����
*��������ֵ����
*��������  ��APB1  36M   36��Ƶ       1��/us     ����1000������1ms ��
             PB8��PB9
*****************************************************************/
void TIM4_Motor_Pwm(void)
{
	/*IO����������*/
	//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//GPIO�˿�����
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	/*��ʱ������������*/
	//ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//����ʱ����Ԫ����
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 255;   //��װ��ֵ
	TIM_TimeBaseInitStruct.TIM_Prescaler = 11;  //ʱ�ӷ�Ƶ
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	
	//ͨ������
	TIM_OCInitTypeDef TIM_OCInitStruct = {0};
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	
	
	  // PWM1 Mode configuration: Channel3 //
  TIM_OCInitStruct.TIM_Pulse = 0;	
  TIM_OC3Init(TIM4, &TIM_OCInitStruct);	 //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  // PWM1 Mode configuration: Channel4 //
  TIM_OCInitStruct.TIM_Pulse = 0;	
  TIM_OC4Init(TIM4, &TIM_OCInitStruct);	//ʹ��ͨ��4
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);



  TIM_ARRPreloadConfig(TIM4, ENABLE);	
	//ʹ�ܼ�����
	TIM_Cmd(TIM4,ENABLE);
}



