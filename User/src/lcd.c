//#include "main.h"                  // Device header



///**************************************************
//*函数名    ：LCD_spi_IO_init
//*函数功能  ：模拟SPI的管脚初始函数
//*函数参数  ：无
//*函数返回值：无
//*函数描述  ：LCD_CLK----------------------------PB13     
//						 LCD_SDA----------------------------PB15        
//****************************************************/
//void LCD_spi_IO_init(void)
//{
//	//GPIO初始化
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//1.开时钟
//	
//	//推挽输出
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
//*函数名    ：LCD_spi_byte
//*函数功能  ：SPI传输一个字节函数
//*函数参数  ：u8 data
//*函数返回值：无
//*函数描述  ：    
//****************************************************/
//void LCD_spi_byte(u8 data)
//{
//	u8 val ;
//	u8 i;
//	//空闲
//	LCD_SPI_SCL_L;
//	LCD_MOSI_H;
//	
//	/*传输数据*/
//	for(i=0;i<8;i++)
//	{
//		LCD_SPI_SCL_L;        //拉低时钟线，主机可以写数据   					
//		if(data & 0x80) LCD_MOSI_H; else LCD_MOSI_L;
//		LCD_SPI_SCL_H;       //产生上升沿，帮助从机，
//		
//		data = data << 1;     //发送下一为数据
//	}	
//}





///**************************************************
//*函数名    ：LCD_IO_init
//*函数功能  ：LCD的管脚初始函数
//*函数参数  ：无
//*函数返回值：无
//*函数描述  ： LEDK-----PB1        背光灯引脚        //通用输出
//							RESET----PB10        复位引脚          //通用输出
//							LCD_CS---PB12        片选引脚          //通用输出	
//							LCD_D/C--PB14        数据命令选择线    //通用输出		  
//****************************************************/
//void LCD_IO_init(void)
//{
//	//GPIO初始化
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//1.开时钟
//	
//	//推挽输出
//	GPIO_InitTypeDef GPIO_InitStruct;
//	GPIO_InitStruct.GPIO_Pin =  GPIO_Pin_1 | GPIO_Pin_10 | GPIO_Pin_12 | GPIO_Pin_14;
//	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_Init(GPIOB, &GPIO_InitStruct);	
//	
//	//初始状态
//	LCD_LED_OFF;               //背光关
//	LCD_CS_H;                  //片选拉高
//}







///**************************************************
//*函数名    ：st7789vm_write_command
//*函数功能  ：对LCD写命令函数
//*函数参数  ：u8 cmd
//*函数返回值：无
//*函数描述  ：    
//****************************************************/
//void st7789vm_write_command(u8 cmd)
//{
//	LCD_CS_L;//先拉低片选
//	LCD_CMD;//表示发送的是命令
//	LCD_spi_byte(cmd);//具体发送的8位 命令
//	LCD_CS_H;//拉高片选
//}





///**************************************************
//*函数名    ：st7789vm_write_command_parameter
//*函数功能  ：对LCD写命令参数值函数
//*函数参数  ：u8 cmd
//*函数返回值：无
//*函数描述  ：    
//****************************************************/
//void st7789vm_write_command_parameter(u8 cmd_data)
//{
//	LCD_CS_L;//先拉低片选
//	LCD_DATA;//表示发送的是数据
//	LCD_spi_byte(cmd_data);//具体发送的8位 命令参数
//	LCD_CS_H;//拉高片选
//}




///**************************************************
//*函数名    ：st7789vm_write_data
//*函数功能  ：对LCD写数据函数
//*函数参数  ：u16 data
//*函数返回值：无
//*函数描述  ：坐标值，颜色值   
//****************************************************/
//void st7789vm_write_data(u16 data)
//{
//	LCD_CS_L;//先拉低片选
//	LCD_DATA;//表示发送的是数据
//	LCD_spi_byte(data>>8);//具体发送的8位 命令参数
//	LCD_spi_byte(data & 0x00ff);
//	LCD_CS_H;//拉高片选
//}




///**************************************************
//*函数名    ：st7789vm_rest
//*函数功能  ：对LCD复位函数
//*函数参数  ：无
//*函数返回值：无
//*函数描述  ：  
//****************************************************/
//void st7789vm_rest(void)
//{
//	LCD_RES_L;
//	Tim5_delay_ms(100);
//	LCD_RES_H;
//	
//}





///**************************************************
//*函数名    ：LCD_init
//*函数功能  ：对LCD初始函数
//*函数参数  ：无
//*函数返回值：无
//*函数描述  ：  
//****************************************************/
//void LCD_init(void)
//{
//	//LCD_IO初始化
//	LCD_IO_init();
//	//SPI_IO初始化
//	LCD_spi_IO_init();
//	//LCD复位
//	st7789vm_rest();
//	//IC驱动代码移植
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
//	//开背光
//	LCD_LED_ON;
//	//清屏
//	LCD_clear(0x0000);
//}



///**************************************************
//*函数名    ：LCD_clear
//*函数功能  ：清屏
//*函数参数  ：u16 color
//*函数返回值：无
//*函数描述  ：  
//****************************************************/
//void LCD_clear(u16 color)
//{
//	/*确定区域*/
//	//确定x方向
//	st7789vm_write_command(0x2A);     //横坐标命令
//	//起始横坐标
//	st7789vm_write_command_parameter(0);
//	st7789vm_write_command_parameter(0);
//	//结束横坐标
//	st7789vm_write_command_parameter((LCD_W-1)>>8);
//	st7789vm_write_command_parameter((LCD_W-1));
//	
//	//确定Y方向
//	st7789vm_write_command(0x2B);     //纵坐标命令
//	//起始纵坐标
//	st7789vm_write_command_parameter(0);
//	st7789vm_write_command_parameter(0);
//	//结束纵坐标
//	st7789vm_write_command_parameter((LCD_H-1)>>8);
//	st7789vm_write_command_parameter((LCD_H-1));
//	
//	
//	/*确定颜色*/
//	st7789vm_write_command(0x2C);     //颜色命令
//	for(u32 i=0;i<LCD_W*LCD_H;i++)
//	{
//		st7789vm_write_data(color);
//	}
//}



///**************************************************
//*函数名    ：LCD_xy_clear
//*函数功能  ：将某个矩形区域清成某个颜色
//*函数参数  ：u16 x,u16 y,u16 w,u16 h,u16 color
//*函数返回值：无
//*函数描述  ：
//****************************************************/
//void LCD_xy_clear(u16 x,u16 y,u16 w,u16 h,u16 color)
//{
//	/*确定区域*/
//	//确定x方向
//	st7789vm_write_command(0x2A);     //横坐标命令
//	//起始横坐标
//	st7789vm_write_data(x);     
//	//结束横坐标
//	st7789vm_write_data(x+w-1);
//	
//	//确定Y方向
//	st7789vm_write_command(0x2B);     //纵坐标命令
//	//起始纵坐标
//	st7789vm_write_data(y);
//	//结束纵坐标
//	st7789vm_write_data(y+h-1);
//	
//	
//	/*确定颜色*/
//	st7789vm_write_command(0x2C);     //颜色命令
//	for(u32 i=0;i<w*h;i++)
//	{
//		st7789vm_write_data(color);
//	}
//}



///**************************************************
//*函数名    ：LCD_Point
//*函数功能  ：打点函数
//*函数参数  ：u16 x,u16 y,u16 color
//*函数返回值：无
//*函数描述  ：  
//****************************************************/
//void LCD_Point(u16 x,u16 y,u16 color)
//{
//	/*确定区域*/
//	//确定x方向
//	st7789vm_write_command(0x2A);     //横坐标命令
//	//起始横坐标
//	st7789vm_write_data(x);     
//	//结束横坐标
//	st7789vm_write_data(x);
//	
//	//确定Y方向
//	st7789vm_write_command(0x2B);     //纵坐标命令
//	//起始纵坐标
//	st7789vm_write_data(y);
//	//结束纵坐标
//	st7789vm_write_data(y);
//	
//	
//	/*确定颜色*/
//	st7789vm_write_command(0x2C);     //颜色命令
//	st7789vm_write_data(color);
//	
//}







///******************************************************************************
//*函数名    ：LCD_Ring
//*函数功能  ：LCD屏幕画圆函数
//*函数参数  ：u16 x,u16 y,u16 r,u16 colour 
//*函数返回值：无
//*函数描述  ：
//						（x - x0）^2 + (y - y0)^2  == r*r 
//*****************************************************************************************/
//void LCD_Ring(u16 x,u16 y,u16 r,u16 colour)
//{
//	u16 i,j;
//	
//	for(i=x-r;i<=x+r;i++)         //遍历横坐标
//	{
//		for(j=y-r;j<=y+r;j++)       //遍历纵坐标
//		{
//			if((i-x)*(i-x) + (j-y)*(j-y) >=(r-2)*(r-2) && (i-x)*(i-x) + (j-y)*(j-y) <=r*r)   //判断遍历的点是否符合条件
//			//if((i-x)*(i-x) + (j-y)*(j-y) ==r*r) 
//			{
//				//打点函数
//				LCD_Point(i,j,colour); //将遍历到的点打出来
//			}
//		}
//	}
//}




///******************************************************************************
//*函数名    ：LCD_Ring_shi
//*函数功能  ：LCD屏幕画圆函数实心圆
//*函数参数  ：u16 x,u16 y,u16 r,u16 colour 
//*函数返回值：无
//*函数描述  ：
//						（x - x0）^2 + (y - y0)^2  <= r*r 
//*****************************************************************************************/
//void LCD_Ring_shi(u16 x,u16 y,u16 r,u16 colour)
//{
//	u16 i,j;
//	
//	for(i=x-r;i<=x+r;i++)         //遍历横坐标
//	{
//		for(j=y-r;j<=y+r;j++)       //遍历纵坐标
//		{
//			if((i-x)*(i-x) + (j-y)*(j-y) <=r*r)   //判断遍历的点是否符合条件
//			{
//				//打点函数
//				LCD_Point(i,j,colour); //将遍历到的点打出来
//			}
//		}
//	}
//}



///******************************************************************************
//*函数名    ：LCD_dis_ch
//*函数功能  ：LCD屏幕显示可选大小的字符
//*函数参数  ：u16 x,u16 y,u16 color，u8 ch，u8 size ,u8 mode,u16 b_color 
//*函数返回值：无
//*函数描述  ：
//						size 字号大小   16  32
//						mode 传入1  就带背景颜色
//						mode 传入0  就不带背景颜色

//					W25Q64的烧录起始地址         0x020000
//						文件名                       偏移量           
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
//	/*计算要显示的字符与空格的偏移值 n*/
//	n = ch - 0;
//	
//	/*显示16*/
//	if(size == 16)
//	{
//		/*从W25q64中取出要要显示的字符的字模数据*/
//		w25q64_read(0x020000+0+n*16,16,buff16);

//		for(i=0;i<size;i++)     //子一共占的行数
//		{	
//			//将要显示的字符的模数据取出来一行像素点的数据放到一个变量里
//			temp16 = buff16[i];
//			
//			for(j=0;j<size/2;j++)   //每行遍历像素点个数
//			{
//				if(temp16 & (0x80 >> j))
//				{
//					LCD_Point(x+j,y+i,color);
//				}
//				else 
//				{
//					if(mode == 1)   //要打背景色
//					{
//						LCD_Point(x+j,y+i,b_color);
//					}
//				}
//				
//			}
//		}	
//	}
//	
//	/*显示32*/
//	else if(size == 32)
//	{
//		/*从W25q64中取出要要显示的字符的字模数据*/
//		w25q64_read(0x020000+0x00000806+n*64,64,buff64);

//		
//		for(i=0;i<size;i++)     //子一共占的行数
//		{
//			//将要显示的字符的模数据取出来一行像素点的数据放到一个变量里
//			temp32 = (buff64[i*2]<<8) | buff64[i*2+1];
//			
//			for(j=0;j<size/2;j++)   //每行遍历像素点个数
//			{
//				if(temp32 & (0x8000 >> j))
//				{
//					LCD_Point(x+j,y+i,color);
//				}
//				else 
//				{
//					if(mode == 1)   //要打背景色
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
//*函数名    ：LCD_dis_hz
//*函数功能  ：LCD屏幕显示可选大小的汉字
//*函数参数  ：u16 x,u16 y,u16 color，u8 *hz，u8 size ,u8 mode,u16 b_color 
//*函数返回值：无
//*函数描述  ：
//						size 字号大小   16  32
//						mode 传入1  就带背景颜色
//						mode 传入0  就不带背景颜色
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
//	/*计算要显示的汉字与字库数组中的汉字的偏移*/
//	n = (*hz-0xa1)*94 + (*(hz+1)-0xa1);
//	
//	/*显示16*/
//	if(size == 16)
//	{
//		/*从W25q64中取出要要显示的字符的字模数据*/
//		w25q64_read(0x020000+0x0000280C+n*32,32,buff32);
//		
//		for(i=0;i<size;i++)     //子一共占的行数
//		{
//			//将要显示的字符的模数据取出来一行像素点的数据放到一个变量里
//			temp16 = (buff32[2*i]<<8)  | buff32[2*i+1];
//			
//			for(j=0;j<size;j++)   //每行遍历像素点个数
//			{
//				if(temp16 & (0x8000 >> j))
//				{
//					LCD_Point(x+j,y+i,color);
//				}
//				else 
//				{
//					if(mode == 1)   //要打背景色
//					{
//						LCD_Point(x+j,y+i,b_color);
//					}
//				}
//				
//			}
//		}	
//	}
//	
//	/*显示32*/
//	else if(size == 32)
//	{
//		/*从W25q64中取出要要显示的字符的字模数据*/
//		w25q64_read(0x020000+0x00042652+n*128,128,buff128);
//		
//		for(i=0;i<size;i++)     //子一共占的行数
//		{
//			//将要显示的字符的模数据取出来一行像素点的数据放到一个变量里
//			temp32 = (buff128[i*4]<<24)   | 
//							 (buff128[i*4+1]<<16) | 
//			         (buff128[i*4+2]<<8)  | 
//			         (buff128[i*4+3]);
//			
//			for(j=0;j<size;j++)   //每行遍历像素点个数
//			{
//				if(temp32 & (0x80000000 >> j))
//				{
//					LCD_Point(x+j,y+i,color);
//				}
//				else 
//				{
//					if(mode == 1)   //要打背景色
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
//*函数名    ：LCD_dis
//*函数功能  ：LCD屏幕显示可选大小的汉字和字符混合
//*函数参数  ：u16 x,u16 y,u16 color，u8 *str，u8 size ,u8 mode,u16 b_color 
//*函数返回值：无
//*函数描述  ：
//						size 字号大小   16  32
//						mode 传入1  就带背景颜色
//						mode 传入0  就不带背景颜色
//********************************************************************************/
//void LCD_dis(u16 x,u16 y,u16 color,u8 *str,u8 size,u8 mode,u16 b_color)
//{
//	
//	while(*str != '\0')
//	{
//		/*判断是字符*/
//		if(*str >= 32 && *str <=127)
//		{
//			LCD_dis_ch(x,y,color,*str,size,mode,b_color);
//			//数组中
//			str++;
//			//屏幕
//			x+=size/2;
//			if(x>=239-size)
//			{
//				y+=size;
//				x=0;
//			}		
//		}
//		
//		/*判断是汉字*/
//		else
//		{
//			LCD_dis_hz(x,y,color,str,size,mode,b_color);
//			//数组中
//			str+=2;
//			//屏幕
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
//*函数名    ：LCD_dis_pic
//*函数功能  ：LCD屏幕显示任意大小图片
//*函数参数  ：u16 x,u16 y,u8 *pic
//*函数返回值：无
//*函数描述  ：
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
//	/*确定区域*/
//	//确定x方向
//	st7789vm_write_command(0x2A);     //横坐标命令
//	//起始横坐标
//	st7789vm_write_data(x);     
//	//结束横坐标
//	st7789vm_write_data(x+(head->w)-1);
//	
//	//确定Y方向
//	st7789vm_write_command(0x2B);     //纵坐标命令
//	//起始纵坐标
//	st7789vm_write_data(y);
//	//结束纵坐标
//	st7789vm_write_data(y+(head->h)-1);
//	
//	
//	/*确定颜色*/
//	st7789vm_write_command(0x2C);     //颜色命令
//	for(u32 i=0;i<(head->h)*(head->w);i++)
//	{
//		st7789vm_write_data(*p);
//		p++;
//	}
//	
//	
//}











