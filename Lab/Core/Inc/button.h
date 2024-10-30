/*
 * button.h
 *
 *  Created on: Oct 5, 2023
 *      Author: KAI
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <main.h>
#include <light_traffic.h>
#include <fsm_auto.h>
#include <global_var.h>

#define NORMAL_STATE SET
#define PRESSED_STATE RESET

int isButton1Pressed();
int isButton2Pressed();
int isButton3Pressed();
int isButton1LongPressed();
int isButton2LongPressed();
int isButton3LongPressed();
void ledDebug();
void getKeyInput();

#endif /* INC_BUTTON_H_ */

