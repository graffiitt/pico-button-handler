#include "FreeRTOS.h"
#include "task.h"

#include <string.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#include "button.h"

static button_cfg_t button[4];

static void initPins(button_cfg_t *bt)
{
    gpio_init(bt->input_pin);
    gpio_set_dir(bt->input_pin, GPIO_IN);
    gpio_pull_up(bt->input_pin);
}

static void handlerButton(bool const state, button_cfg_t *bt)
{
    if ((!state) && bt->last_state) // fix pressed
    {
        bt->timePress = time_us_32();
        bt->flag = 1;
        if (bt->bt_handler)
            bt->bt_handler(PUSH);
    }

    if (!(state && bt->last_state) &&
        ((time_us_32() - bt->timePress) > TIME_PRESS_LONG) && bt->flag)
    {
        bt->flag = 0;
        if (bt->bt_handler)
            bt->bt_handler(HOLDING);
    }

    if ((state && !bt->last_state) && ((time_us_32() - bt->timePress) < TIME_PRESS_LONG))
    {
        if (bt->bt_handler)
            bt->bt_handler(SHORT);
    }
    bt->last_state = state;
}

void buttonTask(__unused void *params)
{
    button[0].input_pin = BUTTON_1;
    button[1].input_pin = BUTTON_2;
    button[2].input_pin = BUTTON_3;
    button[3].input_pin = BUTTON_4;

    for (int i = 0; i < 4; i++)
    {
        initPins(&button[i]);
        button[i].last_state = gpio_get(button[i].input_pin);
    }

    while (true)
    {
        bool state[] = {
            gpio_get(BUTTON_1),
            gpio_get(BUTTON_2),
            gpio_get(BUTTON_3),
            gpio_get(BUTTON_4),
        };

        if ((state[0] + state[1] + state[2] + state[3]) > 2)
        {
            for (int i = 0; i < 4; i++)
                handlerButton(state[i], &button[i]);
            vTaskDelay(UPDATE_BUTTONS_TIME);
        }
        else
        {
            taskYIELD();
        }
    }
}

bool setButtonHandler(int number, button_handler handler)
{
    if (number >= NUMBER_BUTTONS)
        return false;

    button[number].bt_handler = handler;

    return true;
}
