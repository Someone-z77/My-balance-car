#include "include.h"
#include "LQ_PIT.h"


//------------------------------------------------------------------------------------------------    
//全局变量  用于测试PIT定时器
//------------------------------------------------------------------------------------------------ 
volatile uint8_t pit0_test_flag;
volatile uint8_t pit1_test_flag;
volatile uint8_t pit2_test_flag;
volatile uint8_t pit3_test_flag;

/*------------------------------------------------------------------------------------------------------
【函    数】PIT_exitInit
【功    能】初始化pitx的定时中断
【参    数】pitx：pit几，time_ms：定时长/ms,PreemptPriority;SubPriority:优先级
【返 回 值】无
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void PIT_exitInit(int pitx,uint32_t time_ms,uint32_t PreemptPriority, uint32_t SubPriority)
{
  switch(pitx)  //
  {
  case 0:
    PIT_Init(PIT0,time_ms);
    NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),PreemptPriority,SubPriority));
    NVIC_EnableIRQ(PIT0_IRQn);			          //使能PIT0_IRQn的中断
    break;
  case 1:
    PIT_Init(PIT1,time_ms);
    NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),PreemptPriority,SubPriority));
    NVIC_EnableIRQ(PIT1_IRQn);			          //使能PIT1_IRQn的中断
    break;  
  case 2:
    PIT_Init(PIT2,time_ms);
    NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),PreemptPriority,SubPriority));
    NVIC_EnableIRQ(PIT2_IRQn);			          //使能PIT2_IRQn的中断
    break;
  case 3:
    PIT_Init(PIT3,time_ms);
    NVIC_SetPriority(PIT3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),PreemptPriority,SubPriority));
    NVIC_EnableIRQ(PIT3_IRQn);			          //使能PIT3_IRQn的中断
    break;
  default:
    printf("PIT_exitInit 输入参数错误！");
    break;
  }
}

/*------------------------------------------------------------------------------------------------------
【函    数】Test_PIT
【功    能】测试PIT定时器
【参    数】无
【返 回 值】无
【实    例】Test_PIT(); //测试PIT定时器
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void Test_PIT(void)
{
    LED_Init();
    
    PIT_Init(PIT0,   5);       //用示波器测A17频率 100Hz 用于测试PIT定时器是否准确
    PIT_Init(PIT1, 100);
    PIT_Init(PIT2, 200);
    PIT_Init(PIT3, 300);
    
    /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    /* 优先级配置 抢占优先级0  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    
    /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(PIT3_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    NVIC_EnableIRQ(PIT0_IRQn);			          //使能PIT0_IRQn的中断
    NVIC_EnableIRQ(PIT1_IRQn);			          //使能PIT1_IRQn的中断
    NVIC_EnableIRQ(PIT2_IRQn);			          //使能PIT2_IRQn的中断
    NVIC_EnableIRQ(PIT3_IRQn);			          //使能PIT3_IRQn的中断
       
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
【函    数】Test_PitTimer
【功    能】测试PIT定时器计时功能
【参    数】无
【返 回 值】无
【实    例】Test_PIT(); //测试PIT定时器
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void Test_PitTimer(void)
{
    LED_Init();
    
    PIT_TimeStart(PIT0);       //用示波器测A17频率 100Hz 用于测试PIT计时器是否准确
    
    uint32_t nowtime = PIT_TimeGet(PIT0);//最大计时4294967295 + 90000000=47.721858833333333333333333333333 s
    while(1)
    {
        if(PIT_TimeGet(PIT0) >= 5000)
        {
      
            LED_Reverse(0);
            PIT_TimeStart(PIT0);    
        }
      
    }

}

