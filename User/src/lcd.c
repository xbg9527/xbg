//#include "main.h"                  // Device header



///**************************************************
//*������    ��LCD_spi_IO_init
//*��������  ��ģ��SPI�Ĺܽų�ʼ����
//*��������  ����
//*��������ֵ����
//*��������  ��LCD_CLK----------------------------PB13     
//						 LCD_SDA----------------------------PB15        
//****************************************************/
//void LCD_spi_IO_init(void)
//{
//	//GPIO��ʼ��
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//1.��ʱ��
//	
//	//�������
//	GPIO_InitTypeDef GPIO_InitStruct;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_15;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStruct.GPIO_Speed = GPIO_Fast_Speed;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);	
//	
//	
//}




///**************************************************
//*������    ��LCD_spi_byte
//*��������  ��SPI����һ���ֽں���
//*��������  ��u8 data
//*��������ֵ����
//*��������  ��    
//****************************************************/
//void LCD_spi_byte(u8 data)
//{
//	u8 val ;
//	u8 i;
//	//����
//	LCD_SPI_SCL_L;
//	LCD_MOSI_H;
//	
//	/*��������*/
//	for(i=0;i<8;i++)
//	{
//		LCD_SPI_SCL_L;        //����ʱ���ߣ���������д����   					
//		if(data & 0x80) LCD_MOSI_H; else LCD_MOSI_L;
//		LCD_SPI_SCL_H;       //���������أ������ӻ���
//		
//		data = data << 1;     //������һΪ����
//	}	
//}





///**************************************************
//*������    ��LCD_IO_init
//*��������  ��LCD�Ĺܽų�ʼ����
//*��������  ����
//*��������ֵ����
//*��������  �� LEDK-----PB1        ���������        //ͨ�����
//							RESET----PB10        ��λ����          //ͨ�����
//							LCD_CS---PB12        Ƭѡ����          //ͨ�����	
//							LCD_D/C--PB14        ��������ѡ����    //ͨ�����		  
//****************************************************/
//void LCD_IO_init(void)
//{
//	//GPIO��ʼ��
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//1.��ʱ��
//	
//	//�������
//	GPIO_InitTypeDef GPIO_InitStruct;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_14;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);	
//	
//	//��ʼ״̬
//	LCD_LED_OFF;               //�����
//	LCD_CS_H;                  //Ƭѡ����
//}







///**************************************************
//*������    ��st7789vm_write_command
//*��������  ����LCDд�����
//*��������  ��u8 cmd
//*��������ֵ����
//*��������  ��    
//****************************************************/
//void st7789vm_write_command(u8 cmd)
//{
//	LCD_CS_L;//������Ƭѡ
//	LCD_CMD;//��ʾ���͵�������
//	LCD_spi_byte(cmd);//���巢�͵�8λ ����
//	LCD_CS_H;//����Ƭѡ
//}





///**************************************************
//*������    ��st7789vm_write_command_parameter
//*��������  ����LCDд�������ֵ����
//*��������  ��u8 cmd
//*��������ֵ����
//*��������  ��    
//****************************************************/
//void st7789vm_write_command_parameter(u8 cmd_data)
//{
//	LCD_CS_L;//������Ƭѡ
//	LCD_DATA;//��ʾ���͵�������
//	LCD_spi_byte(cmd_data);//���巢�͵�8λ �������
//	LCD_CS_H;//����Ƭѡ
//}




///**************************************************
//*������    ��st7789vm_write_data
//*��������  ����LCDд���ݺ���
//*��������  ��u16 data
//*��������ֵ����
//*��������  ������ֵ����ɫֵ   
//****************************************************/
//void st7789vm_write_data(u16 data)
//{
//	LCD_CS_L;//������Ƭѡ
//	LCD_DATA;//��ʾ���͵�������
//	LCD_spi_byte(data>>8);//���巢�͵�8λ �������
//	LCD_spi_byte(data & 0x00ff);
//	LCD_CS_H;//����Ƭѡ
//}




///**************************************************
//*������    ��st7789vm_rest
//*��������  ����LCD��λ����
//*��������  ����
//*��������ֵ����
//*��������  ��  
//****************************************************/
//void st7789vm_rest(void)
//{
//	LCD_RES_L;
//	Tim5_delay_ms(100);
//	LCD_RES_H;
//	
//}





///**************************************************
//*������    ��LCD_init
//*��������  ����LCD��ʼ����
//*��������  ����
//*��������ֵ����
//*��������  ��  
//****************************************************/
//void LCD_init(void)
//{
//	//LCD_IO��ʼ��
//	LCD_IO_init();
//	//SPI_IO��ʼ��
//	LCD_spi_IO_init();
//	//LCD��λ
//	st7789vm_rest();
//	//IC����������ֲ
//	/* start initial sequence */ 
//	st7789vm_write_command(0x36);
//	st7789vm_write_command_parameter(0x00);

//	st7789vm_write_command(0x3A); 
//	st7789vm_write_command_parameter(0x05);

//	st7789vm_write_command(0xB2);
//	st7789vm_write_command_parameter(0x0C);
//	st7789vm_write_command_parameter(0x0C);
//	st7789vm_write_command_parameter(0x00);
//	st7789vm_write_command_parameter(0x33);
//	st7789vm_write_command_parameter(0x33); 

//	st7789vm_write_command(0xB7); 
//	st7789vm_write_command_parameter(0x35);  

//	st7789vm_write_command(0xBB);
//	st7789vm_write_command_parameter(0x19);

//	st7789vm_write_command(0xC0);
//	st7789vm_write_command_parameter(0x2C);

//	st7789vm_write_command(0xC2);
//	st7789vm_write_command_parameter(0x01);

//	st7789vm_write_command(0xC3);
//	st7789vm_write_command_parameter(0x12);   

//	st7789vm_write_command(0xC4);
//	st7789vm_write_command_parameter(0x20);  

//	st7789vm_write_command(0xC6); 
//	st7789vm_write_command_parameter(0x0F);    

//	st7789vm_write_command(0xD0); 
//	st7789vm_write_command_parameter(0xA4);
//	st7789vm_write_command_parameter(0xA1);

//	st7789vm_write_command(0xE0);
//	st7789vm_write_command_parameter(0xD0);
//	st7789vm_write_command_parameter(0x04);
//	st7789vm_write_command_parameter(0x0D);
//	st7789vm_write_command_parameter(0x11);
//	st7789vm_write_command_parameter(0x13);
//	st7789vm_write_command_parameter(0x2B);
//	st7789vm_write_command_parameter(0x3F);
//	st7789vm_write_command_parameter(0x54);
//	st7789vm_write_command_parameter(0x4C);
//	st7789vm_write_command_parameter(0x18);
//	st7789vm_write_command_parameter(0x0D);
//	st7789vm_write_command_parameter(0x0B);
//	st7789vm_write_command_parameter(0x1F);
//	st7789vm_write_command_parameter(0x23);

//	st7789vm_write_command(0xE1);
//	st7789vm_write_command_parameter(0xD0);
//	st7789vm_write_command_parameter(0x04);
//	st7789vm_write_command_parameter(0x0C);
//	st7789vm_write_command_parameter(0x11);
//	st7789vm_write_command_parameter(0x13);
//	st7789vm_write_command_parameter(0x2C);
//	st7789vm_write_command_parameter(0x3F);
//	st7789vm_write_command_parameter(0x44);
//	st7789vm_write_command_parameter(0x51);
//	st7789vm_write_command_parameter(0x2F);
//	st7789vm_write_command_parameter(0x1F);
//	st7789vm_write_command_parameter(0x1F);
//	st7789vm_write_command_parameter(0x20);
//	st7789vm_write_command_parameter(0x23);

//	st7789vm_write_command(0x21); 
//	st7789vm_write_command(0x11); 
//	st7789vm_write_command(0x29); 
//	
//	//������
//	LCD_LED_ON;
//	//����
//	LCD_clear(0x0000);
//}



///**************************************************
//*������    ��LCD_clear
//*��������  ������
//*��������  ��u16 color
//*��������ֵ����
//*��������  ��  
//****************************************************/
//void LCD_clear(u16 color)
//{
//	/*ȷ������*/
//	//ȷ��x����
//	st7789vm_write_command(0x2A);     //����������
//	//��ʼ������
//	st7789vm_write_command_parameter(0);
//	st7789vm_write_command_parameter(0);
//	//����������
//	st7789vm_write_command_parameter((LCD_W-1)>>8);
//	st7789vm_write_command_parameter((LCD_W-1));
//	
//	//ȷ��Y����
//	st7789vm_write_command(0x2B);     //����������
//	//��ʼ������
//	st7789vm_write_command_parameter(0);
//	st7789vm_write_command_parameter(0);
//	//����������
//	st7789vm_write_command_parameter((LCD_H-1)>>8);
//	st7789vm_write_command_parameter((LCD_H-1));
//	
//	
//	/*ȷ����ɫ*/
//	st7789vm_write_command(0x2C);     //��ɫ����
//	for(u32 i=0;i<LCD_W*LCD_H;i++)
//	{
//		st7789vm_write_data(color);
//	}
//}



///**************************************************
//*������    ��LCD_xy_clear
//*��������  ����ĳ�������������ĳ����ɫ
//*��������  ��u16 x,u16 y,u16 w,u16 h,u16 color
//*��������ֵ����
//*��������  ��
//****************************************************/
//void LCD_xy_clear(u16 x,u16 y,u16 w,u16 h,u16 color)
//{
//	/*ȷ������*/
//	//ȷ��x����
//	st7789vm_write_command(0x2A);     //����������
//	//��ʼ������
//	st7789vm_write_data(x);     
//	//����������
//	st7789vm_write_data(x+w-1);
//	
//	//ȷ��Y����
//	st7789vm_write_command(0x2B);     //����������
//	//��ʼ������
//	st7789vm_write_data(y);
//	//����������
//	st7789vm_write_data(y+h-1);
//	
//	
//	/*ȷ����ɫ*/
//	st7789vm_write_command(0x2C);     //��ɫ����
//	for(u32 i=0;i<w*h;i++)
//	{
//		st7789vm_write_data(color);
//	}
//}



///**************************************************
//*������    ��LCD_Point
//*��������  ����㺯��
//*��������  ��u16 x,u16 y,u16 color
//*��������ֵ����
//*��������  ��  
//****************************************************/
//void LCD_Point(u16 x,u16 y,u16 color)
//{
//	/*ȷ������*/
//	//ȷ��x����
//	st7789vm_write_command(0x2A);     //����������
//	//��ʼ������
//	st7789vm_write_data(x);     
//	//����������
//	st7789vm_write_data(x);
//	
//	//ȷ��Y����
//	st7789vm_write_command(0x2B);     //����������
//	//��ʼ������
//	st7789vm_write_data(y);
//	//����������
//	st7789vm_write_data(y);
//	
//	
//	/*ȷ����ɫ*/
//	st7789vm_write_command(0x2C);     //��ɫ����
//	st7789vm_write_data(color);
//	
//}







///******************************************************************************
//*������    ��LCD_Ring
//*��������  ��LCD��Ļ��Բ����
//*��������  ��u16 x,u16 y,u16 r,u16 colour 
//*��������ֵ����
//*��������  ��
//						��x - x0��^2 + (y - y0)^2  == r*r 
//*****************************************************************************************/
//void LCD_Ring(u16 x,u16 y,u16 r,u16 colour)
//{
//	u16 i,j;
//	
//	for(i=x-r;i<=x+r;i++)         //����������
//	{
//		for(j=y-r;j<=y+r;j++)       //����������
//		{
//			if((i-x)*(i-x) + (j-y)*(j-y) >=(r-2)*(r-2) && (i-x)*(i-x) + (j-y)*(j-y) <=r*r)   //�жϱ����ĵ��Ƿ��������
//			//if((i-x)*(i-x) + (j-y)*(j-y) ==r*r) 
//			{
//				//��㺯��
//				LCD_Point(i,j,colour); //���������ĵ�����
//			}
//		}
//	}
//}




///******************************************************************************
//*������    ��LCD_Ring_shi
//*��������  ��LCD��Ļ��Բ����ʵ��Բ
//*��������  ��u16 x,u16 y,u16 r,u16 colour 
//*��������ֵ����
//*��������  ��
//						��x - x0��^2 + (y - y0)^2  <= r*r 
//*****************************************************************************************/
//void LCD_Ring_shi(u16 x,u16 y,u16 r,u16 colour)
//{
//	u16 i,j;
//	
//	for(i=x-r;i<=x+r;i++)         //����������
//	{
//		for(j=y-r;j<=y+r;j++)       //����������
//		{
//			if((i-x)*(i-x) + (j-y)*(j-y) <=r*r)   //�жϱ����ĵ��Ƿ��������
//			{
//				//��㺯��
//				LCD_Point(i,j,colour); //���������ĵ�����
//			}
//		}
//	}
//}



///******************************************************************************
//*������    ��LCD_dis_ch
//*��������  ��LCD��Ļ��ʾ��ѡ��С���ַ�
//*��������  ��u16 x,u16 y,u16 color��u8 ch��u8 size ,u8 mode,u16 b_color 
//*��������ֵ����
//*��������  ��
//						size �ֺŴ�С   16  32
//						mode ����1  �ʹ�������ɫ
//						mode ����0  �Ͳ���������ɫ

//					W25Q64����¼��ʼ��ַ         0x020000
//						�ļ���                       ƫ����           
//					 ASC16.bin                   0x00000000            
//					 ASC32.bin                   0x00000806            
//					 HZK16.bin                   0x0000280C            
//					 HZK32.bin                   0x00042652            
//********************************************************************************/
//void LCD_dis_ch(u16 x,u16 y,u16 color,u8 ch,u8 size,u8 mode,u16 b_color)
//{
//	u8 n,i,j;
//	u8 temp16;
//	u16 temp32;
//	
//	u8 buff16[16] = {0};
//	u8 buff64[64] = {0};
//	
//	
//	/*����Ҫ��ʾ���ַ���ո��ƫ��ֵ n*/
//	n = ch - 0;
//	
//	/*��ʾ16*/
//	if(size == 16)
//	{
//		/*��W25q64��ȡ��ҪҪ��ʾ���ַ�����ģ����*/
//		w25q64_read(0x020000+0+n*16,16,buff16);

//		for(i=0;i<size;i++)     //��һ��ռ������
//		{	
//			//��Ҫ��ʾ���ַ���ģ����ȡ����һ�����ص�����ݷŵ�һ��������
//			temp16 = buff16[i];
//			
//			for(j=0;j<size/2;j++)   //ÿ�б������ص����
//			{
//				if(temp16 & (0x80 >> j))
//				{
//					LCD_Point(x+j,y+i,color);
//				}
//				else 
//				{
//					if(mode == 1)   //Ҫ�򱳾�ɫ
//					{
//						LCD_Point(x+j,y+i,b_color);
//					}
//				}
//				
//			}
//		}	
//	}
//	
//	/*��ʾ32*/
//	else if(size == 32)
//	{
//		/*��W25q64��ȡ��ҪҪ��ʾ���ַ�����ģ����*/
//		w25q64_read(0x020000+0x00000806+n*64,64,buff64);

//		
//		for(i=0;i<size;i++)     //��һ��ռ������
//		{
//			//��Ҫ��ʾ���ַ���ģ����ȡ����һ�����ص�����ݷŵ�һ��������
//			temp32 = (buff64[i*2]<<8) | buff64[i*2+1];
//			
//			for(j=0;j<size/2;j++)   //ÿ�б������ص����
//			{
//				if(temp32 & (0x8000 >> j))
//				{
//					LCD_Point(x+j,y+i,color);
//				}
//				else 
//				{
//					if(mode == 1)   //Ҫ�򱳾�ɫ
//					{
//						LCD_Point(x+j,y+i,b_color);
//					}
//				}
//				
//			}
//		}		
//	}
//	

//	
//	
//}




///******************************************************************************
//*������    ��LCD_dis_hz
//*��������  ��LCD��Ļ��ʾ��ѡ��С�ĺ���
//*��������  ��u16 x,u16 y,u16 color��u8 *hz��u8 size ,u8 mode,u16 b_color 
//*��������ֵ����
//*��������  ��
//						size �ֺŴ�С   16  32
//						mode ����1  �ʹ�������ɫ
//						mode ����0  �Ͳ���������ɫ
//********************************************************************************/
//void LCD_dis_hz(u16 x,u16 y,u16 color,u8 *hz,u8 size,u8 mode,u16 b_color)
//{
//	u8 i,j;
//	u32 n = 0;
//	u16 temp16;
//	u32 temp32;
//	
//	u8 buff32[32] ={0};
//	u8 buff128[128] ={0};
//	
//	/*����Ҫ��ʾ�ĺ������ֿ������еĺ��ֵ�ƫ��*/
//	n = (*hz-0xa1)*94 + (*(hz+1)-0xa1);
//	
//	/*��ʾ16*/
//	if(size == 16)
//	{
//		/*��W25q64��ȡ��ҪҪ��ʾ���ַ�����ģ����*/
//		w25q64_read(0x020000+0x0000280C+n*32,32,buff32);
//		
//		for(i=0;i<size;i++)     //��һ��ռ������
//		{
//			//��Ҫ��ʾ���ַ���ģ����ȡ����һ�����ص�����ݷŵ�һ��������
//			temp16 = (buff32[2*i]<<8)  | buff32[2*i+1];
//			
//			for(j=0;j<size;j++)   //ÿ�б������ص����
//			{
//				if(temp16 & (0x8000 >> j))
//				{
//					LCD_Point(x+j,y+i,color);
//				}
//				else 
//				{
//					if(mode == 1)   //Ҫ�򱳾�ɫ
//					{
//						LCD_Point(x+j,y+i,b_color);
//					}
//				}
//				
//			}
//		}	
//	}
//	
//	/*��ʾ32*/
//	else if(size == 32)
//	{
//		/*��W25q64��ȡ��ҪҪ��ʾ���ַ�����ģ����*/
//		w25q64_read(0x020000+0x00042652+n*128,128,buff128);
//		
//		for(i=0;i<size;i++)     //��һ��ռ������
//		{
//			//��Ҫ��ʾ���ַ���ģ����ȡ����һ�����ص�����ݷŵ�һ��������
//			temp32 = (buff128[i*4]<<24)   | 
//							 (buff128[i*4+1]<<16) | 
//			         (buff128[i*4+2]<<8)  | 
//			         (buff128[i*4+3]);
//			
//			for(j=0;j<size;j++)   //ÿ�б������ص����
//			{
//				if(temp32 & (0x80000000 >> j))
//				{
//					LCD_Point(x+j,y+i,color);
//				}
//				else 
//				{
//					if(mode == 1)   //Ҫ�򱳾�ɫ
//					{
//						LCD_Point(x+j,y+i,b_color);
//					}
//				}
//				
//			}
//		}		
//	}
//	

//}





///******************************************************************************
//*������    ��LCD_dis
//*��������  ��LCD��Ļ��ʾ��ѡ��С�ĺ��ֺ��ַ����
//*��������  ��u16 x,u16 y,u16 color��u8 *str��u8 size ,u8 mode,u16 b_color 
//*��������ֵ����
//*��������  ��
//						size �ֺŴ�С   16  32
//						mode ����1  �ʹ�������ɫ
//						mode ����0  �Ͳ���������ɫ
//********************************************************************************/
//void LCD_dis(u16 x,u16 y,u16 color,u8 *str,u8 size,u8 mode,u16 b_color)
//{
//	
//	while(*str != '\0')
//	{
//		/*�ж����ַ�*/
//		if(*str >= 32 && *str <=127)
//		{
//			LCD_dis_ch(x,y,color,*str,size,mode,b_color);
//			//������
//			str++;
//			//��Ļ
//			x+=size/2;
//			if(x>=239-size)
//			{
//				y+=size;
//				x=0;
//			}		
//		}
//		
//		/*�ж��Ǻ���*/
//		else
//		{
//			LCD_dis_hz(x,y,color,str,size,mode,b_color);
//			//������
//			str+=2;
//			//��Ļ
//			x+=size;
//			if(x>=239-size)
//			{
//				y+=size;
//				x=0;
//			}			
//		}	
//	}
//}





///******************************************************************************
//*������    ��LCD_dis_pic
//*��������  ��LCD��Ļ��ʾ�����СͼƬ
//*��������  ��u16 x,u16 y,u8 *pic
//*��������ֵ����
//*��������  ��
//********************************************************************************/
//void LCD_dis_pic(u16 x,u16 y,const u8 *pic)
//{
//	HEADCOLOR *head;
//	u16 *p;
//	
//	
//	head = (HEADCOLOR *)pic;
//	p = (u16*)(pic + sizeof(HEADCOLOR));

//	
//	/*ȷ������*/
//	//ȷ��x����
//	st7789vm_write_command(0x2A);     //����������
//	//��ʼ������
//	st7789vm_write_data(x);     
//	//����������
//	st7789vm_write_data(x+(head->w)-1);
//	
//	//ȷ��Y����
//	st7789vm_write_command(0x2B);     //����������
//	//��ʼ������
//	st7789vm_write_data(y);
//	//����������
//	st7789vm_write_data(y+(head->h)-1);
//	
//	
//	/*ȷ����ɫ*/
//	st7789vm_write_command(0x2C);     //��ɫ����
//	for(u32 i=0;i<(head->h)*(head->w);i++)
//	{
//		st7789vm_write_data(*p);
//		p++;
//	}
//	
//	
//}











