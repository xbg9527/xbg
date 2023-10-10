#include "main.h"                  // Device header

/**************************************
*��������Delay_us_use_SysTick
*�������ܣ�ϵͳ�δ���뼶��ʱ
*������������
*��������ֵ����
*����������
**************************************/
void Delay_ms_use_SysTick(int nms)
{
	int fac_us;
	int fac_ms;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	fac_us=SystemCoreClock/8000000;
	fac_ms=(u16)fac_us*1000;
	int temp;
	SysTick->LOAD=(u32)nms*fac_ms;			//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;           //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����
}	



/**************************************
*��������Delay_us_use_SysTick
*�������ܣ�ϵͳ�δ�΢�뼶��ʱ
*������������
*��������ֵ����
*����������
**************************************/
void Delay_us_use_SysTick(int nus)
{ 
	int temp;
	int fac_us;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;
	SysTick->LOAD=nus*fac_us; //ʱ�����
	SysTick->VAL=0x00; //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;          //��ʼ����  
	do
	{
	  temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽�� 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;//��ռ�����
}

