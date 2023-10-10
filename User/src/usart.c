#include "main.h"                  // Device header


/**************************************
*函数名：Usart1_Init
*函数功能：串口1初始化配置
*函数参数：u32 baud
*函数返回值：无
*函数描述：PA9-------USART-Tx
           PA10------USART-Rx
**************************************/
void Usart1_Init(u32 baud)
{
	/*IO口配置*/
	//端口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	//配置串口Tx作为推挽复用端口
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;    //推挽复用输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//配置串口Rx作为悬空输入端口
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;     //浮空输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	/*串口配置*/
	//串口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//串口配置
	USART_InitTypeDef USART_InitStruct = {0};
	
	USART_DeInit(USART1);
	USART_InitStruct.USART_BaudRate = baud;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStruct);
	
	/*NVIC控制器配置*/
	
	
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;            //中断源的名字
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;              //NVIC响应通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;    //抢占级别值
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;           //响应级别值
	
	NVIC_Init(&NVIC_InitStruct);
	
	//接收中断使能
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//空闲中断使能
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
	//串口使能
	USART_Cmd(USART1,ENABLE);
	
	
}


/***********************************************
*函数名    :Usart1_Send_Byte
*函数功能  :
*函数参数  :无
*函数返回值:u8 data
*函数描述  :
************************************************/
void Usart1_Send_Byte(u8 data)
{
	//等待数据发送完成
	while(!(USART_GetFlagStatus(USART1,USART_FLAG_TC)));
	
	//发送一位数据
	USART_SendData(USART1,data);
	
	
}



/***********************************************
*函数名    ：Usart1_Send_Str
*函数功能  ：串口1发送多字节函数
*函数参数  ：u8 *str
*函数返回值：无
*函数描述  ：
***********************************************/
void Usart1_Send_Str(u8 *str)
{
	while(*str != '\0')
	{
		Usart1_Send_Byte(*str);
		str++;
	}
}


/***********************************************
*函数名    ：Usart1_Send_array
*函数功能  ：串口1发送一个数组
*函数参数  ：unsigned char *data_array_Pointer 
*函数返回值：无
*函数描述  ：
***********************************************/
void Usart1_Send_array(unsigned char *data_array_Pointer ) //发送一个数组的每个数据， 第一个数据值+1 设为 整个数组长度
{

    Usart1_Send_Byte( 0x5a ); //数据头
    Usart1_Send_Byte( 0xa5 );
	for( unsigned char i=0; i< ((*data_array_Pointer)+1); i++)
	{
	    Usart1_Send_Byte( *(data_array_Pointer+i) );
  }

}




/**************************************
*函数名：Usart2_Init
*函数功能：串口2初始化配置
*函数参数：u32 baud
*函数返回值：无
*函数描述：PA2------USART-Tx
           PA3------USART-Rx
**************************************/
void Usart2_Init(u32 baud)
{
	/*IO口配置*/
	//端口时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	//配置串口Tx作为推挽复用端口
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;    //推挽复用输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//配置串口Rx作为悬空输入端口
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;     //开漏输入
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	/*串口配置*/
	//串口时钟使能
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	//串口配置
	USART_InitTypeDef USART_InitStruct = {0};
	
	USART_InitStruct.USART_BaudRate = baud;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART2,&USART_InitStruct);
	
	/*NVIC控制器配置*/
	
	
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;            //中断源的名字
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;              //NVIC响应通道
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;    //抢占级别值
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;           //响应级别值
	
	NVIC_Init(&NVIC_InitStruct);
	
	//接收中断使能
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	//空闲中断使能
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
	//串口使能
	USART_Cmd(USART2,ENABLE);
	
	
}



/***********************************************
*函数名    :Usart2_Send_Byte
*函数功能  :串口2发送一个字节函数
*函数参数  :无
*函数返回值:u8 data
*函数描述  :
************************************************/
void Usart2_Send_Byte(u8 data)
{
	//等待数据发送完成
	while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC)));
	
	//发送一位数据
	USART_SendData(USART2,data);
	
	
}

/***********************************************
*函数名    ：Usart2_Send_Str
*函数功能  ：串口2发送多字节函数
*函数参数  ：u8 *str
*函数返回值：无
*函数描述  ：
***********************************************/
void Usart2_Send_Str(u8 *str)
{
	while(*str != '\0')
	{
		Usart2_Send_Byte(*str);
		str++;
	}
}

/***********************************************
*函数名    ：Usart2_Send_array
*函数功能  ：串口2发送一个数组
*函数参数  ：unsigned char *data_array_Pointer 
*函数返回值：无
*函数描述  ：
***********************************************/
unsigned char A0[] =  {0x07,0x82,0x12,0x10,0xB0,0xB4,0xCF,0xC1};//左-按下
unsigned char A1[] =  {0x07,0x82,0x12,0x40,0xB0,0xB4,0xCF,0xC2};//右-按下
unsigned char A2[] =  {0x07,0x82,0x12,0x20,0xB0,0xB4,0xD1,0xB9};//按压
unsigned char A3[] =  {0x07,0x82,0x12,0x30,0xCC,0xA7,0xC6,0xF0};//抬起

unsigned char Z1[] =  {0x0F,0x82,0x01,0x00,0xD7,0xA2,0xC9,0xE4,0xC4,0xA3,0xCA,0xBD,0x00,0x00,0x41,0xEA};//注射模式
unsigned char Z2[] =  {0x0F,0x82,0x02,0x00,0xD7,0xA2,0xC9,0xE4,0xB9,0xE6,0xB8,0xF1,0x00,0x00,0x58,0xA3};//注射规格
unsigned char Z3[] =  {0x0F,0x82,0x03,0x00,0xD7,0xA2,0xC9,0xE4,0xCB,0xD9,0xB6,0xC8,0x00,0x00,0x69,0x52};//注射速度
unsigned char Z4[] =  {0x11,0x82,0x04,0x00,0xB5,0xA5,0xB4,0xCE,0xD7,0xA2,0xC9,0xE4,0xC1,0xBF,0x00,0x00,0xE2,0xA6};//单次注射量
unsigned char Z5[] =  {0x0F,0x82,0x05,0x00,0xD7,0xA2,0xC9,0xE4,0xB4,0xCE,0xCA,0xFD,0x00,0x00,0x17,0x08};//注射次数
unsigned char Z6[] =  {0x12,0x82,0x06,0x00,0x20,0x20,0x20,0xCE,0xFC,0xC1,0xA6,0xB5,0xC8,0xBC,0xB6,0x00,0x00,0x8C,0xB4};//吸力等级
unsigned char Z7[] =  {0x10,0x82,0x07,0x00,0x20,0x20,0x20,0xD6,0xFA,0xCD,0xC6,0xC6,0xF7,0x00,0x00,0xD3,0xA0};//助推器
unsigned char Z8[] =  {0x07,0x82,0x00,0x90,0x00,0x00,0x5C,0x33};//图标：保存方案

unsigned char E1[] =  {0x14,0x82,0x01,0x00,0x49,0x6E,0x6A,0x65,0x63,0x74,0x6F,0x72,0x20,0x4D,0x6F,0x64,0x65,0x00,0x00,0x73,0x17};
unsigned char E2[] =  {0x13,0x82,0x02,0x00,0x53,0x79,0x72,0x69,0x6E,0x67,0x65,0x20,0x54,0x79,0x70,0x65,0x00,0x00,0x39,0x7B};
unsigned char E3[] =  {0x10,0x82,0x03,0x00,0x46,0x6C,0x6F,0x77,0x20,0x52,0x61,0x74,0x65,0x00,0x00,0x91,0xEF};
unsigned char E4[] =  {0x0F,0x82,0x04,0x00,0x4F,0x6E,0x65,0x20,0x44,0x6F,0x73,0x65,0x00,0x00,0xEA,0x22};
unsigned char E5[] =  {0x11,0x82,0x05,0x00,0x54,0x6F,0x74,0x61,0x6C,0x20,0x53,0x68,0x6F,0x74,0x00,0x00,0x49,0xB6};
unsigned char E6[] =  {0x14,0x82,0x06,0x00,0x20,0x20,0x50,0x6F,0x77,0x65,0x72,0x20,0x4C,0x65,0x76,0x65,0x6C,0x00,0x00,0x01,0xA3};
unsigned char E7[] =  {0x11,0x82,0x07,0x00,0x20,0x20,0x20,0x42,0x6F,0x6F,0x73,0x74,0x65,0x72,0x00,0x00,0x9B,0x1E};
unsigned char E8[] =  {0x07,0x82,0x00,0x90,0x00,0x01,0x9D,0xF3};//图标：保存方案


u8 Cheak_page[] =   {0x03,0x81,0x03,0x02};//查询当前界面
u8 JUMP_TO_6[] =    {0x04,0x80,0x03,0x00,0x06};//跳到6页
u8 JUMP_TO_8[] =    {0x04,0x80,0x03,0x00,0x08};//跳到8页
u8 JUMP_TO_10[] =   {0x04,0x80,0x03,0x00,0x0a};//跳到10页
void Usart2_Send_array(unsigned char *data_array_Pointer ) //发送一个数组的每个数据， 第一个数据值+1 设为 整个数组长度
{

    Usart2_Send_Byte( 0x5a ); //数据头
    Usart2_Send_Byte( 0xa5 );
	for( unsigned char i=0; i< ((*data_array_Pointer)+1); i++)
	{
	    Usart2_Send_Byte( *(data_array_Pointer+i) );
  }

}




/**************************************
*函数名：Array_Comparison
*函数功能：数组比对函数
*函数参数：str1,str2,len
*函数返回值：u8
*函数描述：
**************************************/
u8 Array_Comparison(u8 str1[],u8 str2[])
{
	u8 i=0;
	
	while(str1[i] != '\0' && str2[i] != '\0')
	{
		if(str1[i] != str2[i])
		{
			return 0;
		}
		
		i++;
	}
	
	return 1;
}









































#if 1
	#pragma import(__use_no_semihosting)             
	//标准库需要的支持函数                 
	struct __FILE 
	{ 
		int handle; 
		
		
	}; 
	/* FILE is typedef’ d in stdio.h. */ 
	FILE __stdout;       
	//定义_sys_exit()以避免使用半主机模式    
	int _sys_exit(int x) 
	{ 
		x = x; 
	} 
	//重定义fputc函数 
	int fputc(int ch, FILE *f)
	{      
		while((USART2->SR&0X40)==0);//循环发送,直到发送完毕   
		USART2->DR = (u8) ch;      
		return ch;
	}
	#endif






