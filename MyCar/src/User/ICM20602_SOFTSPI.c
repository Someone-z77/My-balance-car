#include "include.h"
#include "ICM20602_SOFTSPI.h"


/**
  * @brief    模拟SPI 延时函数
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/28 星期二
  */
static inline void SPI_SoftDelay(void)
{
    asm("NOP");
    asm("NOP");
    asm("NOP");
}
/**
  * @brief    模拟SPI初始化
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftInit(void)
{
    GPIO_PinInit(SPI_SCK,  GPO, CPOL);
    GPIO_PinInit(SPI_MISO, GPI, 0);
    GPIO_PinInit(SPI_MOSI, GPO, 0);
    GPIO_PinInit(SPI_CS,   GPO, 1);
    SPI_SCK_IDLE;
    
    
}

/**
  * @brief    模拟SPI读写n 字节
  *
  * @param    buff[] 存放要写入的值 写入后存放读取的值
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/28 星期二
  */
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len)
{
    SPI_CS_OUT = 0;
    SPI_SCK_IDLE;
//    SPI_SoftDelay();
#if CPHA    //第二个时钟跳边沿
    do
    {
        for(uint8_t i = 0; i < 8; i++)
        {
            SPI_MOSI_OUT = ((*buff) >= 0x80);
            SPI_SCK_ACTIVE;
            (*buff) = (*buff)<<1;
            
//            SPI_SoftDelay();
            SPI_SCK_IDLE;
//            SPI_SoftDelay();
            (*buff) |= SPI_MISO_IN;          
        }
        buff++;
    }while(--len);
#else
    do
    {
        for(uint8_t i = 0; i < 8; i++)
        {

            SPI_MOSI_OUT = ((*buff) >= 0x80);
            (*buff) = (*buff)<<1;
            SPI_SCK_ACTIVE;
            SPI_SoftDelay();
            (*buff) |= SPI_MISO_IN;
            SPI_SCK_IDLE;
            SPI_SoftDelay();           
        }
        buff++;
    }while(--len);
    
    
#endif
    SPI_CS_OUT = 1;
}
