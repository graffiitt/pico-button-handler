#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

#define BUTTON_1 6
#define BUTTON_2 7
#define BUTTON_3 8
#define BUTTON_4 9

#define UPDATE_BUTTONS_TIME 50 // in ticks sheduler
#define TIME_PRESS_LONG 3000000
#define TIME_PRESS_SHORT 500000

struct Button
{
    bool flag;
    int numberPin;
    bool lastState;
    uint32_t timePress; // timestamp when button was pressed

    void (*handlerShortPress)(void);
    void (*handlerLongPress)(void);
};

void buttonHandlerInit();
void setButtonHandlerShort(uint8_t numButton, void (*fncHandler)());
void setButtonHandlerLong(uint8_t numButton, void (*fncHandler)());

#endif