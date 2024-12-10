
#include "gpio_interrupt.h"
#include "tim.h"
#include "rpm.h"
#include "old_value_hall.h"
#include "steps.h"

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  hall_A = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0);
  hall_B = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1);
  hall_C = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2);
  if (hall_A != oncekiDegerler[0] || hall_B != oncekiDegerler[1] || hall_C != oncekiDegerler[2])
  {
    // rpm_counter++;
    difference_two_coummutation_time = __HAL_TIM_GET_COUNTER(&htim2);
    rpm = get_rpm(difference_two_coummutation_time);
    __HAL_TIM_SET_COUNTER(&htim2, 0);
  }

  else
  {
    return;
  }

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

  set_old_value();
  execute_step(step);
}