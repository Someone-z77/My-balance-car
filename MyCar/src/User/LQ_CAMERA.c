/*---------------------------------------------------------------
【平    台】龙邱K60核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年04月02日
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【编译平台】IAR 8.2
【功    能】OV7725测试
【注意事项】
----------------------------------------------------------------*/
#include "include.h"

volatile uint8_t Image_Data[IMAGEH][IMAGEW];      //图像原始数据存放
uint8_t Image_Use[LCDH][LCDW];           //压缩后之后用于存放屏幕显示数据
uint8_t Pixle[LCDH][LCDW];               //二值化后用于OLED显示的数据
volatile uint8_t  Line_Cont=0;                    //行计数
volatile uint8_t  Field_Over_Flag=0;              //场标识


/*---------------------------------------------------------------
【函    数】PORTC_Interrupt
【功    能】PORTC端口的中断服务函数 用于摄像头行场中断
【参    数】无
【返 回 值】无
【注意事项】注意进入后要清除中断标志位
----------------------------------------------------------------*/
void PORTD_IRQHandler(void)
{     
  //行中断PTD14
  int n;    
    n=14;   //行中断
  if((PORTD_ISFR & (1<<n) ))//行中断 (1<<14)
  {    
    PORTD_ISFR |= (1<<n);   //清除中断标识
    // 用户程序            
    DMATransDataStart(DMA_CH4,(uint32_t)(&Image_Data[Line_Cont][0]));   //开启DMA传输 
    if(Line_Cont > IMAGEH)  //采集结束
    { 
      Line_Cont=0; 
      return ;
    } 
    ++Line_Cont;            //行计数
    return ; 
  }
  //场中断PTD15
  n=15;  //场中断
  if((PORTD_ISFR & (1<<n)))//(1<<15)
  {
    PORTD_ISFR |= (1<<n);  //清除中断标识
    // 用户程序 
    Line_Cont = 0;         //行计数清零
    Field_Over_Flag=1;     //场结束标识
  } 
}
/*---------------------------------------------------------------
【函    数】Test_Camera
【功    能】测试摄像头 
【参    数】无
【返 回 值】无
【注意事项】注意不要使用 灯PD15
----------------------------------------------------------------*/
void CAMERA_Init(void)
{
    /*  摄像头初始化 */
    LQMT9V034_Init(0);            //摄像头初始化
    
    //摄像头有关接口初始化
    GPIO_ExtiInit(PTD14,rising_down);   //行中断
    GPIO_ExtiInit(PTD15,falling_up);    //场中断  
    
    /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(PORTD_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    NVIC_EnableIRQ(PORTD_IRQn);			         //使能PORTC_IRQn的中断 
    
    //八位数据输入口
    GPIO_PinInit(PTD0,GPI,0);                
    GPIO_PinInit(PTD1,GPI,0);
    GPIO_PinInit(PTD2,GPI,0);
    GPIO_PinInit(PTD3,GPI,0);
    GPIO_PinInit(PTD4,GPI,0);
    GPIO_PinInit(PTD5,GPI,0);
    GPIO_PinInit(PTD6,GPI,0);
    GPIO_PinInit(PTD7,GPI,0);     
    
    //初始化DMA采集       通道4        PTD0-PTD7           目的地址      触发信号 每次一个BYTE  长度    下拉上升沿触发
    DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTD_BYTE0_IN,(void*)Image_Data, PTD13, DMA_BYTE1, (IMAGEW ), DMA_rising_down); 
    /* 摄像头初始化结束 */
}

/*---------------------------------------------------------------
【函    数】Test_Camera
【功    能】测试摄像头 
【参    数】无
【返 回 值】无
【注意事项】注意不要使用 灯PD15
----------------------------------------------------------------*/
void Test_Camera(void)
{  
    LED_Init();
    TFTSPI_Init(0);                //TFT1.8初始化  0：横屏显示  1：竖屏显示  
    TFTSPI_CLS(u16BLUE);           //清屏
    UART_Init(UART4, 115200);      //串口初始化
    /*  摄像头初始化 */
    LQMT9V034_Init(50);            //摄像头初始化
    
    //摄像头有关接口初始化
    GPIO_ExtiInit(PTD14,rising_down);   //行中断
    GPIO_ExtiInit(PTD15,falling_up);    //场中断  
    
    /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(PORTD_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),0,2));
    NVIC_EnableIRQ(PORTD_IRQn);			         //使能PORTC_IRQn的中断 
    
    //八位数据输入口
    GPIO_PinInit(PTD0,GPI,0);                
    GPIO_PinInit(PTD1,GPI,0);
    GPIO_PinInit(PTD2,GPI,0);
    GPIO_PinInit(PTD3,GPI,0);
    GPIO_PinInit(PTD4,GPI,0);
    GPIO_PinInit(PTD5,GPI,0);
    GPIO_PinInit(PTD6,GPI,0);
    GPIO_PinInit(PTD7,GPI,0);     
    
    //初始化DMA采集       通道4        PTD0-PTD7           目的地址      触发信号 每次一个BYTE  长度    下拉上升沿触发
    DMA_PORTx2BUFF_Init (DMA_CH4, (void *)&PTD_BYTE0_IN,(void*)Image_Data, PTD13, DMA_BYTE1, (IMAGEW ), DMA_rising_down); 
    /* 摄像头初始化结束 */
    
    while(1)
    { 
        LED_Reverse(1);           //LED指示程序运行状态
        if(Field_Over_Flag)       //完成一场图像采集
        { 
			Get_Use_Image();      //从采集图像数据中取出自己想要使用的大小
            TFTSPI_Show_Cmera(0, 0, 160, 120, Image_Use);      //二值化图像数据
			
            Field_Over_Flag= 0;
        }    
    }
}


/*---------------------------------------------------------------
【函    数】Get_Use_Image
【功    能】获取需要使用的图像大小
【参    数】无
【返 回 值】无
【注意事项】
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
【函    数】Get_01_Value
【功    能】二值化
【参    数】mode  ：  0：使用大津法阈值    1：使用平均阈值
【返 回 值】无
【注意事项】
----------------------------------------------------------------*/
void Get_01_Value(uint8_t mode)
{
  int i = 0,j = 0;
  uint8_t Threshold;
  uint32_t  tv=0;
  char txt[16];
  if(mode)
  {
      //累加
      for(i = 0; i <LCDH; i++)
      {    
          for(j = 0; j <LCDW; j++)
          {                            
              tv+=Image_Use[i][j];   //累加  
          } 
      }
      Threshold=tv/LCDH/LCDW;        //求平均值,光线越暗越小，全黑约35，对着屏幕约160，一般情况下大约100
      Threshold=Threshold*7/10+10;   //此处阈值设置，根据环境的光线来设定 
  }
  else
  {
      Threshold = GetOSTU(Image_Use);//大津法阈值
      Threshold = (uint8_t)(Threshold * 0.5) + 70;
  } 
  sprintf(txt,"%03d",Threshold);//前者为大津法求得的阈值，后者为平均值 
#ifdef LQ_OLED 
  OLED_P6x8Str(80,1,(u8*)txt);
#else
  TFTSPI_P8X8Str(0,15,(u8*)txt,u16RED,u16BLUE);
#endif
  
  for(i = 0; i < LCDH; i++)
  {
    for(j = 0; j < LCDW; j++)
    {                                
      if(Image_Use[i][j] >Threshold) //数值越大，显示的内容越多，较浅的图像也能显示出来    
        Pixle[i][j] =1;        
      else                                        
        Pixle[i][j] =0;
    }    
  }
}

/*---------------------------------------------------------------
【函    数】TFTSPI_Show_Cmera
【功    能】在TFT1.8上画出摄像头的图像
【参    数】xs:  起始X   
【参    数】ys:  起始Y  
【参    数】w:   图片宽度 
【参    数】h:   图片高度  
【参    数】ppic[IMAGEH][IMAGEW]:  图片缓存区   
【返 回 值】无
【注意事项】
----------------------------------------------------------------*/	
void TFTSPI_Show_Cmera(uint8_t xs,uint8_t ys,uint8_t w,uint8_t h,uint8_t ppic[LCDH][LCDW]) 
{
#if 0    //灰度显示
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
#else    //二值化显示
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
【函    数】Draw_Road
【功    能】在OLED上画出摄像头的图像
【参    数】无
【返 回 值】无
【注意事项】
----------------------------------------------------------------*/
void Draw_Road(void)
{ 	 
  u8 i = 0, j = 0,temp=0;
  
  //发送帧头标志
  for(i=8;i<56;i+=8)//6*8=48行 
  {
    OLED_Set_Pos(18,i/8+1);//起始位置
    for(j=0;j<LCDW;j++)  //列数
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
【函    数】Pixle_Filter
【功    能】过滤噪点
【参    数】无
【返 回 值】无
【注意事项】
----------------------------------------------------------------*/
void Pixle_Filter(void)
{  
  int nr; //行
  int nc; //列
  
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
* 函数名称：SendPicture 
* 功能说明：发送图像到上位机 ，不同的上位机注意修改对应的数据接收协议
* 参数说明： 
* 函数返回：void 
* 修改时间：2018年3月27日 
* 备 注： 
***************************************************************/ 
void UARTSendPicture(uint8_t  tmImage[IMAGEH][IMAGEW]) 
{ 
  int i = 0, j = 0; 
  UART_PutChar(UART4,0x01); //发送帧头标志 WindowsFormsApplication1.exe
  UART_PutChar(UART4,0xfe); //发送帧头标志 WindowsFormsApplication1.exe
  for(i=0;i < IMAGEH; i++) 
  { 
    for(j=0;j <IMAGEW ;j++) 
    { 
      if(tmImage[i][j]==0xfe) 
      { 
        tmImage[i][j]=0xff; //防止发送标志位 
      } 
      UART_PutChar(UART4,tmImage[i][j]); 
    } 
  }
  UART_PutChar(UART4,0xfe); //发送帧尾标志 
  UART_PutChar(UART4,0x01); //发送帧尾标志 
} 

/*************************************************************** 
* 
* 函数名称：uint8_t GetOSTU(uint8_t tmImage[IMAGEH][IMAGEW]) 
* 功能说明：求阈值大小 
* 参数说明： 
* 函数返回：阈值大小 
* 修改时间：2018年3月27日 
* 备 注： 
参考：https://blog.csdn.net/zyzhangyue/article/details/45841255
      https://www.cnblogs.com/moon1992/p/5092726.html
      https://www.cnblogs.com/zhonghuasong/p/7250540.html     
Ostu方法又名最大类间差方法，通过统计整个图像的直方图特性来实现全局阈值T的自动选取，其算法步骤为：
1) 先计算图像的直方图，即将图像所有的像素点按照0~255共256个bin，统计落在每个bin的像素点数量
2) 归一化直方图，也即将每个bin中像素点数量除以总的像素点
3) i表示分类的阈值，也即一个灰度级，从0开始迭代
4) 通过归一化的直方图，统计0~i 灰度级的像素(假设像素值在此范围的像素叫做前景像素) 所占整幅图像的比例w0，并统计前景像素的平均灰度u0；统计i~255灰度级的像素(假设像素值在此范围的像素叫做背景像素) 所占整幅图像的比例w1，并统计背景像素的平均灰度u1；
5) 计算前景像素和背景像素的方差 g = w0*w1*(u0-u1) (u0-u1)
6) i++；转到4)，直到i为256时结束迭代
7）将最大g相应的i值作为图像的全局阈值
缺陷:OSTU算法在处理光照不均匀的图像的时候，效果会明显不好，因为利用的是全局像素信息。
解决光照不均匀  https://blog.csdn.net/kk55guang2/article/details/78475414
                https://blog.csdn.net/kk55guang2/article/details/78490069
				https://wenku.baidu.com/view/84e5eb271a37f111f0855b2d.html
***************************************************************/ 
__ramfunc int GetOSTU(uint8_t tmImage[LCDH][LCDW]) 
{ 
/**
  * @brief    未优化过的大津法
  *
  * @param    运算时间比较长
  *
  * @return   实测120*160的图像
  *
  * @note     K66 220MHz需要9ms
  *
  * @example  
  *
  * @date     2019/4/16 星期二
  */
//	int width = LCDW;
//	int height = LCDH;
//	int x = 0, y = 0;
//	int pixelCount[256];
//	float pixelPro[256];
//	int i, j, pixelSum = width * height, threshold = 0;
//	
//	
//	//初始化
//	for (i = 0; i < 256; i++)
//	{
//		pixelCount[i] = 0;
//		pixelPro[i] = 0;
//	}
//	
//	//统计灰度级中每个像素在整幅图像中的个数
//	for (i = y; i < height; i++)
//	{
//		for (j = x; j <width; j++)
//		{
//			pixelCount[tmImage[i][j]]++;
//		}
//	}
//	
//	//计算每个像素在整幅图像中的比例
//	for (i = 0; i < 256; i++)
//	{
//		pixelPro[i] = (float)(pixelCount[i]) / (float)(pixelSum);
//	}
//	
//	//经典ostu算法,得到前景和背景的分割
//	//遍历灰度级[0,255],计算出方差最大的灰度值,为最佳阈值
//	float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
//	for (i = 0; i < 256; i++)
//	{
//		w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
//		
//		for (j = 0; j < 256; j++)
//		{
//			if (j <= i) //背景部分
//			{
//				//以i为阈值分类，第一类总的概率
//				w0 += pixelPro[j];
//				u0tmp += j * pixelPro[j];
//			}
//			else       //前景部分
//			{
//				//以i为阈值分类，第二类总的概率
//				w1 += pixelPro[j];
//				u1tmp += j * pixelPro[j];
//			}
//		}
//		
//		u0 = u0tmp / w0;        //第一类的平均灰度
//		u1 = u1tmp / w1;        //第二类的平均灰度
//		u = u0tmp + u1tmp;        //整幅图像的平均灰度
//		//计算类间方差
//		deltaTmp = w0 * (u0 - u)*(u0 - u) + w1 * (u1 - u)*(u1 - u);
//		//找出最大类间方差以及对应的阈值
//		if (deltaTmp > deltaMax)
//		{
//			deltaMax = deltaTmp;
//			threshold = i;
//		}
//	}
//	//返回最佳阈值;
//	return threshold;
	
/**
  * @brief    优化过的大津法
  *
  * @param    大大减少运算时间
  *
  * @return   实测K66 220MHz 120*160的图像
  *
  * @note     只需要1.5ms
  *
  * @example  未优化的大津法需要9ms
  *
  * @date     2019/4/16 星期二
  */ 
	int16_t i,j; 
	uint32_t Amount = 0; 
	uint32_t PixelBack = 0; 
	uint32_t PixelIntegralBack = 0; 
	uint32_t PixelIntegral = 0; 
	int32_t PixelIntegralFore = 0; 
	int32_t PixelFore = 0; 
	float OmegaBack, OmegaFore, MicroBack, MicroFore, SigmaB, Sigma; // 类间方差; 
	int16_t MinValue, MaxValue; 
	uint8_t Threshold = 0;
	uint8_t HistoGram[256];              //  
	
	for (j = 0; j < 256; j++)  HistoGram[j] = 0; //初始化灰度直方图 
	
	for (j = 0; j < LCDH; j++) 
	{ 
		for (i = 0; i < LCDW; i++) 
		{ 
			HistoGram[tmImage[j][i]]++; //统计灰度级中每个像素在整幅图像中的个数
		} 
	} 
	
	for (MinValue = 0; MinValue < 256 && HistoGram[MinValue] == 0; MinValue++) ;        //获取最小灰度的值
	for (MaxValue = 255; MaxValue > MinValue && HistoGram[MinValue] == 0; MaxValue--) ; //获取最大灰度的值
	
	if (MaxValue == MinValue)     return MaxValue;         // 图像中只有一个颜色    
	if (MinValue + 1 == MaxValue)  return MinValue;        // 图像中只有二个颜色
	
	for (j = MinValue; j <= MaxValue; j++)    Amount += HistoGram[j];        //  像素总数
	
	PixelIntegral = 0;
	for (j = MinValue; j <= MaxValue; j++)
	{
		PixelIntegral += HistoGram[j] * j;//灰度值总数
	}
	SigmaB = -1;
	for (j = MinValue; j < MaxValue; j++)
	{
		PixelBack = PixelBack + HistoGram[j];   //前景像素点数
		PixelFore = Amount - PixelBack;         //背景像素点数
		OmegaBack = (float)PixelBack / Amount;//前景像素百分比
		OmegaFore = (float)PixelFore / Amount;//背景像素百分比
		PixelIntegralBack += HistoGram[j] * j;  //前景灰度值
		PixelIntegralFore = PixelIntegral - PixelIntegralBack;//背景灰度值
		MicroBack = (float)PixelIntegralBack / PixelBack;   //前景灰度百分比
		MicroFore = (float)PixelIntegralFore / PixelFore;   //背景灰度百分比
		Sigma = OmegaBack * OmegaFore * (MicroBack - MicroFore) * (MicroBack - MicroFore);//计算类间方差
		if (Sigma > SigmaB)                    //遍历最大的类间方差g //找出最大类间方差以及对应的阈值
		{
			SigmaB = Sigma;
			Threshold = j;
		}
	}
	return Threshold;                        //返回最佳阈值;
}  