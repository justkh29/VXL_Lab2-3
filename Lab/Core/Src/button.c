#include "button.h"
int KeyReg0_1 = NORMAL_STATE;
int KeyReg1_1 = NORMAL_STATE;
int KeyReg2_1 = NORMAL_STATE;
int KeyReg3_1 = NORMAL_STATE;

int KeyReg0_2 = NORMAL_STATE;
int KeyReg1_2 = NORMAL_STATE;
int KeyReg2_2 = NORMAL_STATE;
int KeyReg3_2 = NORMAL_STATE;

int KeyReg0_3 = NORMAL_STATE;
int KeyReg1_3 = NORMAL_STATE;
int KeyReg2_3 = NORMAL_STATE;
int KeyReg3_3 = NORMAL_STATE;

int TimeOutForKeyPress1 =  150;
int TimeOutForKeyPress2 =  150;
int TimeOutForKeyPress3 =  150;

int isButton1Pressed(){
	if(button1_flag == 1){
		return 1;
	}
	return 0;
}

int isButton2Pressed(){
	if(button2_flag == 1)
	{
		return 1;
	}
	return 0;
}

int isButton3Pressed(){
	if(button3_flag == 1)
	{
		return 1;
	}
	return 0;
}

int isButton1LongPressed(){
	if(button1_long_pressed == 1)
	{
		return 1;
	}
	return 0;
}

int isButton2LongPressed(){
	if(button2_long_pressed == 1)
	{
		return 1;
	}
	return 0;
}

int isButton3LongPressed(){
	if(button3_long_pressed == 1)
	{
		return 1;
	}
	return 0;
}

void subKeyProcess(int button)
{
	switch (button)
	{
		case 1:
			button1_flag = 1;
			break;
		case 2:
			button2_flag = 1;
			break;
		case 3:
			button3_flag = 1;
			break;
	}
}

void subLongKeyProcess(int button) {
    // Handle button long press here
    switch (button)
    {
        case 1:
            button1_long_pressed = 1;

            break;
        case 2:
        	button2_long_pressed = 1;
            // Handle long press for button 2 if needed
            break;
        case 3:
        	button3_long_pressed = 1;
            // Handle long press for button 3 if needed
            break;
    }
}

void getKeyInput()
{

	KeyReg2_1 = KeyReg1_1;
	KeyReg1_1 = KeyReg0_1;
	KeyReg0_1 = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

	int keyState = (KeyReg0_1 == KeyReg1_1) && (KeyReg0_1 == KeyReg2_1);

    switch (keyState)
    {
        case 1: // Key is stable
            if (KeyReg2_1 == PRESSED_STATE)
            {
                if (TimeOutForKeyPress1 == 0)
                {
                    subLongKeyProcess(1);
                    TimeOutForKeyPress1 = 150;

                }
                else
                {
                    TimeOutForKeyPress1--;
                }
            }
            break;
        case 0: // Key state is changing
            if (KeyReg0_1 != KeyReg1_1)
            {
                KeyReg1_1 = KeyReg0_1;
                if (KeyReg1_1 == PRESSED_STATE)
                {
                    TimeOutForKeyPress1 = 150;
                    subKeyProcess(1);
                }
            }
            break;
    }

	KeyReg2_2 = KeyReg1_2;
	KeyReg1_2 = KeyReg0_2;
	KeyReg0_2 = HAL_GPIO_ReadPin(B2_GPIO_Port, B2_Pin);

	int keyState2 = (KeyReg0_2 == KeyReg1_2) && (KeyReg0_2 == KeyReg2_2);

	switch (keyState2)
	{
		case 1: // Key is stable
			if (KeyReg2_2 == PRESSED_STATE)
			{
				if (TimeOutForKeyPress2 == 0)
				{
					subLongKeyProcess(2);
					TimeOutForKeyPress2 = 150;

				}
				else
				{
					TimeOutForKeyPress2--;
				}
			}
			break;
		case 0: // Key state is changing
			if (KeyReg0_2 != KeyReg1_2)
			{
				KeyReg1_2 = KeyReg0_2;
				if (KeyReg1_2 == PRESSED_STATE)
				{
					TimeOutForKeyPress2 = 150;
					subKeyProcess(2);
				}
			}
			break;
	}

	KeyReg2_3 = KeyReg1_3;
	KeyReg1_3 = KeyReg0_3;
	KeyReg0_3 = HAL_GPIO_ReadPin(B3_GPIO_Port, B3_Pin);

	int keyState3 = (KeyReg0_3 == KeyReg1_3) && (KeyReg0_3 == KeyReg2_3);

	switch (keyState3)
	{
		case 1: // Key is stable
			if (KeyReg2_3 == PRESSED_STATE)
			{
				if (TimeOutForKeyPress3 == 0)
				{
					subLongKeyProcess(3);
					TimeOutForKeyPress3 = 150;

				}
				else
				{
					TimeOutForKeyPress3--;
				}
			}
			break;
		case 0: // Key state is changing
			if (KeyReg0_3 != KeyReg1_3)
			{
				KeyReg1_3 = KeyReg0_3;
				if (KeyReg1_3 == PRESSED_STATE)
				{
					TimeOutForKeyPress3 = 150;
					subKeyProcess(3);
				}
			}
			break;
	}

    if (KeyReg3_1 == PRESSED_STATE || KeyReg3_2 == PRESSED_STATE || KeyReg3_3 == PRESSED_STATE)
    {
    	HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, RESET);
    }
    else
    {
    	HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, SET);
    }
}

