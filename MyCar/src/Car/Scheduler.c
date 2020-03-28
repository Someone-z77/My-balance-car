// Header:
// File Name: 简单任务调度器，移植于APM
// Author:Z
// Date:2018/08/03

#include "Scheduler.h"
#include "status.h"
#include "include.h"


extern sched_task_t sched_task[];

//任务调度器初始化
uint8_t num_task;  //任务数量
void shceduler_init(void)
{   
//    num_task = sizeof (sched_task) / sizeof (sched_task[0]);
}

static uint32_t tick_counter = 0;  //shceduler_run执行次数
void shceduler_tick()
{
    tick_counter++;
}

/*
  run one tick
  this will run as many scheduler tasks as we can in the specified time
 */
//#define UART_DEBUG
//任务调度器
void shceduler_run(uint32_t time_available)
{
    uint64_t now;
    uint16_t dt;
    uint16_t interval_ticks;
    
    for (uint8_t i = 0; i < num_task; i++)
    {
        now = systime.get_time_us();//获取当前时间
        dt = tick_counter - sched_task[i].last_tick_counter;//计算任务上次运行到现在相隔多少周期
        interval_ticks = sched_task[i].interval_ticks;  //任务相隔多少周期运行一次
        
        if( dt >= interval_ticks)
        {
            //调试时使用，任务长时间未运行，说明任务的运行周期太长或者shceduler_run的可运行时间太短
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
                //运行任务
                sched_task[i].task_func();
                //更新last_tick_counter
                sched_task[i].last_tick_counter = tick_counter;
                
#ifdef UART_DEBUG
                uint32_t end_time = systime.get_time_us() - now;
                //如果任务运行过后发现时间超出shceduler_run的可运行时间time_available，说明任务的max_time_micros设置小了
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
        //更新time_available
        time_available -= (systime.get_time_us() - now);
    }
    //更新tick_counter
    sched.tick();  // 该函数作用为tick_counter++
}


sched_t sched =
{
	shceduler_init,
	shceduler_tick,
	shceduler_run,
};
