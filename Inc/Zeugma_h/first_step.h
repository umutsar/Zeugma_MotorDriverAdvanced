
#ifndef FIRST_STEP_H
#define FIRST_STEP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h"
#include <stdbool.h>

extern uint8_t commutation_step;

void first_step(bool _a, bool _b, bool _c);
void find_commutation_step(bool _a, bool _b, bool _c);
int step_counter_control();
#ifdef __cplusplus
}
#endif

#endif /* FIRST_STEP_H */
