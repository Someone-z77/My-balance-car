/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ�
��ע�����
-------------------------------------------------------------------------------------------------------*/
#include "include.h"

/*------------------------------------------------------------------------------------------------------
����    ����LED_Init
����    �ܡ���ʼ�����İ��ĸ���ϵ�LED
����    ������
���� �� ֵ����
��ʵ    ����LED_Init(); //��ʼ��LED
��ע�����
--------------------------------------------------------------------------------------------------------*/
void KEY_Init(void)
{
    /* ��ʼ��ĸ���ϵ�KEY */
   GPIO_PinInit(PTB20, GPI_UP, 1);
   GPIO_PinInit(PTB21, GPI_UP, 1);
   GPIO_PinInit(PTB22, GPI_UP, 1);
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵��������������
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ��0���ް������� 1������1����  2:����2����  3:����3����
������ֵ��mode:0,��֧��������;1,֧��������;
������  ��KEY_Read(0);   //������������ĸ�����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint8_t KEY_Read(uint8_t mode)
{
    static uint8_t key_up=1;     //�����ɿ���־
    if(mode==1) 
    {
      key_up=1;      //֧������
    }
    if(key_up && (GPIO_PinRead(PTB20)==0 || GPIO_PinRead(PTB21)==0) || GPIO_PinRead(PTB22)==0)
    {
      delayms(100);   //����
      key_up=0;
      if(GPIO_PinRead(PTB20)==0)      
      {
          return 1;
      }
      
      else if(GPIO_PinRead(PTB21)==0) 
      {
          return 2;    
      }
      
      else if(GPIO_PinRead(PTB22)==0) 
      {
          return 3;    
      }
      
    }
    if(GPIO_PinRead(PTB20)==1 && GPIO_PinRead(PTB21)==1 && GPIO_PinRead(PTB22)==1) 
    {
     key_up=1;   
    }
    return 0;   //�ް�������
     
}

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵�������԰���  
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_KEY(void)
{ 
    LED_Init();
    KEY_Init(); 
    while (1)
    {  
        //���԰���      

        switch(KEY_Read(1))  //
        {
            case 1:
                LED_Reverse(0);
                break;           
            case 2:      
                LED_Reverse(1);
                break;
            case 3:      
                LED_Reverse(2);
                break;
            default:
                LED_Reverse(3);
                break;
        }
        //��ʱ
        delayms(50);
    }
}

//------------------------------------------------------------------------------------------------    
//ȫ�ֱ���  ���ڲ��԰����ⲿ�ж�
//------------------------------------------------------------------------------------------------ 
volatile uint8_t key_exti_flag = 3;
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
����  �ߡ�LQ-005
������˵�������԰���  
������汾��V1.0
�������¡�2017��11��24�� 
����������
������ֵ����
������ֵ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_ExtiKEY(void)
{ 
    LED_Init();
    
    /* �ڲ����� �½��ش����ж� �жϷ������� IRQ_Handler.c */
    GPIO_ExtiInit(PTB20, falling_up);
    GPIO_ExtiInit(PTB21, falling_up);
    GPIO_ExtiInit(PTB22, falling_up);
    
    /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(PORTB_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    NVIC_EnableIRQ(PORTB_IRQn);			         //ʹ��PORTB_IRQn���ж�  
    while (1)
    {  
        //���԰���      

        switch(key_exti_flag)  //
        {
            case 1:
                LED_Reverse(0);
                break;           
            case 2:      
                LED_Reverse(1);
                break;
            case 3:      
                LED_Reverse(2);
                break;
            default:
                LED_Reverse(3);
                break;
        }
        //��ʱ
        delayms(50);
    }
}