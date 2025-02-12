
#ifndef BEMF_H
#define BEMF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f1xx_hal.h"
#include "main.h"



extern uint8_t commutation_step;

void phaseControlBemf();
void abc();


void log_var_analysis();
void set_step();

#ifdef __cplusplus
}
#endif

#endif /* BEMF_H */
