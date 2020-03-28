
#include "include.h"
#include "LQ_SYSTICK.h"

/*------------------------------------------------------------------------------------------------------
����    ����Test_Systick
����    �ܡ�����systick��ʱ��
����    ������
���� �� ֵ����
��ʵ    ����Test_Systick(); //����systick��ʱ��
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_Systick(void)
{
    LED_Init();                          //LED��ʼ��
    systime.init();                      //����systick��ʱ��
    uint64_t nowtime = 0;
    nowtime = systime.get_time_us();
    while(1)
    {
        
        if(systime.get_time_us() - nowtime >= 5000)
        {
            LED_Reverse(0);             //��ʾ������A17Ƶ�� 100Hz ���ڲ���PIT��ʱ���Ƿ�׼ȷ
            nowtime = systime.get_time_us();
        }
    }
    
}