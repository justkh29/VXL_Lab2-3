/*
 * light_traffic.c
 *
 *  Created on: Oct 26, 2024
 *      Author: ADMIN
 */
#include "light_traffic.h"

void ledReset()
{
	HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, SET);
	HAL_GPIO_WritePin(LY_GPIO_Port, LY_Pin, SET);
	HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);
	HAL_GPIO_WritePin(LR1_GPIO_Port, LR1_Pin, SET);
	HAL_GPIO_WritePin(LY1_GPIO_Port, LY1_Pin, SET);
	HAL_GPIO_WritePin(LG1_GPIO_Port, LG1_Pin, SET);
}
void ledRed_Green()
{

	HAL_GPIO_WritePin(LR1_GPIO_Port, LR1_Pin, SET);
	HAL_GPIO_WritePin(LY_GPIO_Port, LY_Pin, SET);

	HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, RESET);
	HAL_GPIO_WritePin(LG1_GPIO_Port, LG1_Pin, RESET);
}

void ledRed_Yellow()
{
	HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, SET);
	HAL_GPIO_WritePin(LG1_GPIO_Port, LG1_Pin, SET);

	HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, RESET);
	HAL_GPIO_WritePin(LY1_GPIO_Port, LY1_Pin, RESET);
}

void ledGreen_Red()
{
	HAL_GPIO_WritePin(LR_GPIO_Port, LR_Pin, SET);
	HAL_GPIO_WritePin(LY1_GPIO_Port, LY1_Pin, SET);

	HAL_GPIO_WritePin(LR1_GPIO_Port, LR1_Pin, RESET);
	HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, RESET);
}

void ledYellow_Red()
{
	HAL_GPIO_WritePin(LR1_GPIO_Port, LR1_Pin, SET);
	HAL_GPIO_WritePin(LG_GPIO_Port, LG_Pin, SET);

	HAL_GPIO_WritePin(LR1_GPIO_Port, LR1_Pin, RESET);
	HAL_GPIO_WritePin(LY_GPIO_Port, LY_Pin, RESET);
}
