/*  【Crystal】 50.000Mhz
    【busclock】 40.000MHz
    【pllclock】200.000MHz
    ICM20602 硬件SPI接口,读取速度比较快，大概20us 
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
      NVIC_SetPriorityGrouping(0x07 - 2); //4个抢占优先级 4个子优先级 
      Test_ICM20602();
     
	
}                                                
