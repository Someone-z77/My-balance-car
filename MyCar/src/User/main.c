
#include "include.h" 
extern volatile uint8_t pit0_test_flag;
extern uint16_t ADC_max[4],ADC_min[4];
 
void main(void)
{   
	
      PLL_Init(PLL180);
      NVIC_SetPriorityGrouping(0x07 - 2); //4个抢占优先级 4个子优先级 
      
      Motor_Enc_Init();
      
      Init_Uart_andexit();//串口4和中断配置
      
      FLASH_Init(); //Flash初始化，可提到主函数之前
      
      LED_Init();
      KEY_Init();
      ExtiKEY_Init();
      
      PIT_exitInit(0,5,1,2);//pit0,定时5ms的（1,2）级中断
      PIT_TimeStart(PIT1);//作为计数器初始化pit1
      
      ADC_Init(ADC0);
      ADC_Init(ADC1);
      
      
   ////////////pid参数每次从flash读取，方便调试/////////////   
  //按PTB20
  float k_pid_temp[K_SUM]={0};
      /* 从倒数第1个扇区 0偏移位置开始 读出数据 */
  FLASH_ReadBuff(2, 0, sizeof(k_pid_temp), (char *)k_pid_temp);
        char  txt[20]={' '};
  for (int i=0;i<K_SUM;i++)
  {
    sprintf((char*)txt,"k%d:%6.3f\n",i+1,k_pid_temp[i]);
    UART_PutStr(UART4,txt);  //显示写入后再读出的数据
  }
    PID_R.p=k_pid_temp[0];
    PID_R.i=k_pid_temp[1];
    PID_R.d=k_pid_temp[2];
    PID_L.p=k_pid_temp[3];
    PID_L.i=k_pid_temp[4];
    PID_L.d=k_pid_temp[5];
   //////////////////////////////////////////////////////////
    
    //初始化最大最小值，用法和pid参数读取一致，按PTB21
    
    FLASH_ReadBuff(3, 0, sizeof(ADC_max), (char *)ADC_max);
    FLASH_ReadBuff(3, sizeof(ADC_max)*8, sizeof(ADC_min), (char *)ADC_min);
   printf("max:  %d   %d   %d   %d\n  ",ADC_max[0],ADC_max[1],ADC_max[2],ADC_max[3]);
   printf("min:  %d   %d   %d   %d\n  ",ADC_min[0],ADC_min[1],ADC_min[2],ADC_min[3]);
 
   /////////////////////////////////////////////////////////
    
      while(1)
      {

        if(pit0_test_flag)
        {
          uint32_t time_t[2]={0};
          //PIT_Close(PIT1);//暂不确定是复位还是把定时器关了，个人认为是复位
          time_t[0]=PIT_TimeGet(PIT1);//初始时间，单位us
        
            pit0_test_flag = 0;
            Speed_PID();
            LED_Reverse(1);
            
         time_t[1]=PIT_TimeGet(PIT1);
         if( time_t[1]-time_t[0] >=5*1000 )//如果中间的程序执行时间大于5ms
         {
           printf("程序执行时间大于速度采样间隔，请调大采样间隔或对执行的程序进行优化\n");
         }
         
        }
        
      }
	
}                                                
