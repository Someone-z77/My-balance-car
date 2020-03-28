#include "include.h"
#include "status.h"
#include "Scheduler.h"
#include "PID.h"
_pid_param_t  Motor_left_pid =      //���PID�����ṹ��
{
     ._kp             =  1.0 ,         //P
     ._ki             =  0.0 ,         //I
     ._kd             =  0.0 ,         //D
     ._imax           =  500 ,         //�����޷�
                                       
     ._pid_out_p      =   0,           //KP���
     ._pid_out_i      =   0,           //KI���
     ._pid_out_d      =   0,           //KD���
     ._pid_out        =   0,           //pid���
     
     ._integrator     =   0,           //����ֵ
     ._last_error     =   0,           //��һ�����
     ._last_derivative=   0,           //�ϴ�΢��
     ._last_t         =   0,           //�ϴ�ʱ��
     .scaler          =   100,         //���ű�

};
_pid_param_t  Motor_right_pid =      //���PID�����ṹ��
{
     ._kp             =  1.0 ,         //P
     ._ki             =  0.0 ,         //I
     ._kd             =  0.0 ,         //D
     ._imax           =  500 ,         //�����޷�
                                       
     ._pid_out_p      =   0,           //KP���
     ._pid_out_i      =   0,           //KI���
     ._pid_out_d      =   0,           //KD���
     ._pid_out        =   0,           //pid���
     
     ._integrator     =   0,           //����ֵ
     ._last_error     =   0,           //��һ�����
     ._last_derivative=   0,           //�ϴ�΢��
     ._last_t         =   0,           //�ϴ�ʱ��
     .scaler          =   100,         //���ű�

};
_pid_param_t  Servo_pid =               //�Ƕ�PID�����ṹ��  ����ֱ��������
{
     ._kp             =  12.0 ,
     ._ki             =   0.5 ,
     ._kd             =  0.02 ,
     ._imax           =   30  , 
     
     ._pid_out_p      =   0,  
     ._pid_out_i      =   0,  
     ._pid_out_d      =   0,  
     ._pid_out        =   0,
     
     ._integrator     =   0, 
     ._last_error     =   0, 
     ._last_derivative=   0,
     ._last_t         =   0,  
     .scaler          =   1,  

};

/**
  * @brief    C�����PID����
  *
  * @param    velocity_left  velocity_right  �������ٶ�ֵ
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/15 ������
  */
void Control_Motor(int16_t velocity_left, int16_t velocity_right) 
{

   
}


/**
  * @brief    �����ǿ���
  *
  * @param    angle �� �����ǽǶ�
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/15 ������
  */
void Control_Servo(short angle)
{

}







