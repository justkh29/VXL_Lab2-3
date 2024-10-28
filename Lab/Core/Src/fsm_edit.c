/*
 * fsm_edit.c
 *
 *  Created on: Oct 28, 2024
 *      Author: ADMIN
 */

#include <fsm_edit.h>

void duration_edit()
{
	switch (status)
	{
		case EDIT_RED:
			if (isButton2Pressed() == 1 || isButton2LongPressed() == 1)
			{
				duration_ADD++;
				button2_flag = 0;
				button2_long_pressed = 0;
			}
			if (isButton3Pressed() == 1)
			{
				duration_R += duration_ADD;
				button3_flag = 0;
			}
			break;
	}
}
