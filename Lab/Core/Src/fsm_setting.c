/*
 * fsm_setting.c
 *
 *  Created on: Oct 27, 2024
 *      Author: ADMIN
 */


#include <fsm_setting.h>
int mode = 1;

void changeMode()
{
	mode++;
	if (mode >= 5)
	{
		mode = 1;
	}
	switch(mode)
	{
		case 1:
			status = 0;
			break;
		case 2:
			status = 5;
			break;
		case 3:
			status = 6;
			break;
		case 4:
			status = 7;
			break;
	}
}

void fsm_config()
{
	if (isButton1Pressed() == 1 || isButton1LongPressed())
	{
		changeMode();
		button1_flag = 0;
		button1_long_pressed = 0;
	}
}
