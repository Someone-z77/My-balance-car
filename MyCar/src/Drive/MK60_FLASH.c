#include "include.h"
#include "MK60_FLASH.h"

//�궨�� FCCOB Number
#define     FCMD        FTFE_FCCOB0         //FTFL ����

#define     FADDR2      FTFE_FCCOB1         //Flash address [23:16]
#define     FADDR1      FTFE_FCCOB2         //Flash address [15:8]
#define     FADDR0      FTFE_FCCOB3         //Flash address [7:0]
//Must be 64-bit aligned (Flash address [2:0] = 000)  8�ֽڶ���

#define     FDATA0      FTFE_FCCOB4         //Data Byte 0       //ע��һ�㣬4�ֽ�����FDATA3�����λ��FDATA0�����λ
#define     FDATA1      FTFE_FCCOB5         //Data Byte 1
#define     FDATA2      FTFE_FCCOB6         //Data Byte 2
#define     FDATA3      FTFE_FCCOB7         //Data Byte 3
#define     FDATA4      FTFE_FCCOB8         //Data Byte 4
#define     FDATA5      FTFE_FCCOB9         //Data Byte 5
#define     FDATA6      FTFE_FCCOBA         //Data Byte 6
#define     FDATA7      FTFE_FCCOBB         //Data Byte 7

//FCMD ����
#define     RD1BLK    0x00   // ������Flash
#define     RD1SEC    0x01   // ����������
#define     PGMCHK    0x02   // д����
#define     RDRSRC    0x03   // ��Ŀ������(8�ֽ�)
#define     PGM8      0x07   // д�볤��(8�ֽ�)
#define     ERSBLK    0x08   // ��������Flash
#define     ERSSCR    0x09   // ����Flash����
#define     PGMSEC    0x0B   // д������
#define     RD1ALL    0x40   // �����еĿ�
#define     RDONCE    0x41   // ֻ��һ��
#define     PGMONCE   0x43   // ֻдһ��
#define     ERSALL    0x44   // �������п�
#define     VFYKEY    0x45   // ��֤���ŷ���Կ��
#define     PGMPART   0x80   // д�����
#define     SETRAM    0x81   // �趨FlexRAM����


void flash_delayms(uint16_t ms)
{
    while(ms--)
    {
        for(int i = 0; i < 100000; i++)
        {
            __asm("NOP");
        }
    }

}

/*!
 *  ���ܣ�      Flash����
 *  ����ֵ��    ����ִ�н��(1�ɹ���0ʧ��)
 */
uint8 flash_cmd()
{
    //д FTFL_FSTAT ���� Flash����
    FTFE_FSTAT =    (0
                     |  FTFE_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                     |  FTFE_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                     |  FTFE_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                     |  FTFE_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                    );

    while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK));    // �ȴ��������

    // �������־
    if( FTFE_FSTAT & (FTFE_FSTAT_ACCERR_MASK | FTFE_FSTAT_RDCOLERR_MASK | FTFE_FSTAT_FPVIOL_MASK | FTFE_FSTAT_MGSTAT0_MASK))
    {
        return 0 ;                                  //ִ���������
    }else{
        return 1;                                   //ִ������ɹ�
    }

}

    



//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLASH��ʼ��
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void FLASH_Init(void)
{
    // ���FlashԤ��ȡ������
    FMC_PFB01CR |= FMC_PFB01CR_S_B_INV_MASK;      //
    //FMC_PFB23CR |= FMC_PFB23CR_S_B_INV_MASK;

    while(!(FTFE_FSTAT & FTFE_FSTAT_CCIF_MASK));    // �ȴ��������

    FTFE_FSTAT =    (0
                     |  FTFE_FSTAT_CCIF_MASK        // ָ����ɱ�־(д1��0)
                     |  FTFE_FSTAT_RDCOLERR_MASK    // ����ͻ�����־(д1��0)
                     |  FTFE_FSTAT_ACCERR_MASK      // ���ʴ����־λ(д1��0)
                     |  FTFE_FSTAT_FPVIOL_MASK      // �Ƿ����ʱ�����־λ(д1��0)
                    );
    flash_delayms(10);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLASH��������
//  @param      SectorNum 		���������ţ�K66ʵ��ʹ��1~256��
//  @return     				����1����ʧ�ܣ�����0�����ɹ�
//  @since      v1.0
//  Sample usage:               uint32 dat = FLASH_GetSectorSize(10);
//-------------------------------------------------------------------------------------------------------------------
uint8 FLASH_EraseSector(uint32 SectorNum)
{
    uint32 addr = (FLASH_SECTOR_NUM - SectorNum) * FLASH_SECTOR_SIZE;

    // ���ò�������
    FCMD = ERSSCR;

    // ����Ŀ���ַ
    FADDR2 = ((Dtype *)&addr)->B[2];
    FADDR1 = ((Dtype *)&addr)->B[1];
    FADDR0 = ((Dtype *)&addr)->B[0];

    if(flash_cmd() == 0)
    {
        return 0;
    }

    if(SectorNum == 0)
    {
        return flash_write(SectorNum,0x000408,(u64)0xFFFFFFFEFFFFFFFF);
    }

    return 1;
}


/*
 *  ���ܣ�   д�볤�ֽ����ݵ� flashָ����ַ
 *  ������   sector_num      ���������ţ�K66ʵ��ʹ��1~256��
 *           offset          д�������ڲ�ƫ�Ƶ�ַ��0~2043 �� 4�ı�����
 *           data            ��Ҫд�������
 *  ����ֵ�� ִ�н��(1�ɹ���0ʧ��)
 *  ����     flash_write(127,0,0xFFFFFFFE);        //����127,ƫ�Ƶ�ַΪ0,д������:0xFFFFFFFE
 */
uint8 flash_write(uint16 sector_num, uint16 offset, FLASH_WRITE_TYPE data)
{
    uint32 addr = (FLASH_SECTOR_NUM - sector_num) * FLASH_SECTOR_SIZE  + offset ;
    uint32 tmpdata;

    // ����Ŀ���ַ
    FADDR2 = ((Dtype *)&addr)->B[2];
    FADDR1 = ((Dtype *)&addr)->B[1];
    FADDR0 = ((Dtype *)&addr)->B[0];

    // ���� ��32λ����
    tmpdata = (uint32)data;

    FDATA0 = ((Dtype *)&tmpdata)->B[3];                    // ����д������
    FDATA1 = ((Dtype *)&tmpdata)->B[2];
    FDATA2 = ((Dtype *)&tmpdata)->B[1];
    FDATA3 = ((Dtype *)&tmpdata)->B[0];

    // ���ò�������
    FCMD = PGM8;

    // ���� ��32λ����
    tmpdata = (uint32)(data>>32);

    FDATA4 = ((Dtype *)&tmpdata)->B[3];                 // ����д������
    FDATA5 = ((Dtype *)&tmpdata)->B[2];
    FDATA6 = ((Dtype *)&tmpdata)->B[1];
    FDATA7 = ((Dtype *)&tmpdata)->B[0];

    if(flash_cmd() == 0)
    {
        return 0;
    }

    return 1;  //�ɹ�ִ��

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      FLASH����д�뵽����
//  @param      SectorNum 		��Ҫд����������
//  @param      *buf	 		�����׵�ַ
//  @param      len		 		д����ֽ��� �ر�����һ��uint16�����������ֽ� һ��uint32�������ĸ��ֽ�
//  @param      offset		 	����Ϊ4��������
//  @return     				����1д��ʧ�ܣ�����0д��ɹ�
//  @since      v1.0
//  Sample usage:               FLASH_WriteSector(10,(const uint8 *)buf,4,0);//��buf���������ǰ��λ����д�뵽10������(ÿһλ��uint8����)
//-------------------------------------------------------------------------------------------------------------------
uint8 FLASH_WriteBuf(uint32 SectorNum, const uint8 *buf, uint32 len, uint32 offset)
{
    uint32  size;

    uint32  addr;
    uint32  data;
    
	addr = (uint32)(FLASH_SECTOR_NUM - SectorNum)*FLASH_SECTOR_SIZE + offset;

	// ����д������
    FCMD = PGM8;

    for(size = 0; size < len; size += FLASH_ALIGN_ADDR )
    {

        // ����Ŀ���ַ
        FADDR2 = ((Dtype *)&addr)->B[2];
        FADDR1 = ((Dtype *)&addr)->B[1];
        FADDR0 = ((Dtype *)&addr)->B[0];

        // ���� ��32λ����
        data =  *(uint32 *)buf;

        FDATA0 = ((Dtype *)&data)->B[3];                    // ����д������
        FDATA1 = ((Dtype *)&data)->B[2];
        FDATA2 = ((Dtype *)&data)->B[1];
        FDATA3 = ((Dtype *)&data)->B[0];


        // ���� ��32λ����
        data = *(uint32 *)(buf+4);

        FDATA4 = ((Dtype *)&data)->B[3];                    // ����д������
        FDATA5 = ((Dtype *)&data)->B[2];
        FDATA6 = ((Dtype *)&data)->B[1];
        FDATA7 = ((Dtype *)&data)->B[0];

        if(flash_cmd() == 0)
        {
            return 0;
        }

        addr += FLASH_ALIGN_ADDR;
        buf += FLASH_ALIGN_ADDR;
    }
    return 1;  //�ɹ�ִ��
}


/*
 *  ���ܣ�      ��ȡ flashָ����ַ���ݵ�������
 *  ������      sector_num      �����ţ�K60N512ʵ��ʹ��0~255��
 *              offset          ��ȡ�����ڲ�ƫ�Ƶ�ַ��0~2043 �� 4�ı�����
 *              cnt             ��Ŀ      sizeof(buff)
 *              buf             ��Ҫд������ݻ������׵�ַ
 *  ����ֵ��    ִ�н��(1�ɹ�)
*/
uint8_t FLASH_ReadBuff(uint16 sectorNo, uint16 offset, uint16 cnt, char *buf)
{
    u32 wAddr = 0;
    wAddr = (FLASH_SECTOR_NUM - sectorNo) * FLASH_SECTOR_SIZE + offset;
    while (cnt--)
        *buf++=*(u8*)wAddr++;
    return 1;
}