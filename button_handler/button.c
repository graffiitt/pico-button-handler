#include "FreeRTOS.h"
#include "task.h"

#include <string.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "hardware/irq.h"

#include "button.h"

struct Button button[4];
repeating_timer_t _timerButton;

static void handlerButton(bool const state, struct Button *bt);

void settingButton(const struct Button *bt)
{
    gpio_init(bt->numberPin);
    gpio_set_dir(bt->numberPin, GPIO_IN);
    gpio_pull_up(bt->numberPin);
}

void setButtonHandlerShort(uint8_t numButton, void (*fncHandler)())
{
    if (numButton > 4)
        return;
    button[numButton].handlerShortPress = fncHandler;
}

void setButtonHandlerLong(uint8_t numButton, void (*fncHandler)())
{
    if (numButton > 4)
        return;
    button[numButton].handlerLongPress = fncHandler;
}

void buttonTask(__unused void *params)
{
    button[0].numberPin = BUTTON_1;
    button[1].numberPin = BUTTON_2;
    button[2].numberPin = BUTTON_3;
    button[3].numberPin = BUTTON_4;

    for (int i = 0; i < 4; i++)
    {
        settingButton(&button[i]);
        button[i].lastState = gpio_get(button[i].numberPin);
    }
    
    while (true)
    {
        bool state[] = {
            gpio_get(BUTTON_1),
            gpio_get(BUTTON_2),
            gpio_get(BUTTON_3),
            gpio_get(BUTTON_4),
        };

        if (3 > (state[0] + state[1] + state[2] + state[3]))
            return;
        for (int i = 0; i < 4; i++)
            handlerButton(state[i], &button[i]);
        vTaskDelay(UPDATE_BUTTONS_TIME);
    }
}

static void handlerButton(bool const state, struct Button *bt)
{
    if ((!state) && bt->lastState) // fix pressed
    {
        bt->timePress = time_us_32();
        bt->flag = 1;
    }
    if (!(state && bt->lastState) &&
        ((time_us_32() - bt->timePress) > TIME_PRESS_LONG) && bt->flag)
    {
        bt->flag = 0;
        if (bt->handlerLongPress)
            bt->handlerLongPress();
    }
    if ((state && !bt->lastState) && ((time_us_32() - bt->timePress) < TIME_PRESS_LONG))
    {
        if (bt->handlerShortPress)
            bt->handlerShortPress();
    }
    bt->lastState = state;
}

void buttonHandlerInit()
{

    xTaskCreate(buttonTask, "buttonTask", BUTTON_TASK_STACK_SIZE, NULL, BUTTON_TASK_PRIORITY, NULL);
}