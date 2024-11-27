/*
 * UART.h
 *
 *  Created on: Nov 23, 2024
 *      Author: ADMIN
 */

#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "software_timer.h"

extern ADC_HandleTypeDef hadc1;

extern UART_HandleTypeDef huart2;

#define MAX_BUFFER_SIZE 30
#define WAIT_RST 1
#define TRANSMIT 2
#define WAIT_OK 3
#define BEGIN 4
#define WRITING_DATA 5
#define DONE 6
uint8_t temp;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t buffer_flag;
uint8_t index_buffer;

void command_parser_fsm();
void uart_communication_fsm();


#endif /* INC_UART_H_ */
