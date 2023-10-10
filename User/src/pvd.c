#include "main.h"                  // Device header


/**************************************
*��������Pvd_Init
*�������ܣ���ѹ�������ʼ��
*������������
*��������ֵ����
*����������
**************************************/
void Pvd_Init(void)
{
	//��Դ�˿�ʹ��
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_PWR, ENABLE);
	
	
  //����PVDģʽ����ֵ
	PWR_PVDLevelConfig(PWR_PVDLevel_2V2);
	
	//ʹ��PVD
	PWR_PVDCmd(ENABLE);
	
}



/**************************************
*��������CheckVoltageStatus
*�������ܣ���ѹ�������ʼ��
*������������
*��������ֵ����
*����������
**************************************/
u8 CheckVoltageStatus(void)
{
	if (PWR_GetFlagStatus(PWR_FLAG_PVDO) != RESET)
	{
		//��ѹ���ڻ򳬳���ֵ
		return 1;
	}
	else
	{
		return 0;
	}
}


















