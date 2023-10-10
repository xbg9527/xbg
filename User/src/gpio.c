#include "main.h"                  // Device header


/**************************************
*��������
*�������ܣ�
*������������
*��������ֵ����
*����������
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
  GPIO_Init(GPIOB, &GPIO_InitStructure);//ִ������Ĳ���
  
  
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
*��������
*�������ܣ�
*������������
*��������ֵ����
*����������
**************************************/
void RCC_Configuration(void)
{
	RCC_DeInit();// �� RCC �����ʼ���ɸ�λ״̬������Ǳ����
	
	//-----------------ʹ��HSI��Ϊϵͳʱ����Դʱ�������HSE��ΪHSI-------------------//		
	
	RCC_HSEConfig(RCC_HSE_ON);//ʹ�� HSE�������ⲿ���� STM32F103 ϵ�п������õ��� 8M
	while(RCC_GetFlagStatus(RCC_FLAG_HSERDY) == RESET);	//�ȴ��ⲿ����ʱ��ʹ�ܾ���	
	
	//-----------------ʹ��FLASHҪ����Pack������Device���Flash�ļ�-------------------//	
	
	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);// ʹ�� FLASH Ԥ��ȡ������
	FLASH_SetLatency(FLASH_Latency_2);// SYSCLK �������������ʱ��ı������ã�����ͳһ���ó� 2
	// ���ó� 2 ��ʱ��SYSCLK ���� 48M Ҳ���Թ�����������ó� 0 ���� 1 ��ʱ��
	// ������õ� SYSCLK �����˷�Χ�Ļ���������Ӳ�����󣬳��������
	// 0��0 < SYSCLK <= 24M
	// 1��24< SYSCLK <= 48M
	// 2��48< SYSCLK <= 72M
	RCC_HCLKConfig(RCC_SYSCLK_Div1);// AHB Ԥ��Ƶ��������Ϊ 1 ��Ƶ��HCLK = SYSCLK
	RCC_PCLK2Config(RCC_HCLK_Div1);// APB2 Ԥ��Ƶ��������Ϊ 1 ��Ƶ��PCLK2 = HCLK
	RCC_PCLK1Config(RCC_HCLK_Div2);// APB1 Ԥ��Ƶ��������Ϊ 1 ��Ƶ��PCLK1 = HCLK/2
	
	//-----------------���ø���Ƶ����Ҫ��������������-------------------//
	
	//-----------------ʹ��HSI��Ϊϵͳʱ����Դʱ�������1��Ϊ2��9��Ϊ16-------------------//		
	
	RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_6);	
	// ���� PLL ʱ����ԴΪ HSE������ PLL ��Ƶ����, PLLCLK = 8MHz * pllmul
	RCC_PLLCmd(ENABLE);// ���� PLL
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);// �ȴ� PLL �ȶ�
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);// �� PLL �ȶ�֮�󣬰� PLL ʱ���л�Ϊϵͳʱ�� SYSCLK
	while (RCC_GetSYSCLKSource() != 0x08);// ��ȡʱ���л�״̬λ��ȷ�� PLLCLK ��ѡΪϵͳʱ��
	
}
















