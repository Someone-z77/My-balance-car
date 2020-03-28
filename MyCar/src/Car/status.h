#ifndef __STATUS_H
#define __STATUS_H

#include "stdint.h"

typedef struct 
{
    volatile uint8_t stop              :        1;    //ͣ����־λ
    volatile uint8_t low_power_flag    :        1;    //�͵�ѹ��־λ
    volatile uint8_t straight_speed    :        1;    //ֱ����־λ
    volatile uint8_t brake_speed       :        1;    //�����־λ
    volatile uint8_t curve_speed       :        1;    //�����־λ
    volatile uint8_t camera_run        :        1;    //ʹ������ͷ 
    volatile uint8_t electromagnetism  :        1;    //ʹ�õ��
    volatile uint8_t ins_calibration   :        1;    //������У׼
    
    volatile uint8_t txOnGoing         :        1;    //����TX���ڷ��ͱ�־λ
    volatile uint8_t rxOnGoing         :        1;    //����RX���ڽ��ձ�־λ
    volatile uint8_t txBufferFull      :        1;    //����TX���ͼĴ�������־λ
    volatile uint8_t rxBufferEmpty     :        1;    //����RX���ռĴ����ձ�־λ
    
    volatile uint8_t get_pid_group1    :        1;    //��λ������Ϊ1ʱ����Ƭ����Ҫ����pid��������λ��
}volatile status_t;

extern status_t car_status;

#endif