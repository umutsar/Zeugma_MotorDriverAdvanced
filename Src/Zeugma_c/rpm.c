

#include "rpm.h"
#include "tim.h"
#include "bemf.h"
#include "main.h"

uint32_t rpm_sampling_array[6] = {0};
uint8_t array_index = 0;
uint8_t first_filterless_count = 0;
uint16_t filtered_rpm = 0;
uint32_t tim4Counter = 0;

uint16_t get_rpm(int32_t _difference_two_coummutation_time)
{
    if (_difference_two_coummutation_time == -1)
    {
        return 0;
    }
    rpm_sampling_array[array_index++] = _difference_two_coummutation_time;

    if (array_index == 6)
    {
        array_index = 0;
    }

    uint32_t sum = 0;
    for (uint8_t i = 0; i < first_filterless_count; i++)
    {
        sum += rpm_sampling_array[i];
    }

    if (first_filterless_count < 6)
    {
        filtered_rpm = rpm_sampling_array[first_filterless_count++];
    }
    else
    {
        filtered_rpm = (rpm_sampling_array[0] + rpm_sampling_array[1] + rpm_sampling_array[2] +
                        rpm_sampling_array[3] + rpm_sampling_array[4] + rpm_sampling_array[5]) /
                       6; // x microsecond / 10
    }

    if (filtered_rpm == 0)
    {
        return 0;
    }

    filtered_rpm = (TIMER_SETTING / (filtered_rpm * COMMUTATIONS_PER_REVOLUTION));
    if (filtered_rpm > 1450)
        rpm_max_limit_flag = 0;
    if (filtered_rpm > 1000)
        backEMF_mode = 0;
    if (filtered_rpm < 900)
        backEMF_mode = 0;
    return filtered_rpm;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    if (htim->Instance == TIM2)
    {
        rpm = 0;
    }

    if (htim->Instance == TIM3)
    {
        HAL_TIM_Base_Stop_IT(&htim3);

        if (bemf_execute_flag)
        {
            abc();
            // HAL_GPIO_EXTI_Callback(GPIO_PIN_1);
        }
    }

    if (htim->Instance == TIM4)
    {
        tim4Counter++;
    }
}