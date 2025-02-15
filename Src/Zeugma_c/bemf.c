
#include "bemf.h"
#include "tim.h"
#include "debug_monitor.h"
#include "main.h"
#include "steps.h"

uint16_t a, b, c, d, e, f = 0;

void decide_step(uint8_t _a, uint8_t _b, uint8_t _c)
{

    if (_a && !_b && _c && (!oldValue[0] && !oldValue[1] && oldValue[2]))
    // 101'den 100'e geçiş
    {
        oldValue[0] = 1;
        oldValue[1] = 0;
        oldValue[2] = 1;
        step = 1;
        bemf_execute_flag = 1;
    }
    else if (_a && !_b && !_c && (oldValue[0] && !oldValue[1] && oldValue[2])) // 100'den 110'a geçiş
    {
        oldValue[0] = 1;
        oldValue[1] = 0;
        oldValue[2] = 0;
        step = 2;
        bemf_execute_flag = 1;
    }

    else if (_a && _b && !_c && (oldValue[0] && !oldValue[1] && !oldValue[2])) // 100'den 110'a geçiş
    {
        oldValue[0] = 1;
        oldValue[1] = 1;
        oldValue[2] = 0;
        step = 3;
        bemf_execute_flag = 1;
    }

    else if (!_a && _b && !_c && (oldValue[0] && oldValue[1] && !oldValue[2])) // 100'den 110'a geçiş
    {
        oldValue[0] = 0;
        oldValue[1] = 1;
        oldValue[2] = 0;
        step = 4;
        bemf_execute_flag = 1;
    }

    else if (!_a && _b && _c && (!oldValue[0] && oldValue[1] && !oldValue[2])) // 100'den 110'a geçiş
    {
        oldValue[0] = 0;
        oldValue[1] = 1;
        oldValue[2] = 1;
        step = 5;
        bemf_execute_flag = 1;
    }
    else if (!_a && !_b && _c && (!oldValue[0] && oldValue[1] && oldValue[2])) // 100'den 110'a geçiş
    {
        oldValue[0] = 0;
        oldValue[1] = 0;
        oldValue[2] = 1;
        step = 6;
        bemf_execute_flag = 1;
    }
    else
    {
        bemf_execute_flag = 0;
    }
}
void abc()
{
    if (backEMF_mode)
    {
        // LOG_VAR(flagg);
        decide_step(polarity_A, polarity_B, polarity_C);
        execute_step(step);
    }
}

void phaseControlBemf()
{
    if (polarity_A + polarity_A_old == 1)
    {
        intersection_interval = __HAL_TIM_GET_COUNTER(&htim4);
        __HAL_TIM_SET_AUTORELOAD(&htim3, (intersection_interval * 2) / 3);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SET_COUNTER(&htim4, 0);
        polarity_A_old = polarity_A;
        // log_var_analysis();
        abc();
    }
    else if (polarity_B + polarity_B_old == 1)
    {
        intersection_interval = __HAL_TIM_GET_COUNTER(&htim4);
        __HAL_TIM_SET_AUTORELOAD(&htim3, (intersection_interval * 2) / 3);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SET_COUNTER(&htim4, 0);
        polarity_B_old = polarity_B;
        // log_var_analysis();
        abc();
    }
    else if (polarity_C + polarity_C_old == 1)
    {
        intersection_interval = __HAL_TIM_GET_COUNTER(&htim4);
        __HAL_TIM_SET_AUTORELOAD(&htim3, (intersection_interval * 2) / 3);
        HAL_TIM_Base_Start_IT(&htim3);
        __HAL_TIM_SET_COUNTER(&htim4, 0);
        polarity_C_old = polarity_C;
        // log_var_analysis();
        abc();
    }
    else
    {
        a = a;
    }
}

void log_var_analysis()
{
    if (rpm > 800 && 0)
    {
        a = polarity_A_old;
        b = polarity_B_old;
        c = polarity_C_old;
        d = hall_A;
        e = hall_B;
        f = hall_C;

        static uint8_t log_counter = 0;
        log_counter += 1;

        if (log_counter == 6)
        {
            LOG_POST();
            log_counter = 0;

            LOG_VAR(a);
            LOG_VAR(b);
            LOG_VAR(c);
            LOG_VAR(d);
            LOG_VAR(e);
            LOG_VAR(f);
        }
        else
        {
            LOG_VAR(a);
            LOG_VAR(b);
            LOG_VAR(c);
            LOG_VAR(d);
            LOG_VAR(e);
            LOG_VAR(f);
        }
    }
}

// a:1,b:1,c:1,d:2,e:2,f:1
