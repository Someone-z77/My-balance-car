#include "include.h"
#include "LQ_UART.h"
#include "MK60_UART.h"
/*------------------------------------------------------------------------------------------------------
【函    数】Test_Uart
【功    能】测试UART 
【参    数】无
【返 回 值】无
【实    例】Test_Uart(); //测试串口
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void Test_Uart(void)
{
    LED_Init();
    
    UART_Init(UART4, 115200);
    
    /* 优先级配置 抢占优先级1  子优先级2   越小优先级越高  抢占优先级可打断别的中断 */
    NVIC_SetPriority(UART4_RX_TX_IRQn,NVIC_EncodePriority(NVIC_GetPriorityGrouping(),1,2));
    
    NVIC_EnableIRQ(UART4_RX_TX_IRQn);			          //使能UART4_RX_TX_IRQn的中断
    
    uint8_t count = 0;
    while(1)
    {
        printf("串口测试例程 第 %d 次打印 \n ", count++);
        UART_PutStr(UART4, "UART_PutStr is OK \n");
        LED_Reverse(0);
        delayms(1000);
    }
    
    
}
/*山外数据传输*/
void vcan_sendware(char *buff)
{   
    UART_PutChar(UART4,0x03);
    UART_PutChar(UART4,0xfc);
    UART_PutChar(UART4,*buff);
    UART_PutChar(UART4,0xfc);
    UART_PutChar(UART4,0x03);
}

