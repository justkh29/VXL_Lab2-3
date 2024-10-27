/*
 * fsm_setting.h
 *
 *  Created on: Oct 27, 2024
 *      Author: ADMIN
 */

#ifndef INC_FSM_SETTING_H_
#define INC_FSM_SETTING_H_

#include <main.h>
#include <button.h>
extern int status;
extern int duration_G;
extern int duration_R;
extern int duration_Y;
extern int duration_G1;
extern int mode;

void changeMode();
void fsm_config();
#endif /* INC_FSM_SETTING_H_ */
