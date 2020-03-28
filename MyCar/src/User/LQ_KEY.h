#ifndef __LQ_KEY_H
#define __LQ_KEY_H

/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】测试按键  
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_KEY(void);


/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】按键处理函数
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】0：无按键按下 1：按键1按下  2:按键2按下  3:按键3按下
【参数值】mode:0,不支持连续按;1,支持连续按;
【例子  】KEY_Read(0);   //检测三个按键哪个按下
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
uint8_t KEY_Read(uint8_t mode);


/*------------------------------------------------------------------------------------------------------
【函    数】LED_Init
【功    能】初始化核心板和母板上的LED
【参    数】无
【返 回 值】无
【实    例】LED_Init(); //初始化LED
【注意事项】
--------------------------------------------------------------------------------------------------------*/
void KEY_Init(void);



/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【作  者】LQ-005
【功能说明】测试按键外部中断  
【软件版本】V1.0
【最后更新】2017年11月24日 
【函数名】
【返回值】无
【参数值】无
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
void Test_ExtiKEY(void);
#endif