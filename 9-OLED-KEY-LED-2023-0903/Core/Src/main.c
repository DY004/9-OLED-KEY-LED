/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "sys.h"
#include "delay.h"
#include "lcd.h"
#include "sdram.h"
#include "stdio.h"
#include "led.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */
    u8 x=0;
    u8 lcd_id[12];

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
    MX_USART1_UART_Init();
    MX_TIM3_Init();
    MX_TIM2_Init();
    /* USER CODE BEGIN 2 */
    delay_init(180);
    SDRAM_Init();                   //SDRAM��ʼ��
    LCD_Init();
    POINT_COLOR=RED;
    LCD_ShowString(1,40,260,32,32,"Apollo STM32F4/F7");
    LCD_ShowString(1,80,240,24,24,"LTDC TEST");
	LCD_ShowString(1,110,240,16,16,"ATOM@ALIENTEK");
	LCD_ShowString(1,130,240,16,16,lcd_id);		//��ʾLCD ID
	LCD_ShowString(1,150,240,12,12,"2016/1/6");
	
	POINT_COLOR=YELLOW;
	Chinese_Show_one(100,200,0,16,0);
	Chinese_Show_one(108,200,1,16,0);
	Chinese_Show_one(116,200,2,16,0);
	Chinese_Show_one(124,200,3,16,0);
	Chinese_Show_one(132,200,4,16,0);
	Chinese_Show_one(140,200,5,16,0);
	Chinese_Show_one(148,200,6,16,0);
	Chinese_Show_one(156,200,7,16,0);
	
    sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣



    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {
        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
//        switch(x)
//        {
//        case 0:
//            LCD_Clear(WHITE);
//            break;
//        case 1:
//            LCD_Clear(BLACK);
//            break;
//        case 2:
//            LCD_Clear(BLUE);
//            break;
//        case 3:
//            LCD_Clear(RED);
//            break;
//        case 4:
//            LCD_Clear(MAGENTA);
//            break;
//        case 5:
//            LCD_Clear(GREEN);
//            break;
//        case 6:
//            LCD_Clear(CYAN);
//            break;
//        case 7:
//            LCD_Clear(YELLOW);
//            break;
//        case 8:
//            LCD_Clear(BRRED);
//            break;
//        case 9:
//            LCD_Clear(GRAY);
//            break;
//        case 10:
//            LCD_Clear(LGRAY);
//            break;
//        case 11:
//            LCD_Clear(BROWN);
//            break;
//        }
//        POINT_COLOR=RED;
//        LCD_ShowString(2,40,260,32,32,"Apollo STM32F4/F7");
//        LCD_ShowString(2,80,240,24,24,"LTDC TEST");
//        LCD_ShowString(2,110,240,16,16,"ATOM@ALIENTEK");
//        LCD_ShowString(2,130,240,16,16,lcd_id);		//��ʾLCD ID
//        LCD_ShowString(2,150,240,12,12,"2016/1/6");
//        LCD_ShowString(2,180,240,12,12,"gImage_bulethouch");
//        Chinese_Show_one(2,200,3,32,0);


        x++;
        if(x==12)x=0;
        HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_1);
        delay_ms(1000);




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
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 15;
    RCC_OscInitStruct.PLL.PLLN = 216;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Activate the Over-Drive mode
    */
    if (HAL_PWREx_EnableOverDrive() != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
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