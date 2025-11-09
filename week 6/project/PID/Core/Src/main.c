/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include<oled.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define EPSILON 0.0001f
#define MAX_rpm 270.0f
#define MAX_counter 100.0f

/*电机参数*/
#define gear_ratio 20.0f
#define encoder_PPR 52.0f
#define encoder_quadrature 4.0f
#define sample_time 0.1f

#define GEAR_1_RPM 1.0f
#define GEAR_2_RPM 2.0f
#define GEAR_3_RPM 3.0f

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/*PID相关全局变量初始化*/
float Target,Actual,Out;
float Kp,Ki,Kd;
float Error0,Error1,Errorint;

int speed = 0;
int flag = 0;

uint32_t last_button_time = 0;
uint8_t current_gear = 0; // 0:旋钮模式, 1:1rpm, 2:2rpm, 3:3rpm
uint8_t last_button_state = 1; // 假设按键默认高电平
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*速度设置函数*/
void SetSpeed(int speed)
{
	if(speed > 0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	}
	else if(speed < 0){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
		speed = -speed;
	}
	else{
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
	}
	if(speed > 100){
		speed = 100;
	}
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,speed);
}

/*测速函数*/
int GetSpeed(TIM_HandleTypeDef *hencoder)
{
	int temp = (int16_t)__HAL_TIM_GET_COUNTER(hencoder);
	__HAL_TIM_SET_COUNTER(hencoder,0);
	return temp;
}

/*模式切换函数*/
GPIO_PinState CheckButton(void)
{
	GPIO_PinState current_state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);

    /*按键检测*/
    if(last_button_state == GPIO_PIN_SET && current_state == GPIO_PIN_RESET) {
    	HAL_Delay(10);
        // 按键按下
        last_button_state = current_state;
        return GPIO_PIN_SET;
    }

    last_button_state = current_state;
    return GPIO_PIN_RESET;
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
  MX_I2C1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */

  /*OLED初始化*/
  OLED_Init();

  /*TIM1初始化*/
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);

  /*TIM2初始化*/
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_3,0);

  /*TIM3初始化*/
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

  /*TIM4初始化*/
  HAL_TIM_Base_Start_IT(&htim4);

  /*局部变量初始化*/
  int16_t encoder = 50;
  int motor_speed = 0;
  int last_tick = 0;
  char MSG_Target[20] = "";
  char MSG_Out[20] = "";
  char MSG_Actual[20] = "";
  char MSG_Kp[20] = "";
  char MSG_Ki[20] = "";
  char MSG_Kd[20] = "";

//  char message[20] = "";

  /*初始速度设为0*/
  __HAL_TIM_SET_COUNTER(&htim1,encoder);

  /*设置PID值*/
  Kp = 1;
  Ki = 0.5;
  Kd = 0;

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  OLED_NewFrame();

	  if(CheckButton() == GPIO_PIN_SET) {
		  // 切换挡位
		  current_gear = (current_gear + 1) % 4; // 0,1,2,3循环
	      // 根据挡位设置目标值
	      switch(current_gear) {
	          case 0: // 旋钮模式
	              // 保持旋钮控制
	              break;
	          case 1: // 1rpm
	              Target = GEAR_1_RPM * (MAX_counter / MAX_rpm) * 60; // 转换为PWM值
	              break;
	          case 2: // 2rpm
	              Target = GEAR_2_RPM * (MAX_counter / MAX_rpm) * 60;
	              break;
	          case 3: // 3rpm
	              Target = GEAR_3_RPM * (MAX_counter / MAX_rpm) * 60;
	              break;
	      }

	      //延时防止连续触发
	      HAL_Delay(200);
	 }

	  if(current_gear == 0) {	//模式0时
		  /*读取旋转编码器的值*/
		  encoder = __HAL_TIM_GET_COUNTER(&htim1);

		  /*计数器阈值*/
		  if(encoder < 0){
			  encoder = 0;
		  }
		  else if(encoder > 100){
			  encoder = 100;
		  }

		  /*设置旋转编码器*/
		  __HAL_TIM_SET_COUNTER(&htim1,encoder);

		  /*将0~50映射到-100~0，将50~100映射到0~100*/
		  Target = (encoder - 50) * 2;

	  }

	  /*每隔10ms测一次速*/
	  if(HAL_GetTick() - last_tick >= 100) {
	    last_tick = HAL_GetTick();

	    /*调用测速函数*/
	    motor_speed = GetSpeed(&htim3);

	    /*计算实际速度(rpm)*/
//	    Actual = (((motor_speed / sample_time)) / (encoder_PPR * gear_ratio * encoder_quadrature)) * 60;	//正常公式
	    Actual = motor_speed;	//神秘公式
	    /*PID公式*/
	    Error1 = Error0;
	    Error0 = Target - Actual / (MAX_rpm / MAX_counter);		//rpm转换为PWM
	    if(fabs(Ki) > EPSILON){		//Ki过小时忽略，防止积分饱和
	    	Errorint += Error0;
	    }
	    else{
	    	Errorint = 0;
	    }
	    Out = Kp * Error0 + Ki * Errorint + Kd * (Error0 - Error1);	//输出

//	    sprintf(message,"encoder = %d",encoder);
//	    OLED_PrintString(0, 20, message, &font16x16, OLED_COLOR_NORMAL);

	    /*设置速度*/
	    SetSpeed(Out);
	  }

	  /*OLED显示*/
	  sprintf(MSG_Target,"Tar=%+4.2f",Target * (MAX_rpm / MAX_counter) / 60);
//	  sprintf(MSG_Target,"Tar_PWM=%+4.2f",Target);
	  OLED_PrintString(0, 0, MSG_Target, &font16x16, OLED_COLOR_NORMAL);

//	  sprintf(MSG_Out,"Out=%+4.2f",Out * (MAX_rpm / MAX_counter) / 60);
	  sprintf(MSG_Out,"Out_PWM=%+4.2f",Out);
	  OLED_PrintString(0, 20, MSG_Out, &font16x16, OLED_COLOR_NORMAL);

//	  sprintf(MSG_Actual,"Act=%+4.2f",Actual / 60);
	  sprintf(MSG_Actual,"rps=%+4.2f",Actual / 60);
	  OLED_PrintString(0, 40, MSG_Actual, &font16x16, OLED_COLOR_NORMAL);

//	  sprintf(MSG_Kp,"Kp=%2.1f",Kp);
//	  OLED_PrintString(80, 0, MSG_Kp, &font16x16, OLED_COLOR_NORMAL);
//	  sprintf(MSG_Ki,"Ki=%2.1f",Ki);
//	  OLED_PrintString(80, 20, MSG_Ki, &font16x16, OLED_COLOR_NORMAL);
//	  sprintf(MSG_Kd,"Kd=%2.1f",Kd);
//	  OLED_PrintString(80, 40, MSG_Kd, &font16x16, OLED_COLOR_NORMAL);

	  OLED_ShowFrame();

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
#ifdef USE_FULL_ASSERT
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
