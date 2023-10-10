#include "main.h"





/***********************************************
*������    :Motor_Init
*��������  :��ֱ���������IO�ڳ�ʼ������
*��������  :��
*��������ֵ:��
*��������  :
            MOTOR-IB------PB8
						MOTOR-IA------PB9
************************************************/
void Motor_Init(void)
{
	//�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;          //IO�ڱ��
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;      //�˿�ģʽ����   ͨ�����
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //����ٶ�����   2M
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	//����������� ��ʼ״̬  ��
//	GPIO_SetBits(GPIOB,GPIO_Pin_8);
//	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	
}





/***********************************************
*������    :Fuya_Init
*��������  :��ѹ�ó�ʼ��
*��������  :��
*��������ֵ:��
*��������  :
            Fuya------PB13
************************************************/
u8 Fuya_wait = 0;
void Fuya_Init(void)
{
	//�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;          //IO�ڱ��       
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;      //�˿�ģʽ����   ͨ�����
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //����ٶ�����   2M

	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	//����������� ��ʼ״̬  ��

	GPIO_ResetBits(GPIOB,GPIO_Pin_13);
	
}

/***********************************************
*������    :Foot_Init
*��������  :��̤��ʼ��
*��������  :��
*��������ֵ:��
*��������  :
            Foot------PB14
************************************************/
void Foot_Init(void)
{
	//�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;          //IO�ڱ��       
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;      //�˿�ģʽ����   ͨ������
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //����ٶ�����   2M

	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	
}

/***********************************************
*������    :Valve_Init
*��������  :��ŷ���ʼ��
*��������  :��
*��������ֵ:��
*��������  :
            Valve----PB12
************************************************/
void Valve_Init(void)
{
	//�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;          //IO�ڱ��       
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;      //�˿�ģʽ����   ͨ�����
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;   //����ٶ�����   2M

	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	
	//����������� ��ʼ״̬  ��

	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
	
}






/***********************************************
*������    :Motor_OFF
*��������  :�������
*��������  :��
*��������ֵ:��
*��������  :
            MOTOR-IB------PB8
						MOTOR-IA------PB9
************************************************/
void Motor_OFF(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}



/***********************************************
*������    :Motor_L
*��������  :�����ת
*��������  :��
*��������ֵ:��
*��������  :
            MOTOR-IB------PB8
						MOTOR-IA------PB9
************************************************/
void Motor_L(void)
{
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);
}


/***********************************************
*������    :Motor_R
*��������  :�����ת
*��������  :��
*��������ֵ:��
*��������  :
            MOTOR-IB------PB8
						MOTOR-IA------PB9
************************************************/
void Motor_R(void)
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}



/***********************************************
*������    :Get_fuya_grade
*��������  :��ȡѹ���ȼ���Ӧ�ĸ�ѹֵ
*��������  :��
*��������ֵ:
*��������  :
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
		case  5: fuya_grade = 1890;fuya_time = 70;  break;        //��ѹ�ȼ�����ǿ��
		case  6: fuya_grade = 2080;fuya_time = 60;  break;
		case  7: fuya_grade = 2270;fuya_time = 50;  break;
		case  8: fuya_grade = 2460;fuya_time = 50;  break;
		case  9: fuya_grade = 2650;fuya_time = 45;  break;
		case 10: fuya_grade = 2850;fuya_time = 31;  break;
	}
	
}


/***********************************************
*������    :Valve_on
*��������  :��ŷ�����
*��������  :��
*��������ֵ:��
*��������  :Valve_on

************************************************/
u8 Valve_flag = 0;
void Volue_on(void)
{
	u16 k;
	
	k = Get_Adc(9);
	if(k >= fuya_grade)
	{
		Valve_flag = 1; //������־λ
		
		Valve_ON;
		timer1_flag[0] = 0;
		
	}
	else if(!Valve_flag)
	{
		Valve_OFF;
	}
}


/********************************************
*������    :TIM2_Encoder_Init
*��������  :��ʱ��2������ģʽ��ʼ��
*��������  :��
*��������ֵ:��
*��������  :
***********************************************/
void TIM2_Encoder_Init(void)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure; 
  GPIO_InitTypeDef GPIO_InitStructure;
  
  /* TIM2ʱ��ʹ�� */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  /* GPIOB��ʱ��ʹ�� */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
  
	/*��ʼ������ı���*/
  GPIO_StructInit(&GPIO_InitStructure);
  /*�������� */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  
  /* ��ʱ��2����*/
	//����ʱ��2�����мĴ������ָ�Ĭ��ֵ
  TIM_DeInit(TIM2);
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);                              
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;               //Ԥ��Ƶ ����Ƶ
  TIM_TimeBaseStructure.TIM_Period = 0xFFFF;  
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;  //����ʱ�ӷ�Ƶϵ��������Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ 
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	//��ʱ��������ģʽ���þ���ͨ���������ز���
  TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12,
                             TIM_ICPolarity_Rising,
														 TIM_ICPolarity_Rising);
 
  /*ͨ������*/
  TIM_ICStructInit(&TIM_ICInitStructure);
  TIM_ICInitStructure.TIM_ICFilter = 6; //���˲���
  //ͨ����ʼ�����ú���
	TIM_ICInit(TIM2, &TIM_ICInitStructure);
  
	
 /*NVIC����*/
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = TIM2_IRQn ;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 3;
	NVIC_Init(&NVIC_InitStruct);
	
	
	
 //��������¼���־λ
  TIM_ClearFlag(TIM2,TIM_IT_Update | TIM_IT_CC1);
  
	//�����ж�ʹ��
	TIM_ITConfig(TIM2,TIM_IT_Update | TIM_IT_CC1,ENABLE);
	TIM2->CNT = around;
  
  TIM_Cmd(TIM2, ENABLE);  	   //ʹ�ܶ�ʱ��2
}


/********************************************
*������    :GetMotorPulse
*��������  :��ȡ������庯��
*��������  :��
*��������ֵ:��

*��������  :
***********************************************/
u16 g_s16LeftMotorPulse = 0;   
u32 Motor_time1 = 0;
u32 Motor_time2 = 1000;
u8 Motor_timeflag = 0;
void GetMotorPulse(void)  //�ɼ�����ٶ�����
{ 	
	
	g_s16LeftMotorPulse = -TIM_GetCounter(TIM2);  
  
  
	
	if(g_s16LeftMotorPulse == 15936)
	{
		Motor_OFF();TIM2->CNT = 0;   //����
		Delay_ms(1000);Motor_R();
		
	}
	
	
	
}


/***********************************************
*������    :Motor_Run
*��������  :�ƽ����ж�
*��������  :��
*��������ֵ:��
*��������  :

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
		Key_scanf();    //����ɨ��
	}
	
	
	Motor_Flag = 0;
	if(Shot_count == 0)
	{
		timer1_flag[3] = 0;
		Motor_Time=around + R_Time;
	}
	else                                //������0С��ô��� �� �ӵ���65535����ô���
	{
		Motor_Time=Motor_Time + L_Time+ R_Time;
	}
	//printf("\r\n��ת---��ǰλ��:%d ���ξ���:%d Ŀ��λ��:%d \r\n",TIM2->CNT,R_Time,Motor_Time);
	
	switch(Flow_rate)//�����ٶȵȼ�����
	{
		case 1 :Motor_LL_M;Motor_Runing=1;break;
		case 2 :Motor_LL_F;Motor_Runing=1;break;
		case 3 :Motor_LL_S;Motor_Runing=1;break;
	}
	Mortor_trend = 1;//��ת����
	//�����жϼ���ֵ
	timer1_flag[1] =0;
	while(!Motor_Flag)//�ȴ�����������ָ��ֵ
	{
		Motor_Blocked();    //�����ֿ�
		if(Stuck_in==0)//������ת
		{
			Motor_Stuck();
			return;//������ǰ�������ص�������
		}
		Key_scanf();    //����ɨ��
	}
	                                //�ӵ���65535����ô�����������
	Motor_Flag = 0;
	
	Motor_Time=Motor_Time - L_Time;//�趨����������
	
	//printf("��ת---��ǰλ��:%d  Ŀ��λ��:%d \r\n",TIM2->CNT,Motor_Time);
	
	Motor_RR_M;Motor_Runing=1;//���˵��ٶȹ̶�
	Mortor_trend = 0;//��ת����
	//�����жϼ���ֵ
	timer1_flag[1] =0;
	while(!Motor_Flag)//�ȴ�����������ָ��ֵ
	{
		//Motor_Blocked();    //��ת����Ҫ�����ֿ�
		if(Stuck_in==0)//������ת
		{
			Motor_Stuck();
			return;//������ǰ�������ص�������
		}
		Key_scanf();    //����ɨ��
	}
	
	Shot_count++;//ע�����+1
	
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
			Key_scanf();    //����ɨ��
		}
		
		
		if(Suction_Ready){Fuya_ON;}
		
	}
	disp_Shot_count_and_Total_Shot();
	
	Motor_Run_Flag = 0;
}


/***********************************************
*������    :Motor_Stuck
*��������  :�����ת
*��������  :��
*��������ֵ:��
*��������  :Blocked

************************************************/
void Motor_Stuck(void)
{
	
	Usart2_Send_array(JUMP_TO_10);   //������ʮҳ
	if(EN1_CHN0==0) //��Ӣ�Ĺ̶�����ʾ����
	{//����
		Dgus_82write_data(0x11,0x00,"ע�����!�ƽ����쳣");
		Dgus_82write_data(0x10,0x00," ȷ��");
	}
	else
	{//Ӣ��
		Dgus_82write_data(0x11,0x00,"Injecting Errors!");
		Dgus_82write_data(0x10,0x00,"  OK");
	}
	if(Mortor_trend == 0)
	{
		Motor_LL_F;Delay_ms(500);//����1s
	}
	else if(Mortor_trend == 1)
	{
		Motor_RR_F;Delay_ms(500);//����1s
	}
	Motor_STOP;Fuya_OFF;Valve_ON;
	Suction_Ready = 0; 
	Dgus_82send_data( 0x60, Suction_Ready);//���¸�ѹ������ʾ
	Delay_ms(100);TIM_CC1 = 1;TIM2->CNT = around;//��������
	
	Motor_Run_Flag = 0;Motor_timeflag = 0;Motor_Runing=0;//���ת����־λ,����
	
}


/***********************************************
*������    :Motor_Blocked
*��������  :���������
*��������  :��
*��������ֵ:��
*��������  :

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
*������    :Motor_Work
*��������  :�ƽ�������
*��������  :��
*��������ֵ:��
*��������  :

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
			
		  
		}//�����ѹ���ڿ���״̬-if���-β
}














