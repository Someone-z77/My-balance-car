
#include "include.h" 
extern volatile uint8_t pit0_test_flag;
extern uint16_t ADC_max[4],ADC_min[4];
 
void main(void)
{   
	
      PLL_Init(PLL180);
      NVIC_SetPriorityGrouping(0x07 - 2); //4����ռ���ȼ� 4�������ȼ� 
      
      Motor_Enc_Init();
      
      Init_Uart_andexit();//����4���ж�����
      
      FLASH_Init(); //Flash��ʼ�������ᵽ������֮ǰ
      
      LED_Init();
      KEY_Init();
      ExtiKEY_Init();
      
      PIT_exitInit(0,5,1,2);//pit0,��ʱ5ms�ģ�1,2�����ж�
      PIT_TimeStart(PIT1);//��Ϊ��������ʼ��pit1
      
      ADC_Init(ADC0);
      ADC_Init(ADC1);
      
      
   ////////////pid����ÿ�δ�flash��ȡ���������/////////////   
  //��PTB20
  float k_pid_temp[K_SUM]={0};
      /* �ӵ�����1������ 0ƫ��λ�ÿ�ʼ �������� */
  FLASH_ReadBuff(2, 0, sizeof(k_pid_temp), (char *)k_pid_temp);
        char  txt[20]={' '};
  for (int i=0;i<K_SUM;i++)
  {
    sprintf((char*)txt,"k%d:%6.3f\n",i+1,k_pid_temp[i]);
    UART_PutStr(UART4,txt);  //��ʾд����ٶ���������
  }
    PID_R.p=k_pid_temp[0];
    PID_R.i=k_pid_temp[1];
    PID_R.d=k_pid_temp[2];
    PID_L.p=k_pid_temp[3];
    PID_L.i=k_pid_temp[4];
    PID_L.d=k_pid_temp[5];
   //////////////////////////////////////////////////////////
    
    //��ʼ�������Сֵ���÷���pid������ȡһ�£���PTB21
    
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
          //PIT_Close(PIT1);//�ݲ�ȷ���Ǹ�λ���ǰѶ�ʱ�����ˣ�������Ϊ�Ǹ�λ
          time_t[0]=PIT_TimeGet(PIT1);//��ʼʱ�䣬��λus
        
            pit0_test_flag = 0;
            Speed_PID();
            LED_Reverse(1);
            
         time_t[1]=PIT_TimeGet(PIT1);
         if( time_t[1]-time_t[0] >=5*1000 )//����м�ĳ���ִ��ʱ�����5ms
         {
           printf("����ִ��ʱ������ٶȲ����������������������ִ�еĳ�������Ż�\n");
         }
         
        }
        
      }
	
}                                                
