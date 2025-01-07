#ifndef DEBUG_MONITOR_H
#define DEBUG_MONITOR_H

#include <stdint.h>
#include <stdio.h>

#define BUFFER_SIZE 512

void log_variable(const char *name, unsigned int value);
void LOG_POST();

#define LOG_VAR(v) log_variable(#v, v)

#endif /* DEBUG_MONITOR_H */