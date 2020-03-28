
#include "include.h"
#include "LQ_SYSTICK.h"

/*------------------------------------------------------------------------------------------------------
【函    数】Test_Systick
【功    能】测试systick定时器
【参    数】无
【返 回 值】无
【实    例】Test_Systick(); //测试systick定时器
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void Test_Systick(void)
{
    LED_Init();                          //LED初始化
    systime.init();                      //开启systick定时器
    uint64_t nowtime = 0;
    nowtime = systime.get_time_us();
    while(1)
    {
        
        if(systime.get_time_us() - nowtime >= 5000)
        {
            LED_Reverse(0);             //用示波器测A17频率 100Hz 用于测试PIT计时器是否准确
            nowtime = systime.get_time_us();
        }
    }
    
}