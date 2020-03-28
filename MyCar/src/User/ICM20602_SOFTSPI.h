#ifndef __ICM20602_SOFTSPI_H
#define __ICM20602_SOFTSPI_H

/* ע�� ICM20602 ʱ�ӿ���ʱΪ�ߵ�ƽ  ��ʱ�ӵڶ��������ش�������  ��NRF2401�Ĳ�ͬ������SPI��ͨ��  */
/* 0: ʱ�ӿ���ʱ��Ϊ�͵�ƽ   1��ʱ�ӿ���ʱ��Ϊ�ߵ�ƽ*/ 
#define CPOL  1

/* 0��ʱ�ӵ�һ�������ش�������   1��ʱ�ӵĵڶ��������ش������� */
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
  * @brief    ģ��SPI��ʼ��
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/28 ���ڶ�
  */
void SPI_SoftInit(void);

/**
  * @brief    ģ��SPI��дn �ֽ�
  *
  * @param    
  *
  * @return   
  *
  * @note     
  *
  * @example  
  *
  * @date     2019/5/28 ���ڶ�
  */
void SPI_SoftRadeWriteNbyte(uint8_t *buff, uint16_t len);

#endif
