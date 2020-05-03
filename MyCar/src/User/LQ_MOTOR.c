/*-----------------------------------------------------------------------------------------------------

FTM0输出PWM信号控制电机例子

-------------------------------------------------------------------------------------------------------*/
#include "include.h"
#include "LQ_MOTOR.h"


/*---------------------------------------------------------------------------------------------------
MOTOR_Ctrl()    (1,A,left)(2,B,right)
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
        break;
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
        break;
    }

}
/*------------------------------------------------------------------------------------------------------
Motor_Enc_Init()
--------------------------------------------------------------------------------------------------------*/
void Motor_Enc_Init()//电机，编码器一起初始化
{
    FTM_PwmInit(FTM0, FTM_CH0, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH1, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH2, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH3, 12000, 0);
    
    FTM_ABInit(FTM1);
    FTM_ABInit(FTM2);
}
void Test_Enc(void)
{
    
    FTM_PwmInit(FTM0, FTM_CH0, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH1, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH2, 12000, 0);
    FTM_PwmInit(FTM0, FTM_CH3, 12000, 0);
    FTM_ABInit(FTM1);
    FTM_ABInit(FTM2);
    short speed1, speed2;
    while(1)
    {
      MOTOR_Ctrl(1,3000);
      MOTOR_Ctrl(2,2500);
        speed1 = FTM_ABGet(FTM1);
        speed2 = FTM_ABGet(FTM2);
        
        printf("\r\n/ENC1 %5d \r\n ",speed1);
        
        printf("\r\n/ENC2 %5d \r\n ",speed2);
        delayms(100);
         
    }

}
