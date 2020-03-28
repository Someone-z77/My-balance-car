/*---------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ�OV7725����
��ע�����
----------------------------------------------------------------*/
#include "include.h"

volatile uint8_t Image_Data[IMAGEH][IMAGEW];      //ͼ��ԭʼ���ݴ��
uint8_t Image_Use[LCDH][LCDW];           //ѹ����֮�����ڴ����Ļ��ʾ����
uint8_t Pixle[LCDH][LCDW];               //��ֵ��������OLED��ʾ������
volatile uint8_t  Line_Cont=0;                    //�м���
volatile uint8_t  Field_Over_Flag=0;              //����ʶ


/*---------------------------------------------------------------
����    ����PORTC_Interrupt
����    �ܡ�PORTC�˿ڵ��жϷ����� ��������ͷ�г��ж�
����    ������
���� �� ֵ����
��ע�����ע������Ҫ����жϱ�־λ
----------------------------------------------------------------*/
void PORTD_IRQHandler(void)
{     
  //���ж�PTD14
  int n;    
    n=14;   //���ж�
  if((PORTD_ISFR & (1<<n) ))//���ж� (1<<14)
  {    
    PORTD_ISFR |= (1<<n);   //����жϱ�ʶ
    // �û�����            
    DMATransDataStart(DMA_CH4,(uint32_t)(&Image_Data[Line_Cont][0]));   //����DMA���� 
    if(Line_Cont > IMAGEH)  //�ɼ�����
    { 
      Line_Cont=0; 
      return ;
    } 
    ++Line_Cont;            //�м���
    return ; 
  }
  //���ж�PTD15
  n=15;  //���ж�
  if((PORTD_ISFR & (1<<n)))//(1<<15)
  {
    PORTD_ISFR |= (1<<n);  //����жϱ�ʶ
    // �û����� 
    Line_Cont = 0;         //�м�������
    Field_Over_Flag=1;     //��������ʶ
  } 
}
/*---------------------------------------------------------------
����    ����Test_Camera
����    �ܡ���������ͷ 
����    ������
���� �� ֵ����
��ע�����ע�ⲻҪʹ�� ��PD15
----------------------------------------------------------------*/
void CAMERA_Init(void)
{
    /*  ����ͷ��ʼ�� */
    LQMT9V034_Init(0);            //����ͷ��ʼ��
    
    //����ͷ�йؽӿڳ�ʼ��
    GPIO_ExtiInit(PTD14,rising_down);   //���ж�
    GPIO_ExtiInit(PTD15,falling_up);    //���ж�  
    
    /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(PORTD_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    NVIC_EnableIRQ(PORTD_IRQn);			         //ʹ��PORTC_IRQn���ж� 
    
    //��λ���������
    GPIO_PinInit(PTD0,GPI,0);                
    GPIO_PinInit(PTD1,GPI,0);
    GPIO_PinInit(PTD2,GPI,0);
    GPIO_PinInit(PTD3,GPI,0);
    GPIO_PinInit(PTD4,GPI,0);
    GPIO_PinInit(PTD5,GPI,0);
    GPIO_PinInit(PTD6,GPI,0);
    GPIO_PinInit(PTD7,GPI,0);     
    
    //��ʼ��DMA�ɼ�       ͨ��4        PTD0-PTD7           Ŀ�ĵ�ַ      �����ź� ÿ��һ��BYTE  ����    ���������ش���
    DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTD_BYTE0_IN,(void*)Image_Data, PTD13, DMA_BYTE1, (IMAGEW ), DMA_rising_down); 
    /* ����ͷ��ʼ������ */
}

/*---------------------------------------------------------------
����    ����Test_Camera
����    �ܡ���������ͷ 
����    ������
���� �� ֵ����
��ע�����ע�ⲻҪʹ�� ��PD15
----------------------------------------------------------------*/
void Test_Camera(void)
{  
    LED_Init();
    TFTSPI_Init(0);                //TFT1.8��ʼ��  0��������ʾ  1��������ʾ  
    TFTSPI_CLS(u16BLUE);           //����
    UART_Init(UART4, 115200);      //���ڳ�ʼ��
    /*  ����ͷ��ʼ�� */
    LQMT9V034_Init(50);            //����ͷ��ʼ��
    
    //����ͷ�йؽӿڳ�ʼ��
    GPIO_ExtiInit(PTD14,rising_down);   //���ж�
    GPIO_ExtiInit(PTD15,falling_up);    //���ж�  
    
    /* ���ȼ����� ��ռ���ȼ�1  �����ȼ�2   ԽС���ȼ�Խ��  ��ռ���ȼ��ɴ�ϱ���ж� */
    NVIC_SetPriority(PORTD_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    NVIC_EnableIRQ(PORTD_IRQn);			         //ʹ��PORTC_IRQn���ж� 
    
    //��λ���������
    GPIO_PinInit(PTD0,GPI,0);                
    GPIO_PinInit(PTD1,GPI,0);
    GPIO_PinInit(PTD2,GPI,0);
    GPIO_PinInit(PTD3,GPI,0);
    GPIO_PinInit(PTD4,GPI,0);
    GPIO_PinInit(PTD5,GPI,0);
    GPIO_PinInit(PTD6,GPI,0);
    GPIO_PinInit(PTD7,GPI,0);     
    
    //��ʼ��DMA�ɼ�       ͨ��4        PTD0-PTD7           Ŀ�ĵ�ַ      �����ź� ÿ��һ��BYTE  ����    ���������ش���
    DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTD_BYTE0_IN,(void*)Image_Data, PTD13, DMA_BYTE1, (IMAGEW ), DMA_rising_down); 
    /* ����ͷ��ʼ������ */
    
    while(1)
    { 
        LED_Reverse(1);           //LEDָʾ��������״̬
        if(Field_Over_Flag)       //���һ��ͼ��ɼ�
        { 
			Get_Use_Image();      //�Ӳɼ�ͼ��������ȡ���Լ���Ҫʹ�õĴ�С
            TFTSPI_Show_Cmera(0, 0, 160, 120, Image_Use);      //��ֵ��ͼ������
			
            Field_Over_Flag= 0;
        }    
    }
}


/*---------------------------------------------------------------
����    ����Get_Use_Image
����    �ܡ���ȡ��Ҫʹ�õ�ͼ���С
����    ������
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/
__ramfunc void Get_Use_Image(void)
{
  int i = 0,j = 0,row = 0,line = 0;
  uint8_t div_h = IMAGEH/LCDH;
  uint8_t div_w = IMAGEW/LCDW;
  for(i = 0; i  < IMAGEH; i += div_h)    //IMAGEH / div  = LCDH
  {
    for(j = 0; j < IMAGEW; j += div_w)   //IMAGEW / div  = LCDW
    {        
      Image_Use[row][line] = Image_Data[i][j];         
      line++;        
    }      
    line = 0;
    row++;      
  }  
}

/*---------------------------------------------------------------
����    ����Get_01_Value
����    �ܡ���ֵ��
����    ����mode  ��  0��ʹ�ô����ֵ    1��ʹ��ƽ����ֵ
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/
void Get_01_Value(uint8_t mode)
{
  int i = 0,j = 0;
  uint8_t Threshold;
  uint32_t  tv=0;
  char txt[16];
  if(mode)
  {
      //�ۼ�
      for(i = 0; i <LCDH; i++)
      {    
          for(j = 0; j <LCDW; j++)
          {                            
              tv+=Image_Use[i][j];   //�ۼ�  
          } 
      }
      Threshold=tv/LCDH/LCDW;        //��ƽ��ֵ,����Խ��ԽС��ȫ��Լ35��������ĻԼ160��һ������´�Լ100
      Threshold=Threshold*7/10+10;   //�˴���ֵ���ã����ݻ����Ĺ������趨 
  }
  else
  {
      Threshold = GetOSTU(Image_Use);//�����ֵ
      Threshold = (uint8_t)(Threshold * 0.5) + 70;
  } 
  sprintf(txt,"%03d",Threshold);//ǰ��Ϊ�����õ���ֵ������Ϊƽ��ֵ 
#ifdef LQ_OLED 
  OLED_P6x8Str(80,1,(u8*)txt);
#else
  TFTSPI_P8X8Str(0,15,(u8*)txt,u16RED,u16BLUE);
#endif
  
  for(i = 0; i < LCDH; i++)
  {
    for(j = 0; j < LCDW; j++)
    {                                
      if(Image_Use[i][j] >Threshold) //��ֵԽ����ʾ������Խ�࣬��ǳ��ͼ��Ҳ����ʾ����    
        Pixle[i][j] =1;        
      else                                        
        Pixle[i][j] =0;
    }    
  }
}

/*---------------------------------------------------------------
����    ����TFTSPI_Show_Cmera
����    �ܡ���TFT1.8�ϻ�������ͷ��ͼ��
����    ����xs:  ��ʼX   
����    ����ys:  ��ʼY  
����    ����w:   ͼƬ��� 
����    ����h:   ͼƬ�߶�  
����    ����ppic[IMAGEH][IMAGEW]:  ͼƬ������   
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/	
void TFTSPI_Show_Cmera(uint8_t xs,uint8_t ys,uint8_t w,uint8_t h,uint8_t ppic[LCDH][LCDW]) 
{
#if 0    //�Ҷ���ʾ
    unsigned int i,j;	
    uint16_t color;
    TFTSPI_Set_Pos(xs,ys,xs+w-1,ys+h);
    for(i = 0; i < h; i += 1)     
    { 	
        for(j = 0; j < w; j += 1) 
        {
           
            color = 0;
            color=((ppic[i][j]>>3))<<11;
            color=color|(((ppic[i][j]>>2))<<5);
            color=color|(((ppic[i][j])>>3));
            TFTSPI_Write_Word(color);
        }
        
    }
#else    //��ֵ����ʾ
    unsigned int i,j;	
    Get_01_Value(1);
    TFTSPI_Set_Pos(xs,ys,xs+w-1,ys+h);
    for(i = 0; i < h; i += 1)     
    { 	
        for(j = 0; j < w; j += 1) 
        {
           
            if(Pixle[i][j])
            {
                TFTSPI_Write_Word(0xFFFF);
            }
            else
            {
                TFTSPI_Write_Word(0);
            }      
        }
        
    }
#endif
 }
/*---------------------------------------------------------------
����    ����Draw_Road
����    �ܡ���OLED�ϻ�������ͷ��ͼ��
����    ������
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/
void Draw_Road(void)
{ 	 
  u8 i = 0, j = 0,temp=0;
  
  //����֡ͷ��־
  for(i=8;i<56;i+=8)//6*8=48�� 
  {
    OLED_Set_Pos(18,i/8+1);//��ʼλ��
    for(j=0;j<LCDW;j++)  //����
    { 
      temp=0; 
      if(Pixle[0+i][j]) temp|=1;
      if(Pixle[1+i][j]) temp|=2;
      if(Pixle[2+i][j]) temp|=4;
      if(Pixle[3+i][j]) temp|=8;
      if(Pixle[4+i][j]) temp|=0x10;
      if(Pixle[5+i][j]) temp|=0x20;
      if(Pixle[6+i][j]) temp|=0x40;
      if(Pixle[7+i][j]) temp|=0x80;
      OLED_WrDat(temp); 	  	  	  	  
    }
  }  
}


/*---------------------------------------------------------------
����    ����Pixle_Filter
����    �ܡ��������
����    ������
���� �� ֵ����
��ע�����
----------------------------------------------------------------*/
void Pixle_Filter(void)
{  
  int nr; //��
  int nc; //��
  
  for(nr=1; nr<LCDH-1; nr++)
  {  	    
    for(nc=1; nc<LCDW-1; nc=nc+1)
    {
      if((Pixle[nr][nc]==0)&&(Pixle[nr-1][nc]+Pixle[nr+1][nc]+Pixle[nr][nc+1]+Pixle[nr][nc-1]>2))         
      {
        Pixle[nr][nc]=1;
      }	
      else if((Pixle[nr][nc]==1)&&(Pixle[nr-1][nc]+Pixle[nr+1][nc]+Pixle[nr][nc+1]+Pixle[nr][nc-1]<2))         
      {
        Pixle[nr][nc]=0;
      }	
    }	  
  }  
}



/***************************************************************
* 
* �������ƣ�SendPicture 
* ����˵��������ͼ����λ�� ����ͬ����λ��ע���޸Ķ�Ӧ�����ݽ���Э��
* ����˵���� 
* �������أ�void 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
***************************************************************/ 
void UARTSendPicture(uint8_t  tmImage[IMAGEH][IMAGEW]) 
{ 
  int i = 0, j = 0; 
  UART_PutChar(UART4,0x01); //����֡ͷ��־ WindowsFormsApplication1.exe
  UART_PutChar(UART4,0xfe); //����֡ͷ��־ WindowsFormsApplication1.exe
  for(i=0;i < IMAGEH; i++) 
  { 
    for(j=0;j <IMAGEW ;j++) 
    { 
      if(tmImage[i][j]==0xfe) 
      { 
        tmImage[i][j]=0xff; //��ֹ���ͱ�־λ 
      } 
      UART_PutChar(UART4,tmImage[i][j]); 
    } 
  }
  UART_PutChar(UART4,0xfe); //����֡β��־ 
  UART_PutChar(UART4,0x01); //����֡β��־ 
} 

/*************************************************************** 
* 
* �������ƣ�uint8_t GetOSTU(uint8_t tmImage[IMAGEH][IMAGEW]) 
* ����˵��������ֵ��С 
* ����˵���� 
* �������أ���ֵ��С 
* �޸�ʱ�䣺2018��3��27�� 
* �� ע�� 
�ο���https://blog.csdn.net/zyzhangyue/article/details/45841255
      https://www.cnblogs.com/moon1992/p/5092726.html
      https://www.cnblogs.com/zhonghuasong/p/7250540.html     
Ostu������������������ͨ��ͳ������ͼ���ֱ��ͼ������ʵ��ȫ����ֵT���Զ�ѡȡ�����㷨����Ϊ��
1) �ȼ���ͼ���ֱ��ͼ������ͼ�����е����ص㰴��0~255��256��bin��ͳ������ÿ��bin�����ص�����
2) ��һ��ֱ��ͼ��Ҳ����ÿ��bin�����ص����������ܵ����ص�
3) i��ʾ�������ֵ��Ҳ��һ���Ҷȼ�����0��ʼ����
4) ͨ����һ����ֱ��ͼ��ͳ��0~i �Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ���ǰ������) ��ռ����ͼ��ı���w0����ͳ��ǰ�����ص�ƽ���Ҷ�u0��ͳ��i~255�Ҷȼ�������(��������ֵ�ڴ˷�Χ�����ؽ�����������) ��ռ����ͼ��ı���w1����ͳ�Ʊ������ص�ƽ���Ҷ�u1��
5) ����ǰ�����غͱ������صķ��� g = w0*w1*(u0-u1) (u0-u1)
6) i++��ת��4)��ֱ��iΪ256ʱ��������
7�������g��Ӧ��iֵ��Ϊͼ���ȫ����ֵ
ȱ��:OSTU�㷨�ڴ�����ղ����ȵ�ͼ���ʱ��Ч�������Բ��ã���Ϊ���õ���ȫ��������Ϣ��
������ղ�����  https://blog.csdn.net/kk55guang2/article/details/78475414
                https://blog.csdn.net/kk55guang2/article/details/78490069
				https://wenku.baidu.com/view/84e5eb271a37f111f0855b2d.html
***************************************************************/ 
__ramfunc int GetOSTU(uint8_t tmImage[LCDH][LCDW]) 
{ 
/**
  * @brief    δ�Ż����Ĵ��
  *
  * @param    ����ʱ��Ƚϳ�
  *
  * @return   ʵ��120*160��ͼ��
  *
  * @note     K66 220MHz��Ҫ9ms
  *
  * @example  
  *
  * @date     2019/4/16 ���ڶ�
  */
//	int width = LCDW;
//	int height = LCDH;
//	int x = 0, y = 0;
//	int pixelCount[256];
//	float pixelPro[256];
//	int i, j, pixelSum = width * height, threshold = 0;
//	
//	
//	//��ʼ��
//	for (i = 0; i < 256; i++)
//	{
//		pixelCount[i] = 0;
//		pixelPro[i] = 0;
//	}
//	
//	//ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
//	for (i = y; i < height; i++)
//	{
//		for (j = x; j <width; j++)
//		{
//			pixelCount[tmImage[i][j]]++;
//		}
//	}
//	
//	//����ÿ������������ͼ���еı���
//	for (i = 0; i < 256; i++)
//	{
//		pixelPro[i] = (float)(pixelCount[i]) / (float)(pixelSum);
//	}
//	
//	//����ostu�㷨,�õ�ǰ���ͱ����ķָ�
//	//�����Ҷȼ�[0,255],������������ĻҶ�ֵ,Ϊ�����ֵ
//	float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
//	for (i = 0; i < 256; i++)
//	{
//		w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
//		
//		for (j = 0; j < 256; j++)
//		{
//			if (j <= i) //��������
//			{
//				//��iΪ��ֵ���࣬��һ���ܵĸ���
//				w0 += pixelPro[j];
//				u0tmp += j * pixelPro[j];
//			}
//			else       //ǰ������
//			{
//				//��iΪ��ֵ���࣬�ڶ����ܵĸ���
//				w1 += pixelPro[j];
//				u1tmp += j * pixelPro[j];
//			}
//		}
//		
//		u0 = u0tmp / w0;        //��һ���ƽ���Ҷ�
//		u1 = u1tmp / w1;        //�ڶ����ƽ���Ҷ�
//		u = u0tmp + u1tmp;        //����ͼ���ƽ���Ҷ�
//		//������䷽��
//		deltaTmp = w0 * (u0 - u)*(u0 - u) + w1 * (u1 - u)*(u1 - u);
//		//�ҳ������䷽���Լ���Ӧ����ֵ
//		if (deltaTmp > deltaMax)
//		{
//			deltaMax = deltaTmp;
//			threshold = i;
//		}
//	}
//	//���������ֵ;
//	return threshold;
	
/**
  * @brief    �Ż����Ĵ��
  *
  * @param    ����������ʱ��
  *
  * @return   ʵ��K66 220MHz 120*160��ͼ��
  *
  * @note     ֻ��Ҫ1.5ms
  *
  * @example  δ�Ż��Ĵ����Ҫ9ms
  *
  * @date     2019/4/16 ���ڶ�
  */ 
	int16_t i,j; 
	uint32_t Amount = 0; 
	uint32_t PixelBack = 0; 
	uint32_t PixelIntegralBack = 0; 
	uint32_t PixelIntegral = 0; 
	int32_t PixelIntegralFore = 0; 
	int32_t PixelFore = 0; 
	float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // ��䷽��; 
	int16_t MinValue, MaxValue; 
	uint8_t Threshold = 0;
	uint8_t HistoGram[256];              //  
	
	for (j = 0; j < 256; j++)  HistoGram[j] = 0; //��ʼ���Ҷ�ֱ��ͼ 
	
	for (j = 0; j < LCDH; j++) 
	{ 
		for (i = 0; i < LCDW; i++) 
		{ 
			HistoGram[tmImage[j][i]]++; //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
		} 
	} 
	
	for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //��ȡ��С�Ҷȵ�ֵ
	for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //��ȡ���Ҷȵ�ֵ
	
	if (MaxValue == MinValue)     return MaxValue;         // ͼ����ֻ��һ����ɫ    
	if (MinValue + 1 == MaxValue)  return MinValue;        // ͼ����ֻ�ж�����ɫ
	
	for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  ��������
	
	PixelIntegral = 0;
	for (j = MinValue; j <= MaxValue; j++)
	{
		PixelIntegral += HistoGram[j] * j;//�Ҷ�ֵ����
	}
	SigmaB = -1;
	for (j = MinValue; j < MaxValue; j++)
	{
		PixelBack = PixelBack + HistoGram[j];   //ǰ�����ص���
		PixelFore = Amount - PixelBack;         //�������ص���
		OmegaBack = (float)PixelBack / Amount;//ǰ�����ذٷֱ�
		OmegaFore = (float)PixelFore / Amount;//�������ذٷֱ�
		PixelIntegralBack += HistoGram[j] * j;  //ǰ���Ҷ�ֵ
		PixelIntegralFore = PixelIntegral - PixelIntegralBack;//�����Ҷ�ֵ
		MicroBack = (float)PixelIntegralBack / PixelBack;   //ǰ���ҶȰٷֱ�
		MicroFore = (float)PixelIntegralFore / PixelFore;   //�����ҶȰٷֱ�
		Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//������䷽��
		if (Sigma > SigmaB)                    //����������䷽��g //�ҳ������䷽���Լ���Ӧ����ֵ
		{
			SigmaB = Sigma;
			Threshold = j;
		}
	}
	return Threshold;                        //���������ֵ;
}  