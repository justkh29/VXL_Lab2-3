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
		case 0:
			ledReset();
			status = 1;
			setTimer(0, duration_G*1000);
			break;
		case 1:
			ledGreen_Red();
			if (timer_flag[0] == 1)
			{
				ledReset();
				timer_flag[0] = 0;
				status = 2;
				setTimer(0, duration_Y*1000);
			}
			break;
		case 2:
			ledYellow_Red();
			if (timer_flag[0] == 1)
			{
				ledReset();
				timer_flag[0] = 0;
				status = 3;
				setTimer(0, (duration_R - duration_Y)*1000);
			}
			break;
		case 3:
			ledRed_Green();
			if (timer_flag[0] == 1)
			{
				ledReset();
				timer_flag[0] = 0;
				status = 4;
				setTimer(0, duration_Y*1000);
			}
			break;
		case 4:
			ledRed_Yellow();
			if (timer_flag[0] == 1)
			{
				ledReset();
				timer_flag[0] = 0;
				status = 1;
				setTimer(0, duration_G*1000);
			}
			break;
		case 5:
			ledReset();
			break;
	}
}
