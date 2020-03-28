// Header:
// File Name: ���������������ֲ��APM
// Author:Z
// Date:2018/08/03

#include "Scheduler.h"
#include "status.h"
#include "include.h"


extern sched_task_t sched_task[];

//�����������ʼ��
uint8_t num_task;  //��������
void shceduler_init(void)
{   
//    num_task = sizeof (sched_task) / sizeof (sched_task[0]);
}

static uint32_t tick_counter = 0;  //shceduler_runִ�д���
void shceduler_tick()
{
    tick_counter++;
}

/*
  run one tick
  this will run as many scheduler tasks as we can in the specified time
 */
//#define UART_DEBUG
//���������
void shceduler_run(uint32_t time_available)
{
    uint64_t now;
    uint16_t dt;
    uint16_t interval_ticks;
    
    for (uint8_t i = 0; i < num_task; i++)
    {
        now = systime.get_time_us();//��ȡ��ǰʱ��
        dt = tick_counter - sched_task[i].last_tick_counter;//���������ϴ����е����������������
        interval_ticks = sched_task[i].interval_ticks;  //�������������������һ��
        
        if( dt >= interval_ticks)
        {
            //����ʱʹ�ã�����ʱ��δ���У�˵���������������̫������shceduler_run�Ŀ�����ʱ��̫��
            if (dt >= interval_ticks*2)
            {
                // we've slipped a whole run of this task!
#ifdef UART_DEBUG
                printf("Scheduler slip task[%u] (%u/%u/%u)\n",
                       (unsigned)i,
                       (unsigned)dt,
                       (unsigned)interval_ticks,
                       (unsigned)sched_task[i].max_time_micros);
#endif //UART_DEBUG
                
            }
            if (sched_task[i].max_time_micros <= time_available)
            {
                //��������
                sched_task[i].task_func();
                //����last_tick_counter
                sched_task[i].last_tick_counter = tick_counter;
                
#ifdef UART_DEBUG
                uint32_t end_time = systime.get_time_us() - now;
                //����������й�����ʱ�䳬��shceduler_run�Ŀ�����ʱ��time_available��˵�������max_time_micros����С��
                if(end_time > time_available)
                {
                    printf("Scheduler slip task[%u] (%u/%u)\n",
                           (unsigned)i,
                           (unsigned)end_time,
                           (unsigned)sched_task[i].max_time_micros);
                    return;
                    
                }
#endif //UART_DEBUG
                
            }
            
        }
        //����time_available
        time_available -= (systime.get_time_us() - now);
    }
    //����tick_counter
    sched.tick();  // �ú�������Ϊtick_counter++
}


sched_t sched =
{
	shceduler_init,
	shceduler_tick,
	shceduler_run,
};
