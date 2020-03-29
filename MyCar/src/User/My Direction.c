#include "include.h"


float g_fDirectionControl_Out;  

uint16_t  AD_left[3]=0,AD_right[3]=0;

float  Direct_error[3]=0;

/*--------------------------------------------------------------------*/
void Direction_Control(void)//方向控制
{
     /*左右水平电感采集 */
     AD_left[0]=ADC_Get(0);
     AD_left[1]=ADC_Get(1);
     AD_right[0]=ADC_Get(3);
     AD_right[1]=ADC_Get(4);           //这里注意位置要对应！！！
     
     /*左右竖直电感采集*/
     AD_left[2]=ADC_Get(2);
     AD_right[2]=ADC_Get(5);
     
     /*归一化=（测量值-最小值）/（最大值-最小值）*/
     
     
     /*差比和---水平*/
     Direct_error[0]=(float)(AD_left[0]-AD_right[0])/(AD_left[0]+AD_right[0]);
     Direct_error[1]=(float)(AD_left[1]-AD_right[1])/(AD_left[1]+AD_right[1]);
     
     /*差比和---竖直*/
     Direct_error[2]=(float)(AD_left[2]-AD_right[2])/(AD_left[2]+AD_right[2]);
     
     //if()
}
void DirectionControl_Output(void)//方向输出平滑函数
{
  
  
  
}

