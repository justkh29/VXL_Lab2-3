/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <software_timer.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* USER CODE BEGIN PV */
const int MAX_LED = 4;
const int MAX_LED_MATRIX = 8;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {
	  0b11100111,
	  0b11011011,
	  0b10111101,
	  0b10111101,
	  0b10000001,
	  0b10111101,
	  0b10111101,
	  0b10111101
};
uint8_t shift = 0;
int index_led = 0;
int led_buffer[4] = {1,2,3,4};
int hour = 15, minute = 8, second = 50;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
void display7SEG(int num);
void offPin();
void update7SEG(int index);
void updateClockBuffer();
void setCol(uint8_t value);
void setMatrix();
void updateLEDMatrix(uint8_t index, uint8_t shift);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void display7SEG(int num)
{
	  char segNumber[10] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};

	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (segNumber[num] >> 0) & 1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, (segNumber[num] >> 1) & 1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, (segNumber[num] >> 2) & 1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, (segNumber[num] >> 3) & 1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, (segNumber[num] >> 4) & 1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, (segNumber[num] >> 5) & 1);
	  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, (segNumber[num] >> 6) & 1);
}
void offPin()
{
	  HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	  HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	  HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	  HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
}

void update7SEG(int index)
{
	  offPin();
	  switch(index)
	  {
		  case 0:
		  {
			  display7SEG(led_buffer[0]);
			  HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
			  break;
		  }
		  case 1:
		  {
			  display7SEG(led_buffer[1]);
			  HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
			  break;
		  }
		  case 2:
		  {
			  display7SEG(led_buffer[2]);
			  HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
			  break;
		  }
		  case 3:
		  {
			  display7SEG(led_buffer[3]);
			  HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
			  break;
		  }
	  }
}

void updateClockBuffer()
{
	  led_buffer[0] = hour/10;
	  led_buffer[1] = hour%10;
	  led_buffer[2] = minute/10;
	  led_buffer[3] = minute%10;
}

void setCol(uint8_t value)
{
	  HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, ((value>>7)&0x01));
	  HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, ((value>>6)&0x01));
	  HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, ((value>>5)&0x01));
	  HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, ((value>>4)&0x01));
	  HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, ((value>>3)&0x01));
	  HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, ((value>>2)&0x01));
	  HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, ((value>>1)&0x01));
	  HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, ((value>>0)&0x01));
}
void setMatrix()
{
	  HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, SET);
	  HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, SET);
	  HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, SET);
	  HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, SET);
	  HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, SET);
	  HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, SET);
	  HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, SET);
	  HAL_GPIO_WritePin(ROW8_GPIO_Port, ROW8_Pin, SET);
}
void updateLEDMatrix(uint8_t index, uint8_t shift)
{
    setMatrix();
    uint8_t matrix_buffer_shift = (matrix_buffer[index] << shift) | (matrix_buffer[index] >> (8 - shift));
    switch (index)
    {
        case 0:
        {
            setCol(matrix_buffer_shift);
            HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, RESET);
            break;
        }
        case 1:
        {
            setCol(matrix_buffer_shift);
            HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, RESET);
            break;
        }
        case 2:
        {
            setCol(matrix_buffer_shift);
            HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, RESET);
            break;
        }
        case 3:
        {
            setCol(matrix_buffer_shift);
            HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, RESET);
            break;
        }
        case 4:
        {
            setCol(matrix_buffer_shift);
            HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, RESET);
            break;
        }
        case 5:
        {
            setCol(matrix_buffer_shift);
            HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, RESET);
            break;
        }
        case 6:
        {
            setCol(matrix_buffer_shift);
            HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, RESET);
            break;
        }
        case 7:
        {
            setCol(matrix_buffer_shift);
            HAL_GPIO_WritePin(ROW8_GPIO_Port, ROW8_Pin, RESET);
            break;
        }
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim2);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */




  setTimer(0,250);
  setTimer(1,1000);
  setTimer(2,50);
  while (1)
  {
	  if(timer_flag[1] == 1)
	  {
		  second++;
		  if(second >= 60)
		  {
			  second = 0;
			  minute++;
		  }
		  if(minute >= 60)
		  {
			  minute = 0;
			  hour++;
		  }
		  if(hour >= 24)
		  {
			  hour = 0;
		  }
		  updateClockBuffer();
		  HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		  HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		  setTimer(1,1000);
	  }
	  if(timer_flag[0] == 1)
	  {
		  updateClockBuffer();
		  update7SEG(index_led++);
		  if (index_led >= MAX_LED)
		  {
			  index_led = 0;
		  }
		  setTimer(0,250);
	  }
	  if(timer_flag[2] == 1)
	  {
		  updateLEDMatrix(index_led_matrix, shift);
		  index_led_matrix++;
		  if (index_led_matrix >= MAX_LED_MATRIX)
		  {
			  index_led_matrix = 0;
			  shift++;
			  if (shift >= 8) shift = 0;
		  }
		  setTimer(2,50);

	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 7999;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 9;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, SEG1_Pin|SEG2_Pin|SEG3_Pin|ROW3_Pin
                          |ROW4_Pin|ROW5_Pin|ROW6_Pin|ROW7_Pin
                          |ROW8_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin
                          |SEG7_Pin|ROW1_Pin|ROW2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : ENM0_Pin ENM1_Pin DOT_Pin LED_RED_Pin
                           EN0_Pin EN1_Pin EN2_Pin EN3_Pin
                           ENM2_Pin ENM3_Pin ENM4_Pin ENM5_Pin
                           ENM6_Pin ENM7_Pin */
  GPIO_InitStruct.Pin = ENM0_Pin|ENM1_Pin|DOT_Pin|LED_RED_Pin
                          |EN0_Pin|EN1_Pin|EN2_Pin|EN3_Pin
                          |ENM2_Pin|ENM3_Pin|ENM4_Pin|ENM5_Pin
                          |ENM6_Pin|ENM7_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : SEG1_Pin SEG2_Pin SEG3_Pin ROW3_Pin
                           ROW4_Pin ROW5_Pin ROW6_Pin ROW7_Pin
                           ROW8_Pin SEG4_Pin SEG5_Pin SEG6_Pin
                           SEG7_Pin ROW1_Pin ROW2_Pin */
  GPIO_InitStruct.Pin = SEG1_Pin|SEG2_Pin|SEG3_Pin|ROW3_Pin
                          |ROW4_Pin|ROW5_Pin|ROW6_Pin|ROW7_Pin
                          |ROW8_Pin|SEG4_Pin|SEG5_Pin|SEG6_Pin
                          |SEG7_Pin|ROW1_Pin|ROW2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef * htim)
{
	timerRun();
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
