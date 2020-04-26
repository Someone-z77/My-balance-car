#include "include.h" 



float g_Lspeed=0,g_Rspeed=0;//编码器脉冲
int16 g_RealSpd_R=0,g_RealSpd_L=0;//测量速度
int16 g_ExpectSpd_R=1000,g_ExpectSpd_L=0;//期望速度   记得初始化
int16 Speed_out_R,Speed_out_L;//pid之后的输出ort
struct // pid 结构体
{
    float error_old;
    float error_new;
    float integral;
    float p;
    float i;
    float d;
    
}PID={0,0,0,1,0,0};

 
float g_fSpeedControlOut_New;            //  SpeedControl_Output
float g_fSpeedControlOut_Old;
float g_nSpeedControlPeriod;
float g_fSpeedControl_Out;


/*------------------------------------------------------*/  
int16  read_CNT_R()//这里需要确定一下左右编码器对应的管jio
{
    short val;   
    val = FTM_CNT_REG(FTM2);    
    FTM_CNT_REG(FTM2) = 0;    //清空标志位         

    return val;
}
int16 read_CNT_L()
{
    short val;   
    val = FTM_CNT_REG(FTM1);    
    FTM_CNT_REG(FTM1) = 0;    //清空标志位         

    return val;
}
/*---------------------------------------------------------*/
void Get_speed()//速度获取
{
     short Left_pulse,Right_pluse;
          MOTOR_Ctrl(1,2500);
          MOTOR_Ctrl(2,2500);
     Left_pulse = FTM_ABGet(FTM1);
     Right_pluse = -FTM_ABGet(FTM2);//注意这里的正负
     //printf("\r\n/ENC1 %5d \r\n",Left_pulse);
     //printf("\r\n/ENC2 %5d \r\n",Right_pluse);
          delayms(100);
    // 先来一个小小的滤波
     g_Lspeed = 0.3*Left_pulse +0.7*g_Lspeed;
     g_Rspeed = 0.3*Right_pluse  +0.7*g_Rspeed;
     
     g_RealSpd_L=0.4*g_RealSpd_L+0.6*g_Lspeed;
     g_RealSpd_R=0.4*g_RealSpd_R+0.6*g_Rspeed;
       
}
void Speed_PID()//pid控制速度
{
     //
     PID.error_old = PID.error_new;
     PID.error_new =  g_ExpectSpd_R-g_RealSpd_R;
     PID.integral+=PID.error_new;
     
     g_ExpectSpd_R= PID.p*PID.error_new+PID.i*PID.integral+PID.d*(PID.error_new-PID.error_old);//积分限幅
     //输出pwm吧
     MOTOR_Ctrl(2,g_RealSpd_R);
     Send(g_ExpectSpd_R,g_RealSpd_R);

}

void Speed_Control()//速度控制
{
   
   
   
}

void SpeedControl_Output(void)//速度输出平滑函数
{
   //这个不会写  
      float fValue; 

   fValue = g_fSpeedControlOut_New - g_fSpeedControlOut_Old; 
   
   g_fSpeedControl_Out = fValue * 
         (g_nSpeedControlPeriod+1) /90 + g_fSpeedControlOut_Old;
   
}




