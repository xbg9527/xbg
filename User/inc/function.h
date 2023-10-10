#ifndef _FUNCTION_H
#define _FUNCTION_H

#include "stm32f10x.h"                  // Device header



extern	u8 Menmory_number;
extern	u8 EN1_CHN0;
extern	u8 Set_Buzzer_off;
extern	u8 Injector_mode;  //注射模式
extern	u8 Syringe_type;       //注射类型
extern	u8 Flow_rate;       //注射速度
extern	u8 Power_level;     //负压等级
extern	u8 Suction_Ready;    //负压状态
extern	u8 Sub_menu;         //子菜单
extern	u8 Sub_menu_data;   //子菜单-分支数
extern	u32 Syringe_volume;     //注射容积
extern	u8 Total_Shot;         //注射总次数
extern	u8 Shot_count;
extern	u16 One_Dose;           //单次注射量
extern	u8 One_Dose_Grade;     //
extern	u8 disp_Shot_count_Total_Shot_Team_selection;
extern	u8 disp_One_Dose[];   // 
extern	u8 disp_Total_Shot_ADJ[];      //

extern	u32 Specs;
extern	u32 R_Time;
extern	u32 L_Time;
extern	u16 Motor_Time;


















void Open_Init(void);                            //开机读取参数
void Motor_Sensor_coder_Error_check(void);       //开机自检
void Key_scanf(void);                            //按键扫描
void Display_Init(void);                         //初始显示
void Error_check(void);


#endif
