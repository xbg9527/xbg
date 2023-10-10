#include "main.h"                  // Device header

/**************************************
*函数名：Delay_us_use_SysTick
*函数功能：系统滴答毫秒级延时
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void Delay_ms_use_SysTick(int nms)
{
	int fac_us;
	int fac_ms;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	
	fac_us=SystemCoreClock/8000000;
	fac_ms=(u16)fac_us*1000;
	int temp;
	SysTick->LOAD=(u32)nms*fac_ms;			//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;           //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;          //开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器
}	



/**************************************
*函数名：Delay_us_use_SysTick
*函数功能：系统滴答微秒级延时
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void Delay_us_use_SysTick(int nus)
{ 
	int temp;
	int fac_us;
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;
	SysTick->LOAD=nus*fac_us; //时间加载
	SysTick->VAL=0x00; //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;          //开始倒数  
	do
	{
	  temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达 
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;//清空计数器
}

