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
#include <software_timer.h>
#include <7SegLED.h>

#define INIT 0
#define GREEN_RED 1
#define YELLOW_RED 2
#define RED_GREEN 3
#define RED_YELLOW 4

#define EDIT_RED 11
#define EDIT_YELLOW 12
#define EDIT_GREEN 13

extern int duration_G;
extern int duration_R;
extern int duration_Y;
extern int duration_G1;
extern int mode;
extern int status;
extern int duration_ADD;

void changeMode();
void fsm_config();
#endif /* INC_FSM_SETTING_H_ */
