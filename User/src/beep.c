#include "main.h"                  // Device header


/**************************************
*��������Beep_Init
*�������ܣ���������ʼ��
*������������
*��������ֵ����
*����������Beep-------PB5
**************************************/
void Beep_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	
	/*ʱ��ʹ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	/*����IO��*/
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//�������ĳ�ʼ״̬�� �͵�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_5);
}



/**************************************
*��������Sound_buzzer_di_di
*�������ܣ��������조�� �Ρ���
*������������
*��������ֵ����
*����������
**************************************/
void Sound_buzzer_di_di(void)
{
	u16 i=190;
	while(i--)
	{
		BEEP_ON;
		Delay_us_use_SysTick(270);//ʵ��3.8 _delay_us(96);
		BEEP_OFF;
		Delay_us_use_SysTick(270);//ʵ��3.8_delay_us(175);
	}
	
	Delay_ms_use_SysTick(100);
	
	i=190;
	while(i--)
	{
		BEEP_ON;
		Delay_us_use_SysTick(270);//ʵ��3.8 _delay_us(96);
		BEEP_OFF;
		Delay_us_use_SysTick(270);//ʵ��3.8_delay_us(175);
	}
	
}





/**************************************
*��������Sound_buzzer_du_di
*�������ܣ��������조�� ཡ���
*������������
*��������ֵ����
*����������
**************************************/
void Sound_buzzer_du_di(void)//�조���֡���
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
		Delay_us_use_SysTick(2);//ʵ��3.8 _delay_us(96);
		BEEP_OFF;
		Delay_us_use_SysTick(2);//ʵ��3.8_delay_us(175);
	}
}






/**************************************
*��������GPIO_ToggleBits
*�������ܣ�ȡ������
*������������
*��������ֵ����
*����������
**************************************/
void GPIO_ToggleBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  /* Check the parameters */
  assert_param(IS_GPIO_ALL_PERIPH(GPIOx));

  GPIOx->ODR ^= GPIO_Pin;
}








