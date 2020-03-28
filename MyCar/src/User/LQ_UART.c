#include "include.h"
#include "LQ_UART.h"
#include "MK60_UART.h"
/*------------------------------------------------------------------------------------------------------
����    ����Test_Uart
����    �ܡ�����UART 
����    ������
���� �� ֵ����
��ʵ    ����Test_Uart(); //���Դ���
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_Uart(void)
{
    LED_Init();
    
    UART_Init(UART4, 115200);
    
    /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(UART4_RX_TX_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    NVIC_EnableIRQ(UART4_RX_TX_IRQn);			          //ʹ��UART4_RX_TX_IRQn���ж�
    
    uint8_t count = 0;
    while(1)
    {
        printf("���ڲ������� �� %d �δ�ӡ \n ", count++);
        UART_PutStr(UART4, "UART_PutStr is OK \n");
        LED_Reverse(0);
        delayms(1000);
    }
    
    
}
/*ɽ�����ݴ���*/
void vcan_sendware(char *buff)
{   
    UART_PutChar(UART4,0x03);
    UART_PutChar(UART4,0xfc);
    UART_PutChar(UART4,*buff);
    UART_PutChar(UART4,0xfc);
    UART_PutChar(UART4,0x03);
}

