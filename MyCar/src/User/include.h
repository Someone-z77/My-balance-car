#ifndef INCLUDE_H_
#define INCLUDE_H_

/*
 * 包含Cortex-M内核的通用头文件
 */
#include    <stdio.h>                       //printf
#include    <string.h>                      //memcpy
#include    <stdlib.h>                      //malloc
#include "math.h"
#include "common.h" 
#include "MK66F18.h"   /* 寄存器映像头文件 */
#include "core_cm4.h"         /* 内核文件用于设置中断优先级 */

/*----------------------------------------------------------------
                   底层驱动文件
------------------------------------------------------------------*/
#include "MK60_ADC.h"              /* 用于ADC模块 */
#include "MK60_GPIO.h"             /* 用于GPIO模块 */
#include "MK60_GPIO_Cfg.h"         /* 用于GPIO模块 类51的IO操作 */
#include "MK60_PLL.h"              /* 用于时钟频率设置 */
#include "MK60_UART.h"             /* 用于串口模块 */
#include "MK60_PIT.h"              /* 用于PIT定时器模块 */
#include "MK60_FTM.h"              /* 用于FTM定时器模块 */
#include "MK60_CMT.h"              /* 用于CMT定时器某块 */
#include "MK60_IIC.h"              /* 用于IIC模块 */
#include "MK60_DMA.h"              /* 用于DMA模块 */
#include "MK60_LPTMR.h"            /* 用于LPTMR定时器模块 */
#include "MK60_WDOG.h"             /* 用于看门狗 */
#include "MK60_SYSTICK.h"          /* systick 内核定时器 */
#include "MK60_FLASH.h"            /* Flash 读写 */
#include "MK60_SPI.h"
/*----------------------------------------------------------------
                    龙邱模块驱动
------------------------------------------------------------------*/
#include "LQ_LED.h"                /* LED         例子 */
#include "LQ_KEY.h"                /* KEY         例子 */
#include "LQ_PIT.h"                /* PIT         例子 */
#include "LQ_UART.h"               /* UART        例子 */
#include "LQ_LPTMR.h"              /* LPTMR       例子 */
#include "LQ_SYSTICK.h"            /* SYSTICK     例子 */
#include "LQ_12864.h"              /* OLED        驱动 */
#include "LQ_SGP18T.h"             /* TFT1.8      驱动 */
#include "LQ_ADC.h"                /* ADC         例子 */
#include "LQ_WDOG.h"               /* WDOG        例子 */
#include "LQ_SD5.h"                /* 舵机        例子 */
#include "LQ_MOTOR.h"              /* 电机        例子 */
#include "LQ_MT9V034.h"            /* 神眼        驱动 */
#include "LQ_CAMERA.h"             /* 摄像头      例子 */
#include "LQ_FLASH.h"              /* FLASH       例子 */
#include "LQ_CCD.h"                /* CCD         例子 */
#include "LQ_Ultrasonic.h"         /* 超声波测距  例子 */
#include "ANO_DT.h"
#include "LQ_ICM20602.h"
#include "IRQ_Handler.h"

#include "status.h"
#include "fsl_edma.h"
#include "Uart_DMA.h"
//-----------------------------
#include "My  Balance.h"
#include "My Direction.h"
#include "My Speed.h"
//-----------------------------
/* 在OLED 上显示或者在TFT1.8显示 */
#define LQ_OLED     
//#define LQ_TFT1_8       
   

#endif