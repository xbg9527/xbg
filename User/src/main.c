#include "main.h"                  // Device header


int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //�ж����ȼ�����
//	Usart1_Init(115200); //����1��ʼ��
	Usart2_Init(115200);   //����2��ʼ��
	
	Beep_Init();           //��������ʼ��
  Fuya_Init();           //��ѹ�ó�ʼ��
	Foot_Init();           //��̤��ʼ��
	Valve_Init();          //��ŷ���ʼ��
//  Motor_Init();        //�����ʼ��
	ADC_DMA_Init();        //DMA��ʼ��
	Adc1_Ch9_Init();       //ADC��ʼ��
	Pvd_Init();            //��ѹ�������ʼ��
	
	TIM2_Encoder_Init();   //��ʱ��2��������ʼ��
	TIM4_Motor_Pwm();      //���pwm��ʼ��
	Tim1_IT_ms(1);         //��ʱ��1-ms���ж�
	
	
//	Open_Init();           //��������,��ȡ����ʾ����ֵ
//	Display_Init();        //��ʼ��ʾ
//	Error_check();         //�����Լ�
	
	
	while(1)
	{
		Motor_Flag = 0;
		
		timer1_flag[3] = 0;
		Motor_LL_M;Motor_Time = 18176;
		while(!Motor_Flag)//�ȴ�����������ָ��ֵ
		{
			
			
		}
		
	  
		
		Sound_buzzer_du_di();
		Delay_ms(1000);
//		timer1_flag[1] =0;Motor_RR_F;Delay_ms(5000);
//		timer1_flag[1] =0;Motor_LL_F;Delay_ms(5000);
		
		//Key_scanf();
		
		
		//Motor_Work();
		
	
  }//while
	
}//main
