/*-----------------------------------------------------------------------------------------------------
【平    台】龙邱K60核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年04月02日
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【编译平台】IAR 8.2
【功    能】测试线性CCD
【注意事项】
-------------------------------------------------------------
CCD接口
              
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
【函    数】Test_CCD
【功    能】CCD测试函数
【参    数】无
【返 回 值】无
【实    例】Test_CCD();
【注意事项】
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
		if(systime.get_time_ms() - now_time >= 50)                  //20帧
		{
			now_time = systime.get_time_ms();
			
			/* 采集ccd图像 */
			CCD_Collect(ccd_buf);
			
			/* 发送到上位机 */
			if(count++%5 == 0)
			{
				UART_PutChar(UART4,'T');
				for(uint8_t i=0; i<128; i++) 
				{
					UART_PutChar(UART4,(unsigned char)(ccd_buf[i]>>8)); //发送高8位
					UART_PutChar(UART4,(unsigned char)ccd_buf[i]);      //发送高低8位 
				}
			}
			
			/* OLED 显示 */
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
【函    数】CCD_Delayus
【功    能】CCD的延时函数，大概延时，
【参    数】us    ：    延时时间
【返 回 值】无
【实    例】CCD_Delayus(1);
【注意事项】
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
【函    数】CCD_Init
【功    能】初始化CCD
【参    数】无
【返 回 值】无
【实    例】CCD_Init(); 
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void CCD_Init(void) 
{
  GPIO_PinInit(CCD_CLK,GPO,1);  
  GPIO_PinInit(CCD_SI, GPO,1);
  ADC_Init(ADC0);
}

/*------------------------------------------------------------------------------------------------------
【函    数】CCD_Collect
【功    能】CCD采集函数
【参    数】p  ：  存放采集数据的首地址
【返 回 值】无
【实    例】uint16_t ccd_buf[128];
【实    例】CCD_Collect(ccd_buf); 
【注意事项】
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



