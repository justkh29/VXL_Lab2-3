/*
 * fsm_auto.h
 *
 *  Created on: Oct 26, 2024
 *      Author: ADMIN
 */

#ifndef INC_FSM_AUTO_H_
#define INC_FSM_AUTO_H_

#include "main.h"
#include "light_traffic.h"
#include "software_timer.h"

extern int status;
extern int duration_G;
extern int duration_R;
extern int duration_Y;

void fsm_auto_run();


#endif /* INC_FSM_AUTO_H_ */
