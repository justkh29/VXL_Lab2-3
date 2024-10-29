/*
 * fsm_edit.c
 *
 *  Created on: Oct 28, 2024
 *      Author: ADMIN
 */

#include <fsm_edit.h>

void fsm_edit()
{
	switch (status)
	{
		case EDIT_RED:
			if (timer_flag[1] == 1)
			{
				HAL_GPIO_TogglePin(LR_GPIO_Port, LR_Pin);
				HAL_GPIO_TogglePin(LR1_GPIO_Port, LR1_Pin);
				display7SEG_Auto(duration_R + duration_ADD, 2);
				timer_flag[1] = 0;
				setTimer(1,500);
			}
			if (isButton2Pressed() == 1 || isButton2LongPressed() == 1)
			{
				duration_ADD++;
				button2_flag = 0;
				button2_long_pressed = 0;
			}
			if (isButton3Pressed() == 1)
			{
				duration_R += duration_ADD;
				if (duration_R > 99)
				{
					duration_R = 1;
				}
				duration_ADD = 0;
				button3_flag = 0;
			}
			if (isButton1Pressed() == 1)
			{
				duration_ADD = 0;
			}
			break;
		case EDIT_YELLOW:
			if (timer_flag[1] == 1)
			{
				HAL_GPIO_TogglePin(LY_GPIO_Port, LY_Pin);
				HAL_GPIO_TogglePin(LY1_GPIO_Port, LY1_Pin);
				display7SEG_Auto(duration_Y + duration_ADD, 3);
				timer_flag[1] = 0;
				setTimer(1,500);
			}
			if (isButton2Pressed() == 1 || isButton2LongPressed() == 1)
			{
				duration_ADD++;

				button2_flag = 0;
				button2_long_pressed = 0;
			}
			if (isButton3Pressed() == 1)
			{
				duration_Y += duration_ADD;
				if (duration_Y > 99)
				{
					duration_Y = 1;
				}
				duration_ADD = 0;
				button3_flag = 0;
			}
			if (isButton1Pressed() == 1)
			{
				duration_ADD = 0;
			}
			break;
		case EDIT_GREEN:
			if (timer_flag[1] == 1)
			{
				HAL_GPIO_TogglePin(LG_GPIO_Port, LG_Pin);
				HAL_GPIO_TogglePin(LG1_GPIO_Port, LG1_Pin);
				display7SEG_Auto(duration_G + duration_ADD, 4);
				timer_flag[1] = 0;
				setTimer(1,500);
			}
			if (isButton2Pressed() == 1 || isButton2LongPressed() == 1)
			{
				duration_ADD++;
				button2_flag = 0;
				button2_long_pressed = 0;
			}
			if (isButton3Pressed() == 1)
			{
				duration_G += duration_ADD;
				if (duration_G > 99)
				{
					duration_G = 1;
				}
				duration_ADD = 0;
				button3_flag = 0;
			}
			if (isButton1Pressed() == 1)
			{
				duration_ADD = 0;
			}
			break;
	}
}
