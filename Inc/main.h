/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdbool.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define HALL_1_Pin GPIO_PIN_0
#define HALL_1_GPIO_Port GPIOA
#define HALL_1_EXTI_IRQn EXTI0_IRQn
#define HALL_2_Pin GPIO_PIN_1
#define HALL_2_GPIO_Port GPIOA
#define HALL_2_EXTI_IRQn EXTI1_IRQn
#define HALL_3_Pin GPIO_PIN_2
#define HALL_3_GPIO_Port GPIOA
#define HALL_3_EXTI_IRQn EXTI2_IRQn
#define Current_Pin GPIO_PIN_0
#define Current_GPIO_Port GPIOB
#define BUMBA_Pin GPIO_PIN_5
#define BUMBA_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

  extern volatile bool oldValue[3];
  extern bool mode;
  extern volatile bool first_step_flag;
  extern volatile bool flagg;
  extern uint32_t adcBuffer[7];
  extern volatile uint16_t speedInAdc;
  extern volatile uint16_t currentValue;
  extern volatile uint16_t filtered_current;
  extern bool run_status;
  extern volatile bool hall_A, hall_B, hall_C;
  extern bool geri_vites;
  extern volatile uint32_t step;
  extern volatile uint32_t pwm_value;
  extern uint32_t pedal_value_mapped;
  extern uint16_t min_pwm_limit;
  extern volatile uint16_t firstStepDelay;
  extern volatile uint32_t previousTime2;
  extern volatile uint8_t oncekiDegerler[3];
  extern uint32_t timeForRotorStopStatusMs;
  extern uint32_t timeForRotorStopStatusMsFlag;
  extern volatile uint32_t rpm_counter; // removable
  extern volatile uint32_t rpm;
  extern volatile uint32_t difference_two_coummutation_time;
  extern uint8_t logvarflag;
  extern uint16_t temporary_current_value;
  extern uint32_t new_ARR;
  extern uint32_t tim3sayi;
  extern uint8_t isStoppedTimers;

  extern volatile uint16_t saved_pwm_rpm[30];

  extern uint32_t interval_of_runstatus;

  extern volatile uint32_t phase_A;
  extern volatile uint32_t phase_B;
  extern volatile uint32_t phase_C;

  extern volatile uint16_t motor_voltage;

  extern uint16_t target_rpm;
  extern uint16_t max_rpm_limit;
  extern uint16_t max_current_limit;
  extern uint16_t max_pwm_limit;

  extern uint16_t battery_voltage;

  extern uint8_t step_counter;

  extern uint16_t analyze_data_1[480];
  extern uint8_t sender_flag;
  extern uint16_t array_counter;

  extern uint16_t rpm_analysis[1024];

  extern uint16_t interval_of_steps[1024];

  extern uint32_t analyze_step_counter;

  extern uint8_t step_atlandi;
  extern uint16_t rpm_max_limit_flag;
  extern uint8_t backEMF_mode;

  // Back EMF Variables
  extern uint32_t tim4Counter;

  extern uint8_t polarity_A;
  extern uint8_t polarity_B;
  extern uint8_t polarity_C;

  extern uint8_t polarity_A_old;
  extern uint8_t polarity_B_old;
  extern uint8_t polarity_C_old;

  extern uint32_t intersection_interval;
  extern uint16_t a, b, c, d, e, f;

  extern uint16_t notr;
  extern uint8_t bemf_execute_flag;


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
