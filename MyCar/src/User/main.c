
#include "include.h" 
void main(void)
{   
	
      PLL_Init(PLL180);
      NVIC_SetPriorityGrouping(0x07 - 2); //4����ռ���ȼ� 4�������ȼ� 
      Motor_Enc_Init();
      UART_Init(UART4, 115200);
      ADC_Init(ADC0);
      ADC_Init(ADC1);
      //PIT0_IRQHandler();
      AD_max();
      AD_min();
      while(1)
      {
        Read_adc();
        //AD_Get_Go();
      }
	
}                                                
