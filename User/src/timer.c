#include "main.h"                  // Device header



/***********************************************
*函数名    ：Tim3_delay_ms
*函数功能  ：定时器3毫秒级延时函数
*函数参数  ：u32 ms
*函数返回值：无
*函数描述  ：APB1  72M    7200分频  10次/ms
***********************************************/
void Delay_ms(u32 ms)
{
	//定时器的时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);                          //重载影子寄存器
	//配置定时器
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;    //可以不写
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//边沿对齐,向上计数
	TIM_TimeBaseInitStruct.TIM_Period = ms*10-1;                //重载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;              //分频
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);            //内部有人为产生更新事件
	
	TIM_SelectOnePulseMode(TIM3, TIM_OPMode_Single);           //单脉冲计数模式
	

	//清除标志位
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//使能定时器
	TIM_Cmd(TIM3,ENABLE);
	//等待计数完成
	while(!(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)));

}




/***********************************************
*函数名    ：Tim3_delay_us
*函数功能  ：定时器3微秒级延时函数
*函数参数  ：u32 us
*函数返回值：无
*函数描述  ：APB1  72M    36分频  2次/us
*********************************	**************/
void Delay_us(u32 us)
{
	//定时器的时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);                          //重载影子寄存器
	//配置定时器
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;    //可以不写
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;//边沿对齐,向上计数
	TIM_TimeBaseInitStruct.TIM_Period = us*2-1;                //重载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;              //分频
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);            //内部有人为产生更新事件
	
	TIM_SelectOnePulseMode(TIM3, TIM_OPMode_Single);           //单脉冲计数模式
	

	//清除标志位
	TIM_ClearFlag(TIM3,TIM_FLAG_Update);
	//使能定时器
	TIM_Cmd(TIM3,ENABLE);
	//等待计数完成
	while(!(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)));

}



/**************************************
*函数名：Tim1_IT_ms
*函数功能：定时器1毫秒级中断
*函数参数：u32 ms
*函数返回值：无
*函数描述：
**************************************/
void Tim1_IT_ms(u32 ms)
{
	/*定时器配置*/
	//端口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//基本时基单元配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;        //递增计数
	TIM_TimeBaseInitStruct.TIM_Period = 10 * ms - 1;                    //重载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200 - 1;                      //7200分频
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);
	//清除计数完成/更新 中断标志Wie
	TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
	
	/*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM1_UP_IRQn ;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
	
	//更新中断使能
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	//使能计数器
	TIM_Cmd(TIM1, ENABLE);
	
}










/********************************************************************
*函数名    ：TIM4_Motor_Pwm
*函数功能  ：定时器4通道3、4输出PWM
*函数参数  ：无
*函数返回值：无
*函数描述  ：APB1  36M   36分频       1次/us     周期1000个数（1ms ）
             PB8、PB9
*****************************************************************/
void TIM4_Motor_Pwm(void)
{
	/*IO控制器配置*/
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//GPIO端口配置
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	/*定时器控制器配置*/
	//时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	//基本时基单元配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct = {0};
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 255;   //重装载值
	TIM_TimeBaseInitStruct.TIM_Prescaler = 11;  //时钟分频
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStruct);
	
	
	//通道配置
	TIM_OCInitTypeDef TIM_OCInitStruct = {0};
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
	
	
	  // PWM1 Mode configuration: Channel3 //
  TIM_OCInitStruct.TIM_Pulse = 0;	
  TIM_OC3Init(TIM4, &TIM_OCInitStruct);	 //使能通道3
  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);

  // PWM1 Mode configuration: Channel4 //
  TIM_OCInitStruct.TIM_Pulse = 0;	
  TIM_OC4Init(TIM4, &TIM_OCInitStruct);	//使能通道4
  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);



  TIM_ARRPreloadConfig(TIM4, ENABLE);	
	//使能计数器
	TIM_Cmd(TIM4,ENABLE);
}



