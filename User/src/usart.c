#include "main.h"                  // Device header


/**************************************
*��������Usart1_Init
*�������ܣ�����1��ʼ������
*����������u32 baud
*��������ֵ����
*����������PA9-------USART-Tx
           PA10------USART-Rx
**************************************/
void Usart1_Init(u32 baud)
{
	/*IO������*/
	//�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	//���ô���Tx��Ϊ���츴�ö˿�
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;    //���츴�����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//���ô���Rx��Ϊ��������˿�
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;     //��������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	/*��������*/
	//����ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
	//��������
	USART_InitTypeDef USART_InitStruct = {0};
	
	USART_DeInit(USART1);
	USART_InitStruct.USART_BaudRate = baud;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART1,&USART_InitStruct);
	
	/*NVIC����������*/
	
	
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;            //�ж�Դ������
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;              //NVIC��Ӧͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;    //��ռ����ֵ
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;           //��Ӧ����ֵ
	
	NVIC_Init(&NVIC_InitStruct);
	
	//�����ж�ʹ��
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	//�����ж�ʹ��
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);
	//����ʹ��
	USART_Cmd(USART1,ENABLE);
	
	
}


/***********************************************
*������    :Usart1_Send_Byte
*��������  :
*��������  :��
*��������ֵ:u8 data
*��������  :
************************************************/
void Usart1_Send_Byte(u8 data)
{
	//�ȴ����ݷ������
	while(!(USART_GetFlagStatus(USART1,USART_FLAG_TC)));
	
	//����һλ����
	USART_SendData(USART1,data);
	
	
}



/***********************************************
*������    ��Usart1_Send_Str
*��������  ������1���Ͷ��ֽں���
*��������  ��u8 *str
*��������ֵ����
*��������  ��
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
*������    ��Usart1_Send_array
*��������  ������1����һ������
*��������  ��unsigned char *data_array_Pointer 
*��������ֵ����
*��������  ��
***********************************************/
void Usart1_Send_array(unsigned char *data_array_Pointer ) //����һ�������ÿ�����ݣ� ��һ������ֵ+1 ��Ϊ �������鳤��
{

    Usart1_Send_Byte( 0x5a ); //����ͷ
    Usart1_Send_Byte( 0xa5 );
	for( unsigned char i=0; i< ((*data_array_Pointer)+1); i++)
	{
	    Usart1_Send_Byte( *(data_array_Pointer+i) );
  }

}




/**************************************
*��������Usart2_Init
*�������ܣ�����2��ʼ������
*����������u32 baud
*��������ֵ����
*����������PA2------USART-Tx
           PA3------USART-Rx
**************************************/
void Usart2_Init(u32 baud)
{
	/*IO������*/
	//�˿�ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	//���ô���Tx��Ϊ���츴�ö˿�
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;    //���츴�����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	//���ô���Rx��Ϊ��������˿�
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;     //��©����
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3;
	
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	/*��������*/
	//����ʱ��ʹ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	
	//��������
	USART_InitTypeDef USART_InitStruct = {0};
	
	USART_InitStruct.USART_BaudRate = baud;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	
	USART_Init(USART2,&USART_InitStruct);
	
	/*NVIC����������*/
	
	
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = USART2_IRQn;            //�ж�Դ������
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;              //NVIC��Ӧͨ��
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;    //��ռ����ֵ
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;           //��Ӧ����ֵ
	
	NVIC_Init(&NVIC_InitStruct);
	
	//�����ж�ʹ��
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	//�����ж�ʹ��
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);
	//����ʹ��
	USART_Cmd(USART2,ENABLE);
	
	
}



/***********************************************
*������    :Usart2_Send_Byte
*��������  :����2����һ���ֽں���
*��������  :��
*��������ֵ:u8 data
*��������  :
************************************************/
void Usart2_Send_Byte(u8 data)
{
	//�ȴ����ݷ������
	while(!(USART_GetFlagStatus(USART2,USART_FLAG_TC)));
	
	//����һλ����
	USART_SendData(USART2,data);
	
	
}

/***********************************************
*������    ��Usart2_Send_Str
*��������  ������2���Ͷ��ֽں���
*��������  ��u8 *str
*��������ֵ����
*��������  ��
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
*������    ��Usart2_Send_array
*��������  ������2����һ������
*��������  ��unsigned char *data_array_Pointer 
*��������ֵ����
*��������  ��
***********************************************/
unsigned char A0[] =  {0x07,0x82,0x12,0x10,0xB0,0xB4,0xCF,0xC1};//��-����
unsigned char A1[] =  {0x07,0x82,0x12,0x40,0xB0,0xB4,0xCF,0xC2};//��-����
unsigned char A2[] =  {0x07,0x82,0x12,0x20,0xB0,0xB4,0xD1,0xB9};//��ѹ
unsigned char A3[] =  {0x07,0x82,0x12,0x30,0xCC,0xA7,0xC6,0xF0};//̧��

unsigned char Z1[] =  {0x0F,0x82,0x01,0x00,0xD7,0xA2,0xC9,0xE4,0xC4,0xA3,0xCA,0xBD,0x00,0x00,0x41,0xEA};//ע��ģʽ
unsigned char Z2[] =  {0x0F,0x82,0x02,0x00,0xD7,0xA2,0xC9,0xE4,0xB9,0xE6,0xB8,0xF1,0x00,0x00,0x58,0xA3};//ע����
unsigned char Z3[] =  {0x0F,0x82,0x03,0x00,0xD7,0xA2,0xC9,0xE4,0xCB,0xD9,0xB6,0xC8,0x00,0x00,0x69,0x52};//ע���ٶ�
unsigned char Z4[] =  {0x11,0x82,0x04,0x00,0xB5,0xA5,0xB4,0xCE,0xD7,0xA2,0xC9,0xE4,0xC1,0xBF,0x00,0x00,0xE2,0xA6};//����ע����
unsigned char Z5[] =  {0x0F,0x82,0x05,0x00,0xD7,0xA2,0xC9,0xE4,0xB4,0xCE,0xCA,0xFD,0x00,0x00,0x17,0x08};//ע�����
unsigned char Z6[] =  {0x12,0x82,0x06,0x00,0x20,0x20,0x20,0xCE,0xFC,0xC1,0xA6,0xB5,0xC8,0xBC,0xB6,0x00,0x00,0x8C,0xB4};//�����ȼ�
unsigned char Z7[] =  {0x10,0x82,0x07,0x00,0x20,0x20,0x20,0xD6,0xFA,0xCD,0xC6,0xC6,0xF7,0x00,0x00,0xD3,0xA0};//������
unsigned char Z8[] =  {0x07,0x82,0x00,0x90,0x00,0x00,0x5C,0x33};//ͼ�꣺���淽��

unsigned char E1[] =  {0x14,0x82,0x01,0x00,0x49,0x6E,0x6A,0x65,0x63,0x74,0x6F,0x72,0x20,0x4D,0x6F,0x64,0x65,0x00,0x00,0x73,0x17};
unsigned char E2[] =  {0x13,0x82,0x02,0x00,0x53,0x79,0x72,0x69,0x6E,0x67,0x65,0x20,0x54,0x79,0x70,0x65,0x00,0x00,0x39,0x7B};
unsigned char E3[] =  {0x10,0x82,0x03,0x00,0x46,0x6C,0x6F,0x77,0x20,0x52,0x61,0x74,0x65,0x00,0x00,0x91,0xEF};
unsigned char E4[] =  {0x0F,0x82,0x04,0x00,0x4F,0x6E,0x65,0x20,0x44,0x6F,0x73,0x65,0x00,0x00,0xEA,0x22};
unsigned char E5[] =  {0x11,0x82,0x05,0x00,0x54,0x6F,0x74,0x61,0x6C,0x20,0x53,0x68,0x6F,0x74,0x00,0x00,0x49,0xB6};
unsigned char E6[] =  {0x14,0x82,0x06,0x00,0x20,0x20,0x50,0x6F,0x77,0x65,0x72,0x20,0x4C,0x65,0x76,0x65,0x6C,0x00,0x00,0x01,0xA3};
unsigned char E7[] =  {0x11,0x82,0x07,0x00,0x20,0x20,0x20,0x42,0x6F,0x6F,0x73,0x74,0x65,0x72,0x00,0x00,0x9B,0x1E};
unsigned char E8[] =  {0x07,0x82,0x00,0x90,0x00,0x01,0x9D,0xF3};//ͼ�꣺���淽��


u8 Cheak_page[] =   {0x03,0x81,0x03,0x02};//��ѯ��ǰ����
u8 JUMP_TO_6[] =    {0x04,0x80,0x03,0x00,0x06};//����6ҳ
u8 JUMP_TO_8[] =    {0x04,0x80,0x03,0x00,0x08};//����8ҳ
u8 JUMP_TO_10[] =   {0x04,0x80,0x03,0x00,0x0a};//����10ҳ
void Usart2_Send_array(unsigned char *data_array_Pointer ) //����һ�������ÿ�����ݣ� ��һ������ֵ+1 ��Ϊ �������鳤��
{

    Usart2_Send_Byte( 0x5a ); //����ͷ
    Usart2_Send_Byte( 0xa5 );
	for( unsigned char i=0; i< ((*data_array_Pointer)+1); i++)
	{
	    Usart2_Send_Byte( *(data_array_Pointer+i) );
  }

}




/**************************************
*��������Array_Comparison
*�������ܣ�����ȶԺ���
*����������str1,str2,len
*��������ֵ��u8
*����������
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
	//��׼����Ҫ��֧�ֺ���                 
	struct __FILE 
	{ 
		int handle; 
		
		
	}; 
	/* FILE is typedef�� d in stdio.h. */ 
	FILE __stdout;       
	//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
	int _sys_exit(int x) 
	{ 
		x = x; 
	} 
	//�ض���fputc���� 
	int fputc(int ch, FILE *f)
	{      
		while((USART2->SR&0X40)==0);//ѭ������,ֱ���������   
		USART2->DR = (u8) ch;      
		return ch;
	}
	#endif






