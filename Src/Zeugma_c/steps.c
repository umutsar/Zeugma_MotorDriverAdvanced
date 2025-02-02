
#include "steps.h"

void execute_step(uint8_t _step)
{
    if (run_status)
    {
        switch (_step)
        {
        case 1:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
            TIM1->CCER = 0x00C5;
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm_value);
            previousTime2 = HAL_GetTick();
            break;
        case 2:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
            TIM1->CCER = 0x0C05;
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm_value);
            previousTime2 = HAL_GetTick();
            break;
        case 3:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
            TIM1->CCER = 0x0C50;
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm_value);
            previousTime2 = HAL_GetTick();
            break;
        case 4:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
            TIM1->CCER = 0x005C;
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, pwm_value);
            previousTime2 = HAL_GetTick();
            break;
        case 5:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
            TIM1->CCER = 0x050C;
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm_value);
            previousTime2 = HAL_GetTick();
            break;
        case 6:
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
            TIM1->CCER = 0x05C0;
            __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm_value);
            previousTime2 = HAL_GetTick();
            break;
        }
    }
}