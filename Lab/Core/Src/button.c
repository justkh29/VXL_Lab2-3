#include "button.h"
int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;
int KeyReg3 = NORMAL_STATE;

int TimeOutForKeyPress =  500;
int button1_pressed = 0;
int button1_long_pressed = 0;
int button1_flag = 0;

int isButton1Pressed(){
	if(button1_flag == 1){
		button1_flag = 0;
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

void subKeyProcess(){
	//TODO
	//HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);
	button1_flag = 1;
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

	int keyState = (KeyReg1_2 == KeyReg2_2) && (KeyReg1_2 == KeyReg3_2);

	switch (keyState)
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

	int keyState = (KeyReg1_3 == KeyReg2_3) && (KeyReg1_3 == KeyReg3_3);

	switch (keyState)
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

