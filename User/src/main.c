#include "main.h"                  // Device header


int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   //中断优先级分组
//	Usart1_Init(115200); //串口1初始化
	Usart2_Init(115200);   //串口2初始化
	
	Beep_Init();           //蜂鸣器初始化
  Fuya_Init();           //负压泵初始化
	Foot_Init();           //脚踏初始化
	Valve_Init();          //电磁阀初始化
//  Motor_Init();        //电机初始化
	ADC_DMA_Init();        //DMA初始化
	Adc1_Ch9_Init();       //ADC初始化
	Pvd_Init();            //电压检测器初始化
	
	TIM2_Encoder_Init();   //定时器2编码器初始化
	TIM4_Motor_Pwm();      //电机pwm初始化
	Tim1_IT_ms(1);         //定时器1-ms级中断
	
	
//	Open_Init();           //开机动作,读取各显示变量值
//	Display_Init();        //初始显示
//	Error_check();         //开机自检
	
	
	while(1)
	{
		Motor_Flag = 0;
		
		timer1_flag[3] = 0;
		Motor_LL_M;Motor_Time = 18176;
		while(!Motor_Flag)//等待脉冲数到达指定值
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
