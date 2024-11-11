/*
 * Scheduler.c
 *
 *  Created on: Nov 11, 2024
 *      Author: ADMIN
 */

#include <Scheduler.h>

sTasks SCH_tasks_G[SCH_MAX_TASKS];
unsigned char current_task_index = 0;
void SCH_Init(void)
{
	unsigned char i;
	for (i = 0;i < SCH_MAX_TASKS;i++)
	{
		SCH_Delete(i);
	}
	current_task_index = 0;
}

void SCH_Update(void)
{
	unsigned char Index;
	for (Index = 0;Index < SCH_MAX_TASKS; Index++)
	{
		if(SCH_tasks_G[Index].pTask)
		{
			if(SCH_tasks_G[Index].Delay == 0)
			{
				SCH_tasks_G[Index].RunMe += 1;
				if(SCH_tasks_G[Index].Period)
				{
					SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
				}
			}
			else
			{
				SCH_tasks_G[Index].Delay -= 1;
			}
		}
	}
}

void SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD)
{
	if (current_task_index < SCH_MAX_TASKS)
	{
		SCH_tasks_G[current_task_index].pTask = pFunction;
		SCH_tasks_G[current_task_index].Delay = DELAY;
		SCH_tasks_G[current_task_index].Period = PERIOD;
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
			if (SCH_tasks_G[i].Period == 0)
			{
				SCH_Delete(SCH_tasks_G[i].TaskID);
			}
		}
	}
}

void SCH_Delete(unsigned char Task_Index)
{
	if(SCH_tasks_G[ID].pTask == 0)
	{
		return;
	}
	else
	{
		SCH_tasks_G[Task_Index].pTask= 0x0000;
		SCH_tasks_G[Task_Index].Delay = 0;
		SCH_tasks_G[Task_Index].Period = 0;
		SCH_tasks_G[Task_Index].RunMe = 0;
	}
}
