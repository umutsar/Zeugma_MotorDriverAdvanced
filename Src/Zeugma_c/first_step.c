
#include <tim.h>
#include <main.h>
#include "first_step.h"

uint8_t commutation_step = 0;
uint8_t step_counter = 0;

uint8_t newflag = 0;

void first_step(bool _a, bool _b, bool _c)
{ // KALKIS

  previousTime2 = HAL_GetTick();

  find_commutation_step(_a, _b, _c);

  pwm_value = min_pwm_limit;
  while (1)
  {
    if (first_step_flag && commutation_step == 1)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
      TIM1->CCER = 0x00C5;
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, min_pwm_limit);
      commutation_step = 2;
      step_counter++;
      if (step_counter_control())
        break;
    }

    if (first_step_flag && commutation_step == 2)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
      TIM1->CCER = 0x0C05;
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, min_pwm_limit);
      commutation_step = 3;
      step_counter++;
      HAL_Delay(firstStepDelay);
      if (step_counter_control())
        break;
    }

    if (first_step_flag && commutation_step == 3)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
      TIM1->CCER = 0x0C50;
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, min_pwm_limit);
      commutation_step = 4;
      step_counter++;
      HAL_Delay(firstStepDelay);
      if (step_counter_control())
        break;
    }

    if (first_step_flag && commutation_step == 4)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
      TIM1->CCER = 0x005C;
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, min_pwm_limit);
      commutation_step = 5;
      step_counter++;
      HAL_Delay(firstStepDelay);
      if (step_counter_control())
        break;
    }

    if (first_step_flag && commutation_step == 5)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
      TIM1->CCER = 0x050C;
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, min_pwm_limit);
      commutation_step = 6;
      step_counter++;
      HAL_Delay(firstStepDelay);
      if (step_counter_control())
        break;
    }

    if (first_step_flag && commutation_step == 6)
    {
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
      TIM1->CCER = 0x05C0;
      __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, min_pwm_limit);
      commutation_step = 1;
      step_counter++;
      HAL_Delay(firstStepDelay);
      if (step_counter_control())
        break;
    }

    else
      break;
  }

  HAL_Delay(firstStepDelay);
  if (first_step_flag)
  {
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
    TIM1->CCER = 0x0000;
  }
}

int step_counter_control()
{
  if (step_counter == 6)
  {
    step_counter = 0;
    return 1;
  }
  else
    return 0;
}

void find_commutation_step(bool _a, bool _b, bool _c)
{
  if (_a && !_b && _c)
    commutation_step = 4; // 4
  else if (_a && !_b && !_c)
    commutation_step = 5; // 5
  else if (_a && _b && !_c)
    commutation_step = 6; // 6
  else if (!_a && _b && !_c)
    commutation_step = 1; // 1
  else if (!_a && _b && _c)
    commutation_step = 2; // 2
  else if (!_a && !_b && _c)
    commutation_step = 3; // 3
}