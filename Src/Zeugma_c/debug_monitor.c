#include "debug_monitor.h"
#include "usbd_cdc_if.h"
#include "usb_device.h"

char log_buffer[BUFFER_SIZE];
int log_length = 0;

void log_variable(const char *name, unsigned int value) {
    int len = snprintf(log_buffer + log_length, BUFFER_SIZE - log_length, "%s:%u,", name, value);
    log_length += len;
}

void LOG_POST() {
    if (log_length > 0) {
        log_buffer[log_length - 1] = '\n';
        CDC_Transmit_FS((uint8_t *)log_buffer, log_length);
    }
    log_length = 0; 
    log_buffer[0] = '\0';
}