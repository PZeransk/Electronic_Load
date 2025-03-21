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
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "menu.h"
#include "functions.h"
#include "DAC70501.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define menuCount 3
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
I2C_HandleTypeDef hi2c1;
uint8_t pulses = 0;
uint8_t positions = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

// define menus
menu CCMenu;
menu CVMenu;
menu CPMenu;
menu CRMenu;
menu BatMenu;


menu menuArray[menuCount]; // there are 4 menus

uint8_t toggles = 0;
uint8_t modToggles = 0;
uint8_t encToggles = 0;
uint8_t setPosition = 0;
uint8_t changeSetToggles = 0;

uint8_t arraySize=0;
bool wasToggled = false;
bool startStop = false;
bool setMode = false;


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
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_SPI2_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_I2C3_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */

  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);

  ssd1306_Init();
  ssd1306_SetCursor(8, 10);
  ssd1306_WriteString("ELECTRTONIC LOAD", Font_7x10, White);
  ssd1306_SetCursor(14, 20);
  ssd1306_WriteString("Ver. V0.0", Font_11x18, White);
  ssd1306_SetCursor(46, 38);
  ssd1306_WriteString("Author", Font_6x8, White);
  ssd1306_SetCursor(40, 46);
  ssd1306_WriteString("PZERANSK", Font_6x8, White);
  ssd1306_UpdateScreen();

  //ssd1306_Fill(Black);
  initStruct(&CCMenu, "CC Mode", "Set I:", "U in:", "Power:");
  initStruct(&CVMenu, "CV Mode", "Set U:", "Power:", "I in:");
  initStruct(&CPMenu, "CP Mode", "Set P:", "Power:", "x");
  initStruct(&CRMenu, "CR Mode", "Set R:", "Power:", "x");
  initStruct(&BatMenu, "BAT Test", "Set I:", "Set U", "Capacity");
  menuArray[0]=CCMenu;
  menuArray[1]=CPMenu;
  menuArray[2]=BatMenu;
  //menuArray[2]=CVMenu;
  //menuArray[3]=CRMenu;
  strcpy(menuArray[0].val_line1,"01000");
  strcpy( menuArray[1].val_line1,"010");
  HAL_Delay(2000);
  //displayMenu(&CCMenu);



  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    ssd1306_Fill(Black);

    checkLongPress(GPIOC, SET_Mode_Pin, &setMode, &changeSetToggles);

	modToggles = toggles%menuCount;
	menuArray[modToggles].status = startStop;
	pulses = TIM3->CNT;
	positions = pulses/2;
	if(setMode){
		if(strncmp(menuArray[modToggles].measVal1,"Set x:",4)==0){

			if(changeSetToggles%2==0){

				arraySize = sizeof(menuArray[modToggles].val_line1)/sizeof(*menuArray[modToggles].val_line1);
				setPosition = encToggles%(arraySize);
				ssd1306_Line(42+7*setPosition, 28, 42+7*setPosition+7, 28, White);
				menuArray[modToggles].val_line1[setPosition] = positions%10+'0';

			}else if(changeSetToggles%2==1){

			    arraySize = sizeof(menuArray[modToggles].val_line2)/sizeof(*menuArray[modToggles].val_line2);
				setPosition = encToggles%(arraySize);
				ssd1306_Line(42+7*setPosition, 38, 42+7*setPosition+7, 38, White);
				menuArray[modToggles].val_line2[setPosition] = positions%10+'0';

			}
		}else{
		    arraySize = sizeof(menuArray[modToggles].val_line1)/sizeof(*menuArray[modToggles].val_line1);
			setPosition = encToggles%(arraySize);
			ssd1306_Line(42+7*setPosition, 28, 42+7*setPosition+7, 28, White);
			menuArray[modToggles].val_line1[setPosition] = positions%10+'0';
		}


	}

	if(strcmp(menuArray[modToggles].menuName, CCMenu.menuName) == 0 && ChangeArrayToInt(menuArray[modToggles].val_line1, arraySize)>10000){
		strcpy(menuArray[modToggles].val_line1,"10000");
	}else if(strcmp(menuArray[modToggles].menuName, CPMenu.menuName) == 0 && ChangeArrayToInt(menuArray[modToggles].val_line1, arraySize)>200){
		strcpy(menuArray[modToggles].val_line1,"200");
	}


	displayMenu(&menuArray[modToggles]);


	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	//HAL_Delay(200);
	//HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	//HAL_Delay(200);

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

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == B1_Pin && !(startStop || setMode)){
		toggles++;
	}

	if(GPIO_Pin == StopStart_Pin){
		startStop = !startStop;
	}

	//if(GPIO_Pin == SET_Mode_Pin){
	//	setMode = !setMode;
	//}

	if(GPIO_Pin == EncoderSwitch_Pin && setMode){
		encToggles++;
		TIM3->CNT = 0;
	}
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
