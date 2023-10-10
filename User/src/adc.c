#include "main.h"                  // Device header




/**************************************
*函数名：DMA_Init
*函数功能：
*函数参数：无
*函数返回值：
*函数描述：
**************************************/
u8 SendBuff[SendBuff_Size] = {0};
void ADC_DMA_Init(void)
{
	//DMA1时钟使能
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
	//DMA1寄存器配置
	DMA_InitTypeDef DMA_InitStruct = {0};
	DMA_InitStruct.DMA_PeripheralBaseAddr = ADC1_DR;                    //取值的外设地址
	DMA_InitStruct.DMA_MemoryBaseAddr = (u32)&SendBuff;                 //DMA存储地址
	DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralSRC;                     //方向-存储器从外设读取数据
	DMA_InitStruct.DMA_BufferSize = SendBuff_Size;                      //每次传输的数据量
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;        //外设地址增量模式
	DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;                //存储器地址增量模式
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//外设数据宽度
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;        //存储器数据宽度:8位
	DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;                          //不执行循环操作
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;                    //通道优先级-高
	DMA_InitStruct.DMA_M2M = DISABLE;                                   //关闭存储器到存储器模式
	
	DMA_Init(DMA1_Channel1,&DMA_InitStruct);
	
	//DMA中断配置
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
*函数名：Adc1_Ch9_Init
*函数功能：
*函数参数：无
*函数返回值：
*函数描述：PB1------ADC1----通道9
**************************************/
void Adc1_Ch9_Init(void)
{
	/*IO口控制器配置*/
	//端口使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);      //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M
	
	//配置IO口
	GPIO_InitTypeDef GPIO_InitStruct = {0};
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AIN;      //模拟输入模式
	
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	ADC_DeInit(ADC1);  //复位ADC1
	
	/*ADC寄存器配置*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	//配置ADC
	ADC_InitTypeDef ADC_InitStruct ={0};
	ADC_InitStruct.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStruct.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStruct.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStruct.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStruct.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStruct);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	//ADC_DMACmd(ADC1,ENABLE);//使能ADC1的DMA请求
	
	ADC_ResetCalibration(ADC1);	//使能复位校准
	
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
  
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
  
}				  
//获得ADC值
//ch:通道值 0~3
/**************************************
*函数名：u16 Get_Adc
*函数功能：
*函数参数：u8 ch
*函数返回值：u16
*函数描述：
**************************************/
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1,ch,1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,从第一个通道开始采样，采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
 
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}
 /**************************************
*函数名：Get_Adc_Average
*函数功能：获取times次采集数据的平均值
*函数参数：u8 ch,u8 times
*函数返回值：u16
*函数描述：
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






