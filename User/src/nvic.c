#include "main.h"                  // Device header



/**************************************
*��������USART1_IRQHandler
*�������ܣ�����1�жϷ�����
*������������
*��������ֵ����
*����������
**************************************/
u8 usart1_buff[30] = {0};

void USART1_IRQHandler(void)
{
	static u8 i = 0;
	//�ж��ǽ����жϴ���
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		//����жϱ�־λ
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		//�����¼�
		usart1_buff[i] = USART_ReceiveData(USART1);
		i++;
	}
	
	
	//�ж��ǿ����жϴ���
	if(USART_GetITStatus(USART1,USART_IT_IDLE))
	{
		//����жϱ�־λ
		USART1->SR;
		USART1->DR;
		//�����¼�
		usart1_buff[i] = '\0';
		i = 0;
		
		Usart1_Send_Str(usart1_buff);
		
	}
	
	
}






/**************************************
*��������USART2_IRQHandler
*�������ܣ�����2�жϷ�����
*������������
*��������ֵ����
*����������
**************************************/
u8 usart2_buff[30] = {0};
u8 src_flag = 0;
void USART2_IRQHandler(void)
{
	static u8 i = 0;
	
	//�ж��ǽ����жϴ���
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{
		//����жϱ�־λ
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		//�����¼�
		usart2_buff[i] = USART_ReceiveData(USART2);
		i++;
	}
	
	
	//�ж��ǿ����жϴ���
	if(USART_GetITStatus(USART2,USART_IT_IDLE))
	{
		//����жϱ�־λ
		USART2->SR;
		USART2->DR;
		//�����¼�
		usart2_buff[i] = '\0';
		i = 0;
		src_flag = 1;
		
	  //Usart2_Send_Str(usart2_buff);
		if(strcmp((char *)usart2_buff,"0")==0)
		{
			usart2_buff[0] = 0;usart2_buff[1] = 0;
			
			Motor_STOP;
		}
		if(strcmp((char *)usart2_buff,"1")==0)
		{
			usart2_buff[0] = 0;usart2_buff[1] = 0;
			
			Motor_LL_M;
		}
		if(strcmp((char *)usart2_buff,"2")==0)
		{
			usart2_buff[0] = 0;usart2_buff[1] = 0;
			
			Motor_RR_M;
		}
	  if(strcmp((char *)usart2_buff,"3")==0)
		{
			usart2_buff[0] = 0;usart2_buff[1] = 0;
			
			Fuya_ON;
		}
		if(strcmp((char *)usart2_buff,"4")==0)
		{
			usart2_buff[0] = 0;usart2_buff[1] = 0;
			
			Fuya_OFF;
		}
	  
		
		
		
		
	}
	
	
}




/***********************************************
*������    ��TIM1_IRQHandler
*��������  ��TIM1���жϷ�����
*��������  ����
*��������ֵ����
*��������  ��
***********************************************/
u32 timer1_flag[5] = {0};
u16 Adc_Fuya;
u16 Motor_speed=50;
u8 Stuck_in = 1;
void TIM1_UP_IRQHandler(void)
{
	static u16 i= 0;
	if(TIM_GetITStatus(TIM1,TIM_IT_Update))
	{
		//����жϱ�־λ
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		//�����¼�
		timer1_flag[0]++;
		timer1_flag[1]++;
		timer1_flag[2]++;
		timer1_flag[3]++;
//--------------------------------------ÿ1ms�жϵ�ǰ��ѹֵ�Ƿ񳬳�-------------------------------		
		
//---------------------------------------------TIM1_flag3----------------------------------------			
		if(timer1_flag[1] == 1000)
		{
			
			timer1_flag[1] =0;
		}
		
		
		
		
		
		
		
	}
}


/***********************************************
*������    ��TIM2_IRQHandler
*��������  ��TIM2���жϷ�����
*��������  ����
*��������ֵ����
*��������  ��
***********************************************/
u8 Motor_Flag = 0;
u32 TIM_CC1 = 0;
u16 TIM_CC2 = 0;
void TIM2_IRQHandler(void)
{
	u8 TIM_CC3 = 0;
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update))
	{
		//����жϱ�־λ
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		//�����¼�
		//TIM2->CNT = 0;
	}
	
	
	if(TIM_GetITStatus(TIM2,TIM_IT_CC1))
	{
		//����жϱ�־λ
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
		//�����¼�
		TIM_CC1++;
		
		
		if(Motor_Flag == 0 && (TIM_CC1 >= Motor_Time))//����ִ��
		{
			Motor_STOP;
			Motor_Flag = 1;//������־λ
			printf("%d\r\n",timer1_flag[3]);
			Delay_ms(50);TIM_CC1 = 0;//��������
			
		}
		//printf("%d\r\n",TIM2->CNT);
		
		
	}
}

/**===========================================================================
	@file     DMA1_Channel1_IRQHandler()
	@brief    DMA�жϷ�����
	@param   	
	@retval 	
	@note			DMA1_Channel1   ���DMA��������жϱ�־  DMA1_FLAG_TC1
===========================================================================**/
void DMA1_Channel1_IRQHandler(void)
{
	
				/* ʧ��DMA1ͨ��1���Է����жϹ����з���DMA���� */
		DMA_Cmd(DMA1_Channel1,DISABLE);
				/* ���DMA���õ���normalģʽ����Ҫ�ֶ���װ������ */
		// DMA1_Channel1->CNDTR = BUFFER_SIZE;
				/* ����жϱ�־λ */
		DMA_ClearITPendingBit(DMA1_FLAG_TC1);
		// DMA_ClearFlag(DMA1_FLAG_TC1);
				/* ����ʹ��DMA1ͨ��1����ʼ���� */
		DMA_Cmd(DMA1_Channel1,ENABLE);
	
}









