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
			time_div = 4;
			ledReset();
			status = 1;
			count = duration_G;
			break;
		case GREEN_RED:
			ledGreen_Red();
			display7SEG_Auto(count, count + duration_Y);
			time_div--;
			if (time_div <= 0)
			{
				count--;
				if (count <= 0)
				{
					ledReset();
					status = 2;
					count = duration_Y;
				}
				time_div = 4;
			}
			break;
		case YELLOW_RED:
			ledYellow_Red();
			display7SEG_Auto(count, count);
			time_div--;
			if (time_div <= 0)
			{
				count--;
				if (count <= 0)
				{
					ledReset();
					status = 3;
					count = duration_R - duration_Y;
				}
				time_div = 4;
			}
			break;
		case RED_GREEN:
			ledRed_Green();
			display7SEG_Auto(count + duration_Y, count);
			time_div--;
			if (time_div <= 0)
			{
				count--;
				if (count <= 0)
				{
					ledReset();
					status = 4;
					count = duration_Y;
				}
				time_div = 4;
			}
			break;
		case RED_YELLOW:
			ledRed_Yellow();
			display7SEG_Auto(count, count);
			time_div--;
			if (time_div <= 4)
			{
				count--;
				if (count <= 0)
				{
					ledReset();
					status = 1;
					count = duration_G;
				}
				time_div = 4;
			}
			break;
	}
}
