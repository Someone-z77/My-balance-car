/*-----------------------------------------------------------------------------------------------------
【平    台】龙邱K60核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年04月02日
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【编译平台】IAR 8.2
【功    能】
【注意事项】
-------------------------------------------------------------------------------------------------------*/
#include "include.h"

/*------------------------------------------------------------------------------------------------------
【函    数】LED_Init
【功    能】初始化核心板和母板上的LED
【参    数】无
【返 回 值】无
【实    例】LED_Init(); //初始化LED
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void KEY_Init(void)
{
    /* 初始化母板上的KEY */
   GPIO_PinInit(PTB20, GPI_UP, 1);
   GPIO_PinInit(PTB21, GPI_UP, 1);
   GPIO_PinInit(PTB22, GPI_UP, 1);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】按键处理函数
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】0：无按键按下 1：按键1按下  2:按键2按下  3:按键3按下
【参数值】mode:0,不支持连续按;1,支持连续按;
【例子  】KEY_Read(0);   //检测三个按键哪个按下
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //按键松开标志
    if(mode==1) 
    {
      key_up=1;      //支持连按
    }
    if(key_up && (GPIO_PinRead(PTB20)==0 || GPIO_PinRead(PTB21)==0) || GPIO_PinRead(PTB22)==0)
    {
      delayms(100);   //消抖
      key_up=0;
      if(GPIO_PinRead(PTB20)==0)      
      {
          return 1;
      }
      
      else if(GPIO_PinRead(PTB21)==0) 
      {
          return 2;    
      }
      
      else if(GPIO_PinRead(PTB22)==0) 
      {
          return 3;    
      }
      
    }
    if(GPIO_PinRead(PTB20)==1 && GPIO_PinRead(PTB21)==1 && GPIO_PinRead(PTB22)==1) 
    {
     key_up=1;   
    }
    return 0;   //无按键按下
     
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】测试按键  
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_KEY(void)
{ 
    LED_Init();
    KEY_Init(); 
    while (1)
    {  
        //测试按键      

        switch(KEY_Read(1))  //
        {
            case 1:
                LED_Reverse(0);
                break;           
            case 2:      
                LED_Reverse(1);
                break;
            case 3:      
                LED_Reverse(2);
                break;
            default:
                LED_Reverse(3);
                break;
        }
        //延时
        delayms(50);
    }
}

//------------------------------------------------------------------------------------------------    
//全局变量  用于测试按键外部中断
//------------------------------------------------------------------------------------------------ 
volatile uint8_t key_exti_flag = 3;
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】测试按键  
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_ExtiKEY(void)
{ 
    LED_Init();
    
    /* 内部上拉 下降沿触发中断 中断服务函数在 IRQ_Handler.c */
    GPIO_ExtiInit(PTB20, falling_up);
    GPIO_ExtiInit(PTB21, falling_up);
    GPIO_ExtiInit(PTB22, falling_up);
    
    /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(PORTB_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    NVIC_EnableIRQ(PORTB_IRQn);			         //使能PORTB_IRQn的中断  
    while (1)
    {  
        //测试按键      

        switch(key_exti_flag)  //
        {
            case 1:
                LED_Reverse(0);
                break;           
            case 2:      
                LED_Reverse(1);
                break;
            case 3:      
                LED_Reverse(2);
                break;
            default:
                LED_Reverse(3);
                break;
        }
        //延时
        delayms(50);
    }
}