#include "main.h"                  // Device header


/**************************************
*函数名：Open_Init
*函数功能：开机动作
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
	u8 Menmory_number= 1;
	u8 Menmory_First;
	u8 EN1_CHN0 = 0;      //中英文模式
	u8 Set_Buzzer_off;    //音量开关
	u8 Injector_mode =0;  //注射模式
	u8 Syringe_type=0;       //注射类型-管子型号大小
	u8 Flow_rate =0;       //注射速度
	u8 Power_level =0;     //负压等级
	u8 Suction_Ready=0;    //负压状态
	u8 Sub_menu=0;         //子菜单
	u8 Sub_menu_data =0;   //子菜单-分支数
	u32 Syringe_volume=0;     //注射容积
	u8 Total_Shot=0;         //注射总次数
	u8 Shot_count=0;         //当前注射次数
	u16 One_Dose=0;           //单次注射量
	u8 One_Dose_Grade=0;     //
	u8 disp_Shot_count_Total_Shot_Team_selection=0;
	u8 disp_One_Dose[] =  {"0.0000 (ml)"};   // 
	u8 disp_Total_Shot_ADJ[] = {"000"};      //
	
	u32 Specs = 0;
	u32 R_Time = 0;
  u32 L_Time = 0;
	u16 Motor_Time = 0;
	
	
void Open_Init(void)
{
		//开机动作
	Menmory_number =1;
	
	
	Menmory_First =   IAP_Flash_ReadHalfWord(10,0); //读出第page页，第add8个半字  0-xxx
	//-----------------------------------------第一次上电，初使化存储的5组参数-----------------------------------------------
	if( Menmory_First != 10 )
	{
		IAP_EraseSector(10); //擦除第10页,必须擦除后才能写入。
		IAP_Flash_ProgramHalfWord(10,0,10);//往第十页的第0个半字写入10
		
		
			IAP_EraseSector(0); //在设定的起始地址算的第几页   0-XXXMenmory_number
			
			for(u8 i_number=1; i_number<8; i_number++)
			{
					IAP_EraseSector(i_number); //擦除在设定的起始地址算的第几页   0-XXXMenmory_number
					
			switch(i_number)  
					{
					case 1:  Power_level   = 1; IAP_Flash_ProgramHalfWord(i_number,0, Power_level  );                
									 Injector_mode = 1; IAP_Flash_ProgramHalfWord(i_number,1, Injector_mode);   
									 Syringe_type  = 1; IAP_Flash_ProgramHalfWord(i_number,2, Syringe_type );  
									 Flow_rate     = 1; IAP_Flash_ProgramHalfWord(i_number,3, Flow_rate    ); 
									 Total_Shot    = 1; IAP_Flash_ProgramHalfWord(i_number,4, Total_Shot   );  
					break;
					case 2:  Power_level   = 2; IAP_Flash_ProgramHalfWord(i_number,0, Power_level  );                 
									 Injector_mode = 2; IAP_Flash_ProgramHalfWord(i_number,1, Injector_mode);  
									 Syringe_type  = 2; IAP_Flash_ProgramHalfWord(i_number,2, Syringe_type );  
									 Flow_rate     = 2; IAP_Flash_ProgramHalfWord(i_number,3, Flow_rate    ); 
									 Total_Shot    = 1; IAP_Flash_ProgramHalfWord(i_number,4, Total_Shot   ); 
					break;
					case 3:  Power_level   = 3; IAP_Flash_ProgramHalfWord(i_number,0, Power_level  );                 
									 Injector_mode = 3; IAP_Flash_ProgramHalfWord(i_number,1, Injector_mode); 
									 Syringe_type  = 1; IAP_Flash_ProgramHalfWord(i_number,2, Syringe_type );
									 Flow_rate     = 3; IAP_Flash_ProgramHalfWord(i_number,3, Flow_rate    ); 
									 Total_Shot    = 1; IAP_Flash_ProgramHalfWord(i_number,4, Total_Shot   ); 
					break;
					case 4:  Power_level   = 4; IAP_Flash_ProgramHalfWord(i_number,0, Power_level  );               
									 Injector_mode = 4; IAP_Flash_ProgramHalfWord(i_number,1, Injector_mode); 
									 Syringe_type  = 1; IAP_Flash_ProgramHalfWord(i_number,2, Syringe_type );  
									 Flow_rate     = 1; IAP_Flash_ProgramHalfWord(i_number,3, Flow_rate    ); 
									 Total_Shot    = 1; IAP_Flash_ProgramHalfWord(i_number,4, Total_Shot   ); 
					break;
					case 5:  Power_level   = 5; IAP_Flash_ProgramHalfWord(i_number,0, Power_level  );                 
									 Injector_mode = 5; IAP_Flash_ProgramHalfWord(i_number,1, Injector_mode);   
									 Syringe_type  = 1; IAP_Flash_ProgramHalfWord(i_number,2, Syringe_type );  
									 Flow_rate     = 1; IAP_Flash_ProgramHalfWord(i_number,3, Flow_rate    ); 
									 Total_Shot    = 5; IAP_Flash_ProgramHalfWord(i_number,4, Total_Shot   );  
					break;
					case 6:  Power_level   = 6; IAP_Flash_ProgramHalfWord(i_number,0, Power_level  );                 
									 Injector_mode = 1; IAP_Flash_ProgramHalfWord(i_number,1, Injector_mode);  
									 Syringe_type  = 3; IAP_Flash_ProgramHalfWord(i_number,2, Syringe_type ); 
									 Flow_rate     = 1; IAP_Flash_ProgramHalfWord(i_number,3, Flow_rate    );  
									 Total_Shot    = 1; IAP_Flash_ProgramHalfWord(i_number,4, Total_Shot   );  
					break;
					case 7:  Power_level   = 7; IAP_Flash_ProgramHalfWord(i_number,0, Power_level  );                
									 Injector_mode = 2; IAP_Flash_ProgramHalfWord(i_number,1, Injector_mode);  
									 Syringe_type  = 1; IAP_Flash_ProgramHalfWord(i_number,2, Syringe_type );  
									 Flow_rate     = 2; IAP_Flash_ProgramHalfWord(i_number,3, Flow_rate    ); 
									 Total_Shot    = 1; IAP_Flash_ProgramHalfWord(i_number,4, Total_Shot   ); 
					break;
					}
			}

	}
	
	else
	{
		switch(Menmory_number)
				{
				case 1:  Power_level   = IAP_Flash_ReadHalfWord(Menmory_number,0);    //吸力等级
								 Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1);    //注射模式
								 Syringe_type  = IAP_Flash_ReadHalfWord(Menmory_number,2);    //针管规格
								 Flow_rate     = IAP_Flash_ReadHalfWord(Menmory_number,3);    //注射速度
								 Total_Shot    = IAP_Flash_ReadHalfWord(Menmory_number,4);    //注射次数
				break;
				case 2:  Power_level   = IAP_Flash_ReadHalfWord(Menmory_number,0);
								 Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1);
					       Syringe_type  = IAP_Flash_ReadHalfWord(Menmory_number,2);
					       Flow_rate     = IAP_Flash_ReadHalfWord(Menmory_number,3);
								 Total_Shot    = IAP_Flash_ReadHalfWord(Menmory_number,4);
				break;
				case 3:  Power_level   = IAP_Flash_ReadHalfWord(Menmory_number,0);
								 Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1);
								 Syringe_type  = IAP_Flash_ReadHalfWord(Menmory_number,2);
								 Flow_rate     = IAP_Flash_ReadHalfWord(Menmory_number,3);
								 Total_Shot    = IAP_Flash_ReadHalfWord(Menmory_number,4);
				break;
								
				case 4:  Power_level   = IAP_Flash_ReadHalfWord(Menmory_number,0);
								 Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1);
								 Syringe_type  = IAP_Flash_ReadHalfWord(Menmory_number,2);
								 Flow_rate     = IAP_Flash_ReadHalfWord(Menmory_number,3);
								 Total_Shot    = IAP_Flash_ReadHalfWord(Menmory_number,4);
				break;
				case 5:  Power_level   = IAP_Flash_ReadHalfWord(Menmory_number,0);
								 Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1);
								 Syringe_type  = IAP_Flash_ReadHalfWord(Menmory_number,2);
								 Flow_rate     = IAP_Flash_ReadHalfWord(Menmory_number,3);
								 Total_Shot    = IAP_Flash_ReadHalfWord(Menmory_number,4);
				break;
				case 6:  Power_level   = IAP_Flash_ReadHalfWord(Menmory_number,0);
								 Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1);
								 Syringe_type  = IAP_Flash_ReadHalfWord(Menmory_number,2);
								 Flow_rate     = IAP_Flash_ReadHalfWord(Menmory_number,3);
								 Total_Shot    = IAP_Flash_ReadHalfWord(Menmory_number,4);
				break;
				case 7:  Power_level   = IAP_Flash_ReadHalfWord(Menmory_number,0);
								 Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1);
								 Syringe_type  = IAP_Flash_ReadHalfWord(Menmory_number,2);
								 Flow_rate     = IAP_Flash_ReadHalfWord(Menmory_number,3);
								 Total_Shot    = IAP_Flash_ReadHalfWord(Menmory_number,4);
				break;
				}
			
	}
	
	IAP_EraseSector(0); //在设定的起始地址算的第几页   0-XXXMenmory_number
	IAP_Flash_ProgramHalfWord(0,0, EN1_CHN0  ); //默认开机中文
	IAP_Flash_ProgramHalfWord(0,1, Set_Buzzer_off  ); //(u8 page,u8 add8, u16 dat)在第page页，第add8个写半字
	
	
}
/**************************************
*函数名：Display_Init
*函数功能：初始显示
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void Display_Init(void)
{
//	while(usart2_buff[7] != 0x04)      //如果没有达到4号界面
//	{
//		Usart2_Send_array(Cheak_page);   //查询当前界面
//	}
	
	Delay_ms(2000);
	Dgus_82send_data(0x80,Menmory_number);
	
	Refresh_all_data_from_RAM();
	
	
	
	Usart2_Send_array(A0);//开机-同步按压用
	Usart2_Send_array(A1);//开机-同步按压用
	Usart2_Send_array(A2);//开机-同步按压用
	Usart2_Send_array(A3);//开机-同步按压用
	 
	 if(EN1_CHN0==0) //中英文固定的显示内容
		{//中文
			Usart2_Send_array(Z1);
			Usart2_Send_array(Z2);
			Usart2_Send_array(Z3);
			Usart2_Send_array(Z4);
			Usart2_Send_array(Z5);
			Usart2_Send_array(Z6);
			Usart2_Send_array(Z7);
			Usart2_Send_array(Z8);
		}
		else if(EN1_CHN0 == 1)
		{//英文
			Usart2_Send_array(E1);
			Usart2_Send_array(E2);
			Usart2_Send_array(E3);
			Usart2_Send_array(E4);
			Usart2_Send_array(E5);
			Usart2_Send_array(E6);
			Usart2_Send_array(E7);
			Usart2_Send_array(E8);
		}
}




/**************************************
*函数名：Error_check
*函数功能：开机自检
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void Error_check(void)
{
	u32 i=20000;
	Fuya_ON;Motor_RR_F;Motor_Runing=1;
	Delay_ms(100);
	while(i--)
	{
		Adc_Fuya = Get_Adc(9); 
		if(Adc_Fuya == 0)
		{
			Fuya_OFF;Motor_STOP;Valve_ON;Motor_Runing=0;  //异常
			
			Usart2_Send_array(JUMP_TO_10);   //跳到第十页
			if(EN1_CHN0==0) //中英文固定的显示内容
			{//中文
				Dgus_82write_data(0x11,0x00,"开机自检：负压异常！");
				Dgus_82write_data(0x10,0x00," 确认");
			}
			else
			{//英文
				Dgus_82write_data(0x11,0x00,"Check：Abnormal negative pressure!");
				Dgus_82write_data(0x10,0x00,"  OK");
			}
			return;
		}
		if(Motor_speed==0)
		{
			Fuya_OFF;Motor_STOP;Valve_ON;Motor_Runing=0;  //异常
			
			Usart2_Send_array(JUMP_TO_10);   //跳到第十页
			if(EN1_CHN0==0) //中英文固定的显示内容
			{//中文
				Dgus_82write_data(0x11,0x00,"开机自检：电机异常！");
				Dgus_82write_data(0x10,0x00," 确认");
			}
			else
			{//英文
				Dgus_82write_data(0x11,0x00,"Check：Motor is abnormal!");
				Dgus_82write_data(0x10,0x00,"  OK");
			}
			return;
		}
	}
	i=1000000;
	Motor_LL_F;Delay_ms(100);
	while(i--)
	{
		if(Motor_speed==0)
		{
			Fuya_OFF;Motor_STOP;Valve_ON;Motor_Runing=0;  //异常
			
			Usart2_Send_array(JUMP_TO_10);   //跳到第十页
			if(EN1_CHN0==0) //中英文固定的显示内容
			{//中文
				Dgus_82write_data(0x11,0x00,"开机自检：电机异常！");
				Dgus_82write_data(0x10,0x00," 确认");
			}
			else
			{//英文
				Dgus_82write_data(0x11,0x00,"Check：Motor is abnormal!");
				Dgus_82write_data(0x10,0x00,"  OK");
			}
			return;
		}
	}
	Fuya_OFF;Motor_STOP;Valve_ON;Motor_Runing=0;  //异常
	Delay_ms(100);TIM2->CNT = around;
}


/**************************************
*函数名：Key_scanf
*函数功能：按键扫描
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void Key_scanf(void)
{
	//----------------------------语言 取反------------------------------------------------
		if(  ( usart2_buff[7]==0x00 )    &&  (usart2_buff[8]==0x0a) ) //语言 取反
    {
      usart2_buff[5]=0;usart2_buff[8]=0;

	    if(EN1_CHN0==1)
			{
				EN1_CHN0=0;
			}
			else
			{
				EN1_CHN0=1;
			}
			
      
		  Sound_buzzer_du_di();//响“杜嘀”声
      
			IAP_EraseSector(0); //在设定的起始地址算的第几页   0-XXXMenmory_number
			IAP_Flash_ProgramHalfWord(0,0, EN1_CHN0  ); //默认开机中文
			IAP_Flash_ProgramHalfWord(0,1, Set_Buzzer_off  ); //(u8 page,u8 add8, u16 dat)在第page页，第add8个写半字
      
	    if(EN1_CHN0==0) //中英文固定的显示内容
			{//中文
				Usart2_Send_array(Z1);
				Usart2_Send_array(Z2);
				Usart2_Send_array(Z3);
				Usart2_Send_array(Z4);
				Usart2_Send_array(Z5);
				Usart2_Send_array(Z6);
				Usart2_Send_array(Z7);
				Usart2_Send_array(Z8);
			}
			else if(EN1_CHN0 == 1)
			{//英文
				Usart2_Send_array(E1);
				Usart2_Send_array(E2);
				Usart2_Send_array(E3);
				Usart2_Send_array(E4);
				Usart2_Send_array(E5);
				Usart2_Send_array(E6);
				Usart2_Send_array(E7);
				Usart2_Send_array(E8);
			}
        Refresh_all_data_from_RAM();//读取并发送数据到屏幕
    }
		
		//----------------------------蜂鸣器 取反------------------------------------------------
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0x0b))
    {
			usart2_buff[5]=0;usart2_buff[8]=0;

			if(Set_Buzzer_off==1)
			{
				Set_Buzzer_off=0;
			}
			else
			{
				Set_Buzzer_off=1;
			}
			
	  	Dgus_82send_data( 0x70, (1-Set_Buzzer_off) );
      
			IAP_EraseSector(0); //擦除第0页
			IAP_Flash_ProgramHalfWord(0,0, EN1_CHN0  ); 
			IAP_Flash_ProgramHalfWord(0,1, Set_Buzzer_off  ); 
      
		  Sound_buzzer_du_di();//响“杜嘀”声
    }
		
		
		//----------------------------负压泵 取反------------------------------------------------
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0x0D))  //负压泵 取反
    {
      usart2_buff[5]=0;usart2_buff[8]=0;
			
	    if(Suction_Ready==1)
			{
				Suction_Ready=0;
				Fuya_OFF;Valve_ON;
			}
		  
			else
			{//2
				Fuya_ON;Delay_ms(100);
				Suction_Ready=1;
				if(Shot_count == (Total_Shot *10))
				{
					Shot_count = 0;
					disp_Shot_count_and_Total_Shot();
				}
				
			}//2
		 Dgus_82send_data( 0x60, Suction_Ready);
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
			
    }
		//----------------------------压力等级-- ------------------------------------------------
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0x15))   //压力等级--
    {
			
		    if(Power_level>1)
			    Power_level--;
				
				 usart2_buff[5]=0;usart2_buff[8]=0;
				 switch(Power_level)
						 {
								case  1: Dgus_82write_data(0x06,0x50,"1");  break;
								case  2: Dgus_82write_data(0x06,0x50,"2");  break;
								case  3: Dgus_82write_data(0x06,0x50,"3");  break;
								case  4: Dgus_82write_data(0x06,0x50,"4");  break;
								case  5: Dgus_82write_data(0x06,0x50,"5");  break;
								case  6: Dgus_82write_data(0x06,0x50,"6");  break;
								case  7: Dgus_82write_data(0x06,0x50,"7");  break;
								case  8: Dgus_82write_data(0x06,0x50,"8");  break;
								case  9: Dgus_82write_data(0x06,0x50,"9");  break;
								case 10: Dgus_82write_data(0x06,0x50,"10"); break;
						 }
			  Get_fuya_grade_time();
				if(Set_Buzzer_off==0)
				{
					Sound_buzzer_du_di();
				}
		    Delay_ms(300);
    }
    //----------------------------压力等级++------------------------------------------------
    if((usart2_buff[7]==0x00) && (usart2_buff[8]==0x16))   //压力等级++
    {
		    if(Power_level<10)
			    Power_level++;

				 usart2_buff[5]=0;usart2_buff[8]=0;
				 switch(Power_level)  
						 {
								case  1: Dgus_82write_data(0x06,0x50,"1");  break;       
								case  2: Dgus_82write_data(0x06,0x50,"2");  break;       
								case  3: Dgus_82write_data(0x06,0x50,"3");  break;        
								case  4: Dgus_82write_data(0x06,0x50,"4");  break;      
								case  5: Dgus_82write_data(0x06,0x50,"5");  break;        
								case  6: Dgus_82write_data(0x06,0x50,"6");  break;        
								case  7: Dgus_82write_data(0x06,0x50,"7");  break;        
								case  8: Dgus_82write_data(0x06,0x50,"8");  break;        
								case  9: Dgus_82write_data(0x06,0x50,"9");  break;        
								case 10: Dgus_82write_data(0x06,0x50,"10"); break;        
						 }
						 Get_fuya_grade_time();
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
			  Delay_ms(300);
    }
		//------------------------------助推器-前------------------------------------------------
		if(Motor_Run_Flag == 0 && usart2_buff[3]==0xC1)
		{
			Motor_Runing=1;timer1_flag[1] =0;
			Mortor_trend = 0;//反转方向
			
			while(usart2_buff[3] != 0xF0)
			{
				Motor_RR_F;
				
				if(Stuck_in==0)//发生堵转
				{
					Motor_Stuck();
					break;
				}
//				
			}
			
			Motor_Runing=0;usart2_buff[3]=0;
			Motor_STOP;Shot_count=0;disp_Shot_count_and_Total_Shot();
			Delay_ms(100);TIM2->CNT = around;//计数恢复初始值
		}
		
		//------------------------------助推器-后------------------------------------------------
		if(Motor_Run_Flag == 0 && usart2_buff[3]==0xC2)
		{
			Motor_Runing=1;timer1_flag[1] =0;
			Mortor_trend = 1;//正转方向
			
			while(usart2_buff[3] != 0xF0)
			{
				Motor_LL_F;
				
				if(Stuck_in==0)//发生堵转
				{
					Motor_Stuck();
					break;
				}
//				
			}
			Motor_Runing=0;usart2_buff[3]=0;
			Motor_STOP;Shot_count=0;disp_Shot_count_and_Total_Shot();
			Delay_ms(100);TIM2->CNT = around;//计数恢复初始值
		}
		
		
		
	if(Suction_Ready==0)       //只有在负压泵关闭时才能设置参数
	{
		//------------------------------7种方案选择------------------------------------------------
		if(  (usart2_buff[0]==0x5a) &&  (usart2_buff[1]==0xa5) &&  (usart2_buff[2]==0x06) &&  (usart2_buff[3]==0x83) &&  (usart2_buff[5]==0x30 ) )
		{

			if(  ( usart2_buff[7]==0x00 )   &&  (usart2_buff[8]>0)  &&  (usart2_buff[8]<=7) ) 
			{
				Menmory_number=usart2_buff[8];

				usart2_buff[5]=0;usart2_buff[8]=0;
				if(Set_Buzzer_off==0)
				{
					Sound_buzzer_du_di();
				}
				
				Refresh_all_data_from_memory();
				Dgus_82send_data(0x80,Menmory_number);
			}
		}
		
		
		
		
		
		
		
			//----------------------------6号界面 减------------------------------------------------	
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0xF7))  //6号界面 减
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			switch(Sub_menu)
			{
				case 1:if(Sub_menu_data>1){Sub_menu_data--;}else{Sub_menu_data = 5;}
				if(EN1_CHN0==0)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"自动感应");break;
						case 2: Dgus_82write_data(0x09,0x50,"自动单次");break;
						case 3: Dgus_82write_data(0x09,0x50,"单次");break;
						case 4: Dgus_82write_data(0x09,0x50,"持续(常规)");break;
						case 5: Dgus_82write_data(0x09,0x50,"持续(慢)");break;
					}
				}
				else if(EN1_CHN0 == 1)
				{
					switch(Sub_menu_data)
					{
						case  1: Dgus_82write_data(0x09,0x50,"Auto-Sensing");  break;
					  case  2: Dgus_82write_data(0x09,0x50,"Auto Dose");  break;
					  case  3: Dgus_82write_data(0x09,0x50,"Dose");      break;
					  case  4: Dgus_82write_data(0x09,0x50,"Cont.(Normal)");break;
					  case  5: Dgus_82write_data(0x09,0x50,"Cont.(Slow)");  break;
					}
				}
				
				break;
				
				case 2:if(Sub_menu_data>1){Sub_menu_data--;}else{Sub_menu_data = 7;}
				switch(Sub_menu_data)
				{
					case 1: Dgus_82write_data(0x09,0x50,"1 (ml)");break;
					case 2: Dgus_82write_data(0x09,0x50,"1.5 (ml)");break;
					case 3: Dgus_82write_data(0x09,0x50,"2 (ml)");break;
					case 4: Dgus_82write_data(0x09,0x50,"2.5 (ml)");break;
					case 5: Dgus_82write_data(0x09,0x50,"3 (ml)");break;
					case 6: Dgus_82write_data(0x09,0x50,"4 (ml)");break;
					case 7: Dgus_82write_data(0x09,0x50,"5 (ml)");break;
				}
				break;
				
				case 3:if(Sub_menu_data>1){Sub_menu_data--;}else{Sub_menu_data = 3;}
				if(EN1_CHN0==0)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"常规");break;
						case 2: Dgus_82write_data(0x09,0x50,"快速");break;
						case 3: Dgus_82write_data(0x09,0x50,"慢速");break;
					}
				}
				else if(EN1_CHN0 == 1)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"Normal");break;
						case 2: Dgus_82write_data(0x09,0x50,"Fast");break;
						case 3: Dgus_82write_data(0x09,0x50,"Slow");break;
					}
				}
				
				break;
				
				case 4:if(Sub_menu_data<14){Sub_menu_data++;}else{Sub_menu_data = 1;}
				switch(Syringe_type)
				{
					case 1: Syringe_volume = 1000;break;
					case 2: Syringe_volume = 1500;break;
					case 3: Syringe_volume = 2000;break;
					case 4: Syringe_volume = 2500;break;
					case 5: Syringe_volume = 3000;break;
					case 6: Syringe_volume = 4000;break;
					case 7: Syringe_volume = 5000;break;
				}
				Total_Shot =  (15-Sub_menu_data);
				One_Dose = (Syringe_volume/Total_Shot); 
				
				if((Syringe_volume % Total_Shot) > (Total_Shot /2))   //四舍五入
				{
					One_Dose +=1;
				}
				
				disp_One_Dose[2] = ( 0x30+( One_Dose/1000)   );
				disp_One_Dose[3] = ( 0x30+((One_Dose%1000)/100)   );
				disp_One_Dose[4] = ( 0x30+((One_Dose%100 )/10)    );
				disp_One_Dose[5] = ( 0x30+(One_Dose%10) );
				
        Dgus_82write_data(0x09,0x50,disp_One_Dose);
				break;
				
				case 5:if(Sub_menu_data>1){Sub_menu_data--;}else{Sub_menu_data = 14;}
				if(Sub_menu_data>=10)
				{
					disp_Total_Shot_ADJ[0]= ( 0x30+(Sub_menu_data/10));
					disp_Total_Shot_ADJ[1]= ( 0x30+(Sub_menu_data%10));
					disp_Total_Shot_ADJ[2]=  0x30;
        }
				else
				{ 
												disp_Total_Shot_ADJ[0]= ( 0x30+(Sub_menu_data%10));
												disp_Total_Shot_ADJ[1]=  0x30;
												disp_Total_Shot_ADJ[2]= '\0';
				}
					 
				Dgus_82write_data(0x09,0x50,disp_Total_Shot_ADJ);
				break;
				}
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}
		
	 //----------------------------6号界面 加------------------------------------------------	
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0xF8))  //6号界面 加
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			switch(Sub_menu)//根据子菜单+ - 
			{
				case 1:if(Sub_menu_data<5){Sub_menu_data++;}else{Sub_menu_data = 1;}
				if(EN1_CHN0==0)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"自动感应");break;
						case 2: Dgus_82write_data(0x09,0x50,"自动单次");break;
						case 3: Dgus_82write_data(0x09,0x50,"单次");break;
						case 4: Dgus_82write_data(0x09,0x50,"持续(常规)");break;
						case 5: Dgus_82write_data(0x09,0x50,"持续(慢)");break;
					}
				}
				else if(EN1_CHN0 == 1)
				{
					switch(Sub_menu_data)
					{
						case  1: Dgus_82write_data(0x09,0x50,"Auto-Sensing");  break;
					  case  2: Dgus_82write_data(0x09,0x50,"Auto Dose");  break;
					  case  3: Dgus_82write_data(0x09,0x50,"Dose");      break;
					  case  4: Dgus_82write_data(0x09,0x50,"Cont.(Normal)");break;
					  case  5: Dgus_82write_data(0x09,0x50,"Cont.(Slow)");  break;
					}
				}
				break;
				
				case 2:if(Sub_menu_data<7){Sub_menu_data++;}else{Sub_menu_data = 1;}
				switch(Sub_menu_data)
				{
					case 1: Dgus_82write_data(0x09,0x50,"1 (ml)");break;
					case 2: Dgus_82write_data(0x09,0x50,"1.5 (ml)");break;
					case 3: Dgus_82write_data(0x09,0x50,"2 (ml)");break;
					case 4: Dgus_82write_data(0x09,0x50,"2.5 (ml)");break;
					case 5: Dgus_82write_data(0x09,0x50,"3 (ml)");break;
					case 6: Dgus_82write_data(0x09,0x50,"4 (ml)");break;
					case 7: Dgus_82write_data(0x09,0x50,"5 (ml)");break;
				}
				break;
				
				case 3:if(Sub_menu_data<3){Sub_menu_data++;}else{Sub_menu_data = 1;}
				if(EN1_CHN0==0)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"常规");break;
						case 2: Dgus_82write_data(0x09,0x50,"快速");break;
						case 3: Dgus_82write_data(0x09,0x50,"慢速");break;
					}
				}
				else if(EN1_CHN0 == 1)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"Normal");break;
						case 2: Dgus_82write_data(0x09,0x50,"Fast");break;
						case 3: Dgus_82write_data(0x09,0x50,"Slow");break;
					}
				}
				break;
				
				case 4:if(Sub_menu_data>1){Sub_menu_data--;}else{Sub_menu_data = 14;}
				switch(Syringe_type)
				{
					case 1: Syringe_volume = 1000;break;
					case 2: Syringe_volume = 1500;break;
					case 3: Syringe_volume = 2000;break;
					case 4: Syringe_volume = 2500;break;
					case 5: Syringe_volume = 3000;break;
					case 6: Syringe_volume = 4000;break;
					case 7: Syringe_volume = 5000;break;
				}
				Total_Shot =  (15-Sub_menu_data);
				One_Dose = (Syringe_volume/Total_Shot); 
				
				if((Syringe_volume % Total_Shot) > (Total_Shot /2))
				{
					One_Dose +=1;
				}
				
				disp_One_Dose[2] = ( 0x30+( One_Dose/1000)   );
				disp_One_Dose[3] = ( 0x30+((One_Dose%1000)/100)   );
				disp_One_Dose[4] = ( 0x30+((One_Dose%100 )/10)    );
				disp_One_Dose[5] = ( 0x30+(One_Dose%10) );
				
        Dgus_82write_data(0x09,0x50,disp_One_Dose);
				break;
				
				case 5:if(Sub_menu_data<14){Sub_menu_data++;}else{Sub_menu_data = 1;}
				if(Sub_menu_data>=10)
				{
					disp_Total_Shot_ADJ[0]= ( 0x30+(Sub_menu_data/10));
					disp_Total_Shot_ADJ[1]= ( 0x30+(Sub_menu_data%10));
					disp_Total_Shot_ADJ[2]=  0x30;
        }
				else
				{ 
												disp_Total_Shot_ADJ[0]= ( 0x30+(Sub_menu_data%10));
												disp_Total_Shot_ADJ[1]=  0x30;
												disp_Total_Shot_ADJ[2]= '\0';
				}
					 
				Dgus_82write_data(0x09,0x50,disp_Total_Shot_ADJ);
				break;
				}
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}		
		
		//----------------------------注射模式------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x10)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			Sub_menu=1;
      Sub_menu_data=Injector_mode;
			Usart2_Send_array(JUMP_TO_6);   //跳到第六页
			
			if(EN1_CHN0==0)
			{
				Dgus_82write_data(0x09,0x00,"注射模式");
				Dgus_82write_data(0x10,0x00," 确认");
				Dgus_82write_data(0x10,0x50," 取消");
			}
			else if(EN1_CHN0 == 1)
			{
				Dgus_82write_data(0x09,0x00,"Injector");
				Dgus_82write_data(0x10,0x00,"  OK");
				Dgus_82write_data(0x10,0x50," Cancel");
			}
			
			
			if(EN1_CHN0==0)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"自动感应");break;
						case 2: Dgus_82write_data(0x09,0x50,"自动单次");break;
						case 3: Dgus_82write_data(0x09,0x50,"单次");break;
						case 4: Dgus_82write_data(0x09,0x50,"持续(常规)");break;
						case 5: Dgus_82write_data(0x09,0x50,"持续(慢)");break;
					}
				}
				else if(EN1_CHN0 == 1)
				{
					switch(Sub_menu_data)
					{
						case  1: Dgus_82write_data(0x09,0x50,"Auto-Sensing");  break;
					  case  2: Dgus_82write_data(0x09,0x50,"Auto Dose");  break;
					  case  3: Dgus_82write_data(0x09,0x50,"Dose");      break;
					  case  4: Dgus_82write_data(0x09,0x50,"Cont.(Normal)");break;
					  case  5: Dgus_82write_data(0x09,0x50,"Cont.(Slow)");  break;
					}
				}
				if(Set_Buzzer_off==0)
				{
					Sound_buzzer_du_di();
				}
		}
		
		
		//----------------------------注射规格------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x11)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			Sub_menu=2;
      Sub_menu_data=Syringe_type;
			Usart2_Send_array(JUMP_TO_6);   //跳到第六页
			if(EN1_CHN0 == 0)
			{
				Dgus_82write_data(0x09,0x00,"注射规格");
				Dgus_82write_data(0x10,0x00," 确认");
				Dgus_82write_data(0x10,0x50," 取消");
			}
			else
			{
				Dgus_82write_data(0x09,0x00,"Syringe");
				Dgus_82write_data(0x10,0x00,"  OK");
				Dgus_82write_data(0x10,0x50," Cancel");
			}
			
			
			switch(Sub_menu_data)
			{
				case 1: Dgus_82write_data(0x09,0x50,"1 (ml)");break;
				case 2: Dgus_82write_data(0x09,0x50,"1.5 (ml)");break;
				case 3: Dgus_82write_data(0x09,0x50,"2 (ml)");break;
				case 4: Dgus_82write_data(0x09,0x50,"2.5 (ml)");break;
				case 5: Dgus_82write_data(0x09,0x50,"3 (ml)");break;
				case 6: Dgus_82write_data(0x09,0x50,"4 (ml)");break;
				case 7: Dgus_82write_data(0x09,0x50,"5 (ml)");break;
			}
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}
		
		
		//----------------------------注射速度------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x12)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			if((Injector_mode==1) || (Injector_mode==2) || (Injector_mode==3))
			{
				
				Sub_menu=3;
				Sub_menu_data=Flow_rate;
				Usart2_Send_array(JUMP_TO_6);   //跳到第六页
				if(EN1_CHN0 == 0)
				{
					Dgus_82write_data(0x09,0x00,"注射速度");
					Dgus_82write_data(0x10,0x00," 确认");
					Dgus_82write_data(0x10,0x50," 取消");
				}
				else
				{
					Dgus_82write_data(0x09,0x00,"Flow_Rat");
					Dgus_82write_data(0x10,0x00,"  OK");
					Dgus_82write_data(0x10,0x50,"Cancel");
				}
				if(EN1_CHN0 == 0)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"常规");break;
						case 2: Dgus_82write_data(0x09,0x50,"快速");break;
						case 3: Dgus_82write_data(0x09,0x50,"慢速");break;
					}
				}
				else
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"Normal");break;
						case 2: Dgus_82write_data(0x09,0x50,"Fast");break;
						case 3: Dgus_82write_data(0x09,0x50,"Slow");break;
					}
				}
				
			}
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}
		
		//----------------------------单次注射------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x13)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			if((Injector_mode==1) || (Injector_mode==2) || (Injector_mode==3))
			{
				
				Sub_menu=4;
				Sub_menu_data=One_Dose_Grade;
				Usart2_Send_array(JUMP_TO_6);   //跳到第六页
				
				if(EN1_CHN0 == 0)
				{
					Dgus_82write_data(0x09,0x00,"单次注射");
					Dgus_82write_data(0x10,0x00," 确认");
					Dgus_82write_data(0x10,0x50," 取消");
				}
				else
				{
					Dgus_82write_data(0x09,0x00,"One Dose");
					Dgus_82write_data(0x10,0x00,"  OK");
					Dgus_82write_data(0x10,0x50,"Cancel");
				}
				
				
				switch(Syringe_type)
				{
					case 1: Syringe_volume = 1000;break;
					case 2: Syringe_volume = 1500;break;
					case 3: Syringe_volume = 2000;break;
					case 4: Syringe_volume = 2500;break;
					case 5: Syringe_volume = 3000;break;
					case 6: Syringe_volume = 4000;break;
					case 7: Syringe_volume = 5000;break;
				}
				Total_Shot =  (15-Sub_menu_data);
				One_Dose = (Syringe_volume/Total_Shot);
				
				if((Syringe_volume % Total_Shot) > (Total_Shot /2))
				{
					One_Dose +=1;
				}
				
				disp_One_Dose[2] = ( 0x30+( One_Dose/1000)   );
				disp_One_Dose[3] = ( 0x30+((One_Dose%1000)/100)   );
				disp_One_Dose[4] = ( 0x30+((One_Dose%100 )/10)    );
				disp_One_Dose[5] = ( 0x30+(One_Dose%10) );
				
        Dgus_82write_data(0x09,0x50,disp_One_Dose);
	  	}
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}
		
		//----------------------------注射次数------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x14)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			if((Injector_mode==1) || (Injector_mode==2) || (Injector_mode==3))
			{
				
				Sub_menu=5;
				Sub_menu_data=Total_Shot;
				Usart2_Send_array(JUMP_TO_6);   //跳到第六页
				
				if(EN1_CHN0==0)
				{
					Dgus_82write_data(0x09,0x00,"注射次数");
					Dgus_82write_data(0x10,0x00," 确认");
					Dgus_82write_data(0x10,0x50," 取消");
				}
				else if(EN1_CHN0 == 1)
				{
					Dgus_82write_data(0x09,0x00,"Total Sh");
					Dgus_82write_data(0x10,0x00,"  OK");
					Dgus_82write_data(0x10,0x50,"Cancel");
				}
				
				if(Sub_menu_data>=10)
				{
					disp_Total_Shot_ADJ[0]= ( 0x30+(Sub_menu_data/10));     
					disp_Total_Shot_ADJ[1]= ( 0x30+(Sub_menu_data%10)); 
					disp_Total_Shot_ADJ[2]=  0x30;
        }
				else
				{ 
					disp_Total_Shot_ADJ[0]= ( 0x30+(Sub_menu_data%10)); 
					disp_Total_Shot_ADJ[1]=  0x30; 
					disp_Total_Shot_ADJ[2]= '\0';
				}
					 
				Dgus_82write_data(0x09,0x50,disp_Total_Shot_ADJ);
	  	}
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}
		
	  //----------------------------参数确认------------------------------------------------	
		if((usart2_buff[7]==0x0D) && (usart2_buff[8]==0x0D) && (Sub_menu<6) )
    { 
			
      usart2_buff[5]=0;usart2_buff[8]=0;
		  
        if(Sub_menu==1)
        {//1
            Injector_mode=Sub_menu_data;
            Shot_count=0;
            Refresh_all_data_from_RAM();
        }//1
        if(Sub_menu==2)
        {//2
            Syringe_type=Sub_menu_data;
            Shot_count=0;
            Refresh_all_data_from_RAM();
        }//2
        if(Sub_menu==3)
        {//3
            Flow_rate=Sub_menu_data;
            Refresh_all_data_from_RAM();
        }//3
        if(Sub_menu==4)
        {//4
            One_Dose_Grade=Sub_menu_data;
            Total_Shot=(15-One_Dose_Grade);
            Shot_count=0; 
            Refresh_all_data_from_RAM();  
        }//4
        if(Sub_menu==5)
        {//5
            Total_Shot=Sub_menu_data;
            One_Dose_Grade=(15-Total_Shot);
            Shot_count=0; 
            Refresh_all_data_from_RAM();  
        }//5      
      if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}				
    } 
		
		
		
		
		//----------------------------覆盖方案------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x0C)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			Sub_menu=8;
			Usart2_Send_array(JUMP_TO_8);   //跳到第八页
			
			if(EN1_CHN0==0)
			{
				Dgus_82write_data(0x08,0x00,"确定覆盖保存该方案吗？");
				Dgus_82write_data(0x10,0x00," 确认");
				Dgus_82write_data(0x10,0x50," 取消");
			}
			else if(EN1_CHN0 == 1)
			{
				Dgus_82write_data(0x08,0x00,"Are you sure to save it?");
				Dgus_82write_data(0x10,0x00," OK");
				Dgus_82write_data(0x10,0x50,"Cancel");
			}
			if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}
		
		//----------------------------确定覆盖方案------------------------------------------------	
		
		if(usart2_buff[7] == 0x0D && usart2_buff[8] == 0x0D && Sub_menu==8)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			IAP_EraseSector(Menmory_number);
		  IAP_Flash_ProgramHalfWord(Menmory_number,0, Power_level  );    //吸力等级
			IAP_Flash_ProgramHalfWord(Menmory_number,1, Injector_mode);    //注射模式
		  IAP_Flash_ProgramHalfWord(Menmory_number,2, Syringe_type );    //注射规格
		  IAP_Flash_ProgramHalfWord(Menmory_number,3, Flow_rate    );    //注射速度
		  IAP_Flash_ProgramHalfWord(Menmory_number,4, Total_Shot   );    //异常？？？
      if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}
	}
	 
}
	
	
	
	
	
	
	
	
	

