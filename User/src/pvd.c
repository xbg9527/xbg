#include "main.h"                  // Device header


/**************************************
*函数名：Pvd_Init
*函数功能：电压监测器初始化
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
void Pvd_Init(void)
{
	//电源端口使能
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
	
	
  //配置PVD模式和阈值
	PWR_PVDLevelConfig(PWR_PVDLevel_2V2);
	
	//使能PVD
	PWR_PVDCmd(ENABLE);
	
}



/**************************************
*函数名：CheckVoltageStatus
*函数功能：电压监测器初始化
*函数参数：无
*函数返回值：无
*函数描述：
**************************************/
u8 CheckVoltageStatus(void)
{
	if (PWR_GetFlagStatus(PWR_FLAG_PVDO) != RESET)
	{
		//电压低于或超出阈值
		return 1;
	}
	else
	{
		return 0;
	}
}


















