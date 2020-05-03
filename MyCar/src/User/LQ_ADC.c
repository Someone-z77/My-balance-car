#include "include.h"
#include "LQ_ADC.h"


/*------取中值后的100个数据后再取均值------*/
uint16_t ADC_Get(uint8_t num)
{
    switch(num)
    {
      case 0:
        return ADC_Ave(ADC1,ADC1_SE10,ADC_12bit,100);
        break;
        
      case 1:
        return ADC_Ave(ADC1,ADC1_SE11,ADC_12bit,100);
        break;
        
      case 2:
        return ADC_Ave(ADC1,ADC1_SE12,ADC_12bit,100);
        break;
        
      case 3:
        return ADC_Ave(ADC1,ADC1_SE13,ADC_12bit,100);
        break;
        
      case 4:
        return ADC_Ave(ADC1,ADC1_SE14,ADC_12bit,100);
        break;
        
      case 5:
        return ADC_Ave(ADC1,ADC1_SE15,ADC_12bit,100);
        break;
        
      case 6:
        return ADC_Ave(ADC1,ADC1_SE16,ADC_12bit,100);
        break;
        
      case 7:
        return ADC_Ave(ADC0,ADC0_SE16,ADC_12bit,100);
        break;
        
      case 8:
        return ADC_Ave(ADC0,ADC0_SE11,ADC_12bit,100);
        break;
        
        
      default:
        return 0;   
    }
}



void  AD_Get_Go()
{
    UART_Init(UART4, 115200);
    
    ADC_Init(ADC0);
    ADC_Init(ADC1);
    
    uint16_t ad_left[2]={0},ad_right[2]={0};
  
    ad_left[0]=ADC_Get(0);   ad_left[1]=ADC_Get(1);
    ad_right[0]=ADC_Get(2);   ad_right[1]=ADC_Get(3);
    
    printf("%d    ",ad_left[0]);
    printf("%d    ",ad_left[1]);
    printf("%d    ",ad_right[0]);
    printf("%d\n",ad_right[1]);
          
}


