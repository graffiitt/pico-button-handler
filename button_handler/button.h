#ifndef BUTTON_HANDLER_H
#define BUTTON_HANDLER_H

#define BUTTON_TASK_PRIORITY (tskIDLE_PRIORITY + 2UL)
#define BUTTON_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

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