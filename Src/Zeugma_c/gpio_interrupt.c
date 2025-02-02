
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
  first_step_flag = 1;
  if (hall_A != oncekiDegerler[0] || hall_B != oncekiDegerler[1] || hall_C != oncekiDegerler[2])
  {
    // rpm_counter++;
    difference_two_coummutation_time = __HAL_TIM_GET_COUNTER(&htim2);
    rpm = get_rpm(difference_two_coummutation_time);

    // if (rpm < 100 && rpm > 0)
    //   saved_pwm_rpm[0] = pwm_value;
    // else if (rpm < 200 && rpm > 100)
    //   saved_pwm_rpm[1] = pwm_value;
    // else if (rpm < 300 && rpm > 200)
    //   saved_pwm_rpm[2] = pwm_value;
    // else if (rpm < 400 && rpm > 300)
    //   saved_pwm_rpm[3] = pwm_value;
    // else if (rpm < 500 && rpm > 400)
    //   saved_pwm_rpm[4] = pwm_value;

    for (int i = 0; i < 30; i++)
    {
      if (rpm > (i * 100) && rpm <= ((i + 1) * 100))
      {
        saved_pwm_rpm[i] = pwm_value;
        break;
      }
    }

    if (rpm < 100)
      rpm = 0;
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