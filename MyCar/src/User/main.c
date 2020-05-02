
#include "include.h" 
void main(void)
{   
	
      PLL_Init(PLL180);
      NVIC_SetPriorityGrouping(0x07 - 2); //4����ռ���ȼ� 4�������ȼ� 
      
      Motor_Enc_Init();
      
      Test_Uart();
      
      KEY_Init();
      Test_ExtiKEY();
      
      ADC_Init(ADC0);
      ADC_Init(ADC1);
      
      //PIT_Init(PIT0,   5);
      //PIT_TimeStart(PIT0);
      /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
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
