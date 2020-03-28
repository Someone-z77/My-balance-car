/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ���������CCD
��ע�����
-------------------------------------------------------------
CCD�ӿ�
              
GND            GND 
VDD            5V
AO             ADC0_SE16 
CLK            PTE2        
SI             PTE3               
-------------------------------------------------------------
-------------------------------------------------------------------------------------------------------*/
#include "include.h"
#include "LQ_CCD.h"
#define CCD_A0   ADC0_SE16
#define CCD_CLK  PTE2
#define CCD_SI   PTE3

#define TSL_CLK  PTE2_OUT   //PTE2 
#define TSL_SI   PTE3_OUT   //PTE3


/*------------------------------------------------------------------------------------------------------
����    ����Test_CCD
����    �ܡ�CCD���Ժ���
����    ������
���� �� ֵ����
��ʵ    ����Test_CCD();
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_CCD(void)
{
	LED_Init();
    UART_Init(UART4, 115200);
	OLED_Init();
    OLED_CLS();
	CCD_Init();
	systime.init();
	
	OLED_P8x16Str(15,0,"LQ CCD Test"); 
    printf("\r\nLQ CCD Test");
	
	uint32_t now_time = systime.get_time_ms();
	uint16_t ccd_buf[128];
	static uint8_t count = 0;
	while(1)
	{
		if(systime.get_time_ms() - now_time >= 50)                  //20֡
		{
			now_time = systime.get_time_ms();
			
			/* �ɼ�ccdͼ�� */
			CCD_Collect(ccd_buf);
			
			/* ���͵���λ�� */
			if(count++%5 == 0)
			{
				UART_PutChar(UART4,'T');
				for(uint8_t i=0; i<128; i++) 
				{
					UART_PutChar(UART4,(unsigned char)(ccd_buf[i]>>8)); //���͸�8λ
					UART_PutChar(UART4,(unsigned char)ccd_buf[i]);      //���͸ߵ�8λ 
				}
			}
			
			/* OLED ��ʾ */
			if(count % 3 == 0)
			{
				for(uint8_t i=0; i<128; i++)
				{
					OLED_Set_Pos(i , 7); 
					if(ccd_buf[i] > 1500)	      			
						OLED_WrDat(0xFF);
					else
						OLED_WrDat(0x00);	
				}
			
			}	
			
		}
	}
}


/*------------------------------------------------------------------------------------------------------
����    ����CCD_Delayus
����    �ܡ�CCD����ʱ�����������ʱ��
����    ����us    ��    ��ʱʱ��
���� �� ֵ����
��ʵ    ����CCD_Delayus(1);
��ע�����
--------------------------------------------------------------------------------------------------------*/
void CCD_Delayus(uint8_t us)
{
  while(us--)
  {
    for(uint16_t i=0;i<50;i++)
	{
		 asm("nop");  
	}  
  }
}

/*------------------------------------------------------------------------------------------------------
����    ����CCD_Init
����    �ܡ���ʼ��CCD
����    ������
���� �� ֵ����
��ʵ    ����CCD_Init(); 
��ע�����
--------------------------------------------------------------------------------------------------------*/
void CCD_Init(void) 
{
  GPIO_PinInit(CCD_CLK,GPO,1);  
  GPIO_PinInit(CCD_SI, GPO,1);
  ADC_Init(ADC0);
}

/*------------------------------------------------------------------------------------------------------
����    ����CCD_Collect
����    �ܡ�CCD�ɼ�����
����    ����p  ��  ��Ųɼ����ݵ��׵�ַ
���� �� ֵ����
��ʵ    ����uint16_t ccd_buf[128];
��ʵ    ����CCD_Collect(ccd_buf); 
��ע�����
--------------------------------------------------------------------------------------------------------*/
void CCD_Collect(uint16_t *p) 
{
	unsigned char i;
	unsigned int  temp = 0;

	TSL_SI=1;;             //SI  = 1 
	CCD_Delayus(1);
	TSL_CLK = 1;           // CLK = 1 
	CCD_Delayus(1);
	TSL_SI=0;              // SI  = 0 
	CCD_Delayus(1);

	for(i=0; i<128; i++) 
	{
		CCD_Delayus(1);
		TSL_CLK = 1;       // CLK = 1 
		CCD_Delayus(1);
		temp= ADC_Ave(ADC0, CCD_A0, ADC_12bit, 5);       
		*p++ = temp;     
		TSL_CLK = 0;       // CLK = 0 
	}
	CCD_Delayus(1);
	TSL_CLK = 1;           // CLK = 1 
	CCD_Delayus(1);
	TSL_CLK = 0;           // CLK = 0 
}



