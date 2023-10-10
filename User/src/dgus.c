#include "main.h"

/***********************************************
*函数名    :Dgus_82send_data
*函数功能  :迪文屏-发送显示变量编号
*函数参数  :u8 addr_L      地位地址
					  u8 addr_Data   要写入的数据
*函数返回值:无
*函数描述  :
************************************************/
void Dgus_82send_data(u8 addr_L,u8 addr_Data)
{
	
	//发送数据
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
*函数名    :Dgus_82write_data
*函数功能  :迪文屏写指令函数
*函数参数  :u8 addr_H      高位地址
            u8 addr_L      地位地址
						u8 *str        要写入的数据
*函数返回值:无
*函数描述  :
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
	
	//发送数据
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
*函数名    :Dgus_83read_data
*函数功能  :迪文屏读指令函数
*函数参数  :无
*函数返回值:无
*函数描述  :
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
*函数名    :Clear_array
*函数功能  :数组清零
*函数参数  :u8 *str
*函数返回值:无
*函数描述  :
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
*函数名    :Change
*函数功能  :十进制转十六进制
*函数参数  :u16 n
*函数返回值:u8*
*函数描述  :
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
*函数名    :IAP_EraseSector
*函数功能  :擦除初始地址+1024*page页
*函数参数  :u8 page
*函数返回值:无
*函数描述  :
************************************************/
void IAP_EraseSector(u8 page) //在设定的起始地址算的第几页   0-XXX
{
    //在初使化时钟处有 FLASH_SetLatency(FLASH_Latency_2);  // 因为系统时钟为72M所以要设置两个时钟周期的延时
    __ASM volatile ("cpsid i");  //关中断 
    FLASH_Unlock(); 
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR | FLASH_FLAG_EOP);

    // 写入页之前要擦除整页,并判断是否擦除成功
    while(FLASH_ErasePage((STARTADDR+1024*page)) != FLASH_COMPLETE);
    FLASH_Lock();
    __ASM volatile ("cpsie i"); //开中断
}


/***********************************************
*函数名    :IAP_Flash_ProgramHalfWord
*函数功能  :在指定初始地址+1024*page页的第2*add8个半字处，写入数据dat。
*函数参数  :u8 page,u8 add8, u16 dat
*函数返回值:无
*函数描述  :
************************************************/
void IAP_Flash_ProgramHalfWord(u8 page,u8 add8, u16 dat) //在第page页，第add8个写半字 
{
    
    __ASM volatile ("cpsid i");  //关中断 
    FLASH_Unlock(); 
    FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR | FLASH_FLAG_EOP);

    while(FLASH_ProgramHalfWord( (STARTADDR + 1024*page + 2*add8) , dat) != FLASH_COMPLETE );
    FLASH_Lock();
    __ASM volatile ("cpsie i"); //开中断
}

/***********************************************
*函数名    :IAP_Flash_ReadHalfWord
*函数功能  :读出第page页，第add8个半字  0-xxx
*函数参数  :u8 page,u8 add8
*函数返回值:u16
*函数描述  :
************************************************/
u16 IAP_Flash_ReadHalfWord(u8 page,u8 add8) 
{
      uint32_t faddr=( (STARTADDR + 1024*page + 2*add8) );
	  return *(uint16_t*)faddr; 
}




/***********************************************
*函数名    :disp_Shot_count_and_Total_Shot
*函数功能  :显示当前注射次数/总次数
*函数参数  :无
*函数返回值:无
*函数描述  :
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
						case 0x88://当前注射次数>=100 且 注射总次数>=100
										disp_Shot_count_Total_Shot[0]= ( 0x30+(Shot_count/100));
										disp_Shot_count_Total_Shot[1]=( 0x30+((Shot_count%100)/10));
										disp_Shot_count_Total_Shot[2]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[3]='/';
										disp_Shot_count_Total_Shot[4]= ( 0x30+(Total_Shot/10));
										disp_Shot_count_Total_Shot[5]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[6]=  0x30;
						break;
						case 0x48://10<=当前注射次数<100  且 注射总次数>=100
										disp_Shot_count_Total_Shot[0]=( 0x30+((Shot_count%100)/10));
										disp_Shot_count_Total_Shot[1]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[2]='/';
										disp_Shot_count_Total_Shot[3]= ( 0x30+(Total_Shot/10));
										disp_Shot_count_Total_Shot[4]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[5]=  0x30;
										disp_Shot_count_Total_Shot[6]= '\0';
						break;
						case 0x08://当前注射次数<10   且   注射总次数>=100
										disp_Shot_count_Total_Shot[0]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[1]='/';
										disp_Shot_count_Total_Shot[2]= ( 0x30+(Total_Shot/10));
										disp_Shot_count_Total_Shot[3]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[4]=  0x30;
										disp_Shot_count_Total_Shot[5]= '\0';
						break;
						case 0x40://10<=当前注射次数<100  且 注射总次数<100
										disp_Shot_count_Total_Shot[0]=( 0x30+((Shot_count%100)/10));
										disp_Shot_count_Total_Shot[1]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[2]='/';
										disp_Shot_count_Total_Shot[3]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[4]=  0x30;
										disp_Shot_count_Total_Shot[5]= '\0';
						break;
						case 0x00://当前注射次数<10  且 注射总次数<100
										disp_Shot_count_Total_Shot[0]= ( 0x30+(Shot_count%10));
										disp_Shot_count_Total_Shot[1]='/';
										disp_Shot_count_Total_Shot[2]= ( 0x30+(Total_Shot%10));
										disp_Shot_count_Total_Shot[3]=  0x30;
										disp_Shot_count_Total_Shot[4]= '\0';
						break;
			 }
			 
		 Dgus_82write_data(0x05,0x50,disp_Shot_count_Total_Shot);//发送数组 到 16位地址寄存器
}












/***********************************************
*函数名    :display___One_Dose_Grade_Flow_Rate_Total_Shot
*函数功能  :显示单次注射量、速度、总次
*函数参数  :无
*函数返回值:无
*函数描述  :
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
						 
					disp_One_Dose[2] = ( 0x30+( One_Dose/1000)   );        // 发送One_Dose数据到屏幕  
					disp_One_Dose[3] = ( 0x30+((One_Dose%1000)/100)   );   // 发送One_Dose数据到屏幕  
					disp_One_Dose[4] = ( 0x30+((One_Dose%100 )/10)    );   // 发送One_Dose数据到屏幕  
					disp_One_Dose[5] = ( 0x30+(One_Dose%10) );            // 发送One_Dose数据到屏幕

					Dgus_82write_data(0x04,0x50,disp_One_Dose); //发送数组 到 16位地址寄存器   
			 if(EN1_CHN0==0)
			 {//中文
				 switch(Flow_rate)  
				 {
					case  1: Dgus_82write_data(0x03,0x50,"常规");  break;//发送数组 到 16位地址寄存器        
					case  2: Dgus_82write_data(0x03,0x50,"快速");  break;//发送数组 到 16位地址寄存器        
					case  3: Dgus_82write_data(0x03,0x50,"慢速");  break;//发送数组 到 16位地址寄存器        
				 }
			 }
			 else if(EN1_CHN0==1)
			 {//英文
				 switch(Flow_rate)  
				 {
					case  1: Dgus_82write_data(0x03,0x50,"Normal");  break;//发送数组 到 16位地址寄存器        
					case  2: Dgus_82write_data(0x03,0x50,"Fast");  break;//发送数组 到 16位地址寄存器        
					case  3: Dgus_82write_data(0x03,0x50,"Slow");  break;//发送数组 到 16位地址寄存器        
				 }
			 }
				 
	
		//Shot_count=0;
					disp_Shot_count_and_Total_Shot();     
		}
	else
	{
		 Dgus_82write_data(0x03,0x50,"---"); //发送数组 到 16位地址寄存器 // (0x0a)0不显示 并在 Flow_Rate显示“---”
		 Dgus_82write_data(0x04,0x50,"---"); //发送数组 到 16位地址寄存器 // (0x0a)0不显示 并在 One_Dose显示“---”
		 Dgus_82write_data(0x05,0x50,"--/--"); //发送数组 到 16位地址寄存器 // (0x0a)0不显示 并在 时显示“---”
	}
 }//3



/***********************************************
*函数名    :Refresh_all_data_from_RAM
*函数功能  :参数显示
*函数参数  :无
*函数返回值:无
*函数描述  :
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
		case  1: Dgus_82write_data(0x02,0x50,"1 (ml)");  Specs = 86750;  break;     //1ml针筒注完        
		case  2: Dgus_82write_data(0x02,0x50,"1.5 (ml)");Specs = 54448;  break;     //3ml针筒注完一半        
		case  3: Dgus_82write_data(0x02,0x50,"2 (ml)");  Specs = 54448;  break;     //3ml针筒注完2/3      
		case  4: Dgus_82write_data(0x02,0x50,"2.5 (ml)");Specs = 54448;  break;     //3ml针筒注完2.5/3         
		case  5: Dgus_82write_data(0x02,0x50,"3 (ml)");  Specs = 54448;  break;     //3ml针筒注完         
		case  6: Dgus_82write_data(0x02,0x50,"4 (ml)");  Specs = 45137;  break;     //5ml针筒注完4/5         
		case  7: Dgus_82write_data(0x02,0x50,"5 (ml)");  Specs = 59940;  break;     //5ml针筒注完   
  }
						 

						 
	if(Injector_mode> 5) Injector_mode= 5;
  if(EN1_CHN0 == 0)
	{//中文
		switch(Injector_mode)  
		{
		 case  1: Dgus_82write_data(0x01,0x50,"自动感应");  break;
		 case  2: Dgus_82write_data(0x01,0x50,"自动单次");  break;
		 case  3: Dgus_82write_data(0x01,0x50,"单次");      break;
		 case  4: Dgus_82write_data(0x01,0x50,"持续(常规)");break;
		 case  5: Dgus_82write_data(0x01,0x50,"持续(慢)");  break;
		}
	}
  else
	{//英文
		switch(Injector_mode)  
		{
		 case  1: Dgus_82write_data(0x01,0x50,"Auto-Sensing");  break;
		 case  2: Dgus_82write_data(0x01,0x50,"Auto Dose");  break;
		 case  3: Dgus_82write_data(0x01,0x50,"Dose");      break;
		 case  4: Dgus_82write_data(0x01,0x50,"Cont.(Normal)");break;
		 case  5: Dgus_82write_data(0x01,0x50,"Cont.(Slow)");  break;
		}
	}		
  
	 
			
	 if(Total_Shot> 14) Total_Shot= 10;  //总次数如果大于14,则为10。

	 if(Flow_rate> 3) Flow_rate= 1;      //注射速度如果大于3,则为1。

	 One_Dose_Grade =  (15-Total_Shot);  //单次注射 = 15 - 总次数。
	
	Get_fuya_grade_time();//根据负压等级获取负压强度和卸气频率
	
	
	//计算推进器前后脉冲数
	 R_Time = Specs/(Total_Shot*10);
	 if((Specs % (Total_Shot*10)) > ((Total_Shot*10)/2))   //四舍五入
	 {
		 R_Time +=1;
	 }
	 switch(Flow_rate)//根据速度等级调速
	 {
		case 1 :L_Time = 4000;break;
		case 2 :L_Time = 4000;break;
	 	case 3 :L_Time = 4000;break;
	 }

//调速度，不清0  Shot_count=0; 
//根据 " if( (Injector_Mode==1)  || (Injector_Mode==2)  || (Injector_Mode==3)  )  "  显示或不显示 这三个参数
display___One_Dose_Grade_Flow_Rate_Total_Shot(); 
}




/***********************************************
*函数名    :Refresh_all_data_from_memory
*函数功能  :参数确认啦啦啦
*函数参数  :无
*函数返回值:无
*函数描述  :
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
                     
                     
		Syringe_type =  IAP_Flash_ReadHalfWord(Menmory_number,2); //读出第page页，第add8个半字  0-xxx
	  if(Syringe_type> 7) Syringe_type= 1;
	  switch(Syringe_type)  
	  {
			case  1: Dgus_82write_data(0x02,0x50,"1 (ml)");  break;//发送数组 到 16位地址寄存器        
			case  2: Dgus_82write_data(0x02,0x50,"1.5 (ml)");  break;//发送数组 到 16位地址寄存器        
			case  3: Dgus_82write_data(0x02,0x50,"2 (ml)");  break;//发送数组 到 16位地址寄存器        
			case  4: Dgus_82write_data(0x02,0x50,"2.5 (ml)");  break;//发送数组 到 16位地址寄存器        
			case  5: Dgus_82write_data(0x02,0x50,"3 (ml)");  break;//发送数组 到 16位地址寄存器        
			case  6: Dgus_82write_data(0x02,0x50,"4 (ml)");  break;//发送数组 到 16位地址寄存器        
			case  7: Dgus_82write_data(0x02,0x50,"5 (ml)");  break;//发送数组 到 16位地址寄存器        
	  }
  
                     
		Injector_mode = IAP_Flash_ReadHalfWord(Menmory_number,1); //读出第page页，第add8个半字  0-xxx
	  if(Injector_mode> 5) Injector_mode= 5;
						 
		if(EN1_CHN0==0)
		{
			switch(Injector_mode)  
			 {
				 case  1: Dgus_82write_data(0x01,0x50,"自动感应");  break;//发送数组 到 16位地址寄存器        
				 case  2: Dgus_82write_data(0x01,0x50,"自动单次");  break;//发送数组 到 16位地址寄存器        
				 case  3: Dgus_82write_data(0x01,0x50,"单次");  break;//发送数组 到 16位地址寄存器        
				 case  4: Dgus_82write_data(0x01,0x50,"持续(常规)");  break;//发送数组 到 16位地址寄存器        
				 case  5: Dgus_82write_data(0x01,0x50,"持续(慢)");  break;//发送数组 到 16位地址寄存器        
			 }
		}
		else if(EN1_CHN0==1)
		{
			switch(Injector_mode)  
			 {
				 case  1: Dgus_82write_data(0x01,0x50,"Auto-Sensing");  break;//发送数组 到 16位地址寄存器        
				 case  2: Dgus_82write_data(0x01,0x50,"Auto Dose");  break;//发送数组 到 16位地址寄存器        
				 case  3: Dgus_82write_data(0x01,0x50,"Dose");  break;//发送数组 到 16位地址寄存器        
				 case  4: Dgus_82write_data(0x01,0x50,"Cont.(Normal)");  break;//发送数组 到 16位地址寄存器        
				 case  5: Dgus_82write_data(0x01,0x50,"Cont.(Slow)");  break;//发送数组 到 16位地址寄存器        
			 }
		}
		 
		
		

		 Total_Shot =    IAP_Flash_ReadHalfWord(Menmory_number,4); //读出第page页，第add8个半字  0-xxx
		 if(Total_Shot> 14) Total_Shot= 10;

		 Flow_rate =     IAP_Flash_ReadHalfWord(Menmory_number,3); //读出第page页，第add8个半字  0-xxx
		 if(Flow_rate> 3) Flow_rate= 1;

		 One_Dose_Grade =  (15-Total_Shot);

	   Shot_count=0; 
	   display___One_Dose_Grade_Flow_Rate_Total_Shot(); //根据 " if( (Injector_Mode==1)  || (Injector_Mode==2)  || (Injector_Mode==3)  )  "  显示或不显示 这三个参数
}












