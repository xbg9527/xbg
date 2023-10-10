#include "main.h"





/***********************************************
*函数名    :Motor_Init
*函数功能  :对直流电机所用IO口初始化配置
*函数参数  :无
*函数返回值:无
*函数描述  :
            MOTOR-IB------PB8
						MOTOR-IA------PB9
************************************************/
void Motor_Init(void)
{
	//端口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;          //IO口编号
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;      //端口模式配置   通用输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //输出速度配置   2M
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	//输出数据配置 初始状态  开
//	GPIO_SetBits(GPIOB,GPIO_Pin_8);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	
}





/***********************************************
*函数名    :Fuya_Init
*函数功能  :负压泵初始化
*函数参数  :无
*函数返回值:无
*函数描述  :
            Fuya------PB13
************************************************/
u8 Fuya_wait = 0;
void Fuya_Init(void)
{
	//端口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;          //IO口编号       
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;      //端口模式配置   通用输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //输出速度配置   2M

	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	//输出数据配置 初始状态  关

	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	
}

/***********************************************
*函数名    :Foot_Init
*函数功能  :脚踏初始化
*函数参数  :无
*函数返回值:无
*函数描述  :
            Foot------PB14
************************************************/
void Foot_Init(void)
{
	//端口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;          //IO口编号       
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //端口模式配置   通用输入
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //输出速度配置   2M

	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	
}

/***********************************************
*函数名    :Valve_Init
*函数功能  :电磁阀初始化
*函数参数  :无
*函数返回值:无
*函数描述  :
            Valve----PB12
************************************************/
void Valve_Init(void)
{
	//端口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;          //IO口编号       
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;      //端口模式配置   通用输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //输出速度配置   2M

	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	//输出数据配置 初始状态  关

	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	
}






/***********************************************
*函数名    :Motor_OFF
*函数功能  :电机：关
*函数参数  :无
*函数返回值:无
*函数描述  :
            MOTOR-IB------PB8
						MOTOR-IA------PB9
************************************************/
void Motor_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}



/***********************************************
*函数名    :Motor_L
*函数功能  :电机反转
*函数参数  :无
*函数返回值:无
*函数描述  :
            MOTOR-IB------PB8
						MOTOR-IA------PB9
************************************************/
void Motor_L(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
}


/***********************************************
*函数名    :Motor_R
*函数功能  :电机正转
*函数参数  :无
*函数返回值:无
*函数描述  :
            MOTOR-IB------PB8
						MOTOR-IA------PB9
************************************************/
void Motor_R(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}



/***********************************************
*函数名    :Get_fuya_grade
*函数功能  :获取压力等级对应的负压值
*函数参数  :无
*函数返回值:
*函数描述  :
************************************************/
u16 fuya_grade;
u16 fuya_time;
void Get_fuya_grade_time(void)
{
	switch(Power_level)
	{
		case  1: fuya_grade = 1130;fuya_time = 200;  break;
		case  2: fuya_grade = 1320;fuya_time = 170;  break;
		case  3: fuya_grade = 1510;fuya_time = 140;  break;
		case  4: fuya_grade = 1700;fuya_time = 110;  break;
		case  5: fuya_grade = 1890;fuya_time = 70;  break;        //负压等级吸力强度
		case  6: fuya_grade = 2080;fuya_time = 60;  break;
		case  7: fuya_grade = 2270;fuya_time = 50;  break;
		case  8: fuya_grade = 2460;fuya_time = 50;  break;
		case  9: fuya_grade = 2650;fuya_time = 45;  break;
		case 10: fuya_grade = 2850;fuya_time = 31;  break;
	}
	
}


/***********************************************
*函数名    :Valve_on
*函数功能  :电磁阀放气
*函数参数  :无
*函数返回值:无
*函数描述  :Valve_on

************************************************/
u8 Valve_flag = 0;
void Volue_on(void)
{
	u16 k;
	
	k = Get_Adc(9);
	if(k >= fuya_grade)
	{
		Valve_flag = 1; //锁定标志位
		
		Valve_ON;
		timer1_flag[0] = 0;
		
	}
	else if(!Valve_flag)
	{
		Valve_OFF;
	}
}


/********************************************
*函数名    :TIM2_Encoder_Init
*函数功能  :定时器2编码器模式初始化
*函数参数  :无
*函数返回值:无
*函数描述  :
***********************************************/
void TIM2_Encoder_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure; 
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* TIM2时钟使能 */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* GPIOB的时钟使能 */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
	/*初始化定义的变量*/
  GPIO_StructInit(&GPIO_InitStructure);
  /*参数配置 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  /* 定时器2配置*/
	//将定时器2的所有寄存器都恢复默认值
  TIM_DeInit(TIM2);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);                              
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;               //预分频 不分频
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //设置时钟分频系数：不分频
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式 
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	//定时器编码器模式设置具体通道和上升沿捕获
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,
                             TIM_ICPolarity_Rising,
														 TIM_ICPolarity_Rising);
 
  /*通道配置*/
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6; //无滤波器
  //通道初始化配置函数
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
  
	
 /*NVIC配置*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn ;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
	
	
	
 //清除更新事件标志位
  TIM_ClearFlag(TIM2,TIM_IT_Update | TIM_IT_CC1);
  
	//更新中断使能
	TIM_ITConfig(TIM2,TIM_IT_Update | TIM_IT_CC1,ENABLE);
	TIM2->CNT = around;
  
  TIM_Cmd(TIM2, ENABLE);  	   //使能定时器2
}


/********************************************
*函数名    :GetMotorPulse
*函数功能  :获取电机脉冲函数
*函数参数  :无
*函数返回值:无

*函数描述  :
***********************************************/
u16 g_s16LeftMotorPulse = 0;   
u32 Motor_time1 = 0;
u32 Motor_time2 = 1000;
u8 Motor_timeflag = 0;
void GetMotorPulse(void)  //采集电机速度脉冲
{ 	
	
	g_s16LeftMotorPulse = -TIM_GetCounter(TIM2);  
  
  
	
	if(g_s16LeftMotorPulse == 15936)
	{
		Motor_OFF();TIM2->CNT = 0;   //清零
		Delay_ms(1000);Motor_R();
		
	}
	
	
	
}


/***********************************************
*函数名    :Motor_Run
*函数功能  :推进器行动
*函数参数  :无
*函数返回值:无
*函数描述  :

************************************************/
u8 Motor_Run_Flag;
u8 Motor_Runing = 0;
u8 Mortor_trend;
void Motor_Run(void)
{
	
	timer1_flag[2] =0;Fuya_wait = 0;//TIM2->CNT =61535;
	Motor_Run_Flag = 1;
	
	while(Fuya_wait != 1)
	{
		Key_scanf();    //按键扫描
	}
	
	
	Motor_Flag = 0;
	if(Shot_count == 0)
	{
		timer1_flag[3] = 0;
		Motor_Time=around + R_Time;
	}
	else                                //减到比0小怎么办↓ 或 加到比65535大怎么办↑
	{
		Motor_Time=Motor_Time + L_Time+ R_Time;
	}
	//printf("\r\n正转---当前位置:%d 单次距离:%d 目标位置:%d \r\n",TIM2->CNT,R_Time,Motor_Time);
	
	switch(Flow_rate)//根据速度等级调速
	{
		case 1 :Motor_LL_M;Motor_Runing=1;break;
		case 2 :Motor_LL_F;Motor_Runing=1;break;
		case 3 :Motor_LL_S;Motor_Runing=1;break;
	}
	Mortor_trend = 1;//正转方向
	//清零中断计数值
	timer1_flag[1] =0;
	while(!Motor_Flag)//等待脉冲数到达指定值
	{
		Motor_Blocked();    //阻力抵抗
		if(Stuck_in==0)//发生堵转
		{
			Motor_Stuck();
			return;//结束当前函数，回到主函数
		}
		Key_scanf();    //按键扫描
	}
	                                //加到比65535大怎么办↓正常计算
	Motor_Flag = 0;
	
	Motor_Time=Motor_Time - L_Time;//设定回退脉冲数
	
	//printf("反转---当前位置:%d  目标位置:%d \r\n",TIM2->CNT,Motor_Time);
	
	Motor_RR_M;Motor_Runing=1;//回退的速度固定
	Mortor_trend = 0;//反转方向
	//清零中断计数值
	timer1_flag[1] =0;
	while(!Motor_Flag)//等待脉冲数到达指定值
	{
		//Motor_Blocked();    //反转不需要阻力抵抗
		if(Stuck_in==0)//发生堵转
		{
			Motor_Stuck();
			return;//结束当前函数，回到主函数
		}
		Key_scanf();    //按键扫描
	}
	
	Shot_count++;//注射次数+1
	
	if(Shot_count >= (Total_Shot*10))
	{
		Fuya_OFF;Valve_ON;Suction_Ready=0;//Shot_count = 0;
		Dgus_82send_data( 0x60, Suction_Ready);
	}
	else
	{
		Fuya_OFF;Valve_ON;
		timer1_flag[2] =0;Fuya_wait = 0;
		while(Fuya_wait != 2)
		{
			Key_scanf();    //按键扫描
		}
		
		
		if(Suction_Ready){Fuya_ON;}
		
	}
	disp_Shot_count_and_Total_Shot();
	
	Motor_Run_Flag = 0;
}


/***********************************************
*函数名    :Motor_Stuck
*函数功能  :电机堵转
*函数参数  :无
*函数返回值:无
*函数描述  :Blocked

************************************************/
void Motor_Stuck(void)
{
	
	Usart2_Send_array(JUMP_TO_10);   //跳到第十页
	if(EN1_CHN0==0) //中英文固定的显示内容
	{//中文
		Dgus_82write_data(0x11,0x00,"注射错误!推进器异常");
		Dgus_82write_data(0x10,0x00," 确认");
	}
	else
	{//英文
		Dgus_82write_data(0x11,0x00,"Injecting Errors!");
		Dgus_82write_data(0x10,0x00,"  OK");
	}
	if(Mortor_trend == 0)
	{
		Motor_LL_F;Delay_ms(500);//回退1s
	}
	else if(Mortor_trend == 1)
	{
		Motor_RR_F;Delay_ms(500);//回退1s
	}
	Motor_STOP;Fuya_OFF;Valve_ON;
	Suction_Ready = 0; 
	Dgus_82send_data( 0x60, Suction_Ready);//更新负压开关显示
	Delay_ms(100);TIM_CC1 = 1;TIM2->CNT = around;//计数清零
	
	Motor_Run_Flag = 0;Motor_timeflag = 0;Motor_Runing=0;//电机转动标志位,解锁
	
}


/***********************************************
*函数名    :Motor_Blocked
*函数功能  :电机受阻检测
*函数参数  :无
*函数返回值:无
*函数描述  :

************************************************/
void Motor_Blocked(void)
{
	
	switch(Flow_rate)
	{
		case 1:if(Motor_speed<=105)
					{
						if(TIM4->CCR3<255)
						{
							if(timer1_flag[3] >= 10)
							{
								timer1_flag[3] =0;
								TIM4->CCR3++;
							}
						}
					}
					if(Motor_speed>=110)
					{
						if(TIM4->CCR3>76)
						{
							if(timer1_flag[3] >= 10)
							{
								timer1_flag[3] =0;
								TIM4->CCR3--;
							}
						}
					}
					break;
		case 3:if(Motor_speed<=90)
					{
						if(TIM4->CCR3<255)
						{
							if(timer1_flag[3] >= 10)
							{
								timer1_flag[3] =0;
								TIM4->CCR3++;
							}		
						}
					}
					if(Motor_speed>=95)
					{
						if(TIM4->CCR3>60)
						{
							if(timer1_flag[3] >= 10)
							{
								timer1_flag[3] =0;
								TIM4->CCR3--;
							}		
						}
					}
					break;
	}
	
	
	
	
	
}




/***********************************************
*函数名    :Motor_Work
*函数功能  :推进器工作
*函数参数  :无
*函数返回值:无
*函数描述  :

************************************************/
void Motor_Work(void)
{
	if(Suction_Ready)
		{
			
			switch(Injector_mode)
			{
				case 1 :
				if(Adc_Fuya > fuya_grade)
				{
					
					Motor_Run();
					
				}
				;break;
				
				case 2 :
				if(Foot_State)
				{
					Motor_Run();
					
				}
				;break;
				
				case 3 :
				if(Foot_State)
				{
					Motor_Run();
					
				}
				;break;
				
				case 4 :
				if(Foot_State)
				{
					while(Foot_State)
					{
						Motor_LL_M;
					}
					Motor_RR_F;
					timer1_flag[2] =0;Fuya_wait = 0;
					Delay_ms(500);

					Motor_STOP;Delay_ms(50);TIM2->CNT = around;
					Fuya_OFF;Valve_ON;
					timer1_flag[2] =0;Fuya_wait = 0;
					Delay_ms(1000);
					
					Fuya_ON;
					
				}
				;break;
				
				case 5 :
					if(Foot_State)
					{
						while(Foot_State)
						{
							Motor_LL_S;
						}
					Motor_RR_F;
						Delay_ms(500);

					Motor_STOP;Delay_ms(50);TIM2->CNT = around;
					Fuya_OFF;Valve_ON;
					Delay_ms(1000);

					Fuya_ON;
					}
				;break;
			}
			
		  
		}//如果负压处于开启状态-if语句-尾
}














