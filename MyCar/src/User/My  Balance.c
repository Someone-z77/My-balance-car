
#include "include.h"


//  1ms�жϣ�����
//float dt=PIT_period;

//  �������ݣ�����

/*����1 ------------------------------------------ */ 
float x_gyro;//���ٶ�              // Angle_Calculate
float x_acc; //���ٶ�    
float g_fCarAngle;                //  Angle_Control

float ANGLE_CONTROL_P;           //P
float ANGLE_CONTROL_D;              //D
float ANGLE_CONTROL_OUT_MAX;
float ANGLE_CONTROL_OUT_MIN;        //�Ƕ�����޷�
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



void Hubu_Filter(float x_acc,float x_gyro)//�����˲�
{
   float angle;
   float k1;      //Ȩ��            
   float dt;
      angle+=x_gyro*dt;
      g_fCarAngle=k1*angle+(1-k1)*x_acc;
}

void Angle_Calculate(void)//�������
{
   
   
   ICM20602_Attitude_Read();
   
   Gyro_offset();//��������Ư

   //���ٶȼ�
   x_acc=asin(Attitude_data.acc_x)*180/pi;//�Ƕ� ��
   //������
   x_gyro=Attitude_data.gyro_x-Attitude_offset.gyro_x;//����-���ٶ� ��/s
   
   Hubu_Filter(x_acc,x_gyro);
  
}


void Angle_Control(void)//ֱ������
{
   float fValue; 

   fValue = g_fCarAngle*ANGLE_CONTROL_P + 
        x_gyro* ANGLE_CONTROL_D;            //  P & D
   
   if(fValue > ANGLE_CONTROL_OUT_MAX)             fValue = ANGLE_CONTROL_OUT_MAX;//�޷�
   else if(fValue < ANGLE_CONTROL_OUT_MIN)          fValue = ANGLE_CONTROL_OUT_MIN;
   
   g_fAngleControl_Out=fValue;
}



void Speed_Control(void)//�ٶȿ���
{
   float fValue; 

   fValue = g_fSpeedControlOut_New - g_fSpeedControlOut_Old; 
   
   g_fSpeedControl_Out = fValue * 
         (g_nSpeedControlPeriod+1) /90 + g_fSpeedControlOut_Old;
   
}

void SpeedControl_Output(void)//�ٶ����ƽ������
{
  
     
}



void Direction_Control(void)//�������
{
}
void DirectionControl_Output(void)//�������ƽ������
{
}




void Motor_Output(void)//������
{
}
void Motor_Speed_Out(void)//���PWM����
{
}
void Set_Motor_Voltage(void)//PWM���
{
}






