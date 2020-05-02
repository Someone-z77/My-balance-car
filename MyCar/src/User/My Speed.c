#include "include.h" 


int16 Left_pulse,Right_pluse;
float g_Lspeed=0,g_Rspeed=0;//编码器脉冲
int16 g_RealSpd_R=0,g_RealSpd_L=0;//测量速度
int16 g_ExpectSpd_R=900,g_ExpectSpd_L=0;//期望速度   记得初始化
int16 Speed_out_R,Speed_out_L;//pid之后的输出ort

Speed_pid  PID;
 
float g_fSpeedControlOut_New;            //  SpeedControl_Output
float g_fSpeedControlOut_Old;
float g_nSpeedControlPeriod;
float g_fSpeedControl_Out;



/*---------------------------------------------------------*/
void Get_speed()//速度获取
{
          //MOTOR_Ctrl(1,2500);
          //MOTOR_Ctrl(2,2500);
     //Left_pulse = FTM_ABGet(FTM1);
     //Right_pluse = -FTM_ABGet(FTM2);//注意这里的正负
      g_RealSpd_R = -FTM_ABGet(FTM2);
          delayms(100);
          
    // 先来一个小小的滤波
     //g_Lspeed = 0.3*Left_pulse +0.7*g_Lspeed;
     //g_Rspeed = 0.3*R/ght_pluse  +0.7*g_Rspeed;
     
     //g_RealSpd_L=0.4*g_RealSpd_L+0.6*g_Lspeed;
     //g_RealSpd_R=0.4*g_RealSpd_R+0.6*g_Rspeed;
       
}
void Speed_PID()//pid控制速度   ---位置式
{
     int16  pwm_shuchu=0;
     //
     PID.error_old = PID.error_new;
     PID.error_new =  g_ExpectSpd_R-g_RealSpd_R;
     PID.integral+=PID.error_new;
     
     pwm_shuchu = PID.p*PID.error_new+PID.i*PID.integral+PID.d*(PID.error_new-PID.error_old);//积分限幅
     //输出pwm吧
     MOTOR_Ctrl(2,pwm_shuchu);
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




