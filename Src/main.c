/* USER CODE BEGIN Header */
/**
 **************************
 * @file           : main.c
 * @brief          : Main program body
 **************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 **************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"
#include "usb_device.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdbool.h"
#include "debug_monitor.h"
#include "first_step.h"
#include "rpm.h"
#include "steps.h"
#include "old_value_hall.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define voltageConversion_value 0.0396593777777778
#define currentConversionValue 0.00083008
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

volatile bool oldValue[3] = {0, 0, 0};
bool mode = 1;
volatile bool first_step_flag = 1;
volatile bool flagg = 1;
uint32_t adcbuffer[2] = {0, 0};
volatile uint16_t speedInAdc = 0;
volatile uint16_t currentValue = 0;
volatile uint16_t filtered_current = 0;
bool run_status = false;
volatile bool hall_A = 0, hall_B = 0, hall_C = 0;
bool geri_vites = true;
volatile uint32_t step = 0;
volatile uint32_t pwm_value = 0;
uint32_t pedal_value_mapped = 0;
uint16_t min_pwm_limit = 100;
volatile uint16_t firstStepDelay = 40;
volatile uint32_t previousTime2 = 0;
volatile uint8_t oncekiDegerler[3];
uint32_t timeForRotorStopStatusMs = 0;
uint32_t timeForRotorStopStatusMsFlag = 0;

volatile uint32_t rpm_counter = 0;
volatile uint32_t rpm;
volatile uint32_t difference_two_coummutation_time = 1;

uint32_t previousTime3 = 0;

// Temporary variables
uint16_t minCurrent = 5000;
uint16_t maxCurrent = 0;
uint16_t temporary_current_value = 0;
uint16_t average = 0;

long map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
// {
//   rpm = rpm_counter * 25;
//   rpm_counter = 0;
// }

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{ // ADC DMA LEMLERİ
  if (hadc->Instance == ADC1)
  {
    currentValue = adcbuffer[1];
    filtered_current = 4500 - currentValue;

    // TEMPORARY DEVELOPING LINES
    if (filtered_current <= 1000 && filtered_current >= 0)
      temporary_current_value = map(filtered_current, 0, 1000, 0, 4430);
    else if (filtered_current > 1000)
      temporary_current_value = 1000;
    else
      temporary_current_value = 0;
    // END

    speedInAdc = adcbuffer[0];
    if ((currentValue <= 1500) && (pwm_value > 100))
    {
      pwm_value = pwm_value - 1;
    }

    if (minCurrent > filtered_current)
      minCurrent = filtered_current;
    if (maxCurrent < filtered_current)
      maxCurrent = filtered_current;
  }
}

// GPIO INTERRUPT HAS BEEN REMOVED FROM HERE

uint16_t filtreye_koy(uint16_t num)
{
  static uint16_t dizi[40] = {0}; // Ortalama hesaplama için dizi
  static uint16_t dizi_index = 0; // Diziye ekleme için indeks
  uint32_t toplam = 0;            // Toplamı tutmak için değişken
  uint16_t average = 0;           // Ortalama değeri tutmak için

  // Yeni numarayı diziye ekle
  dizi[dizi_index++] = num;

  // Dizi indexi sınır kontrolü
  if (dizi_index == 40)
    dizi_index = 0;

  // Dizi elemanlarının toplamını hesapla
  for (int i = 0; i < 40; i++)
  {
    toplam += dizi[i];
  }

  // Ortalama hesapla
  average = toplam / 40;

  return average;
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
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_USB_DEVICE_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  HAL_ADC_Start_DMA(&hadc1, adcbuffer, 2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);

  HAL_TIM_Base_Start(&htim2);

  uint32_t previousTime = HAL_GetTick();
  HAL_Delay(1000);
  TIM1->CCER = 0x0000;
  previousTime2 = HAL_GetTick();
  previousTime3 = HAL_GetTick();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    uint32_t filtreli_akim = filtreye_koy(filtered_current);
    average = 0;

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
    if (HAL_GetTick() - previousTime3 > 65)
    {
      // LOG_VAR(rpm);
      filtreli_akim = map(filtreli_akim, 1200, 1600, 20, 800);
      LOG_VAR(rpm);
      LOG_VAR(filtreli_akim);
      LOG_VAR(pedal_value_mapped);
      LOG_VAR(pwm_value);
      LOG_POST();
      previousTime3 = HAL_GetTick();
    }

    hall_A = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
    hall_B = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
    hall_C = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);

    // LOG_VAR(rpm);

    // LOG_VAR(filtered_current);
    // LOG_VAR(pwm_value);

    // LOG_VAR(pedal_value_mapped);
    // LOG_VAR(temporary_current_value);

    // LOG_POST();

    if (HAL_GetTick() - previousTime2 > 400)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
      TIM1->CCER = 0x0000;
      rpm = get_rpm(-1);
      previousTime2 = HAL_GetTick();
    }

    if (HAL_GetTick() - timeForRotorStopStatusMs > 450)
    {
      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
      HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
      HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
      HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
      HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);
      
    }
    if (speedInAdc >= 900 && HAL_GetTick() - timeForRotorStopStatusMs > 450) // Checked
    {
      timeForRotorStopStatusMsFlag = 1;

      mode = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5); // Nitro mod
      if (mode == 0)
      {
        pedal_value_mapped = map(speedInAdc, 700, 3600, 0, 10000);
      }
      else
      {
        pedal_value_mapped = map(speedInAdc, 700, 3600, 0, 10000);
      }
      HAL_Delay(10); // Kaldırılabilir

      if (temporary_current_value > pedal_value_mapped) // if (filtered_current > pedal_value_mapped)
      {
        if (pwm_value > min_pwm_limit)
        {
          pwm_value -= 1;
        }
        else
        {
          pwm_value = min_pwm_limit;
        }
      }

      else
      {
        if (pwm_value < min_pwm_limit)
        {
          pwm_value = min_pwm_limit;
        }
        else if (pwm_value < 900)
        {
          if (HAL_GetTick() - previousTime > 2)
          {
            pwm_value += 4;
            previousTime = HAL_GetTick();
          }
        }
      }

      if (!run_status)
      {
        run_status = true;
        geri_vites = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_3);
        first_step(hall_A, hall_B, hall_C);
      }
    }
    else if ((run_status) && (speedInAdc < 900))
    {
      pwm_value = 0;
      // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, 0);
      // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_14, 0);
      // HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, 0);
      // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0); // Mosfetleri kapatıyoruz
      // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
      // __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
      TIM1->CCER = 0x0CCC;
      flagg = 1;
      oldValue[0] = 0;
      oldValue[1] = 0;
      oldValue[2] = 0;
      hall_A = 0;
      hall_B = 0;
      hall_C = 0;
      step = 0;
      pedal_value_mapped = 0;
      first_step_flag = 1;
      run_status = false;

      HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
      HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
      HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
      HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);
      HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_3);
      HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_3);
      if (timeForRotorStopStatusMsFlag)
      {
        timeForRotorStopStatusMs = HAL_GetTick();
        timeForRotorStopStatusMsFlag = 0;
      }
    }
  }

  hall_A = HAL_GPIO_ReadPin(GPIOA, HALL_1_Pin);
  hall_B = HAL_GPIO_ReadPin(GPIOA, HALL_2_Pin);
  hall_C = HAL_GPIO_ReadPin(GPIOA, HALL_3_Pin);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

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
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC | RCC_PERIPHCLK_USB;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  PeriphClkInit.UsbClockSelection = RCC_USBCLKSOURCE_PLL_DIV1_5;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
