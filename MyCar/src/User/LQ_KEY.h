#ifndef __LQ_KEY_H
#define __LQ_KEY_H

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵�������԰���  
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_KEY(void);


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵��������������
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ��0���ް������� 1������1����  2:����2����  3:����3����
������ֵ��mode:0,��֧��������;1,֧��������;
������  ��KEY_Read(0);   //������������ĸ�����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint8_t KEY_Read(uint8_t mode);


/*------------------------------------------------------------------------------------------------------
����    ����LED_Init
����    �ܡ���ʼ�����İ��ĸ���ϵ�LED
����    ������
���� �� ֵ����
��ʵ    ����LED_Init(); //��ʼ��LED
��ע�����
--------------------------------------------------------------------------------------------------------*/
void KEY_Init(void);



/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵�������԰����ⲿ�ж�  
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_ExtiKEY(void);
#endif