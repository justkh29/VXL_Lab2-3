#include "button.h"
int KeyReg0 = NORMAL_STATE;
int KeyReg1 = NORMAL_STATE;
int KeyReg2 = NORMAL_STATE;
int KeyReg3 = NORMAL_STATE;

int TimeOutForKeyPress =  500;
int button1_pressed = 0;
int button1_long_pressed = 0;
int button1_flag = 0;

typedef enum {
	BUTTON_IDLE,
	BUTTON_PRESSED,
	BUTTON_LONG_PRESSED,
	BUTTON_RELEASED
} state;
int isButton1Pressed(){
	if(button1_flag == 1){
		button1_flag = 0;
		return 1;
	}
	return 0;
}

int isButton1LongPressed()
{
	if(button1_long_pressed == 1)
	{
		button1_long_pressed = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int process)
{
	//TODO

	HAL_GPIO_TogglePin(LED1_GPIO_Port, LED1_Pin);

	button1_flag = 1;
}

void getKeyInput()
{
  KeyReg2 = KeyReg1;
  KeyReg1 = KeyReg0;
  // Add your key
  KeyReg0 = HAL_GPIO_ReadPin(BUTTON_GPIO_Port, BUTTON_Pin);

  switch(state)
  {
	  case BUTTON_IDLE:
		  if (KeyReg1 == PRESSED_STATE && KeyReg1 == KeyReg2 && KeyReg1 == KeyReg0)
		  {
			  buttonState = BUTTON_PRESSED;
			  TimeOutForKeyPress = 500;
			  subKeyProcess(1);
		  }
		  break;

	  case BUTTON_PRESSED:
		  if (KeyReg1 == PRESSED_STATE && KeyReg1 == KeyReg2 && KeyReg1 == KeyReg0) {
			  if (TimeOutForKeyPress > 0) {
				  TimeOutForKeyPress--;
			  } else {
				  buttonState = BUTTON_LONG_PRESSED;
				  TimeOutForKeyPress = 500;
				  subKeyProcess(1);
				  button1_long_pressed = 1;
			  }
		  } else {
			  buttonState = BUTTON_RELEASED;
		  }
		  break;

	  case BUTTON_LONG_PRESSED:
		  if (KeyReg1 != PRESSED_STATE || KeyReg1 != KeyReg2 || KeyReg1 != KeyReg0) {
			  buttonState = BUTTON_RELEASED;
		  }
		  break;

	  case BUTTON_RELEASED:
		  if (KeyReg1 == NORMAL_STATE && KeyReg1 == KeyReg2 && KeyReg1 == KeyReg0) {
			  buttonState = BUTTON_IDLE;
		  }
		  break
  }
}

