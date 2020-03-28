
#include "include.h"


//  1ms中断？？？
//float dt=PIT_period;

//  参数传递？？？

/*变量1 ------------------------------------------ */ 
float x_gyro;//角速度              // Angle_Calculate
float x_acc; //加速度    
float g_fCarAngle;                //  Angle_Control

float ANGLE_CONTROL_P;           //P
float ANGLE_CONTROL_D;              //D
float ANGLE_CONTROL_OUT_MAX;
float ANGLE_CONTROL_OUT_MIN;        //角度输出限幅
/*-------------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------*/
float g_fSpeedControlIntegral;           //  Speed_Control
 
float g_fSpeedControlOut_New;            //  SpeedControl_Output
float g_fSpeedControlOut_Old;

float g_fDirectionControlOut_New;       //  DirectionControl_Output
float g_fDirectionControlOut_Old;

float g_fAngleControl_Out;
float g_fDirectionControl_Out;    //Motor_Output
float g_fSpeedControl_Out;

float g_fLeftMotorOut;
float g_fRightMotorOut;    //Motor_Speed_Out

float fLeftVoltage; 
float fRightVoltage;       //Set_Motor_Voltage

float g_nSpeedControlPeriod;
/**************************************************************/



void Hubu_Filter(float x_acc,float x_gyro)//互补滤波
{
   float angle;
   float k1;      //权重            
   float dt;
      angle+=x_gyro*dt;
      g_fCarAngle=k1*angle+(1-k1)*x_acc;
}

void Angle_Calculate(void)//计算倾角
{
   
   
   ICM20602_Attitude_Read();
   
   Gyro_offset();//陀螺仪零漂

   //加速度计
   x_acc=asin(Attitude_data.acc_x)*180/pi;//角度 °
   //陀螺仪
   x_gyro=Attitude_data.gyro_x-Attitude_offset.gyro_x;//俯仰-角速度 °/s
   
   Hubu_Filter(x_acc,x_gyro);
  
}


void Angle_Control(void)//直立控制
{
   float fValue; 

   fValue = g_fCarAngle*ANGLE_CONTROL_P + 
        x_gyro* ANGLE_CONTROL_D;            //  P & D
   
   if(fValue > ANGLE_CONTROL_OUT_MAX)             fValue = ANGLE_CONTROL_OUT_MAX;//限幅
   else if(fValue < ANGLE_CONTROL_OUT_MIN)          fValue = ANGLE_CONTROL_OUT_MIN;
   
   g_fAngleControl_Out=fValue;
}



void Speed_Control(void)//速度控制
{
   float fValue; 

   fValue = g_fSpeedControlOut_New - g_fSpeedControlOut_Old; 
   
   g_fSpeedControl_Out = fValue * 
         (g_nSpeedControlPeriod+1) /90 + g_fSpeedControlOut_Old;
   
}

void SpeedControl_Output(void)//速度输出平滑函数
{
  
     
}



void Direction_Control(void)//方向控制
{
}
void DirectionControl_Output(void)//方向输出平滑函数
{
}




void Motor_Output(void)//电机输出
{
}
void Motor_Speed_Out(void)//电机PWM计算
{
}
void Set_Motor_Voltage(void)//PWM输出
{
}






