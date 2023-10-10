#include "main.h"                  // Device header




/**************************************
*��������DMA_Init
*�������ܣ�
*������������
*��������ֵ��
*����������
**************************************/
u8 SendBuff[SendBuff_Size] = {0};
void ADC_DMA_Init(void)
{
	//DMA1ʱ��ʹ��
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//DMA1�Ĵ�������
	DMA_InitTypeDef DMA_InitStruct = {0};
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR;                    //ȡֵ�������ַ
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)&SendBuff;                 //DMA�洢��ַ
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                     //����-�洢���������ȡ����
	DMA_InitStruct.DMA_BufferSize = SendBuff_Size;                      //ÿ�δ����������
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;        //�����ַ����ģʽ
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                //�洢����ַ����ģʽ
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//�������ݿ��
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        //�洢�����ݿ��:8λ
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;                          //��ִ��ѭ������
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;                    //ͨ�����ȼ�-��
	DMA_InitStruct.DMA_M2M = DISABLE;                                   //�رմ洢�����洢��ģʽ
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//DMA�ж�����
	NVIC_InitTypeDef NVIC_InitStruct = {0};
	NVIC_InitStruct.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	
	NVIC_Init(&NVIC_InitStruct);
	
	DMA_ITConfig(DMA1_Channel1,DMA_IT_TC,ENABLE);
	DMA_Cmd(DMA1_Channel1,ENABLE);
	
	
	
}



/**************************************
*��������Adc1_Ch9_Init
*�������ܣ�
*������������
*��������ֵ��
*����������PB1------ADC1----ͨ��9
**************************************/
void Adc1_Ch9_Init(void)
{
	/*IO�ڿ���������*/
	//�˿�ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);      //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M
	
	//����IO��
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;      //ģ������ģʽ
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	ADC_DeInit(ADC1);  //��λADC1
	
	/*ADC�Ĵ�������*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//����ADC
	ADC_InitTypeDef ADC_InitStruct ={0};
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStruct.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStruct);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	//ADC_DMACmd(ADC1,ENABLE);//ʹ��ADC1��DMA����
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
  
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
  
}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
/**************************************
*��������u16 Get_Adc
*�������ܣ�
*����������u8 ch
*��������ֵ��u16
*����������
**************************************/
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1,ch,1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,�ӵ�һ��ͨ����ʼ����������ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
 
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}
 /**************************************
*��������Get_Adc_Average
*�������ܣ���ȡtimes�βɼ����ݵ�ƽ��ֵ
*����������u8 ch,u8 times
*��������ֵ��u16
*����������
**************************************/
u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		Delay_ms(5);
	}
	return temp_val/times;
}






