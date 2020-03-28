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
#include "LQ_ADC.h"
/*------------------------------------------------------------------------------------------------------
����    ����ADC_Get
����    �ܡ���ȡ����ĸ���ϵ�11·ADCֵ
����    ����num �� 0 ~ 10
���� �� ֵ��ADC��ȡ��ֵ
��ʵ    ����ADC_Get(0);         //��ȡAD0�ӿڵ�ֵ
��ע�����ADC1_SE10 =10,       // PTB4      ĸ���ϵ�AD0      
            ADC1_SE11 =11,       // PTB5      ĸ���ϵ�AD1
            ADC1_SE12 =12,       // PTB6      ĸ���ϵ�AD2
            ADC1_SE13 =13,       // PTB7      ĸ���ϵ�AD3
            ADC1_SE14 =14,       // PTB10     ĸ���ϵ�AD4
            ADC1_SE15 =15,       // PTB11     ĸ���ϵ�AD5
            ADC1_SE16 =16,       // ADC1_SE16 ĸ���ϵ�AD6
            ADC0_SE16 =16,       // ADC0_SE16 ĸ���ϵ�AD7
            ADC0_SE11 =11,       // PTA8      ĸ���ϵ�AD8
--------------------------------------------------------------------------------------------------------*/
uint16_t ADC_Get(uint8_t num)
{
    switch(num)
    {
      case 0:
        return ADC_Mid(ADC1, ADC1_SE10, ADC_12bit);
        break;
        
      case 1:
        return ADC_Mid(ADC1, ADC1_SE11, ADC_12bit);
        break;
        
      case 2:
        return ADC_Mid(ADC1, ADC1_SE12, ADC_12bit);
        break;
        
      case 3:
        return ADC_Mid(ADC1, ADC1_SE13, ADC_12bit);
        break;
        
      case 4:
        return ADC_Mid(ADC1, ADC1_SE14, ADC_12bit);
        break;
        
      case 5:
        return ADC_Mid(ADC1, ADC1_SE15, ADC_12bit);
        break;
        
      case 6:
        return ADC_Mid(ADC1, ADC1_SE16, ADC_12bit);
        break;
        
      case 7:
        return ADC_Mid(ADC0, ADC0_SE16, ADC_12bit);
        break;
        
      case 8:
        return ADC_Mid(ADC0, ADC0_SE11, ADC_12bit);
        break;
        
        
      default:
        return 0;   
    }
}



/*------------------------------------------------------------------------------------------------------
����    ����Test_ADC
����    �ܡ�����ĸ���ϵ�10·ADC�ӿ�
����    ������
���� �� ֵ����
��ʵ    ����Test_ADC(); //��ӡ����ʾ��ѹ
��ע�����
--------------------------------------------------------------------------------------------------------*/
#ifdef LQ_OLED
void Test_ADC(void)
{
    LED_Init();
    KEY_Init();
    UART_Init(UART4, 115200);
    
    ADC_Init(ADC0);
    ADC_Init(ADC1);
    
    OLED_Init();
    OLED_CLS();
    printf("ADC ��������");
    printf("ADC1_SE10 =10,       // PTB4      ĸ���ϵ�AD0\n  ");  
    printf("ADC1_SE11 =11,       // PTB5      ĸ���ϵ�AD1\n ");
    printf("ADC1_SE12 =12,       // PTB6      ĸ���ϵ�AD2\n ");
    printf("ADC1_SE13 =13,       // PTB7      ĸ���ϵ�AD3\n ");
    printf("ADC1_SE14 =14,       // PTB10     ĸ���ϵ�AD4\n ");
    printf("ADC1_SE15 =15,       // PTB11     ĸ���ϵ�AD5\n ");
    printf("ADC1_SE16 =16,       // ADC1_SE16 ĸ���ϵ�AD6\n ");
    printf("ADC0_SE16 =16,       // ADC0_SE16 ĸ���ϵ�AD7\n ");
    printf("ADC0_SE11 =11,       // PTA8      ĸ���ϵ�AD8\n ");

    
    uint16_t batv0 = (uint16_t)(ADC_Get(0)*0.806);
    uint16_t batv1 = (uint16_t)(ADC_Get(1)*0.806);
    uint16_t batv2 = (uint16_t)(ADC_Get(2)*0.806);
    uint16_t batv3 = (uint16_t)(ADC_Get(3)*0.806);
    uint16_t batv4 = (uint16_t)(ADC_Get(4)*0.806);
    uint16_t batv5 = (uint16_t)(ADC_Get(5)*0.806);
    uint16_t batv6 = (uint16_t)(ADC_Get(6)*0.806);
    uint16_t batv7 = (uint16_t)(ADC_Get(7)*0.806);
    uint16_t batv8 = (uint16_t)(ADC_Get(8)*0.806);

    uint8_t key = 0;
    char txt[16];
    while(1)
    {
        /* ��ȡ ADCͨ��ֵ */
        batv0 = (uint16_t)(ADC_Get(0)*0.806);
        batv1 = (uint16_t)(ADC_Get(1)*0.806);
        batv2 = (uint16_t)(ADC_Get(2)*0.806);
        batv3 = (uint16_t)(ADC_Get(3)*0.806);
        batv4 = (uint16_t)(ADC_Get(4)*0.806);
        batv5 = (uint16_t)(ADC_Get(5)*0.806);
        batv6 = (uint16_t)(ADC_Get(6)*0.806);
        batv7 = (uint16_t)(ADC_Get(7)*0.806);
        batv8 = (uint16_t)(ADC_Get(8)*0.806);
          
        switch(KEY_Read(1))     //�������·�ҳ
        {
          case 1:
            OLED_CLS();          //LCD����
            key = 0;            //K0 ���� ��һҳ
            break;           
          case 2: 
            OLED_CLS();          //LCD����
            key = 1;            //K1 ���� �ڶ�ҳ
            break;
          case 3: 
            OLED_CLS();          //LCD����
            key = 2;            //K1 ���� �ڶ�ҳ
            break;
          default:
            
            break;
        }
        
        if(0 == key)
        {
            OLED_P8x16Str(4,0,(uint8_t*)"LQ ADC Test Bat"); 
            
            printf("\r\n/AD0***********************%5d mv\r\n ",batv0);
            sprintf(txt,"AD0:%5d mv ",batv0);
            OLED_P8x16Str(20,2,(uint8_t*)txt);
            
            printf("\r\n/AD1***********************%5d mv\r\n ",batv1);
            sprintf(txt,"AD1:%5d mv ",batv1);
            OLED_P8x16Str(20,4,(uint8_t*)txt);
            
            printf("\r\n/AD2***********************%5d mv\r\n ",batv2);
            sprintf(txt,"AD2:%5d mv ",batv2);
            OLED_P8x16Str(20,6,(uint8_t*)txt);
            
        }
        if(1 == key)
        {
            printf("\r\n/AD3***********************%5d mv\r\n ",batv3);
            sprintf(txt,"AD3:%5d mv ",batv3);
            OLED_P8x16Str(20,0,(uint8_t*)txt);
            
            printf("\r\n/AD4***********************%5d mv\r\n ",batv4);
            sprintf(txt,"AD4:%5d mv ",batv4);
            OLED_P8x16Str(20,2,(uint8_t*)txt);
            
            printf("\r\n/AD5***********************%5d mv\r\n ",batv5);
            sprintf(txt,"AD5:%5d mv ",batv5);
            OLED_P8x16Str(20,4,(uint8_t*)txt);
            
            printf("\r\n/AD6***********************%5d mv\r\n ",batv6);
            sprintf(txt,"AD6:%5d mv ",batv6);
            OLED_P8x16Str(20,6,(uint8_t*)txt);    
        }
        if(2 == key)
        {
            printf("\r\n/AD7***********************%5d mv\r\n ",batv7);
            sprintf(txt,"AD7:%5d mv ",batv7);
            OLED_P8x16Str(20,0,(uint8_t*)txt);
            
            printf("\r\n/AD8***********************%5d mv\r\n ",batv8);
            sprintf(txt,"AD8:%5d mv ",batv8);
            OLED_P8x16Str(20,2,(uint8_t*)txt);
               
        }
   
        LED_Reverse(1);    
        delayms(100);
    }
    
}
#else
void Test_ADC(void)
{
    LED_Init();
    UART_Init(UART4, 115200);
    
    ADC_Init(ADC0);
    ADC_Init(ADC1);
    
    TFTSPI_Init(1);                 //LCD��ʼ��  0:����  1������
    TFTSPI_CLS(u16BLUE);
    printf("ADC ��������");
    printf("ADC1_SE10 =10,       // PTB4      ĸ���ϵ�AD0\n  ");  
    printf("ADC1_SE11 =11,       // PTB5      ĸ���ϵ�AD1\n ");
    printf("ADC1_SE12 =12,       // PTB6      ĸ���ϵ�AD2\n ");
    printf("ADC1_SE13 =13,       // PTB7      ĸ���ϵ�AD3\n ");
    printf("ADC1_SE14 =14,       // PTB10     ĸ���ϵ�AD4\n ");
    printf("ADC1_SE15 =15,       // PTB11     ĸ���ϵ�AD5\n ");
    printf("ADC1_SE16 =16,       // ADC1_SE16 ĸ���ϵ�AD6\n ");
    printf("ADC0_SE16 =16,       // ADC0_SE16 ĸ���ϵ�AD7\n ");
    printf("ADC0_SE11 =11,       // PTA8      ĸ���ϵ�AD8\n ");

    TFTSPI_P8X16Str(2,0,"LQ ADC Test",u16RED,u16BLUE);
    uint16_t batv0 = (uint16_t)(ADC_Get(0)*0.806);
    uint16_t batv1 = (uint16_t)(ADC_Get(1)*0.806);
    uint16_t batv2 = (uint16_t)(ADC_Get(2)*0.806);
    uint16_t batv3 = (uint16_t)(ADC_Get(3)*0.806);
    uint16_t batv4 = (uint16_t)(ADC_Get(4)*0.806);
    uint16_t batv5 = (uint16_t)(ADC_Get(5)*0.806);
    uint16_t batv6 = (uint16_t)(ADC_Get(6)*0.806);
    uint16_t batv7 = (uint16_t)(ADC_Get(7)*0.806);
    uint16_t batv8 = (uint16_t)(ADC_Get(8)*0.806);

    char txt[16];
    while(1)
    {
        /* ��ȡ ADCͨ��ֵ */
        batv0 = (uint16_t)(ADC_Get(0)*0.806);
        batv1 = (uint16_t)(ADC_Get(1)*0.806);
        batv2 = (uint16_t)(ADC_Get(2)*0.806);
        batv3 = (uint16_t)(ADC_Get(3)*0.806);
        batv4 = (uint16_t)(ADC_Get(4)*0.806);
        batv5 = (uint16_t)(ADC_Get(5)*0.806);
        batv6 = (uint16_t)(ADC_Get(6)*0.806);
        batv7 = (uint16_t)(ADC_Get(7)*0.806);
        batv8 = (uint16_t)(ADC_Get(8)*0.806);

          
        
            TFTSPI_P8X16Str(4,0,(char*)"LQ ADC Test Bat",u16RED,u16BLUE); 
            
            printf("\r\n/AD0***********************%5d mv\r\n ",batv0);
            sprintf(txt,"AD0:%5d mv ",batv0);
            TFTSPI_P8X8Str(1,3,txt,u16RED,u16BLUE);
            
            printf("\r\n/AD1***********************%5d mv\r\n ",batv1);
            sprintf(txt,"AD1:%5d mv ",batv1);
            TFTSPI_P8X8Str(1,4,txt,u16RED,u16BLUE);
            
            printf("\r\n/AD2***********************%5d mv\r\n ",batv2);
            sprintf(txt,"AD2:%5d mv ",batv2);
            TFTSPI_P8X8Str(1,5,txt,u16RED,u16BLUE);
            
            printf("\r\n/AD3***********************%5d mv\r\n ",batv3);
            sprintf(txt,"AD3:%5d mv ",batv3);
            TFTSPI_P8X8Str(1,6,txt,u16RED,u16BLUE);
            
            printf("\r\n/AD4***********************%5d mv\r\n ",batv4);
            sprintf(txt,"AD4:%5d mv ",batv4);
            TFTSPI_P8X8Str(1,7,txt,u16RED,u16BLUE);
            
            printf("\r\n/AD5***********************%5d mv\r\n ",batv5);
            sprintf(txt,"AD5:%5d mv ",batv5);
            TFTSPI_P8X8Str(1,8,txt,u16RED,u16BLUE);
            
            printf("\r\n/AD6***********************%5d mv\r\n ",batv6);
            sprintf(txt,"AD6:%5d mv ",batv6);
            TFTSPI_P8X8Str(1,9,txt,u16RED,u16BLUE);   
            
            printf("\r\n/AD7***********************%5d mv\r\n ",batv7);
            sprintf(txt,"AD7:%5d mv ",batv7);
            TFTSPI_P8X8Str(1,10,txt,u16RED,u16BLUE);
            
            printf("\r\n/AD8***********************%5d mv\r\n ",batv8);
            sprintf(txt,"AD8:%5d mv ",batv8);
            TFTSPI_P8X8Str(1,11,txt,u16RED,u16BLUE);
             
   
        LED_Reverse(1);    
        delayms(100);
    }
    
}
#endif