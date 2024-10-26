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

int TimeOutForKeyPress1 =  500;
int TimeOutForKeyPress2 =  500;
int TimeOutForKeyPress3 =  500;
int button1_pressed = 0;
int button1_long_pressed = 0;
int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;
int mode = 1;

int isButton1Pressed(){
	if(button1_flag == 1){
		return 1;
	}
	return 0;
}

int isButton1LongPressed(){
	if(button1_long_pressed == 1){
		button1_long_pressed = 0;
		return 1;
	}
	return 0;
}

void changeMode()
{
	if (button1_flag == 1)
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
		button1_flag = 0;
	}
}
void subKeyProcess(int button)
{
	//TODO
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

void getKeyInput(){

	KeyReg2_1 = KeyReg1_1;
	KeyReg1_1 = KeyReg0_1;
	KeyReg0_1 = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

	int keyState = (KeyReg1_1 == KeyReg2_1) && (KeyReg1_1 == KeyReg3_1);

	switch (keyState)
	{
	    case 1: // Key is stable
	        if (KeyReg3_1 == PRESSED_STATE)
	        {
	            if (TimeOutForKeyPress1 == 0)
	            {
	                TimeOutForKeyPress1 = 500;
	                subKeyProcess(1);
	            }
	            else
	            {
	                TimeOutForKeyPress1--;
	            }
	        }
	        break;
	    case 0: // Key state is changing
	        if (KeyReg2_1 != KeyReg3_1)
	        {
	            KeyReg3_1 = KeyReg2_1;
	            if (KeyReg3_1 == PRESSED_STATE)
	            {
	                TimeOutForKeyPress1 = 500;
	                subKeyProcess(1);
	            }
	        }
	        break;
	}

	KeyReg2_2 = KeyReg1_2;
	KeyReg1_2 = KeyReg0_2;
	KeyReg0_2 = HAL_GPIO_ReadPin(B2_GPIO_Port, B2_Pin);

	int keyState2 = (KeyReg1_2 == KeyReg2_2) && (KeyReg1_2 == KeyReg3_2);

	switch (keyState2)
	{
	    case 1: // Key is stable
	        if (KeyReg3_2 == PRESSED_STATE)
	        {
	            if (TimeOutForKeyPress2 == 0)
	            {
	                TimeOutForKeyPress2 = 500;
	                subKeyProcess(2);
	            }
	            else
	            {
	                TimeOutForKeyPress2--;
	            }
	        }
	        break;
	    case 0: // Key state is changing
	        if (KeyReg2_2 != KeyReg3_2)
	        {
	            KeyReg3_2 = KeyReg2_2;
	            if (KeyReg3_2 == PRESSED_STATE)
	            {
	                TimeOutForKeyPress2 = 500;
	                subKeyProcess(2);
	            }
	        }
	        break;
	}

	KeyReg2_3 = KeyReg1_3;
	KeyReg1_3 = KeyReg0_3;
	KeyReg0_3 = HAL_GPIO_ReadPin(B3_GPIO_Port, B3_Pin);

	int keyState3 = (KeyReg1_3 == KeyReg2_3) && (KeyReg1_3 == KeyReg3_3);

	switch (keyState3)
	{
	    case 1: // Key is stable
	        if (KeyReg3_3 == PRESSED_STATE)
	        {
	            if (TimeOutForKeyPress3 == 0)
	            {
	                TimeOutForKeyPress3 = 500;
	                subKeyProcess(3);
	            }
	            else
	            {
	                TimeOutForKeyPress3--;
	            }
	        }
	        break;
	    case 0: // Key state is changing
	        if (KeyReg2_3 != KeyReg3_3)
	        {
	            KeyReg3_3 = KeyReg2_3;
	            if (KeyReg3_3 == PRESSED_STATE)
	            {
	                TimeOutForKeyPress3 = 500;
	                subKeyProcess(3);
	            }
	        }
	        break;
	}
}

