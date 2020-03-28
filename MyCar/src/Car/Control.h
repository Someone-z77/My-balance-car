#ifndef __LQ_CONTROL_H
#define __LQ_CONTROL_H

#include "PID.h"


/**
  * @brief    C车电机PID控制
  *
  * @param    velocity_left  velocity_right  编码器速度值
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/15 星期三
  */
void Control_Motor(int16_t velocity_left, int16_t velocity_right);


/**
  * @brief    舵机打角控制
  *
  * @param    angle ： 舵机打角角度
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/15 星期三
  */
void Control_Servo(short angle);  


extern _pid_param_t  Motor_left_pid;
extern _pid_param_t  Motor_right_pid;
extern _pid_param_t  Servo_pid;


#endif