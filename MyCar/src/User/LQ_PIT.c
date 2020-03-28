#include "include.h"
#include "LQ_PIT.h"


//------------------------------------------------------------------------------------------------    
//ȫ�ֱ���  ���ڲ���PIT��ʱ��
//------------------------------------------------------------------------------------------------ 
volatile uint8_t pit0_test_flag;
volatile uint8_t pit1_test_flag;
volatile uint8_t pit2_test_flag;
volatile uint8_t pit3_test_flag;


/*------------------------------------------------------------------------------------------------------
����    ����Test_PIT
����    �ܡ�����PIT��ʱ��
����    ������
���� �� ֵ����
��ʵ    ����Test_PIT(); //����PIT��ʱ��
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_PIT(void)
{
    LED_Init();
    
    PIT_Init(PIT0,   5);       //��ʾ������A17Ƶ�� 100Hz ���ڲ���PIT��ʱ���Ƿ�׼ȷ
    PIT_Init(PIT1, 100);
    PIT_Init(PIT2, 200);
    PIT_Init(PIT3, 300);
    
    /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    /* ���ȼ����� ��ռ���ȼ�0  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    
    /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(PIT3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    NVIC_EnableIRQ(PIT0_IRQn);			          //ʹ��PIT0_IRQn���ж�
    NVIC_EnableIRQ(PIT1_IRQn);			          //ʹ��PIT1_IRQn���ж�
    NVIC_EnableIRQ(PIT2_IRQn);			          //ʹ��PIT2_IRQn���ж�
    NVIC_EnableIRQ(PIT3_IRQn);			          //ʹ��PIT3_IRQn���ж�
       
    while(1)
    {
        if(pit0_test_flag)
        {
            pit0_test_flag = 0;
            LED_Reverse(0);
        }
        if(pit1_test_flag)
        {
            pit1_test_flag = 0;
            LED_Reverse(1);
        }
        if(pit2_test_flag)
        {
            pit2_test_flag = 0;
            LED_Reverse(2);
        }
        if(pit3_test_flag)
        {
            pit3_test_flag = 0;
            LED_Reverse(3);
        }
    
    }

}

            
/*------------------------------------------------------------------------------------------------------
����    ����Test_PitTimer
����    �ܡ�����PIT��ʱ����ʱ����
����    ������
���� �� ֵ����
��ʵ    ����Test_PIT(); //����PIT��ʱ��
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_PitTimer(void)
{
    LED_Init();
    
    PIT_TimeStart(PIT0);       //��ʾ������A17Ƶ�� 100Hz ���ڲ���PIT��ʱ���Ƿ�׼ȷ
    
    uint32_t nowtime = PIT_TimeGet(PIT0);
    while(1)
    {
        if(PIT_TimeGet(PIT0) >= 5000)
        {
      
            LED_Reverse(0);
            PIT_TimeStart(PIT0);    
        }
      
    }

}

