#include "include.h" 



int16 g_RealSpd_R=0,g_RealSpd_L=0;//测量速度
int16 g_ExpectSpd_R=0,g_ExpectSpd_L=0;//期望速度   记得初始化
int16  PWM_R_out=0,PWM_L_out=0;

Speed_pid  PID_R;
Speed_pid  PID_L;
 
float g_fSpeedControlOut_New;            //  SpeedControl_Output
float g_fSpeedControlOut_Old;
float g_nSpeedControlPeriod;
float g_fSpeedControl_Out;



/*---------------------------------------------------------*/
void Get_speed()//速度获取
{
      g_RealSpd_L = FTM_ABGet(FTM1);
      g_RealSpd_R = -FTM_ABGet(FTM2);
      
          delayms(100);
       
}
void Speed_PID()//pid控制速度   ---位置式
{
     
     g_ExpectSpd_R=700+g_Dirction_pwm*300;
     g_ExpectSpd_L=700-g_Dirction_pwm*300;
     
     /*   右轮pid及输出  */
     PID_R.error_old = PID_R.error_new;
     PID_R.error_new =  g_ExpectSpd_R-g_RealSpd_R;
     PID_R.integral+=PID_R.error_new;
     
     PWM_R_out= PID_R.p*PID_R.error_new+PID_R.i*PID_R.integral+PID_R.d*(PID_R.error_new-PID_R.error_old);//积分限幅
     
     /*   左轮pid及输出  */
     PID_L.error_old = PID_L.error_new;
     PID_L.error_new =  g_ExpectSpd_L-g_RealSpd_L;
     PID_L.integral+=PID_L.error_new;
     
     PWM_L_out= PID_L.p*PID_L.error_new+PID_L.i*PID_L.integral+PID_L.d*(PID_L.error_new-PID_L.error_old);
     
     MOTOR_Ctrl(2,PWM_R_out);
     MOTOR_Ctrl(1,PWM_L_out);
     Send(g_ExpectSpd_R,g_RealSpd_R);
     Send(g_ExpectSpd_L,g_RealSpd_L);

}

void Speed_Control()//速度控制
{
     MOTOR_Ctrl(2,PWM_R_out);
     MOTOR_Ctrl(1,PWM_L_out);
     Send(g_ExpectSpd_R,g_RealSpd_R);
     Send(g_ExpectSpd_L,g_RealSpd_L);
  
}

void SpeedControl_Output(void)//速度输出平滑函数
{
   //这个不会写  
      float fValue; 

   fValue = g_fSpeedControlOut_New - g_fSpeedControlOut_Old; 
   
   g_fSpeedControl_Out = fValue * 
         (g_nSpeedControlPeriod+1) /90 + g_fSpeedControlOut_Old;
   
}




