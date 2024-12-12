/*
 * fsm_auto.c
 *
 *  Created on: Oct 26, 2024
 *      Author: ADMIN
 */

#include "fsm_auto.h"

void fsm_auto_run()
{
	switch(status)
	{
		case INIT:
			ledReset();
			status = 1;
			setTimer(0, 1000);
			setTimer(1, 250);
			count = duration_G;
			ledGreen_Red();
			break;
		case GREEN_RED:
			if (timer_flag[0] == 1)
			{
				ledGreen_Red();
				display7SEG_Auto(count, count);
				count--;
				if (count <= 0)
				{
					status = 2;
					count = duration_Y;

				}
				timer_flag[0] = 0;
				setTimer(0, 1000);
			}
			if (isButton2Pressed() == 1)
			{
				button2_flag = 0;
			}
			break;
		case YELLOW_RED:

			if (timer_flag[0] == 1)
			{
				ledYellow_Red();
				display7SEG_Auto(count, count);
				count--;
				if (count <= 0)
				{
					status = 3;
					count = duration_R - duration_Y;
				}
				timer_flag[0] = 0;
				setTimer(0, 1000);
			}
			if (isButton2Pressed() == 1)
			{
				button2_flag = 0;
			}
			break;
		case RED_GREEN:

			if (timer_flag[0] == 1)
			{
				ledRed_Green();
				display7SEG_Auto(count + duration_Y, count);
				count--;
				if (count <= 0)
				{
					status = 4;
					count = duration_Y;
				}
				timer_flag[0] = 0;
				setTimer(0, 1000);
			}
			if (isButton2Pressed() == 1)
			{
				button2_flag = 0;
			}
			break;
		case RED_YELLOW:

			if (timer_flag[0] == 1)
			{
				ledRed_Yellow();
				display7SEG_Auto(count, count);
				count--;
				if (count <= 0)
				{
					status = 1;
					count = duration_G;
				}
				timer_flag[0] = 0;
				setTimer(0, 1000);
			}
			if (isButton2Pressed() == 1)
			{
				button2_flag = 0;
			}
			break;
	}

}
