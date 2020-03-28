#ifndef __LQ_CONTROL_H
#define __LQ_CONTROL_H

#include "PID.h"


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
void Control_Motor(int16_t velocity_left, int16_t velocity_right);


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
void Control_Servo(short angle);  


extern _pid_param_t  Motor_left_pid;
extern _pid_param_t  Motor_right_pid;
extern _pid_param_t  Servo_pid;


#endif