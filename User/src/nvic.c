#include "main.h"                  // Device header



/**************************************
*函数名：USART1_IRQHandler
*函数功能：串口1中断服务函数
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
u8 usart1_buff[30] = {0};

void USART1_IRQHandler(void)
{
	static u8 i = 0;
	//判断是接收中断触发
	if(USART_GetITStatus(USART1,USART_IT_RXNE))
	{
		//清除中断标志位
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		//紧急事件
		usart1_buff[i] = USART_ReceiveData(USART1);
		i++;
	}
	
	
	//判断是空闲中断触发
	if(USART_GetITStatus(USART1,USART_IT_IDLE))
	{
		//清除中断标志位
		USART1->SR;
		USART1->DR;
		//紧急事件
		usart1_buff[i] = '\0';
		i = 0;
		
		Usart1_Send_Str(usart1_buff);
		
	}
	
	
}






/**************************************
*函数名：USART2_IRQHandler
*函数功能：串口2中断服务函数
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
u8 usart2_buff[30] = {0};
u8 src_flag = 0;
void USART2_IRQHandler(void)
{
	static u8 i = 0;
	
	//判断是接收中断触发
	if(USART_GetITStatus(USART2,USART_IT_RXNE))
	{
		//清除中断标志位
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		//紧急事件
		usart2_buff[i] = USART_ReceiveData(USART2);
		i++;
	}
	
	
	//判断是空闲中断触发
	if(USART_GetITStatus(USART2,USART_IT_IDLE))
	{
		//清除中断标志位
		USART2->SR;
		USART2->DR;
		//紧急事件
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
*函数名    ：TIM1_IRQHandler
*函数功能  ：TIM1的中断服务函数
*函数参数  ：无
*函数返回值：无
*函数描述  ：
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
		//清除中断标志位
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		//紧急事件
		timer1_flag[0]++;
		timer1_flag[1]++;
		timer1_flag[2]++;
		timer1_flag[3]++;
//--------------------------------------每1ms判断当前负压值是否超出-------------------------------		
		
//---------------------------------------------TIM1_flag3----------------------------------------			
		if(timer1_flag[1] == 1000)
		{
			
			timer1_flag[1] =0;
		}
		
		
		
		
		
		
		
	}
}


/***********************************************
*函数名    ：TIM2_IRQHandler
*函数功能  ：TIM2的中断服务函数
*函数参数  ：无
*函数返回值：无
*函数描述  ：
***********************************************/
u8 Motor_Flag = 0;
u32 TIM_CC1 = 0;
u16 TIM_CC2 = 0;
void TIM2_IRQHandler(void)
{
	u8 TIM_CC3 = 0;
	
	if(TIM_GetITStatus(TIM2,TIM_IT_Update))
	{
		//清除中断标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		//紧急事件
		//TIM2->CNT = 0;
	}
	
	
	if(TIM_GetITStatus(TIM2,TIM_IT_CC1))
	{
		//清除中断标志位
		TIM_ClearITPendingBit(TIM2,TIM_IT_CC1);
		//紧急事件
		TIM_CC1++;
		
		
		if(Motor_Flag == 0 && (TIM_CC1 >= Motor_Time))//条件执行
		{
			Motor_STOP;
			Motor_Flag = 1;//解锁标志位
			printf("%d\r\n",timer1_flag[3]);
			Delay_ms(50);TIM_CC1 = 0;//计数清零
			
		}
		//printf("%d\r\n",TIM2->CNT);
		
		
	}
}

/**===========================================================================
	@file     DMA1_Channel1_IRQHandler()
	@brief    DMA中断服务函数
	@param   	
	@retval 	
	@note			DMA1_Channel1   清除DMA传输完成中断标志  DMA1_FLAG_TC1
===========================================================================**/
void DMA1_Channel1_IRQHandler(void)
{
	
				/* 失能DMA1通道1，以防在中断过程中发生DMA传输 */
		DMA_Cmd(DMA1_Channel1,DISABLE);
				/* 如果DMA设置的是normal模式，需要手动重装计数器 */
		// DMA1_Channel1->CNDTR = BUFFER_SIZE;
				/* 清除中断标志位 */
		DMA_ClearITPendingBit(DMA1_FLAG_TC1);
		// DMA_ClearFlag(DMA1_FLAG_TC1);
				/* 重新使能DMA1通道1，开始工作 */
		DMA_Cmd(DMA1_Channel1,ENABLE);
	
}









