/*-----------------------------------------------------------------------------------------------------
【平    台】龙邱K60核心板-智能车板
【编    写】LQ-005
【E-mail  】chiusir@163.com
【软件版本】V1.0，龙邱开源代码，仅供参考，后果自负
【最后更新】2019年04月02日
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【编译平台】IAR 8.2
【功    能】FLASH 读写例子
【注意事项】不要写靠前的扇区  会覆盖程序
-------------------------------------------------------------------------------------------------------*/
#include "include.h"



/*------------------------------------------------------------------------------------------------------
【函    数】Test_Flash
【功    能】测试flash 读写
【参    数】无
【返 回 值】无
【实    例】Test_Flash(); 
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void Test_Flash(void)
{
	UART_Init(UART4, 115200);
    OLED_Init();                  //LCD初始化
    OLED_CLS();                   //LCD清屏
	KEY_Init();
	FLASH_Init();
    OLED_P8x16Str(15,0,"LQ FLASH Test"); 
    printf("\r\nLQ FLASH Test");
	printf("\r\n不要写靠前的扇区  会覆盖程序");
	
    uint8_t  write_data[8] = {1,2,3,4,5,6,7,8};
    uint8_t  read_data[8]  = {0};
    
	FLASH_EraseSector(1);
    FLASH_WriteBuf(1,write_data, 8, 0);//写入扇区
    
	/* 从倒数第一个扇区 0偏移位置开始 读出结构体数据 */
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
