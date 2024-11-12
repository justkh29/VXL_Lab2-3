/*
 * Scheduler.h
 *
 *  Created on: Nov 11, 2024
 *      Author: ADMIN
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <main.h>
#include <stdint.h>
typedef struct{
	void (*pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;

	uint32_t TaskID;
} sTasks;

#define SCH_MAX_TASKS	40
#define NO_TASK_ID	0
#define TICK 10

extern sTasks SCH_tasks_G[SCH_MAX_TASKS];
void SCH_Init(void);

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD); //setTimer

void SCH_Update(void); //timerRun

void SCH_Dispatch_Tasks(void); //flag check


#endif /* INC_SCHEDULER_H_ */
