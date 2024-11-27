#include <UART.h>
uint8_t temp=0;
uint8_t buffer[MAX_BUFFER_SIZE];
uint8_t index_buffer=0;
uint8_t buffer_flag=0;

uint8_t data_received[MAX_BUFFER_SIZE];
uint8_t data_received_index=0;
uint8_t data[MAX_BUFFER_SIZE];
uint8_t data_transmit[MAX_BUFFER_SIZE];
uint8_t data_size=0;


int data_parser = BEGIN;
int state = WAIT_RST;


void command_parser_fsm()
{
	switch(data_parser)
	{
		case BEGIN:
			if (temp == '!'){
				data_parser = WRITING_DATA;
				data_received_index=0;
				memset(data_received,0,MAX_BUFFER_SIZE);
			}
			break;
		case WRITING_DATA:
			if (temp == '#')
			{
				data_parser = BEGIN;
				memcpy(data,data_received,MAX_BUFFER_SIZE);
			}
			else
			{
				data_received[data_received_index++] = temp;  //Writing data from temp to data_receive
			}
			break;
	}
}

void uart_communication_fsm()
{
	switch (state)
	{
		case WAIT_RST:
			if(strcmp((char*)data, "RST") == 0)
			{
				state=TRANSMIT;
				data_size = sprintf((char*)data_transmit, "\r\n!ADC=%d#", (int) HAL_ADC_GetValue(&hadc1));
			}
			break;
		case TRANSMIT:
			HAL_UART_Transmit(&huart2, data_transmit, sizeof(data_transmit), 1000);
			state=WAIT_OK;
			setTimer(1, 3000);
			break;
		case WAIT_OK:
			if (strcmp((char*)data, "OK") == 0)
			{
				state = WAIT_RST;
				memset(data, 0, MAX_BUFFER_SIZE);
			}
			if (timer_flag[1] == 1)
			{
				state = TRANSMIT;
			}
			break;
	}
}
