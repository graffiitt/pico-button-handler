#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_1 6
#define BUTTON_2 7
#define BUTTON_3 8
#define BUTTON_4 9

#define NUMBER_BUTTONS 4

#define UPDATE_BUTTONS_TIME 50 // in ticks sheduler
#define TIME_PRESS_LONG 2000000
#define TIME_PRESS_SHORT 500000

enum BUTTON_ACTION
{
    PUSH,
    SHORT,
    HOLDING
};

typedef void (*button_handler)(enum BUTTON_ACTION);

typedef struct
{
    int input_pin;
    bool last_state;
    bool flag;
    uint32_t timePress; // timestamp when button was pressed

    button_handler bt_handler;
} button_cfg_t;

void buttonTask(__unused void *params);

bool setButtonHandler(int number, button_handler handler);

#endif