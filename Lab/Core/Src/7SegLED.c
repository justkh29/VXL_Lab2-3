/*
 * 7SegLED.c
 *
 *  Created on: Oct 27, 2024
 *      Author: ADMIN
 */

#include "7SegLED.h"

void display7SEG(int num, uint32_t GPIO_Pin)
{
    char segNumber[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

    HAL_GPIO_WritePin(GPIOB, GPIO_Pin << 0, (segNumber[num] >> 0) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin << 1, (segNumber[num] >> 1) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin << 2, (segNumber[num] >> 2) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin << 3, (segNumber[num] >> 3) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin << 4, (segNumber[num] >> 4) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin << 5, (segNumber[num] >> 5) & 1);
    HAL_GPIO_WritePin(GPIOB, GPIO_Pin << 6, (segNumber[num] >> 6) & 1);
}

void offPin()
{
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
}

void display7SEG_Dual(int num)
{
	int tens = num / 10;
	int unit = num % 10;

	display7SEG(tens, GPIO_PIN_0);
	display7SEG(unit, GPIO_PIN_7);
}

void display7SEG_Auto(int duration1, int duration2)
{
	offPin();
	display7SEG_Dual(duration1);
	HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);

}
