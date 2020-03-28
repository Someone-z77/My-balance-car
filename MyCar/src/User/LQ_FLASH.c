/*-----------------------------------------------------------------------------------------------------
��ƽ    ̨������K60���İ�-���ܳ���
����    д��LQ-005
��E-mail  ��chiusir@163.com
������汾��V1.0������Դ���룬�����ο�������Ը�
�������¡�2019��04��02��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
������ƽ̨��IAR 8.2
����    �ܡ�FLASH ��д����
��ע�������Ҫд��ǰ������  �Ḳ�ǳ���
-------------------------------------------------------------------------------------------------------*/
#include "include.h"



/*------------------------------------------------------------------------------------------------------
����    ����Test_Flash
����    �ܡ�����flash ��д
����    ������
���� �� ֵ����
��ʵ    ����Test_Flash(); 
��ע�����
--------------------------------------------------------------------------------------------------------*/
void Test_Flash(void)
{
	UART_Init(UART4, 115200);
    OLED_Init();                  //LCD��ʼ��
    OLED_CLS();                   //LCD����
	KEY_Init();
	FLASH_Init();
    OLED_P8x16Str(15,0,"LQ FLASH Test"); 
    printf("\r\nLQ FLASH Test");
	printf("\r\n��Ҫд��ǰ������  �Ḳ�ǳ���");
	
    uint8_t  write_data[8] = {1,2,3,4,5,6,7,8};
    uint8_t  read_data[8]  = {0};
    
	FLASH_EraseSector(1);
    FLASH_WriteBuf(1,write_data, 8, 0);//д������
    
	/* �ӵ�����һ������ 0ƫ��λ�ÿ�ʼ �����ṹ������ */
	read_data[0] = FLASH_Read(1, 0, uint8_t);
    read_data[1] = FLASH_Read(1, 1, uint8_t);
    read_data[2] = FLASH_Read(1, 2, uint8_t);
    read_data[3] = FLASH_Read(1, 3, uint8_t);
    read_data[4] = FLASH_Read(1, 4, uint8_t);
    read_data[5] = FLASH_Read(1, 5, uint8_t);
    read_data[6] = FLASH_Read(1, 6, uint8_t);
    read_data[7] = FLASH_Read(1, 7, uint8_t);

	

	if(read_data[0] == write_data[0] 
       &&read_data[1] == write_data[1]
       &&read_data[2] == write_data[2]
       &&read_data[3] == write_data[3]
       &&read_data[4] == write_data[4]
       &&read_data[5] == write_data[5]
       &&read_data[6] == write_data[6]
       &&read_data[7] == write_data[7])    
    {
        printf("Flash is OK \n");
    }
    else
    {
        printf("Flash is fail \n");
    }
        
        
        
	while(1);

}
