// Header:
// File Name: 简单任务调度器，移植与APM
// Author:Z
// Date:2018/08/03



#ifndef __SCHEDULER_H
#define __SCHEDULER_H


#include "stdint.h"
typedef struct
{
	void (*task_func)(void);  //function
	uint16_t interval_ticks;  //pre tick
	uint16_t max_time_micros; //max run time
	uint32_t last_tick_counter;//last run tick
}sched_task_t;


typedef struct 
{
	void (* init )(void);
	void (* tick )(void);
	void (* run )(uint32_t time_available);

}sched_t;

extern sched_t sched;

extern uint8_t num_task;  //任务数量




#endif //__SCHEDULER_H
