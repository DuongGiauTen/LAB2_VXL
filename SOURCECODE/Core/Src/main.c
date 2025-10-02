/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2025 STMicroelectronics.
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
#include "timer.h"

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

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
/* USER CODE BEGIN PFP */
void EN1_STATE(int state);
void EN2_STATE(int state);
void EN3_STATE(int state);
void EN0_STATE(int state);
void update7SEG(int index);
void display7SEG(int num);
void updateClockBuffer();
void updateLEDMatrix(int index);


/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
const int MAX_LED = 4;
int index_led = 0;
int led_buffer[4] = {1,2,3,4};
int hour = 23, minute = 59, second = 50;

//ex9
const int MAX_LED_MATRIX = 8;
int counter_matrix = 0;
int index_led_matrix = 0;
uint8_t matrix_buffer[8] = {
    0x00, // 00000000
    0x7C, // 01111100
    0x12, // 00010010
    0x11, // 00010001
    0x11, // 00010001
    0x12, // 00010010
    0x7C, // 01111100
    0x00  // 00000000
};
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
  setTimer1(250);
  setTimer2(250);
  HAL_TIM_Base_Start_IT(&htim2);
  int counter = 0;
  //int counterClk = 0;


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  //HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, SET);

//	  HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, SET);
	  //HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, SET);
//	  HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, SET);
	  if (flag2 == 1){
		 setTimer2(50);
		 updateLEDMatrix(counter++);
		 if(counter >= 8){
			 counter = 0;
		 }




	  }
	  //HAL_Delay(1000);

	  if (flag == 1){
		  setTimer1(250);
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
  HAL_GPIO_WritePin(GPIOB, SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin, GPIO_PIN_RESET);

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

  /*Configure GPIO pins : SEG0_Pin SEG1_Pin SEG2_Pin ROW2_Pin
                           ROW3_Pin ROW4_Pin ROW5_Pin ROW6_Pin
                           ROW7_Pin SEG3_Pin SEG4_Pin SEG5_Pin
                           SEG6_Pin ROW0_Pin ROW1_Pin */
  GPIO_InitStruct.Pin = SEG0_Pin|SEG1_Pin|SEG2_Pin|ROW2_Pin
                          |ROW3_Pin|ROW4_Pin|ROW5_Pin|ROW6_Pin
                          |ROW7_Pin|SEG3_Pin|SEG4_Pin|SEG5_Pin
                          |SEG6_Pin|ROW0_Pin|ROW1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */


// HÀM ĐƯỢC YÊU CẦU: updateLEDMatrix
// Phiên bản này hoạt động với cả chân ENM và ROW không liên tiếp,
// giữ nguyên cấu trúc switch-case và không dùng vòng lặp for.

void updateLEDMatrix(int index) {
    // Bước 1: Tắt tất cả các cột để tránh hiện tượng ghosting.
    // Bước này vẫn giữ nguyên, gọi từng chân một.
    HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_RESET);

    // Bước 2: Gửi dữ liệu của cột hiện tại ra các chân ROW.
    // Đây là phần thay đổi chính để xử lý các chân ROW không liên tiếp.
    uint8_t column_data = matrix_buffer[index];

    // "Trải phẳng" vòng lặp: Kiểm tra từng bit và đặt trạng thái cho từng chân ROW
    // Giả sử ROWx được nối với cực Anode, nên SET = Sáng, RESET = Tắt.
    HAL_GPIO_WritePin(ENM0_GPIO_Port, ENM0_Pin, (column_data & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Bit 0 cho ENM0
    HAL_GPIO_WritePin(ENM1_GPIO_Port, ENM1_Pin, (column_data & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Bit 1 cho ENM1
    HAL_GPIO_WritePin(ENM2_GPIO_Port, ENM2_Pin, (column_data & 0x04) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Bit 2 cho ENM2
    HAL_GPIO_WritePin(ENM3_GPIO_Port, ENM3_Pin, (column_data & 0x08) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Bit 3 cho ENM3
    HAL_GPIO_WritePin(ENM4_GPIO_Port, ENM4_Pin, (column_data & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Bit 4 cho ENM4
    HAL_GPIO_WritePin(ENM5_GPIO_Port, ENM5_Pin, (column_data & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Bit 5 cho ENM5
    HAL_GPIO_WritePin(ENM6_GPIO_Port, ENM6_Pin, (column_data & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Bit 6 cho ENM6
    HAL_GPIO_WritePin(ENM7_GPIO_Port, ENM7_Pin, (column_data & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET); // Bit 7 cho ENM7

    // Bước 3: Bật đúng cột đang được quét bằng cấu trúc switch-case.
    // Cấu trúc này được giữ nguyên theo yêu cầu của bạn.
    switch (index) {
        case 0:
            HAL_GPIO_WritePin(ROW0_GPIO_Port, ROW0_Pin, GPIO_PIN_SET);
            break;
        case 1:
            HAL_GPIO_WritePin(ROW1_GPIO_Port, ROW1_Pin, GPIO_PIN_SET);
            break;
        case 2:
            HAL_GPIO_WritePin(ROW2_GPIO_Port, ROW2_Pin, GPIO_PIN_SET);
            break;
        case 3:
            HAL_GPIO_WritePin(ROW3_GPIO_Port, ROW3_Pin, GPIO_PIN_SET);
            break;
        case 4:
            HAL_GPIO_WritePin(ROW4_GPIO_Port, ROW4_Pin, GPIO_PIN_SET);
            break;
        case 5:
            HAL_GPIO_WritePin(ROW5_GPIO_Port, ROW5_Pin, GPIO_PIN_SET);
            break;
        case 6:
            HAL_GPIO_WritePin(ROW6_GPIO_Port, ROW6_Pin, GPIO_PIN_SET);
            break;
        case 7:
            HAL_GPIO_WritePin(ROW7_GPIO_Port, ROW7_Pin, GPIO_PIN_SET);
            break;
        default:
            // Không làm gì nếu index không hợp lệ.
            break;
    }
}





void updateClockBuffer(){
	led_buffer[0] = minute / 10;
	led_buffer[1] = minute % 10;
	led_buffer[2] = second / 10;
	led_buffer[3] = second % 10;
}


void EN0_STATE(int state){
	if (state == 0){
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, RESET);
	}
	else{
		HAL_GPIO_WritePin(EN0_GPIO_Port, EN0_Pin, SET);
	}
}
void EN1_STATE(int state){
	if (state == 0){
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, RESET);
	}
	else{
		HAL_GPIO_WritePin(EN1_GPIO_Port, EN1_Pin, SET);
	}
}
void EN2_STATE(int state){
	if (state == 0){
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, RESET);
	}
	else{
		HAL_GPIO_WritePin(EN2_GPIO_Port, EN2_Pin, SET);
	}
}
void EN3_STATE(int state){
	if (state == 0){
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, RESET);
	}
	else{
		HAL_GPIO_WritePin(EN3_GPIO_Port, EN3_Pin, SET);
	}
}

void display7SEG(int num) {
    // Mapping assumed:
    // SEG0 -> segment a
    // SEG1 -> segment b
    // SEG2 -> segment c
    // SEG3 -> segment d
    // SEG4 -> segment e
    // SEG5 -> segment f
    // SEG6 -> segment g
    //
    // Assumption: RESET lights a segment, SET turns it off.
    if (num == 0) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET); // a on
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET); // b on
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET); // d on
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, RESET); // e on
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET); // f on
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, SET);   // g off
    }
    else if (num == 1) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, SET);   // a off
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET); // b on
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, SET);   // d off
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);   // e off
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);   // f off
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, SET);   // g off
    }
    else if (num == 2) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET); // a on
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET); // b on
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, SET);   // c off
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET); // d on
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, RESET); // e on
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);   // f off
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET); // g on
    }
    else if (num == 3) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET); // a on
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET); // b on
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET); // d on
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);   // e off
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);   // f off
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET); // g on
    }
    else if (num == 4) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, SET);   // a off
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET); // b on
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, SET);   // d off
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);   // e off
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET); // f on
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET); // g on
    }
    else if (num == 5) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET); // a on
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, SET);   // b off
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET); // d on
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);   // e off
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET); // f on
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET); // g on
    }
    else if (num == 6) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET); // a on
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, SET);   // b off
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET); // d on
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, RESET); // e on
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET); // f on
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET); // g on
    }
    else if (num == 7) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET); // a on
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET); // b on
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, SET);   // d off
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);   // e off
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);   // f off
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, SET);   // g off
    }
    else if (num == 8) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET); // a on
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET); // b on
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET); // d on
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, RESET); // e on
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET); // f on
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET); // g on
    }
    else if (num == 9) {
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, RESET); // a on
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, RESET); // b on
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, RESET); // c on
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, RESET); // d on
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);   // e off
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, RESET); // f on
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, RESET); // g on
    }
    else {
        // default: tắt tất cả segment (hiển thị trống)
        HAL_GPIO_WritePin(SEG0_GPIO_Port, SEG0_Pin, SET);
        HAL_GPIO_WritePin(SEG1_GPIO_Port, SEG1_Pin, SET);
        HAL_GPIO_WritePin(SEG2_GPIO_Port, SEG2_Pin, SET);
        HAL_GPIO_WritePin(SEG3_GPIO_Port, SEG3_Pin, SET);
        HAL_GPIO_WritePin(SEG4_GPIO_Port, SEG4_Pin, SET);
        HAL_GPIO_WritePin(SEG5_GPIO_Port, SEG5_Pin, SET);
        HAL_GPIO_WritePin(SEG6_GPIO_Port, SEG6_Pin, SET);
    }
}



void update7SEG(int index){
	switch (index){
	case 0:
		// First 7SEG
		EN0_STATE(0);
		EN1_STATE(1);
		EN2_STATE(1);
		EN3_STATE(1);
		display7SEG(led_buffer[index]);
		break;
	case 1:
		// Second 7SEG
		EN0_STATE(1);
		EN1_STATE(0);
		EN2_STATE(1);
		EN3_STATE(1);
		display7SEG(led_buffer[index]);
		break;
	case 2:
		//Third 7SEG
		EN0_STATE(1);
		EN1_STATE(1);
		EN2_STATE(0);
		EN3_STATE(1);
		display7SEG(led_buffer[index]);
		break;
	case 3:
		//Forth 7SEG
		EN0_STATE(1);
		EN1_STATE(1);
		EN2_STATE(1);
		EN3_STATE(0);
		display7SEG(led_buffer[index]);
		break;
	default:
		break;
	}

}



//int counter = 200;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	timer1Run();
	timer2Run();
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
