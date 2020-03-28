#ifndef __ICM20602_SOFTSPI_H
#define __ICM20602_SOFTSPI_H

/* 注意 ICM20602 时钟空闲时为高电平  在时钟第二个跳边沿传输数据  与NRF2401的不同，所以SPI不通用  */
/* 0: 时钟空闲时刻为低电平   1：时钟空闲时刻为高电平*/ 
#define CPOL  1

/* 0：时钟第一个跳边沿传输数据   1：时钟的第二个跳边沿传输数据 */
#define CPHA  1 



#define SPI_SCK      PTE2
#define SPI_MISO     PTE3
#define SPI_MOSI     PTE4
#define SPI_CS       PTE5   

#if CPOL
#define SPI_SCK_IDLE      PTE2_OUT = 1
#define SPI_SCK_ACTIVE    PTE2_OUT = 0
#else
#define SPI_SCK_IDLE      PTE2_OUT = 0
#define SPI_SCK_ACTIVE    PTE2_OUT = 1
#endif

#define SPI_MOSI_OUT      PTE4_OUT
#define SPI_MISO_IN       PTE3_IN
#define SPI_CS_OUT        PTE5_OUT


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
void SPI_SoftInit(void);

/**
  * @brief    模拟SPI读写n 字节
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
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len);

#endif
