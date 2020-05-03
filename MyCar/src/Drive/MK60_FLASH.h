#ifndef _MK60_FLASH_H_
#define _MK60_FLASH_H_

//k66����1024K�ĳ���Flash  
//1024K�ĳ���Flash��Ϊ256��������ÿ������4K��С
//    sector��4K��Ϊ������С��λ
//    ���֣�32b��Ϊд����С��λ

#include "common.h"

#define FLASH_SECTOR_SIZE     	    (4096)                  //������С 4k �ֽ�
#define FLASH_SECTOR_NUM        	(256)                   //������
#define FLASH_ALIGN_ADDR        	8                       //��ַ����������
typedef u64                    	FLASH_WRITE_TYPE;       //flash_write ����д�� ����������


/*
 * �����λ�������������
 */
typedef union
{
    uint32  DW;
    uint16  W[2];
    uint8   B[4];
    struct
    {
        uint32 b0: 1;
        uint32 b1: 1;
        uint32 b2: 1;
        uint32 b3: 1;
        uint32 b4: 1;
        uint32 b5: 1;
        uint32 b6: 1;
        uint32 b7: 1;
        uint32 b8: 1;
        uint32 b9: 1;
        uint32 b10: 1;
        uint32 b11: 1;
        uint32 b12: 1;
        uint32 b13: 1;
        uint32 b14: 1;
        uint32 b15: 1;
        uint32 b16: 1;
        uint32 b17: 1;
        uint32 b18: 1;
        uint32 b19: 1;
        uint32 b20: 1;
        uint32 b21: 1;
        uint32 b22: 1;
        uint32 b23: 1;
        uint32 b24: 1;
        uint32 b25: 1;
        uint32 b26: 1;
        uint32 b27: 1;
        uint32 b28: 1;
        uint32 b29: 1;
        uint32 b30: 1;
        uint32 b31: 1;
    };
} Dtype;    //sizeof(Dtype) Ϊ 4



/*
 *  ���ܣ�      ��ȡ flashָ����ַ���ݵ�������
 *  ������      sector_num      �����ţ�K60N512ʵ��ʹ��0~255��
 *              offset          ��ȡ�����ڲ�ƫ�Ƶ�ַ��0~2043 �� 4�ı�����
 *              len             ��Ŀ      sizeof(buff)
 *              buf             ��Ҫд������ݻ������׵�ַ
 *  ����ֵ��    ִ�н��(1�ɹ�)
*/
uint8_t FLASH_ReadBuff(uint16 sectorNo, uint16 offset, uint16 len, char *buf);


/*!
 *  @brief      ʹ�ú궨���flash�������ݶ�ȡ
 *  @param      sectorNo 		���������ţ�K66ʵ��ʹ��1~256��
 *  @param      offset	 		�������ڲ�ƫ�Ƶ�ַ��0~4095 �� 4�ı�����
 *  @param      type		 	��ȡ����������
 *  @return     				���ظ�����ַ������
 *  @notice     ������Ҫʹ��ǰ���  �������ڿ�ǰ�����������������sector_num�ǵ�����
 *  Sample usage:               FLASH_Read(1,0,uint32);//��ȡ������һ������ƫ��0��������Ϊuint32
 */
#define     FLASH_Read(sectorNo,offset,type)        (*(type *)((uint32_t)(((FLASH_SECTOR_NUM - sectorNo)*FLASH_SECTOR_SIZE) + (offset)))) 

/*!
 *  @brief      Flash ��ʼ��   
 *  @return     ��
 *  @notice     ʹ��Flashʱһ���ǵó�ʼ��
 *  Sample usage:  
 */
void FLASH_Init(void);


/*
 *  ���ܣ�   д�볤�ֽ����ݵ� flashָ����ַ
 *  ������   sector_num      ���������ţ�K66ʵ��ʹ��1~256��
 *           offset          д�������ڲ�ƫ�Ƶ�ַ��0~2043 �� 4�ı�����
 *           data            ��Ҫд�������
 *  ����ֵ�� ִ�н��(1�ɹ���0ʧ��)
 *  ����     flash_write(127,0,0xFFFFFFFE);        //����127,ƫ�Ƶ�ַΪ0,д������:0xFFFFFFFE
 */
uint8 flash_write(uint16 sector_num, uint16 offset, FLASH_WRITE_TYPE data);

/*!
 *  @brief      ��������
 *  @param      sectorNo 		���������ţ�K66ʵ��ʹ��1~256��
 *  @return     ����1����ʧ�ܣ�����0�����ɹ�
 *  @notice     
 *  Sample usage: uint32 dat = FLASH_GetSectorSize(10);
 */
uint8 FLASH_EraseSector(uint32 SectorNum);


/*!
 *  @brief      ������д������
 *  @param      sectorNo 		���������ţ�K66ʵ��ʹ��1~256��
 *  @param      offset	 		�������ڲ�ƫ�Ƶ�ַ��0~4095 �� 4�ı�����
 *  @param      buf		 	    �����׵�ַ
 *  @param      len		 	    ���ݳ���
 *  @return     				���ظ�����ַ������
 *  @notice     ������Ҫʹ��ǰ���  �������ڿ�ǰ�����������������sector_num�ǵ�����
 *  Sample usage:               FLASH_Read(1,0,uint32);//��ȡ������һ������ƫ��0��������Ϊuint32
 */
uint8 FLASH_WriteBuf(uint32 SectorNum, const uint8 *buf, uint32 len, uint32 offset);



#endif //_FLASH_H_