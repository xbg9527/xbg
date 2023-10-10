#include "main.h"                  // Device header


/**************************************
*��������Open_Init
*�������ܣ���������
*������������
*��������ֵ����
*����������
**************************************/
	u8 Menmory_number= 1;
	u8 Menmory_First;
	u8 EN1_CHN0 = 0;      //��Ӣ��ģʽ
	u8 Set_Buzzer_off;    //��������
	u8 Injector_mode =0;  //ע��ģʽ
	u8 Syringe_type=0;       //ע������-�����ͺŴ�С
	u8 Flow_rate =0;       //ע���ٶ�
	u8 Power_level =0;     //��ѹ�ȼ�
	u8 Suction_Ready=0;    //��ѹ״̬
	u8 Sub_menu=0;         //�Ӳ˵�
	u8 Sub_menu_data =0;   //�Ӳ˵�-��֧��
	u32 Syringe_volume=0;     //ע���ݻ�
	u8 Total_Shot=0;         //ע���ܴ���
	u8 Shot_count=0;         //��ǰע�����
	u16 One_Dose=0;           //����ע����
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
		//��������
	Menmory_number =1;
	
	
	Menmory_First =   IAP_Flash_ReadHalfWord(10,0); //������pageҳ����add8������  0-xxx
	//-----------------------------------------��һ���ϵ磬��ʹ���洢��5�����-----------------------------------------------
	if( Menmory_First != 10 )
	{
		IAP_EraseSector(10); //������10ҳ,������������д�롣
		IAP_Flash_ProgramHalfWord(10,0,10);//����ʮҳ�ĵ�0������д��10
		
		
			IAP_EraseSector(0); //���趨����ʼ��ַ��ĵڼ�ҳ   0-XXXMenmory_number
			
			for(u8 i_number=1; i_number<8; i_number++)
			{
					IAP_EraseSector(i_number); //�������趨����ʼ��ַ��ĵڼ�ҳ   0-XXXMenmory_number
					
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
				case 1:  Power_level   = IAP_Flash_ReadHalfWord(Menmory_number,0);    //�����ȼ�
								 Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1);    //ע��ģʽ
								 Syringe_type  = IAP_Flash_ReadHalfWord(Menmory_number,2);    //��ܹ��
								 Flow_rate     = IAP_Flash_ReadHalfWord(Menmory_number,3);    //ע���ٶ�
								 Total_Shot    = IAP_Flash_ReadHalfWord(Menmory_number,4);    //ע�����
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
	
	IAP_EraseSector(0); //���趨����ʼ��ַ��ĵڼ�ҳ   0-XXXMenmory_number
	IAP_Flash_ProgramHalfWord(0,0, EN1_CHN0  ); //Ĭ�Ͽ�������
	IAP_Flash_ProgramHalfWord(0,1, Set_Buzzer_off  ); //(u8 page,u8 add8, u16 dat)�ڵ�pageҳ����add8��д����
	
	
}
/**************************************
*��������Display_Init
*�������ܣ���ʼ��ʾ
*������������
*��������ֵ����
*����������
**************************************/
void Display_Init(void)
{
//	while(usart2_buff[7] != 0x04)      //���û�дﵽ4�Ž���
//	{
//		Usart2_Send_array(Cheak_page);   //��ѯ��ǰ����
//	}
	
	Delay_ms(2000);
	Dgus_82send_data(0x80,Menmory_number);
	
	Refresh_all_data_from_RAM();
	
	
	
	Usart2_Send_array(A0);//����-ͬ����ѹ��
	Usart2_Send_array(A1);//����-ͬ����ѹ��
	Usart2_Send_array(A2);//����-ͬ����ѹ��
	Usart2_Send_array(A3);//����-ͬ����ѹ��
	 
	 if(EN1_CHN0==0) //��Ӣ�Ĺ̶�����ʾ����
		{//����
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
		{//Ӣ��
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
*��������Error_check
*�������ܣ������Լ�
*������������
*��������ֵ����
*����������
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
			Fuya_OFF;Motor_STOP;Valve_ON;Motor_Runing=0;  //�쳣
			
			Usart2_Send_array(JUMP_TO_10);   //������ʮҳ
			if(EN1_CHN0==0) //��Ӣ�Ĺ̶�����ʾ����
			{//����
				Dgus_82write_data(0x11,0x00,"�����Լ죺��ѹ�쳣��");
				Dgus_82write_data(0x10,0x00," ȷ��");
			}
			else
			{//Ӣ��
				Dgus_82write_data(0x11,0x00,"Check��Abnormal negative pressure!");
				Dgus_82write_data(0x10,0x00,"  OK");
			}
			return;
		}
		if(Motor_speed==0)
		{
			Fuya_OFF;Motor_STOP;Valve_ON;Motor_Runing=0;  //�쳣
			
			Usart2_Send_array(JUMP_TO_10);   //������ʮҳ
			if(EN1_CHN0==0) //��Ӣ�Ĺ̶�����ʾ����
			{//����
				Dgus_82write_data(0x11,0x00,"�����Լ죺����쳣��");
				Dgus_82write_data(0x10,0x00," ȷ��");
			}
			else
			{//Ӣ��
				Dgus_82write_data(0x11,0x00,"Check��Motor is abnormal!");
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
			Fuya_OFF;Motor_STOP;Valve_ON;Motor_Runing=0;  //�쳣
			
			Usart2_Send_array(JUMP_TO_10);   //������ʮҳ
			if(EN1_CHN0==0) //��Ӣ�Ĺ̶�����ʾ����
			{//����
				Dgus_82write_data(0x11,0x00,"�����Լ죺����쳣��");
				Dgus_82write_data(0x10,0x00," ȷ��");
			}
			else
			{//Ӣ��
				Dgus_82write_data(0x11,0x00,"Check��Motor is abnormal!");
				Dgus_82write_data(0x10,0x00,"  OK");
			}
			return;
		}
	}
	Fuya_OFF;Motor_STOP;Valve_ON;Motor_Runing=0;  //�쳣
	Delay_ms(100);TIM2->CNT = around;
}


/**************************************
*��������Key_scanf
*�������ܣ�����ɨ��
*������������
*��������ֵ����
*����������
**************************************/
void Key_scanf(void)
{
	//----------------------------���� ȡ��------------------------------------------------
		if(  ( usart2_buff[7]==0x00 )    &&  (usart2_buff[8]==0x0a) ) //���� ȡ��
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
			
      
		  Sound_buzzer_du_di();//�조���֡���
      
			IAP_EraseSector(0); //���趨����ʼ��ַ��ĵڼ�ҳ   0-XXXMenmory_number
			IAP_Flash_ProgramHalfWord(0,0, EN1_CHN0  ); //Ĭ�Ͽ�������
			IAP_Flash_ProgramHalfWord(0,1, Set_Buzzer_off  ); //(u8 page,u8 add8, u16 dat)�ڵ�pageҳ����add8��д����
      
	    if(EN1_CHN0==0) //��Ӣ�Ĺ̶�����ʾ����
			{//����
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
			{//Ӣ��
				Usart2_Send_array(E1);
				Usart2_Send_array(E2);
				Usart2_Send_array(E3);
				Usart2_Send_array(E4);
				Usart2_Send_array(E5);
				Usart2_Send_array(E6);
				Usart2_Send_array(E7);
				Usart2_Send_array(E8);
			}
        Refresh_all_data_from_RAM();//��ȡ���������ݵ���Ļ
    }
		
		//----------------------------������ ȡ��------------------------------------------------
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
      
			IAP_EraseSector(0); //������0ҳ
			IAP_Flash_ProgramHalfWord(0,0, EN1_CHN0  ); 
			IAP_Flash_ProgramHalfWord(0,1, Set_Buzzer_off  ); 
      
		  Sound_buzzer_du_di();//�조���֡���
    }
		
		
		//----------------------------��ѹ�� ȡ��------------------------------------------------
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0x0D))  //��ѹ�� ȡ��
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
		//----------------------------ѹ���ȼ�-- ------------------------------------------------
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0x15))   //ѹ���ȼ�--
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
    //----------------------------ѹ���ȼ�++------------------------------------------------
    if((usart2_buff[7]==0x00) && (usart2_buff[8]==0x16))   //ѹ���ȼ�++
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
		//------------------------------������-ǰ------------------------------------------------
		if(Motor_Run_Flag == 0 && usart2_buff[3]==0xC1)
		{
			Motor_Runing=1;timer1_flag[1] =0;
			Mortor_trend = 0;//��ת����
			
			while(usart2_buff[3] != 0xF0)
			{
				Motor_RR_F;
				
				if(Stuck_in==0)//������ת
				{
					Motor_Stuck();
					break;
				}
//				
			}
			
			Motor_Runing=0;usart2_buff[3]=0;
			Motor_STOP;Shot_count=0;disp_Shot_count_and_Total_Shot();
			Delay_ms(100);TIM2->CNT = around;//�����ָ���ʼֵ
		}
		
		//------------------------------������-��------------------------------------------------
		if(Motor_Run_Flag == 0 && usart2_buff[3]==0xC2)
		{
			Motor_Runing=1;timer1_flag[1] =0;
			Mortor_trend = 1;//��ת����
			
			while(usart2_buff[3] != 0xF0)
			{
				Motor_LL_F;
				
				if(Stuck_in==0)//������ת
				{
					Motor_Stuck();
					break;
				}
//				
			}
			Motor_Runing=0;usart2_buff[3]=0;
			Motor_STOP;Shot_count=0;disp_Shot_count_and_Total_Shot();
			Delay_ms(100);TIM2->CNT = around;//�����ָ���ʼֵ
		}
		
		
		
	if(Suction_Ready==0)       //ֻ���ڸ�ѹ�ùر�ʱ�������ò���
	{
		//------------------------------7�ַ���ѡ��------------------------------------------------
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
		
		
		
		
		
		
		
			//----------------------------6�Ž��� ��------------------------------------------------	
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0xF7))  //6�Ž��� ��
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			switch(Sub_menu)
			{
				case 1:if(Sub_menu_data>1){Sub_menu_data--;}else{Sub_menu_data = 5;}
				if(EN1_CHN0==0)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"�Զ���Ӧ");break;
						case 2: Dgus_82write_data(0x09,0x50,"�Զ�����");break;
						case 3: Dgus_82write_data(0x09,0x50,"����");break;
						case 4: Dgus_82write_data(0x09,0x50,"����(����)");break;
						case 5: Dgus_82write_data(0x09,0x50,"����(��)");break;
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
						case 1: Dgus_82write_data(0x09,0x50,"����");break;
						case 2: Dgus_82write_data(0x09,0x50,"����");break;
						case 3: Dgus_82write_data(0x09,0x50,"����");break;
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
				
				if((Syringe_volume % Total_Shot) > (Total_Shot /2))   //��������
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
		
	 //----------------------------6�Ž��� ��------------------------------------------------	
		if((usart2_buff[7]==0x00) && (usart2_buff[8]==0xF8))  //6�Ž��� ��
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			switch(Sub_menu)//�����Ӳ˵�+ - 
			{
				case 1:if(Sub_menu_data<5){Sub_menu_data++;}else{Sub_menu_data = 1;}
				if(EN1_CHN0==0)
				{
					switch(Sub_menu_data)
					{
						case 1: Dgus_82write_data(0x09,0x50,"�Զ���Ӧ");break;
						case 2: Dgus_82write_data(0x09,0x50,"�Զ�����");break;
						case 3: Dgus_82write_data(0x09,0x50,"����");break;
						case 4: Dgus_82write_data(0x09,0x50,"����(����)");break;
						case 5: Dgus_82write_data(0x09,0x50,"����(��)");break;
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
						case 1: Dgus_82write_data(0x09,0x50,"����");break;
						case 2: Dgus_82write_data(0x09,0x50,"����");break;
						case 3: Dgus_82write_data(0x09,0x50,"����");break;
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
		
		//----------------------------ע��ģʽ------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x10)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			Sub_menu=1;
      Sub_menu_data=Injector_mode;
			Usart2_Send_array(JUMP_TO_6);   //��������ҳ
			
			if(EN1_CHN0==0)
			{
				Dgus_82write_data(0x09,0x00,"ע��ģʽ");
				Dgus_82write_data(0x10,0x00," ȷ��");
				Dgus_82write_data(0x10,0x50," ȡ��");
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
						case 1: Dgus_82write_data(0x09,0x50,"�Զ���Ӧ");break;
						case 2: Dgus_82write_data(0x09,0x50,"�Զ�����");break;
						case 3: Dgus_82write_data(0x09,0x50,"����");break;
						case 4: Dgus_82write_data(0x09,0x50,"����(����)");break;
						case 5: Dgus_82write_data(0x09,0x50,"����(��)");break;
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
		
		
		//----------------------------ע����------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x11)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			Sub_menu=2;
      Sub_menu_data=Syringe_type;
			Usart2_Send_array(JUMP_TO_6);   //��������ҳ
			if(EN1_CHN0 == 0)
			{
				Dgus_82write_data(0x09,0x00,"ע����");
				Dgus_82write_data(0x10,0x00," ȷ��");
				Dgus_82write_data(0x10,0x50," ȡ��");
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
		
		
		//----------------------------ע���ٶ�------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x12)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			if((Injector_mode==1) || (Injector_mode==2) || (Injector_mode==3))
			{
				
				Sub_menu=3;
				Sub_menu_data=Flow_rate;
				Usart2_Send_array(JUMP_TO_6);   //��������ҳ
				if(EN1_CHN0 == 0)
				{
					Dgus_82write_data(0x09,0x00,"ע���ٶ�");
					Dgus_82write_data(0x10,0x00," ȷ��");
					Dgus_82write_data(0x10,0x50," ȡ��");
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
						case 1: Dgus_82write_data(0x09,0x50,"����");break;
						case 2: Dgus_82write_data(0x09,0x50,"����");break;
						case 3: Dgus_82write_data(0x09,0x50,"����");break;
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
		
		//----------------------------����ע��------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x13)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			if((Injector_mode==1) || (Injector_mode==2) || (Injector_mode==3))
			{
				
				Sub_menu=4;
				Sub_menu_data=One_Dose_Grade;
				Usart2_Send_array(JUMP_TO_6);   //��������ҳ
				
				if(EN1_CHN0 == 0)
				{
					Dgus_82write_data(0x09,0x00,"����ע��");
					Dgus_82write_data(0x10,0x00," ȷ��");
					Dgus_82write_data(0x10,0x50," ȡ��");
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
		
		//----------------------------ע�����------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x14)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			if((Injector_mode==1) || (Injector_mode==2) || (Injector_mode==3))
			{
				
				Sub_menu=5;
				Sub_menu_data=Total_Shot;
				Usart2_Send_array(JUMP_TO_6);   //��������ҳ
				
				if(EN1_CHN0==0)
				{
					Dgus_82write_data(0x09,0x00,"ע�����");
					Dgus_82write_data(0x10,0x00," ȷ��");
					Dgus_82write_data(0x10,0x50," ȡ��");
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
		
	  //----------------------------����ȷ��------------------------------------------------	
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
		
		
		
		
		//----------------------------���Ƿ���------------------------------------------------	
		
		if(usart2_buff[7] == 0x00 && usart2_buff[8] == 0x0C)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			Sub_menu=8;
			Usart2_Send_array(JUMP_TO_8);   //�����ڰ�ҳ
			
			if(EN1_CHN0==0)
			{
				Dgus_82write_data(0x08,0x00,"ȷ�����Ǳ���÷�����");
				Dgus_82write_data(0x10,0x00," ȷ��");
				Dgus_82write_data(0x10,0x50," ȡ��");
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
		
		//----------------------------ȷ�����Ƿ���------------------------------------------------	
		
		if(usart2_buff[7] == 0x0D && usart2_buff[8] == 0x0D && Sub_menu==8)
		{
			
			usart2_buff[5]=0;usart2_buff[8]=0;
			
			IAP_EraseSector(Menmory_number);
		  IAP_Flash_ProgramHalfWord(Menmory_number,0, Power_level  );    //�����ȼ�
			IAP_Flash_ProgramHalfWord(Menmory_number,1, Injector_mode);    //ע��ģʽ
		  IAP_Flash_ProgramHalfWord(Menmory_number,2, Syringe_type );    //ע����
		  IAP_Flash_ProgramHalfWord(Menmory_number,3, Flow_rate    );    //ע���ٶ�
		  IAP_Flash_ProgramHalfWord(Menmory_number,4, Total_Shot   );    //�쳣������
      if(Set_Buzzer_off==0)
			{
				Sound_buzzer_du_di();
			}
		}
	}
	 
}
	
	
	
	
	
	
	
	
	

