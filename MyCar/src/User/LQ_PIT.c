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
����    ����PIT_exitInit
����    �ܡ���ʼ��pitx�Ķ�ʱ�ж�
����    ����pitx��pit����time_ms����ʱ��/ms,PreemptPriority;SubPriority:���ȼ�
���� �� ֵ����
��ע�����
--------------------------------------------------------------------------------------------------------*/
void PIT_exitInit(int pitx,uint32_t time_ms,uint32_t PreemptPriority, uint32_t SubPriority)
{
  switch(pitx)  //
  {
  case 0:
    PIT_Init(PIT0,time_ms);
    NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),PreemptPriority,SubPriority));
    NVIC_EnableIRQ(PIT0_IRQn);			          //ʹ��PIT0_IRQn���ж�
    break;
  case 1:
    PIT_Init(PIT1,time_ms);
    NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),PreemptPriority,SubPriority));
    NVIC_EnableIRQ(PIT1_IRQn);			          //ʹ��PIT1_IRQn���ж�
    break;  
  case 2:
    PIT_Init(PIT2,time_ms);
    NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),PreemptPriority,SubPriority));
    NVIC_EnableIRQ(PIT2_IRQn);			          //ʹ��PIT2_IRQn���ж�
    break;
  case 3:
    PIT_Init(PIT3,time_ms);
    NVIC_SetPriority(PIT3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),PreemptPriority,SubPriority));
    NVIC_EnableIRQ(PIT3_IRQn);			          //ʹ��PIT3_IRQn���ж�
    break;
  default:
    printf("PIT_exitInit �����������");
    break;
  }
}

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
    
    uint32_t nowtime = PIT_TimeGet(PIT0);//����ʱ4294967295 + 90000000=47.721858833333333333333333333333 s
    while(1)
    {
        if(PIT_TimeGet(PIT0) >= 5000)
        {
      
            LED_Reverse(0);
            PIT_TimeStart(PIT0);    
        }
      
    }

}

