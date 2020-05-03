#include "include.h"


float g_fDirectionControl_Out; 
float Flag_circle1=0,Flag_circle2=0;

float  left_value[2]={0},right_value[2]={0};
float Direct_error[2]={0};
/*--------------------------------------------------*/

uint16_t ADC_max[4]={0},ADC_min[4]={0};
float  Dir_shuiping_err[3]={0},Dir_shuzhi_err[3]={0};
float g_Dirction_pwm;
float Direct_out1,Direct_out2;

/*--------------------------------------------------------------------*/
/*读取最大值，最小值，在赛道多处移动*/
void AD_max_min()//采集500次
{

     int i=0,j=0;
     uint16_t ADC_max_temp[4]={0},ADC_min_temp[4]={0};
     uint16_t ad_get[4]={0};//没注意还是需要作为中介的作用
   
     for(i=0;i<4;i++)
        ADC_min_temp[i]=4048;//赋min初值
   
   ad_get[0]=ADC_Get(0);
   ad_get[1]=ADC_Get(1);
   ad_get[2]=ADC_Get(2);
   ad_get[3]=ADC_Get(3);
   printf("you have 1s for preparation");
   LPTMR_Delayms(1000);//准备时间1s
   printf("begin to shake your car");
   
   for(j=0;j<500;j++)
   {
     LPTMR_Delayms(4);//隔4ms取一次，总共500次，即在2s内左右晃完
      for(i=0;i<4;i++)
      {
          if(ad_get[i]>=ADC_max_temp[i])    
              ADC_max_temp[i]=ad_get[i];
          if(ad_get[i]<=ADC_min_temp[i])
              ADC_min_temp[i]=ad_get[i];
      }
   }
   
  //写入 ADC_max_temp，ADC_min_temp到倒数第三扇区
  FLASH_EraseSector(3);
  FLASH_WriteBuf(3,(uint8_t *)ADC_max_temp, sizeof(ADC_max_temp), 0);//写入扇区，sizeof(）加的很妙，应该是float储存内容不变，但函数内部每次按8b来放
  FLASH_WriteBuf(3,(uint8_t *)ADC_min_temp, sizeof(ADC_min_temp), 8*sizeof(ADC_max_temp));//写入扇区，sizeof(）加的很妙，应该是float储存内容不变，但函数内部每次按8b来放

 
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

void My_adc()
{
   uint16_t i=0,adc[4]={0};
   float  ADC_guiyi[4]={0},adc_value[4][3]={0};   
   
   /*  中值滤波 + 滑动滤波 + 均值滤波 + 归一化*/
   for(i=0;i<10;i++)
   {
     adc[0]+=ADC_Mid(ADC1,ADC1_SE10,ADC_10bit);
     adc[1]+=ADC_Mid(ADC1,ADC1_SE11,ADC_10bit);
     adc[2]+=ADC_Mid(ADC1,ADC1_SE12,ADC_10bit);
     adc[3]+=ADC_Mid(ADC1,ADC1_SE13,ADC_10bit);
   }

   for(i=0;i<4;i++)
   {         
     adc_value[i][2]=adc_value[i][1];       
     adc_value[i][1]=adc_value[i][0];
     adc_value[i][0]=ADC_guiyi[i]*100;//将精度调至0-100
     ADC_guiyi[i]=(adc[i]/10-ADC_min[i])/(ADC_max[i]-ADC_min[i]);//归一化
   }
   /*差比和*/
   for(i=0;i<3;i++)
   {
     
      Dir_shuiping_err[i]=(adc_value[1][i]-adc_value[2][i])/(adc_value[1][i]+adc_value[2][i]);
      Dir_shuiping_err[i]=(Dir_shuiping_err[i]>1?1:Dir_shuiping_err[i]);
      Dir_shuiping_err[i]=(Dir_shuiping_err[i]<-1?-1:Dir_shuiping_err[i]);
      
      Dir_shuzhi_err[i]=(adc_value[0][i]-adc_value[4][i])/(adc_value[0][i]+adc_value[4][i]);
      Dir_shuzhi_err[i]=(Dir_shuzhi_err[i]>1?1:Dir_shuzhi_err[i]);
      Dir_shuzhi_err[i]=(Dir_shuzhi_err[i]<-1?-1:Dir_shuzhi_err[i]);
      
   }
   
}

void Direction_Control(void)//方向控制
{
  
     /*      Direction_PD     PD控制    */
   Direct_out1=0.5*Dir_shuiping_err[0]+0.5*(Dir_shuiping_err[0]-Dir_shuiping_err[2]);
   Direct_out2=0.5*Dir_shuzhi_err[0]+0.5*(Dir_shuzhi_err[0]-Dir_shuzhi_err[2]);
   
   /*     设置水平与竖直的权重，不同赛道，权重不一    */
    
   g_Dirction_pwm=0.7*Direct_out1+0.3*Direct_out2; 
  
}

void DirectionControl_Output(void)//方向输出平滑函数
{
  
     
  
}

