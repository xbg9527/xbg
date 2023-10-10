//#include "main.h"                  // Device header


///**************************************
//*函数名：
//*函数功能：
//*函数参数：无
//*函数返回值：无
//*函数描述：
//**************************************/
//void DGUS_0x82_CRC16_Transmit_one_Data(unsigned char addr_L,unsigned char data_L)//发送16位数据 到 16位地址寄存器
//{
//        u16 tmp = 0xffff; //可缩减

//        tmp = ( 0x82 ) ^ tmp; //0x82
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        }   
// 
//        tmp = ( 0x00) ^ tmp; //0x00
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        }   
//        
//        tmp = (addr_L) ^ tmp; //addr_L
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        } 
//        
//        tmp = ( 0x00) ^ tmp; //0x00
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        }   
//        
//        tmp = (data_L) ^ tmp; //data_L
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        } 
//       
//     
////__asm__ __volatile__ ("cli" ::) ; 
//		
//    USART_Transmit( 0x5a ); //数据头
//    USART_Transmit( 0xa5 );

//    USART_Transmit( 0x07 );
//    USART_Transmit( 0x82 );

//    USART_Transmit( 0x00 );
//    USART_Transmit( addr_L );
//    USART_Transmit( 0x00 );
//    USART_Transmit( data_L );
//        
//    USART_Transmit(  (u8)(tmp%256) ); //校验位低字节   //数据正确  //迪文的校验码低8位先传输。
//    USART_Transmit(  (u8)(tmp/256) );
//    
////__asm__ __volatile__ ("sei" ::) ; 
//}


///**************************************
//*函数名：
//*函数功能：
//*函数参数：无
//*函数返回值：无
//*函数描述：
//**************************************/
//void DGUS_DIR_Transmit_array(unsigned char *data_array_Pointer ) //发送一个数组的每个数据， 第一个数据值+1 设为 整个数组长度
//{
////__asm__ __volatile__ ("cli" ::) ; 
//    USART_Transmit( 0x5a ); //数据头
//    USART_Transmit( 0xa5 );
//	for( unsigned char i=0; i< ((*data_array_Pointer)+1); i++)
//	{
//	    USART_Transmit( *(data_array_Pointer+i) );
//    }
////__asm__ __volatile__ ("sei" ::) ; 
//}


///**************************************
//*函数名：
//*函数功能：
//*函数参数：无
//*函数返回值：无
//*函数描述：
//**************************************/
//void  DGUS_0x82_CRC16_Transmit_one_array(u8 addr_H,u8 addr_L,u8 *data_array_Pointer)//发送数组 到 16位地址寄存器
//{
//    u8 input_data_count=0;
//    u8 TX_data_count=0;
//    
//    while(  ( *(data_array_Pointer+input_data_count) ) !='\0')
//    {input_data_count++;}
//    input_data_count++;  //将结束标志'\0'也算上
//    
//    TX_data_count =(input_data_count+5); //将0x82,addr_H,u8 addr_L,      ,crc低，crc高

//    
//    
//    u16 tmp = 0xffff;

//        tmp = (0x82) ^ tmp;
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        }  
//        
//        tmp = (addr_H) ^ tmp;
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        }  
//    
//        tmp = (addr_L) ^ tmp;
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        }  
//    
//    for(u8 n = 0; n < input_data_count; n++)//要校验的位数为len个
//    {
//        tmp =( *(data_array_Pointer+n) ^ tmp);
//        
//        for(u8 i = 0;i < 8;i++) //此处的8 -- 指每一个char类型的8bit，每bit都要处理
//        { 
//            if(tmp & 0x01)
//            {
//                tmp = tmp >> 1;
//                tmp = tmp ^ 0xa001;
//            }   
//            else
//            {
//                tmp = tmp >> 1;
//            }   
//        }   
//    }   
//    
//    USART_Transmit( 0x5a ); //数据头
//    USART_Transmit( 0xa5 );

//    USART_Transmit( TX_data_count );
//    USART_Transmit( 0x82 );

//    USART_Transmit( addr_H );
//    USART_Transmit( addr_L );
//    
//    for(u8 n = 0; n < input_data_count; n++)
//    {
//        USART_Transmit(  *(data_array_Pointer+n)  );
//    } 
//        
//    USART_Transmit(  (u8)(tmp%256) ); //校验位低字节   //数据正确  //迪文的校验码低8位先传输。
//    USART_Transmit(  (u8)(tmp/256) );
//    
//}





















