#ifndef _DGUS_H
#define _DGUS_H

#include "stm32f10x.h"                  // Device header

#define DGUS_write      0x82
#define DGUS_read       0x83
#define  STARTADDR      0x08010000






extern unsigned char disp_Shot_count_Total_Shot[];






void Dgus_82send_data(u8 addr_L,u8 addr_Data);              //迪文屏-发送显示变量编号
void Dgus_82write_data(u8 addr_H,u8 addr_L,u8 *str);        //82写指令
void Dgus_83read_data(u8 addr_H,u8 addr_L,u8 len);          //83读指令
void Clear_array(u8 *str);                                  //清空数组
u8* Change(u16 n);                                          //十进制转十六进制
void IAP_EraseSector(u8 page);                              //擦除指定页
void IAP_Flash_ProgramHalfWord(u8 page,u8 add8, u16 dat);   //指定页写入数据
u16 IAP_Flash_ReadHalfWord(u8 page,u8 add8);                //读取指定页的数据
void Refresh_all_data_from_RAM(void);                       //参数确认
void display___One_Dose_Grade_Flow_Rate_Total_Shot(void);   //显示单次、速度、总次
void disp_Shot_count_and_Total_Shot(void);                  //显示当前/总 注射次数

void Refresh_all_data_from_memory(void);
#endif
