#include "include.h" 


int16 Left_pulse,Right_pluse;
float g_Lspeed=0,g_Rspeed=0;//编码器脉冲
float g_RealSpd=0;//测量速度
float g_ExpectSpd=0;//期望速度   记得初始化
float Speed_out;//pid之后的输出

struct // pid 结构体
{
    float error_old;
    float error_new;
    float integral;
    float p;
    float i;
    float d;
    
}PID;

 
float g_fSpeedControlOut_New;            //  SpeedControl_Output
float g_fSpeedControlOut_Old;
float g_nSpeedControlPeriod;
float g_fSpeedControl_Out;


/*------------------------------------------------------*/  
int16  read_CNT_R()//这里需要确定一下左右编码器对应的管jio
{
    short val;   
    val = FTM_CNT_REG(FTM1);    
    FTM_CNT_REG(FTM1) = 0;    //清空标志位         

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
     Left_pulse = read_CNT_L();
     Right_pluse = read_CNT_R();
     
     //先来一个小小的滤波
     g_Lspeed = 0.3*Left_pulse +0.7*g_Lspeed;
     g_Rspeed = 0.3*Right_pluse  +0.7*g_Rspeed;
     
     //接下来是计算速度,也有一个小小的滤波
     g_RealSpd=0.1*g_RealSpd+0.3*(g_Lspeed+g_Rspeed)*0.5;//这后面少了一系列的数！！！
       
}
void Speed_PID()//pid控制速度
{
     //
     PID.error_old = PID.error_new;
     PID.error_new =  g_ExpectSpd-g_RealSpd;
     PID.integral+=PID.error_new;
     
     Speed_out= PID.p*PID.error_new+PID.i*PID.integral+PID.d*(PID.error_new-PID.error_old);
     //输出pwm吧
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




