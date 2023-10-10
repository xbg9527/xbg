#ifndef _DGUS_H
#define _DGUS_H

#include "stm32f10x.h"                  // Device header

#define DGUS_write      0x82
#define DGUS_read       0x83
#define  STARTADDR      0x08010000






extern unsigned char disp_Shot_count_Total_Shot[];






void Dgus_82send_data(u8 addr_L,u8 addr_Data);              //������-������ʾ�������
void Dgus_82write_data(u8 addr_H,u8 addr_L,u8 *str);        //82дָ��
void Dgus_83read_data(u8 addr_H,u8 addr_L,u8 len);          //83��ָ��
void Clear_array(u8 *str);                                  //�������
u8* Change(u16 n);                                          //ʮ����תʮ������
void IAP_EraseSector(u8 page);                              //����ָ��ҳ
void IAP_Flash_ProgramHalfWord(u8 page,u8 add8, u16 dat);   //ָ��ҳд������
u16 IAP_Flash_ReadHalfWord(u8 page,u8 add8);                //��ȡָ��ҳ������
void Refresh_all_data_from_RAM(void);                       //����ȷ��
void display___One_Dose_Grade_Flow_Rate_Total_Shot(void);   //��ʾ���Ρ��ٶȡ��ܴ�
void disp_Shot_count_and_Total_Shot(void);                  //��ʾ��ǰ/�� ע�����

void Refresh_all_data_from_memory(void);
#endif
