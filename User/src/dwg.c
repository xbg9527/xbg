//#include "main.h"                  // Device header


///**************************************
//*��������
//*�������ܣ�
//*������������
//*��������ֵ����
//*����������
//**************************************/
//void DGUS_0x82_CRC16_Transmit_one_Data(unsigned char addr_L,unsigned char data_L)//����16λ���� �� 16λ��ַ�Ĵ���
//{
//        u16 tmp = 0xffff; //������

//        tmp = ( 0x82 ) ^ tmp; //0x82
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//    USART_Transmit( 0x5a ); //����ͷ
//    USART_Transmit( 0xa5 );

//    USART_Transmit( 0x07 );
//    USART_Transmit( 0x82 );

//    USART_Transmit( 0x00 );
//    USART_Transmit( addr_L );
//    USART_Transmit( 0x00 );
//    USART_Transmit( data_L );
//        
//    USART_Transmit(  (u8)(tmp%256) ); //У��λ���ֽ�   //������ȷ  //���ĵ�У�����8λ�ȴ��䡣
//    USART_Transmit(  (u8)(tmp/256) );
//    
////__asm__ __volatile__ ("sei" ::) ; 
//}


///**************************************
//*��������
//*�������ܣ�
//*������������
//*��������ֵ����
//*����������
//**************************************/
//void DGUS_DIR_Transmit_array(unsigned char *data_array_Pointer ) //����һ�������ÿ�����ݣ� ��һ������ֵ+1 ��Ϊ �������鳤��
//{
////__asm__ __volatile__ ("cli" ::) ; 
//    USART_Transmit( 0x5a ); //����ͷ
//    USART_Transmit( 0xa5 );
//	for( unsigned char i=0; i< ((*data_array_Pointer)+1); i++)
//	{
//	    USART_Transmit( *(data_array_Pointer+i) );
//    }
////__asm__ __volatile__ ("sei" ::) ; 
//}


///**************************************
//*��������
//*�������ܣ�
//*������������
//*��������ֵ����
//*����������
//**************************************/
//void  DGUS_0x82_CRC16_Transmit_one_array(u8 addr_H,u8 addr_L,u8 *data_array_Pointer)//�������� �� 16λ��ַ�Ĵ���
//{
//    u8 input_data_count=0;
//    u8 TX_data_count=0;
//    
//    while(  ( *(data_array_Pointer+input_data_count) ) !='\0')
//    {input_data_count++;}
//    input_data_count++;  //��������־'\0'Ҳ����
//    
//    TX_data_count =(input_data_count+5); //��0x82,addr_H,u8 addr_L,      ,crc�ͣ�crc��

//    
//    
//    u16 tmp = 0xffff;

//        tmp = (0x82) ^ tmp;
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//    for(u8 n = 0; n < input_data_count; n++)//ҪУ���λ��Ϊlen��
//    {
//        tmp =( *(data_array_Pointer+n) ^ tmp);
//        
//        for(u8 i = 0;i < 8;i++) //�˴���8 -- ָÿһ��char���͵�8bit��ÿbit��Ҫ����
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
//    USART_Transmit( 0x5a ); //����ͷ
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
//    USART_Transmit(  (u8)(tmp%256) ); //У��λ���ֽ�   //������ȷ  //���ĵ�У�����8λ�ȴ��䡣
//    USART_Transmit(  (u8)(tmp/256) );
//    
//}





















