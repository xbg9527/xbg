#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "stm32f10x.h"                  // Device header



extern	u8 Menmory_number;
extern	u8 EN1_CHN0;
extern	u8 Set_Buzzer_off;
extern	u8 Injector_mode;  //ע��ģʽ
extern	u8 Syringe_type;       //ע������
extern	u8 Flow_rate;       //ע���ٶ�
extern	u8 Power_level;     //��ѹ�ȼ�
extern	u8 Suction_Ready;    //��ѹ״̬
extern	u8 Sub_menu;         //�Ӳ˵�
extern	u8 Sub_menu_data;   //�Ӳ˵�-��֧��
extern	u32 Syringe_volume;     //ע���ݻ�
extern	u8 Total_Shot;         //ע���ܴ���
extern	u8 Shot_count;
extern	u16 One_Dose;           //����ע����
extern	u8 One_Dose_Grade;     //
extern	u8 disp_Shot_count_Total_Shot_Team_selection;
extern	u8 disp_One_Dose[];   // 
extern	u8 disp_Total_Shot_ADJ[];      //

extern	u32 Specs;
extern	u32 R_Time;
extern	u32 L_Time;
extern	u16 Motor_Time;


















void Open_Init(void);                            //������ȡ����
void Motor_Sensor_coder_Error_check(void);       //�����Լ�
void Key_scanf(void);                            //����ɨ��
void Display_Init(void);                         //��ʼ��ʾ
void Error_check(void);


#endif
