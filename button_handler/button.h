#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

#define TIMER_DELAY 1000000
#define ALARM_NUM 0
#define ALARM_IRQ TIMER_IRQ_0

void alarmIrq();
void buttonHandlerInit();

#endif