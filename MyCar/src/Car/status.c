#include "status.h"


status_t car_status = 
{
    .stop                = 1,  //ͣ����־λ
    .low_power_flag      = 0,  //�͵�ѹ��־λ
    .straight_speed      = 1,  //ֱ����־λ
    .brake_speed         = 0,  //�����־λ
    .curve_speed         = 0,  //�����־λ
    .camera_run          = 1,  //ʹ������ͷ 
    .electromagnetism    = 1,  //ʹ�õ��
    .ins_calibration     = 1,  //������У׼
    
    /*ʹ��DMA���ͱ�־λ*/
    .txOnGoing           = 0,  //����TX���ڷ��ͱ�־λ
    .rxOnGoing           = 0,  //����RX���ڽ��ձ�־λ
    .txBufferFull        = 0,  //����TX���ͼĴ�������־λ
    .rxBufferEmpty       = 0,  //����RX���ռĴ����ձ�־λ
    
    .get_pid_group1      = 0,  //��λ������Ϊ1ʱ����Ƭ����Ҫ����pid��������λ��
    
    
    
};


