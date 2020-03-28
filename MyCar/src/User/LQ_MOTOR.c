/*-----------------------------------------------------------------------------------------------------
【平    台】龙邱K60核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年04月02日
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【编译平台】IAR 8.2
【功    能】FTM0输出PWM信号控制电机例子
【注意事项】
-------------------------------------------------------------------------------------------------------*/
#include "include.h"
#include "LQ_MOTOR.h"


/*------------------------------------------------------------------------------------------------------
【函    数】Test_Motor
【功    能】FTM0输出PWM信号控制电机例子
【参    数】num  :  电机标号  用PTC1 和 PTC2控制电机1  用PTC3 和 PTC4控制电机2
【返 回 值】duty ： 占空比    范围 -FTM_PRECISON  到 +FTM_PRECISON
【实    例】Test_Motor(); //测试电机
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void MOTOR_Ctrl(uint8_t num, short duty)
{
    if(abs(duty) > FTM_PRECISON)     //防止占空比给错
    {
        duty = 0;
    }
    switch(num)
    {
      case 1:
        if(duty > 0)
        {
            FTM_PwmDuty(FTM0, FTM_CH0, duty);
            FTM_PwmDuty(FTM0, FTM_CH1, 0);
        }
        else
        {
            FTM_PwmDuty(FTM0, FTM_CH0, 0);
            FTM_PwmDuty(FTM0, FTM_CH1, -duty);
        }
      case 2:
        if(duty > 0)
        {
            FTM_PwmDuty(FTM0, FTM_CH2, duty);
            FTM_PwmDuty(FTM0, FTM_CH3, 0);
        }
        else
        {
            FTM_PwmDuty(FTM0, FTM_CH2, 0);
            FTM_PwmDuty(FTM0, FTM_CH3, -duty);
        }
        
    }

}
/*------------------------------------------------------------------------------------------------------
【函    数】Test_Motor
【功    能】FTM0输出PWM信号控制电机例子
【参    数】无
【返 回 值】无
【实    例】Test_Motor(); //测试电机
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void Test_Motor(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    FTM_PwmInit(FTM0, FTM_CH0, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH1, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH2, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH3, 12000, 0);
    printf("电机测试例程 \n");
    printf("第一次使用的同学，调试之前最好用示波器观察一下波形 \n");
    printf("这里使用12KHz的PWM信号控制 \n");
    printf("按下K0按键电机不动 \n");
    printf("按下K1按键电机向前加速 \n");
    printf("按下K2按键电机向后加速 \n");
    
    short duty = 0;
    while(1)
    {
        switch(KEY_Read(1))     
        {
          case 1:
            LED_Reverse(1); 
            duty = 0;
            MOTOR_Ctrl(1, duty);     //设置电机1的转速
            MOTOR_Ctrl(2, duty);     //设置电机2的转速
            break;           
          case 2: 
            LED_Reverse(2); 
            duty += 100;
            if(duty > FTM_PRECISON)  //防止duty超
            {
                duty = FTM_PRECISON;
            }
            MOTOR_Ctrl(1, duty);     //设置电机1的转速
            MOTOR_Ctrl(2, duty);     //设置电机2的转速
            break;
          case 3: 
            LED_Reverse(3); 
            duty -= 100;
            if(duty < -FTM_PRECISON)  //防止duty超
            {
                duty = -FTM_PRECISON;
            }
            MOTOR_Ctrl(1, duty);     //设置电机1的转速
            MOTOR_Ctrl(2, duty);     //设置电机2的转速
            break;
          default:
            
            break;
        }
        LED_Reverse(0);    
        delayms(100);
    }

}

/*------------------------------------------------------------------------------------------------------
【函    数】Test_Enc
【功    能】测试正交解码功能
【参    数】无
【返 回 值】无
【实    例】Test_Enc(); //测试正交解码功能
【注意事项】
--------------------------------------------------------------------------------------------------------*/
#ifdef LQ_OLED
void Test_Enc(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    FTM_ABInit(FTM1);
    FTM_ABInit(FTM2);
    printf("正交解码测试例程 \n");

    OLED_Init();
    OLED_CLS();
    
    OLED_P8x16Str(5,0,(uint8_t*)"LQ ENC Test"); 
    
    char txt[16];
    short speed1, speed2;
    while(1)
    {
        speed1 = FTM_ABGet(FTM1);
        speed2 = FTM_ABGet(FTM2);
        
        printf("\r\n/ENC1 %5d \r\n ",speed1);
        sprintf(txt,"enc1:%5d ",speed1);
        OLED_P8x16Str(20,2,(uint8_t*)txt);
        
        printf("\r\n/ENC2 %5d \r\n ",speed2);
        sprintf(txt,"enc2:%5d ",speed2);
        OLED_P8x16Str(20,4,(uint8_t*)txt);
        
        delayms(100);
    }

}
#else

void Test_Enc(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    FTM_ABInit(FTM1);
    FTM_ABInit(FTM2);
    printf("正交解码测试例程 \n");

    TFTSPI_Init(1);                 //LCD初始化  0:横屏  1：竖屏
    TFTSPI_CLS(u16BLUE);
    
    TFTSPI_P8X16Str(2, 0, "LQ ENC Test", u16RED, u16BLUE);
    
    char txt[16]; 
    short speed1, speed2;
    while(1)
    {
        speed1 = FTM_ABGet(FTM1);
        speed2 = FTM_ABGet(FTM2);
        
        printf("\r\n/ENC1 %5d \r\n ",speed1);
        sprintf(txt,"enc1:%5d ",speed1);
        TFTSPI_P8X16Str(2, 2, txt, u16RED, u16BLUE);
        
        printf("\r\n/ENC2 %5d \r\n ",speed2);
        sprintf(txt,"enc2:%5d ",speed2);
        TFTSPI_P8X16Str(2, 4, txt, u16RED, u16BLUE);
        
        delayms(100);
    }

}
#endif