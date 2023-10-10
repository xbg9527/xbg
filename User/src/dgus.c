#include "main.h"

/***********************************************
*������    :Dgus_82send_data
*��������  :������-������ʾ�������
*��������  :u8 addr_L      ��λ��ַ
					  u8 addr_Data   Ҫд�������
*��������ֵ:��
*��������  :
************************************************/
void Dgus_82send_data(u8 addr_L,u8 addr_Data)
{
	
	//��������
	Usart2_Send_Byte(0x5a);
	Usart2_Send_Byte(0xa5);
	
	Usart2_Send_Byte(0x07);
	Usart2_Send_Byte(0x82);
	
	Usart2_Send_Byte(0x00);
	Usart2_Send_Byte(addr_L);
	Usart2_Send_Byte(0x00);
	Usart2_Send_Byte(addr_Data);
	
	Usart2_Send_Byte(0xff);
	Usart2_Send_Byte(0xff);
	
}


/***********************************************
*������    :Dgus_82write_data
*��������  :������дָ���
*��������  :u8 addr_H      ��λ��ַ
            u8 addr_L      ��λ��ַ
						u8 *str        Ҫд�������
*��������ֵ:��
*��������  :
************************************************/
void Dgus_82write_data(u8 addr_H,u8 addr_L,u8 *str)
{
	u8 i=0;
	u8 data_cont=0;
	
	while(str[i] != '\0')
	{
		i++;
		data_cont++;
	}
	i=0;
	data_cont +=5;
	
	//��������
	Usart2_Send_Byte(0x5a);
	Usart2_Send_Byte(0xa5);
	Usart2_Send_Byte(data_cont);
	Usart2_Send_Byte(0x82);
	Usart2_Send_Byte(addr_H);
	Usart2_Send_Byte(addr_L);
	Usart2_Send_Str(str);
	Usart2_Send_Byte(0xff);
	Usart2_Send_Byte(0xff);
	
	
}


/***********************************************
*������    :Dgus_83read_data
*��������  :��������ָ���
*��������  :��
*��������ֵ:��
*��������  :
************************************************/
void Dgus_83read_data(u8 addr_H,u8 addr_L,u8 len)
{
	Usart2_Send_Byte(0x5a);
	Usart2_Send_Byte(0xa5);
	Usart2_Send_Byte(0x04);
	Usart2_Send_Byte(0x83);
	Usart2_Send_Byte(addr_H);
	Usart2_Send_Byte(addr_L);
	Usart2_Send_Byte(len);
	
}

/***********************************************
*������    :Clear_array
*��������  :��������
*��������  :u8 *str
*��������ֵ:��
*��������  :
************************************************/
void Clear_array(u8 *str)
{
	u8 i=0;
	while(str[i] != '\0')
	{
		str[i] =0;
		i++;
	}
}








/***********************************************
*������    :Change
*��������  :ʮ����תʮ������
*��������  :u16 n
*��������ֵ:u8*
*��������  :
************************************************/

u8* Change(u16 n)
{
	static u8 a[50]={0};
	u8 i=0;
	
	while(n)
	{
		switch(n%16)
		{
			case 0:  a[i++]='0'; break;
			case 1:  a[i++]='1'; break;
			case 2:  a[i++]='2'; break;
			case 3:  a[i++]='3'; break;
			case 4:  a[i++]='4'; break;
			case 5:  a[i++]='5'; break;
			case 6:  a[i++]='6'; break;
			case 7:  a[i++]='7'; break;
			case 8:  a[i++]='8'; break;
			case 9:  a[i++]='9'; break;
			case 10: a[i++]='A'; break;
			case 11: a[i++]='B'; break;
			case 12: a[i++]='C'; break;
			case 13: a[i++]='D'; break;
			case 14: a[i++]='E'; break;
			case 15: a[i++]='F'; break;
		}
		n=n/16;
	}
	return a;
}














/***********************************************
*������    :IAP_EraseSector
*��������  :������ʼ��ַ+1024*pageҳ
*��������  :u8 page
*��������ֵ:��
*��������  :
************************************************/
void IAP_EraseSector(u8 page) //���趨����ʼ��ַ��ĵڼ�ҳ   0-XXX
{
    //�ڳ�ʹ��ʱ�Ӵ��� FLASH_SetLatency(FLASH_Latency_2);  // ��Ϊϵͳʱ��Ϊ72M����Ҫ��������ʱ�����ڵ���ʱ
    __ASM volatile ("cpsid i");  //���ж� 
    FLASH_Unlock(); 
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR | FLASH_FLAG_EOP);

    // д��ҳ֮ǰҪ������ҳ,���ж��Ƿ�����ɹ�
    while(FLASH_ErasePage((STARTADDR+1024*page)) != FLASH_COMPLETE);
    FLASH_Lock();
    __ASM volatile ("cpsie i"); //���ж�
}


/***********************************************
*������    :IAP_Flash_ProgramHalfWord
*��������  :��ָ����ʼ��ַ+1024*pageҳ�ĵ�2*add8�����ִ���д������dat��
*��������  :u8 page,u8 add8, u16 dat
*��������ֵ:��
*��������  :
************************************************/
void IAP_Flash_ProgramHalfWord(u8 page,u8 add8, u16 dat) //�ڵ�pageҳ����add8��д���� 
{
    
    __ASM volatile ("cpsid i");  //���ж� 
    FLASH_Unlock(); 
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR | FLASH_FLAG_EOP);

    while(FLASH_ProgramHalfWord( (STARTADDR + 1024*page + 2*add8) , dat) != FLASH_COMPLETE );
    FLASH_Lock();
    __ASM volatile ("cpsie i"); //���ж�
}

/***********************************************
*������    :IAP_Flash_ReadHalfWord
*��������  :������pageҳ����add8������  0-xxx
*��������  :u8 page,u8 add8
*��������ֵ:u16
*��������  :
************************************************/
u16 IAP_Flash_ReadHalfWord(u8 page,u8 add8) 
{
      uint32_t faddr=( (STARTADDR + 1024*page + 2*add8) );
	  return *(uint16_t*)faddr; 
}




/***********************************************
*������    :disp_Shot_count_and_Total_Shot
*��������  :��ʾ��ǰע�����/�ܴ���
*��������  :��
*��������ֵ:��
*��������  :
************************************************/
void disp_Shot_count_and_Total_Shot(void)
{
      disp_Shot_count_Total_Shot_Team_selection=0;
    
			if(Shot_count>=100)
			{
				disp_Shot_count_Total_Shot_Team_selection|=0x80;
			}
			else
			{
				if(Shot_count>=10)
				{
					disp_Shot_count_Total_Shot_Team_selection|=0x40;
				}
			}
            /////////////////////////////////////////////////////////////////////////////////
			if(Total_Shot>=10)
			{
				disp_Shot_count_Total_Shot_Team_selection|=0x08;
			}

			 unsigned char disp_Shot_count_Total_Shot[] =  {"000/000"}; 
			 switch(disp_Shot_count_Total_Shot_Team_selection)
			 {
						case 0x88://��ǰע�����>=100 �� ע���ܴ���>=100
										disp_Shot_count_Total_Shot[0]= ( 0x30+(Shot_count/100));
										disp_Shot_count_Total_Shot[1]=( 0x30+((Shot_count%100)/10));
										disp_Shot_count_Total_Shot[2]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[3]='/';
										disp_Shot_count_Total_Shot[4]= ( 0x30+(Total_Shot/10));
										disp_Shot_count_Total_Shot[5]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[6]=  0x30;
						break;
						case 0x48://10<=��ǰע�����<100  �� ע���ܴ���>=100
										disp_Shot_count_Total_Shot[0]=( 0x30+((Shot_count%100)/10));
										disp_Shot_count_Total_Shot[1]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[2]='/';
										disp_Shot_count_Total_Shot[3]= ( 0x30+(Total_Shot/10));
										disp_Shot_count_Total_Shot[4]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[5]=  0x30;
										disp_Shot_count_Total_Shot[6]= '\0';
						break;
						case 0x08://��ǰע�����<10   ��   ע���ܴ���>=100
										disp_Shot_count_Total_Shot[0]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[1]='/';
										disp_Shot_count_Total_Shot[2]= ( 0x30+(Total_Shot/10));
										disp_Shot_count_Total_Shot[3]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[4]=  0x30;
										disp_Shot_count_Total_Shot[5]= '\0';
						break;
						case 0x40://10<=��ǰע�����<100  �� ע���ܴ���<100
										disp_Shot_count_Total_Shot[0]=( 0x30+((Shot_count%100)/10));
										disp_Shot_count_Total_Shot[1]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[2]='/';
										disp_Shot_count_Total_Shot[3]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[4]=  0x30;
										disp_Shot_count_Total_Shot[5]= '\0';
						break;
						case 0x00://��ǰע�����<10  �� ע���ܴ���<100
										disp_Shot_count_Total_Shot[0]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[1]='/';
										disp_Shot_count_Total_Shot[2]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[3]=  0x30;
										disp_Shot_count_Total_Shot[4]= '\0';
						break;
			 }
			 
		 Dgus_82write_data(0x05,0x50,disp_Shot_count_Total_Shot);//�������� �� 16λ��ַ�Ĵ���
}












/***********************************************
*������    :display___One_Dose_Grade_Flow_Rate_Total_Shot
*��������  :��ʾ����ע�������ٶȡ��ܴ�
*��������  :��
*��������ֵ:��
*��������  :
************************************************/
void display___One_Dose_Grade_Flow_Rate_Total_Shot(void) 
{//3
	
  if( (Injector_mode==1)  || (Injector_mode==2)  || (Injector_mode==3)  )  
	{
		 switch(Syringe_type)
		 {
			 case 1:Syringe_volume = 1000;
			 break;
			 case 2:Syringe_volume = 1500;
			 break;
			 case 3:Syringe_volume = 2000;
			 break;
			 case 4:Syringe_volume = 2500;
			 break;
			 case 5:Syringe_volume = 3000;
			 break;
			 case 6:Syringe_volume = 4000;
			 break;
			 case 7:Syringe_volume = 5000;
			 break;
		 }

			One_Dose = (Syringe_volume/Total_Shot); 
			if((Syringe_volume%Total_Shot) > (Total_Shot/2)) 
			{  One_Dose = (One_Dose+1);  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
				 //  unsigned char disp_One_Dose[] =  {"0.0000 (ml)"}; 
						 
					disp_One_Dose[2] = ( 0x30+( One_Dose/1000)   );        // ����One_Dose���ݵ���Ļ  
					disp_One_Dose[3] = ( 0x30+((One_Dose%1000)/100)   );   // ����One_Dose���ݵ���Ļ  
					disp_One_Dose[4] = ( 0x30+((One_Dose%100 )/10)    );   // ����One_Dose���ݵ���Ļ  
					disp_One_Dose[5] = ( 0x30+(One_Dose%10) );            // ����One_Dose���ݵ���Ļ

					Dgus_82write_data(0x04,0x50,disp_One_Dose); //�������� �� 16λ��ַ�Ĵ���   
			 if(EN1_CHN0==0)
			 {//����
				 switch(Flow_rate)  
				 {
					case  1: Dgus_82write_data(0x03,0x50,"����");  break;//�������� �� 16λ��ַ�Ĵ���        
					case  2: Dgus_82write_data(0x03,0x50,"����");  break;//�������� �� 16λ��ַ�Ĵ���        
					case  3: Dgus_82write_data(0x03,0x50,"����");  break;//�������� �� 16λ��ַ�Ĵ���        
				 }
			 }
			 else if(EN1_CHN0==1)
			 {//Ӣ��
				 switch(Flow_rate)  
				 {
					case  1: Dgus_82write_data(0x03,0x50,"Normal");  break;//�������� �� 16λ��ַ�Ĵ���        
					case  2: Dgus_82write_data(0x03,0x50,"Fast");  break;//�������� �� 16λ��ַ�Ĵ���        
					case  3: Dgus_82write_data(0x03,0x50,"Slow");  break;//�������� �� 16λ��ַ�Ĵ���        
				 }
			 }
				 
	
		//Shot_count=0;
					disp_Shot_count_and_Total_Shot();     
		}
	else
	{
		 Dgus_82write_data(0x03,0x50,"---"); //�������� �� 16λ��ַ�Ĵ��� // (0x0a)0����ʾ ���� Flow_Rate��ʾ��---��
		 Dgus_82write_data(0x04,0x50,"---"); //�������� �� 16λ��ַ�Ĵ��� // (0x0a)0����ʾ ���� One_Dose��ʾ��---��
		 Dgus_82write_data(0x05,0x50,"--/--"); //�������� �� 16λ��ַ�Ĵ��� // (0x0a)0����ʾ ���� ʱ��ʾ��---��
	}
 }//3



/***********************************************
*������    :Refresh_all_data_from_RAM
*��������  :������ʾ
*��������  :��
*��������ֵ:��
*��������  :
************************************************/
void Refresh_all_data_from_RAM(void)
{
	Dgus_82send_data( 0x50,  EN1_CHN0 );
	Dgus_82send_data( 0x70, (1-Set_Buzzer_off) );
	
	if(Power_level>10)Power_level =10;
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

	if(Syringe_type> 7) Syringe_type= 1;
	switch(Syringe_type)  
  {
		case  1: Dgus_82write_data(0x02,0x50,"1 (ml)");  Specs = 86750;  break;     //1ml��Ͳע��        
		case  2: Dgus_82write_data(0x02,0x50,"1.5 (ml)");Specs = 54448;  break;     //3ml��Ͳע��һ��        
		case  3: Dgus_82write_data(0x02,0x50,"2 (ml)");  Specs = 54448;  break;     //3ml��Ͳע��2/3      
		case  4: Dgus_82write_data(0x02,0x50,"2.5 (ml)");Specs = 54448;  break;     //3ml��Ͳע��2.5/3         
		case  5: Dgus_82write_data(0x02,0x50,"3 (ml)");  Specs = 54448;  break;     //3ml��Ͳע��         
		case  6: Dgus_82write_data(0x02,0x50,"4 (ml)");  Specs = 45137;  break;     //5ml��Ͳע��4/5         
		case  7: Dgus_82write_data(0x02,0x50,"5 (ml)");  Specs = 59940;  break;     //5ml��Ͳע��   
  }
						 

						 
	if(Injector_mode> 5) Injector_mode= 5;
  if(EN1_CHN0 == 0)
	{//����
		switch(Injector_mode)  
		{
		 case  1: Dgus_82write_data(0x01,0x50,"�Զ���Ӧ");  break;
		 case  2: Dgus_82write_data(0x01,0x50,"�Զ�����");  break;
		 case  3: Dgus_82write_data(0x01,0x50,"����");      break;
		 case  4: Dgus_82write_data(0x01,0x50,"����(����)");break;
		 case  5: Dgus_82write_data(0x01,0x50,"����(��)");  break;
		}
	}
  else
	{//Ӣ��
		switch(Injector_mode)  
		{
		 case  1: Dgus_82write_data(0x01,0x50,"Auto-Sensing");  break;
		 case  2: Dgus_82write_data(0x01,0x50,"Auto Dose");  break;
		 case  3: Dgus_82write_data(0x01,0x50,"Dose");      break;
		 case  4: Dgus_82write_data(0x01,0x50,"Cont.(Normal)");break;
		 case  5: Dgus_82write_data(0x01,0x50,"Cont.(Slow)");  break;
		}
	}		
  
	 
			
	 if(Total_Shot> 14) Total_Shot= 10;  //�ܴ����������14,��Ϊ10��

	 if(Flow_rate> 3) Flow_rate= 1;      //ע���ٶ��������3,��Ϊ1��

	 One_Dose_Grade =  (15-Total_Shot);  //����ע�� = 15 - �ܴ�����
	
	Get_fuya_grade_time();//���ݸ�ѹ�ȼ���ȡ��ѹǿ�Ⱥ�ж��Ƶ��
	
	
	//�����ƽ���ǰ��������
	 R_Time = Specs/(Total_Shot*10);
	 if((Specs % (Total_Shot*10)) > ((Total_Shot*10)/2))   //��������
	 {
		 R_Time +=1;
	 }
	 switch(Flow_rate)//�����ٶȵȼ�����
	 {
		case 1 :L_Time = 4000;break;
		case 2 :L_Time = 4000;break;
	 	case 3 :L_Time = 4000;break;
	 }

//���ٶȣ�����0  Shot_count=0; 
//���� " if( (Injector_Mode==1)  || (Injector_Mode==2)  || (Injector_Mode==3)  )  "  ��ʾ����ʾ ����������
display___One_Dose_Grade_Flow_Rate_Total_Shot(); 
}




/***********************************************
*������    :Refresh_all_data_from_memory
*��������  :����ȷ��������
*��������  :��
*��������ֵ:��
*��������  :
************************************************/
void Refresh_all_data_from_memory(void)
{
    EN1_CHN0 =   IAP_Flash_ReadHalfWord(0,0);
		Dgus_82send_data( 0x50, EN1_CHN0);

    Set_Buzzer_off =  IAP_Flash_ReadHalfWord(0,1);
		Dgus_82send_data( 0x70, (1-Set_Buzzer_off) );

		Dgus_82send_data( 0x60,0 );

		Power_level =   IAP_Flash_ReadHalfWord(Menmory_number,0);
		 if(Power_level>10)Power_level =10;
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
                     
                     
		Syringe_type =  IAP_Flash_ReadHalfWord(Menmory_number,2); //������pageҳ����add8������  0-xxx
	  if(Syringe_type> 7) Syringe_type= 1;
	  switch(Syringe_type)  
	  {
			case  1: Dgus_82write_data(0x02,0x50,"1 (ml)");  break;//�������� �� 16λ��ַ�Ĵ���        
			case  2: Dgus_82write_data(0x02,0x50,"1.5 (ml)");  break;//�������� �� 16λ��ַ�Ĵ���        
			case  3: Dgus_82write_data(0x02,0x50,"2 (ml)");  break;//�������� �� 16λ��ַ�Ĵ���        
			case  4: Dgus_82write_data(0x02,0x50,"2.5 (ml)");  break;//�������� �� 16λ��ַ�Ĵ���        
			case  5: Dgus_82write_data(0x02,0x50,"3 (ml)");  break;//�������� �� 16λ��ַ�Ĵ���        
			case  6: Dgus_82write_data(0x02,0x50,"4 (ml)");  break;//�������� �� 16λ��ַ�Ĵ���        
			case  7: Dgus_82write_data(0x02,0x50,"5 (ml)");  break;//�������� �� 16λ��ַ�Ĵ���        
	  }
  
                     
		Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1); //������pageҳ����add8������  0-xxx
	  if(Injector_mode> 5) Injector_mode= 5;
						 
		if(EN1_CHN0==0)
		{
			switch(Injector_mode)  
			 {
				 case  1: Dgus_82write_data(0x01,0x50,"�Զ���Ӧ");  break;//�������� �� 16λ��ַ�Ĵ���        
				 case  2: Dgus_82write_data(0x01,0x50,"�Զ�����");  break;//�������� �� 16λ��ַ�Ĵ���        
				 case  3: Dgus_82write_data(0x01,0x50,"����");  break;//�������� �� 16λ��ַ�Ĵ���        
				 case  4: Dgus_82write_data(0x01,0x50,"����(����)");  break;//�������� �� 16λ��ַ�Ĵ���        
				 case  5: Dgus_82write_data(0x01,0x50,"����(��)");  break;//�������� �� 16λ��ַ�Ĵ���        
			 }
		}
		else if(EN1_CHN0==1)
		{
			switch(Injector_mode)  
			 {
				 case  1: Dgus_82write_data(0x01,0x50,"Auto-Sensing");  break;//�������� �� 16λ��ַ�Ĵ���        
				 case  2: Dgus_82write_data(0x01,0x50,"Auto Dose");  break;//�������� �� 16λ��ַ�Ĵ���        
				 case  3: Dgus_82write_data(0x01,0x50,"Dose");  break;//�������� �� 16λ��ַ�Ĵ���        
				 case  4: Dgus_82write_data(0x01,0x50,"Cont.(Normal)");  break;//�������� �� 16λ��ַ�Ĵ���        
				 case  5: Dgus_82write_data(0x01,0x50,"Cont.(Slow)");  break;//�������� �� 16λ��ַ�Ĵ���        
			 }
		}
		 
		
		

		 Total_Shot =    IAP_Flash_ReadHalfWord(Menmory_number,4); //������pageҳ����add8������  0-xxx
		 if(Total_Shot> 14) Total_Shot= 10;

		 Flow_rate =     IAP_Flash_ReadHalfWord(Menmory_number,3); //������pageҳ����add8������  0-xxx
		 if(Flow_rate> 3) Flow_rate= 1;

		 One_Dose_Grade =  (15-Total_Shot);

	   Shot_count=0; 
	   display___One_Dose_Grade_Flow_Rate_Total_Shot(); //���� " if( (Injector_Mode==1)  || (Injector_Mode==2)  || (Injector_Mode==3)  )  "  ��ʾ����ʾ ����������
}












