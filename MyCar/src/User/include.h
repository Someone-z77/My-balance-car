#ifndef INCLUDE_H_
#define INCLUDE_H_

/*
 * ����Cortex-M�ں˵�ͨ��ͷ�ļ�
 */
#include    <stdio.h>                       //printf
#include    <string.h>                      //memcpy
#include    <stdlib.h>                      //malloc
#include "math.h"
#include "common.h" 
#include "MK66F18.h"   /* �Ĵ���ӳ��ͷ�ļ� */
#include "core_cm4.h"         /* �ں��ļ����������ж����ȼ� */

/*----------------------------------------------------------------
                   �ײ������ļ�
------------------------------------------------------------------*/
#include "MK60_ADC.h"              /* ����ADCģ�� */
#include "MK60_GPIO.h"             /* ����GPIOģ�� */
#include "MK60_GPIO_Cfg.h"         /* ����GPIOģ�� ��51��IO���� */
#include "MK60_PLL.h"              /* ����ʱ��Ƶ������ */
#include "MK60_UART.h"             /* ���ڴ���ģ�� */
#include "MK60_PIT.h"              /* ����PIT��ʱ��ģ�� */
#include "MK60_FTM.h"              /* ����FTM��ʱ��ģ�� */
#include "MK60_CMT.h"              /* ����CMT��ʱ��ĳ�� */
#include "MK60_IIC.h"              /* ����IICģ�� */
#include "MK60_DMA.h"              /* ����DMAģ�� */
#include "MK60_LPTMR.h"            /* ����LPTMR��ʱ��ģ�� */
#include "MK60_WDOG.h"             /* ���ڿ��Ź� */
#include "MK60_SYSTICK.h"          /* systick �ں˶�ʱ�� */
#include "MK60_FLASH.h"            /* Flash ��д */
#include "MK60_SPI.h"
/*----------------------------------------------------------------
                    ����ģ������
------------------------------------------------------------------*/
#include "LQ_LED.h"                /* LED         ���� */
#include "LQ_KEY.h"                /* KEY         ���� */
#include "LQ_PIT.h"                /* PIT         ���� */
#include "LQ_UART.h"               /* UART        ���� */
#include "LQ_LPTMR.h"              /* LPTMR       ���� */
#include "LQ_SYSTICK.h"            /* SYSTICK     ���� */
#include "LQ_12864.h"              /* OLED        ���� */
#include "LQ_SGP18T.h"             /* TFT1.8      ���� */
#include "LQ_ADC.h"                /* ADC         ���� */
#include "LQ_WDOG.h"               /* WDOG        ���� */
#include "LQ_SD5.h"                /* ���        ���� */
#include "LQ_MOTOR.h"              /* ���        ���� */
#include "LQ_MT9V034.h"            /* ����        ���� */
#include "LQ_CAMERA.h"             /* ����ͷ      ���� */
#include "LQ_FLASH.h"              /* FLASH       ���� */
#include "LQ_CCD.h"                /* CCD         ���� */
#include "LQ_Ultrasonic.h"         /* ���������  ���� */
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
/* ��OLED ����ʾ������TFT1.8��ʾ */
#define LQ_OLED     
//#define LQ_TFT1_8       
   

#endif