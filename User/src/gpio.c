#include "main.h"                  // Device header


/**************************************
*函数名：
*函数功能：
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void GPIO_Configuration(void)
{

  GPIO_InitTypeDef GPIO_InitStructure;
	

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
    
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //GPIO_Speed_50MHz ;	  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //GPIO_Speed_50MHz ;	  
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  




  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
  
 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;	
  GPIO_Init(GPIOB, &GPIO_InitStructure);//执行上面的操作
  
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //GPIO_Speed_50MHz ;	  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 | GPIO_Pin_12 | GPIO_Pin_13 |GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  //GPIO_Speed_50MHz ;	  
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
 

}


/**************************************
*函数名：
*函数功能：
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void RCC_Configuration(void)
{
	RCC_DeInit();// 把 RCC 外设初始化成复位状态，这句是必须的
	
	//-----------------使用HSI作为系统时钟来源时把下面的HSE改为HSI-------------------//		
	
	RCC_HSEConfig(RCC_HSE_ON);//使能 HSE，开启外部晶振， STM32F103 系列开发板用的是 8M
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);	//等待外部高速时钟使能就绪	
	
	//-----------------使用FLASH要加入Pack管理中Device里的Flash文件-------------------//	
	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);// 使能 FLASH 预存取缓冲区
	FLASH_SetLatency(FLASH_Latency_2);// SYSCLK 周期与闪存访问时间的比例设置，这里统一设置成 2
	// 设置成 2 的时候，SYSCLK 低于 48M 也可以工作，如果设置成 0 或者 1 的时候，
	// 如果配置的 SYSCLK 超出了范围的话，则会进入硬件错误，程序就死了
	// 0：0 < SYSCLK <= 24M
	// 1：24< SYSCLK <= 48M
	// 2：48< SYSCLK <= 72M
	RCC_HCLKConfig(RCC_SYSCLK_Div1);// AHB 预分频因子设置为 1 分频，HCLK = SYSCLK
	RCC_PCLK2Config(RCC_HCLK_Div1);// APB2 预分频因子设置为 1 分频，PCLK2 = HCLK
	RCC_PCLK1Config(RCC_HCLK_Div2);// APB1 预分频因子设置为 1 分频，PCLK1 = HCLK/2
	
	//-----------------设置各种频率主要就是在这里设置-------------------//
	
	//-----------------使用HSI作为系统时钟来源时把下面的1改为2，9改为16-------------------//		
	
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_6);	
	// 设置 PLL 时钟来源为 HSE，设置 PLL 倍频因子, PLLCLK = 8MHz * pllmul
	RCC_PLLCmd(ENABLE);// 开启 PLL
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);// 等待 PLL 稳定
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);// 当 PLL 稳定之后，把 PLL 时钟切换为系统时钟 SYSCLK
	while (RCC_GetSYSCLKSource() != 0x08);// 读取时钟切换状态位，确保 PLLCLK 被选为系统时钟
	
}
















