/*  ��Crystal�� 50.000Mhz
    ��busclock�� 40.000MHz
    ��pllclock��200.000MHz
    ICM20602 Ӳ��SPI�ӿ�,��ȡ�ٶȱȽϿ죬���20us 
    GND   ------   GND
    3-5V  ------   3.3V
    SCL   ------   PTE2
    SDA   ------   PTE1
    SA    ------   PTE3
    CS    ------   PTE0*/

#include "include.h" 

void main(void)
{   
	
      PLL_Init(PLL180);
      NVIC_SetPriorityGrouping(0x07 - 2); //4����ռ���ȼ� 4�������ȼ� 
      Test_ICM20602();
     
	
}                                                
