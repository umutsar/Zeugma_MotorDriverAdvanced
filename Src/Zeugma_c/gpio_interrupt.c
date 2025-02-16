
#include "gpio_interrupt.h"
#include "tim.h"
#include "rpm.h"
#include "old_value_hall.h"
#include "steps.h"
#include <stdlib.h>
#include "main.h"
#include <debug_monitor.h>

#define ALPHA_SHIFT_B 4            // α = 1 / 2^ALPHA_SHIFT (örn: 3 → α = 1/8)
#define ALPHA_B (1 << ALPHA_SHIFT_B) // 2^ALPHA_SHIFT

uint16_t ema_filter4(uint16_t new_value)
{
  static uint16_t filtered_value4 = 0;

  if (filtered_value4 == 0)
    filtered_value4 = new_value;

  filtered_value4 = filtered_value4 + ((new_value - filtered_value4) >> ALPHA_SHIFT_B);

  return filtered_value4;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

  hall_A = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
  hall_B = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
  hall_C = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
  first_step_flag = 1;
  // if (hall_A != oncekiDegerler[0] || hall_B != oncekiDegerler[1] || hall_C != oncekiDegerler[2])
  // {
  // rpm_counter++;
  difference_two_coummutation_time = __HAL_TIM_GET_COUNTER(&htim2);
  difference_two_coummutation_time_filtered = ema_filter4(difference_two_coummutation_time);

  rpm = get_rpm(difference_two_coummutation_time);

  for (int i = 0; i < 30; i++)
  {
    if (rpm > (i * 100) && rpm <= ((i + 1) * 100))
    {
      saved_pwm_rpm[i] = pwm_value;
      break;
    }
  }

  __HAL_TIM_SET_COUNTER(&htim2, 0);
  // }

  if (run_status)
  {
    if ((hall_A == hall_C) && (hall_A == hall_B))
    {
      hall_A = oncekiDegerler[0];
      hall_B = oncekiDegerler[1];
      hall_C = oncekiDegerler[2];
    }
    else
    {
      oncekiDegerler[0] = hall_A;
      oncekiDegerler[1] = hall_B;
      oncekiDegerler[2] = hall_C;
    }
  }
  // sample_phase_data(rpm, (uint16_t)phase_A, (uint16_t)phase_B, (uint16_t)phase_C);
  if (!backEMF_mode)
  {
    set_old_value();
    execute_step(step);
  }
  // analyze_step_counter++;
}

// void ZeroCross_Interrupt_Handler()
// {
//   static uint32_t last_zc_time = 0;
//   uint32_t current_time = __HAL_TIM_GET_COUNTER(&htim3); // Timer'dan zaman oku

//   uint32_t T_previous_comm = current_time - last_zc_time;
//   last_zc_time = current_time;

//   uint32_t T_delay = T_previous_comm / 2; // Gecikme süresi hesapla

//   __HAL_TIM_SET_COUNTER(&htim3, 0);          // Timer sıfırla
//   __HAL_TIM_SET_AUTORELOAD(&htim3, T_delay); // Yeni süre ayarla
//   HAL_TIM_Base_Start_IT(&htim3);             // Timer başlat ve interrupt etkinleştir
// }
