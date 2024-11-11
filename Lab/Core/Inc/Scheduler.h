/*
 * Scheduler.h
 *
 *  Created on: Nov 11, 2024
 *      Author: ADMIN
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <main.h>

typedef struct{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint32_t RunMe;
	uint32_t TaskID;
} sTask;

#define SCH_MAX_TASKS	40
#define NO_TASK_ID	0
sTask SCH_tasks_G[SCH_MAX_TASKS];
void SCH_Init(void);

void SCH_Add_Task(void (*pFunction)(), unsigned int DELAY, unsigned int PERIOD);

void SCH_Update(void);

void SCH_Dispatch_Tasks(void);

void SCH_Delete(uint32_t ID);


#endif /* INC_SCHEDULER_H_ */
