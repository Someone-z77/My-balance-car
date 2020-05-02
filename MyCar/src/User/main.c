
#include "include.h" 
void main(void)
{   
	
      PLL_Init(PLL180);
      NVIC_SetPriorityGrouping(0x07 - 2); //4个抢占优先级 4个子优先级 
      
      Motor_Enc_Init();
      
      Test_Uart();
      
      KEY_Init();
      Test_ExtiKEY();
      
      ADC_Init(ADC0);
      ADC_Init(ADC1);
      
      //PIT_Init(PIT0,   5);
      //PIT_TimeStart(PIT0);
      /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
      //NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
      //PIT0_IRQHandler();
      
      while(1)
      {
         //AD_Get_Go();
         //Read_adc();       
         //Direction_Control();
        switch(KEY_Read(1))  //
        {
            case 1:
               LED_Reverse(0);              
               Parameter_Init();               
                break;           
            case 2: 
              LED_Reverse(1);
               Get_speed();
               Speed_PID();
                break;
            case 3:      
                LED_Reverse(2);
                AD_max_min();
                break;
            default:
                LED_Reverse(3);
                break;
        }
         
      }
	
}                                                
