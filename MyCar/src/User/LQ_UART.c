#include "include.h"
#include "LQ_UART.h"
#include "MK60_UART.h"

extern char u4_data[40];
extern int success_fg;


/*------------------------------------------------------------------------------------------------------
����    ����Test_Uart
����    �ܡ�����UART 
����    ������
���� �� ֵ����
��ʵ    ����Test_Uart(); //���Դ���
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Init_Uart_andexit(void)
{
    
    UART_Init(UART4, 115200);
    
    /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(UART4_RX_TX_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    NVIC_EnableIRQ(UART4_RX_TX_IRQn);			          //ʹ��UART4_RX_TX_IRQn���ж�
        
}

//ͨ����ϴ���4������ﵽ�޸Ĳ�����Ŀ��

//��Ҫ��ֵ����K_pid�У����ŵ�flash���ض�λ��

void Parameter_Init(void)

{

   int t_n;
float K_pid[K_SUM]={0};

  Label_restart:

  success_fg=0;//��0��������

  t_n=0;

  UART_PutStr(UART4,"input ");
  UART_PutChar(UART4,(char)(K_SUM+48));
  UART_PutStr(UART4," parameters :\n");
  UART_PutStr(UART4,"input K...A...E strings!\n");

  while(1)

    {
      if(success_fg==1) 
        break;
      LPTMR_delayus(10);
    }                  //�����ݴ���

  
  for (int i=0;i<40;i++)
    {
      if(u4_data[i]!=0) //�ҵ���ͷλ��
      {
        t_n=i;
        break;
      }
    }

  int fg_kind=0;//������С����־λ

  if(u4_data[t_n]!='K' && u4_data[t_n]!='k' )//��ͷ���ԣ��������

    {
       UART_PutStr(UART4,"�����������������\n");

       for(int i=0;i<40; i++)
          u4_data[i]=0;
         goto Label_restart;

     }

  else//��ȡ����k_pid

  {t_n++;//�Ƚ�һλ�����֣���������ĸ�ϣ�  

    for(int k=0;k<K_SUM;k++)//ִ��K_SUM��

    {

      int x_tp=-1;//����С���õģ�only��

      fg_kind=0;

      K_pid[k]=u4_data[t_n]-48;

      do

      {

          if(u4_data[t_n+1]=='.')

          {

          t_n++;

          fg_kind=1;

          }

          t_n++;

          if(fg_kind==0)

          {

              K_pid[k]=u4_data[t_n]-48+K_pid[k]*10;

          } 

          else

          {

              K_pid[k]+=(u4_data[t_n]-48)*pow(10,x_tp--);

          }

        

      }while(t_n<40 && u4_data[t_n+1]!='A' && u4_data[t_n+1]!='a' && u4_data[t_n+1]!='E' && u4_data[t_n+1]!='e' );

        

      if(t_n>=40)

      {

        UART_PutStr(UART4,"��ȡ��������������ȡ\n");

        for(int i=0;i<40; i++)

          u4_data[i]=0;

        goto Label_restart;

      }

      else if(u4_data[t_n+1]=='E' || u4_data[t_n+1]=='e' )

      {

      UART_PutStr(UART4,"��ȡ�����ɹ�\n");  

      break;

      }

      t_n+=2;

    }

  }


  FLASH_EraseSector(2);

  FLASH_WriteBuf(2,(uint8_t *)K_pid, sizeof(K_pid), 0);//д��������sizeof(���ӵĺ��Ӧ����float�������ݲ��䣬�������ڲ�ÿ�ΰ�8b����


}
