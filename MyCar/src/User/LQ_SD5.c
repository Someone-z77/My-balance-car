/*-----------------------------------------------------------------------------------------------------
【平    台】龙邱K60核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年04月02日
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【编译平台】IAR 8.2
【功    能】测试CMT输出PWM控制SD5舵机
【注意事项】
-------------------------------------------------------------------------------------------------------*/
#include "include.h"
#include "LQ_SD5.h"


/*------------------------------------------------------------------------------------------------------
【函    数】Test_SD5
【功    能】测试CMT输出PWM控制SD5舵机
【参    数】无
【返 回 值】无
【实    例】Test_SD5(); //测试SD5舵机
【注意事项】注意，一定要对舵机打角进行限制
--------------------------------------------------------------------------------------------------------*/
void Test_SD5(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    CMT_PwmInit(50, 0);
    printf("SD5舵机测试例程 \n");
    printf("第一次使用舵机的同学，调试之前最好不要装车防止舵机卡死堵转烧坏 \n");
    printf("这里使用50Hz的PWM信号控制 \n");
    printf("使用1.5ms作为舵机的中值 \n");
    printf("按下K0按键舵机归中 \n");
    printf("按下K1按键舵机向左 \n");
    printf("按下K2按键舵机向右 \n");
    
    uint16_t duty = 75;
    while(1)
    {
        switch(KEY_Read(1))     
        {
          case 1:
            LED_Reverse(1); 
            duty = 75;
            CMT_PwmDuty(duty);     //50Hz 一个周期20ms  1.5 / 20 * CMT_PRECISON  = 75
            break;           
          case 2: 
            LED_Reverse(2); 
            duty ++;
            if(duty > 85)        //根据自己的实际情况对舵机打角进行限制，防止卡死
            {
                duty = 85;
            }
            CMT_PwmDuty(duty);
            break;
          case 3: 
            LED_Reverse(3); 
            duty --;
            if(duty < 65)        //根据自己的实际情况对舵机打角进行限制，防止卡死
            {
                duty = 65;
            }
            CMT_PwmDuty(duty);
            break;
          default:
            
            break;
        }
        LED_Reverse(0);    
        delayms(100);
    }

}

/*------------------------------------------------------------------------------------------------------
【函    数】Test_FTMSD5
【功    能】测试FTM输出PWM控制SD5舵机
【参    数】无
【返 回 值】无
【实    例】Test_FTMSD5(); //测试SD5舵机
【注意事项】注意，一定要对舵机打角进行限制
--------------------------------------------------------------------------------------------------------*/
void Test_FTMSD5(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    FTM_PwmInit(FTM3, FTM_CH6, 50, 0);
	FTM_PwmInit(FTM3, FTM_CH7, 50, 0);
    printf("SD5舵机测试例程 \n");
    printf("第一次使用舵机的同学，调试之前最好不要装车防止舵机卡死堵转烧坏 \n");
    printf("这里使用50Hz的PWM信号控制 \n");
    printf("使用1.5ms作为舵机的中值 \n");
    printf("按下K0按键舵机归中 \n");
    printf("按下K1按键舵机向左 \n");
    printf("按下K2按键舵机向右 \n");
    
    uint16_t duty = 750;
    while(1)
    {
        switch(KEY_Read(1))     
        {
          case 1:
            LED_Reverse(1); 
            duty = 750;
            FTM_PwmDuty(FTM3, FTM_CH6, duty);     //50Hz 一个周期20ms  1.5 / 20 * FTM_PRECISON  = 75
			FTM_PwmDuty(FTM3, FTM_CH7, duty);     //50Hz 一个周期20ms  1.5 / 20 * FTM_PRECISON  = 75
            break;           
          case 2: 
            LED_Reverse(2); 
            duty += 10;
            if(duty > 850)        //根据自己的实际情况对舵机打角进行限制，防止卡死
            {
                duty = 850;
            }
            FTM_PwmDuty(FTM3, FTM_CH6, duty); 
			FTM_PwmDuty(FTM3, FTM_CH7, duty); 
            break;
          case 3: 
            LED_Reverse(3); 
            duty -= 10;
            if(duty < 650)        //根据自己的实际情况对舵机打角进行限制，防止卡死
            {
                duty = 650;
            }
			FTM_PwmDuty(FTM3, FTM_CH6, duty); 
			FTM_PwmDuty(FTM3, FTM_CH7, duty); 
            break;
          default:
            
            break;
        }
        LED_Reverse(0);    
        delayms(100);
    }

}