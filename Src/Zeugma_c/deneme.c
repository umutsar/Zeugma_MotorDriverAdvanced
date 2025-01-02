
#include <main.h>

int flag1 = 0;
int flag = 0;
int flag_count = 0;
uint32_t previous_time = 0;

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    flag = 1;
    flag1 = 1;
}

int main()
{

    while (1)
    {
        if (flag1 == 1)
        {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
            flag1 = 0;
        }
        if (flag == 1 && HAL_GetTick() - previous_time > 500)
        {
            HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_4);
            flag_count++;
            if (flag_count == 5)
            {
                flag == 0;
                flag_count = 0;
            }
            previous_time = HAL_GetTick();
        }

        // jhglhkjlkj
    }
}