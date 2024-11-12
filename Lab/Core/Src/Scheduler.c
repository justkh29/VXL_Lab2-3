/*
 * Scheduler.c
 *
 *  Created on: Nov 11, 2024
 *      Author: ADMIN
 */

#include <Scheduler.h>

sTasks SCH_tasks_G[SCH_MAX_TASKS];
uint8_t current_task_index = 0;

void SCH_Init(void)
{
	current_task_index = 0;
}

void SCH_Update(void)
{
	for (int i = 0;i < current_task_index;i++)
	{
		if (SCH_tasks_G[i].Delay > 0)
		{
			SCH_tasks_G[i].Delay--;
		}
		else
		{
			SCH_tasks_G[i].Delay = SCH_tasks_G[i].Period;
			SCH_tasks_G[i].RunMe += 1;
		}
	}
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD)
{
	if (current_task_index < SCH_MAX_TASKS)
	{
		SCH_tasks_G[current_task_index].pTask = pFunction;
		SCH_tasks_G[current_task_index].Delay = DELAY / TICK;
		SCH_tasks_G[current_task_index].Period = PERIOD / TICK;
		SCH_tasks_G[current_task_index].RunMe = 0;

		SCH_tasks_G[current_task_index].TaskID = current_task_index;
		current_task_index++;
	}
}

void SCH_Dispatch_Tasks(void)
{
	for(int i = 0;i < current_task_index;i++)
	{
		if (SCH_tasks_G[i].RunMe > 0)
		{
			SCH_tasks_G[i].RunMe--;
			(*SCH_tasks_G[i].pTask)();

		}
	}
}


