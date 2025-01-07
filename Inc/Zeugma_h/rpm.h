
#ifndef RPM_H
#define RPM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"

#define COMMUTATIONS_PER_REVOLUTION 24
#define TIMER_SETTING 6000000

uint16_t get_rpm(int32_t _difference_two_coummutation_time);

#ifdef __cplusplus
}
#endif

#endif /* RPM_H */
