#include "main.h"                  // Device header


/**************************************
*函数名：Beep_Init
*函数功能：蜂鸣器初始化
*函数参数：无
*函数返回值：无
*函数描述：Beep-------PB5
**************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/*时钟使能*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	/*配置IO口*/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//蜂鸣器的初始状态关 低电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}



/**************************************
*函数名：Sound_buzzer_di_di
*函数功能：蜂鸣器响“滴 滴”声
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void Sound_buzzer_di_di(void)
{
	u16 i=190;
	while(i--)
	{
		BEEP_ON;
		Delay_us_use_SysTick(270);//实测3.8 _delay_us(96);
		BEEP_OFF;
		Delay_us_use_SysTick(270);//实测3.8_delay_us(175);
	}
	
	Delay_ms_use_SysTick(100);
	
	i=190;
	while(i--)
	{
		BEEP_ON;
		Delay_us_use_SysTick(270);//实测3.8 _delay_us(96);
		BEEP_OFF;
		Delay_us_use_SysTick(270);//实测3.8_delay_us(175);
	}
	
}





/**************************************
*函数名：Sound_buzzer_du_di
*函数功能：蜂鸣器响“滴 嘟”声
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void Sound_buzzer_du_di(void)//响“杜嘀”声
{
	u16 i=95;
	while(i--)
	{
		BEEP_ON;
		Delay_us_use_SysTick(270);
		BEEP_OFF;
		Delay_us_use_SysTick(270);
	}
	
	Delay_ms_use_SysTick(2);
	
	i=500;
	while(i--)
	{
		BEEP_ON;
		Delay_us_use_SysTick(2);//实测3.8 _delay_us(96);
		BEEP_OFF;
		Delay_us_use_SysTick(2);//实测3.8_delay_us(175);
	}
}






/**************************************
*函数名：GPIO_ToggleBits
*函数功能：取反函数
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR ^= GPIO_Pin;
}








