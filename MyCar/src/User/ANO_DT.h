#ifndef __ANO_DT_H
#define __ANO_DT_H
#include "include.h" 

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�Z
������˵�������Դ�����������λ���ϻ�������
������汾��V1.0
�������¡�2018��10��18�� 
����������
������ֵ����
������ֵ����  
��ʵ���� Test_ANO();
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_ANO(void);

void ANO_DT_send_int16(short data1, short data2, short data3, short data4, short data5, short data6, short data7, short data8 /*,short data7, short data8, short .....�ɸ�����Ҫ������� */);
void ANO_DT_Send_PID(uint8_t group,float p1_p,float p1_i,float p1_d,float p2_p,float p2_i,float p2_d,float p3_p,float p3_i,float p3_d);
void ANO_DT_Data_Receive_Prepare(uint8_t data);


#endif