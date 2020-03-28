#include "include.h"
#include "status.h"
#include "Scheduler.h"
#include "PID.h"
_pid_param_t  Motor_left_pid =      //电机PID参数结构体
{
     ._kp             =  1.0 ,         //P
     ._ki             =  0.0 ,         //I
     ._kd             =  0.0 ,         //D
     ._imax           =  500 ,         //积分限幅
                                       
     ._pid_out_p      =   0,           //KP输出
     ._pid_out_i      =   0,           //KI输出
     ._pid_out_d      =   0,           //KD输出
     ._pid_out        =   0,           //pid输出
     
     ._integrator     =   0,           //积分值
     ._last_error     =   0,           //上一次误差
     ._last_derivative=   0,           //上次微分
     ._last_t         =   0,           //上次时间
     .scaler          =   100,         //缩放比

};
_pid_param_t  Motor_right_pid =      //电机PID参数结构体
{
     ._kp             =  1.0 ,         //P
     ._ki             =  0.0 ,         //I
     ._kd             =  0.0 ,         //D
     ._imax           =  500 ,         //积分限幅
                                       
     ._pid_out_p      =   0,           //KP输出
     ._pid_out_i      =   0,           //KI输出
     ._pid_out_d      =   0,           //KD输出
     ._pid_out        =   0,           //pid输出
     
     ._integrator     =   0,           //积分值
     ._last_error     =   0,           //上一次误差
     ._last_derivative=   0,           //上次微分
     ._last_t         =   0,           //上次时间
     .scaler          =   100,         //缩放比

};
_pid_param_t  Servo_pid =               //角度PID参数结构体  用于直立环控制
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
void Control_Motor(int16_t velocity_left, int16_t velocity_right) 
{

   
}


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
void Control_Servo(short angle)
{

}







