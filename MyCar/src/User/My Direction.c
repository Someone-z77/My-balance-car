#include "include.h"


float g_fDirectionControl_Out; 
float Flag_circle1=0,Flag_circle2=0;
short pwmR,pwmL;
uint16_t  ADC_max[4]={0},ADC_min[4]={1000,1000,1000,1000};

float  left_value[2]={0},right_value[2]={0};
float  Direct_error[2]={0},Error;

/*--------------------------------------------------------------------*/
/*读取最大值，最小值，在赛道多处移动*/
void AD_max_min()//采集500次
{
   uint16_t ad_get[4]={0};
   int i=0,j=0;
   //for(j=0;j<2000;j++)
   //{
       ad_get[0]=ADC_Get(0);
       ad_get[1]=ADC_Get(1);
       ad_get[2]=ADC_Get(2);
       ad_get[3]=ADC_Get(3);   
      for(i=0;i<4;i++)
      {
          if(ad_get[i]>=ADC_max[i])
         {
            ADC_max[i]=ad_get[i];
         }        
      }
   //}
   //printf("max:  %d   %d   %d   %d\n  ",ADC_max[0],ADC_max[1],ADC_max[2],ADC_max[3]);
}

void Read_adc(void)
{    
     AD_max_min();
     uint16_t  AD_left[2]={0},AD_right[2]={0};
     /*左右水平电感采集 */
     AD_left[0]=ADC_Get(1);
     AD_right[0]=ADC_Get(2);
     /*左右竖直电感采集*/
     AD_left[1]=ADC_Get(0);
     AD_right[1]=ADC_Get(3);           //这里注意位置要对应！！！
    
     /*归一化=（测量值-最小值）/（最大值-最小值）*/
     //left_value[0]=(AD_left[0]-ADC_min[1])/(ADC_max[1]-ADC_min[1]);
     //left_value[1]=(AD_left[1]-ADC_min[0])/(ADC_max[0]-ADC_min[0]);
     //right_value[0]=(AD_right[0]-ADC_min[2])/(ADC_max[2]-ADC_min[2]);
     //right_value[1]=(AD_right[1]-ADC_min[3])/(ADC_max[3]-ADC_min[3]);
     /*归一化  最大值100，最小值1*/
     left_value[0]=AD_left[0]*100/ADC_max[1];
     left_value[1]=AD_left[1]*100/ADC_max[0];
     right_value[0]=AD_right[0]*100/ADC_max[2];
     right_value[1]=AD_right[1]*100/ADC_max[3];
     
     left_value[0]=(left_value[0]<1?1:left_value[0]);
     left_value[1]=(left_value[1]<1?1:left_value[1]);
     right_value[0]=(right_value[0]<1?1:right_value[0]);
     right_value[1]=(right_value[1]<1?1:right_value[1]);
     
     if((left_value[0]+right_value[0]!=0)&&(left_value[1]+right_value[1]!=0))//防止出现nan情况
     {
         /*差比和---水平*/
         Direct_error[0]=(left_value[0]-right_value[0])/(left_value[0]+right_value[0]);
         Direct_error[0]=(Direct_error[0]>1?1:Direct_error[0]);
         Direct_error[0]=(Direct_error[0]<-1?-1:Direct_error[0]);
         /*差比和---竖直*/
         Direct_error[1]=(left_value[1]-right_value[1])/(left_value[1]+right_value[1]);
         Direct_error[1]=(Direct_error[1]>1?1:Direct_error[1]);
         Direct_error[1]=(Direct_error[1]<-1?-1:Direct_error[1]);       
     }
     printf("%.2f  ",Direct_error[0]);
     printf("  %.2f\n",Direct_error[1] );
     
}
void Direction_Control(void)//方向控制
{
      Error=(0.4*Direct_error[1]+0.6*Direct_error[0])*500;
      pwmR=2500+Error;
      pwmL=3050-Error;
      MOTOR_Ctrl(1,pwmL);
      MOTOR_Ctrl(2,pwmR);
  
}
void DirectionControl_Output(void)//方向输出平滑函数
{
  
  
  
}

