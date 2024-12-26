#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "button.h"
#include <stdio.h>
#include "pico/stdlib.h"

#define BUTTON_TASK_PRIORITY (tskIDLE_PRIORITY + 4UL)
#define BUTTON_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void btshort(enum BUTTON_ACTION action)
{
    switch (action)
    {
    case push:
        printf("%d push\n", 1);
        break;
    case release:
        printf("%d release\n", 1);
        break;
    case holding:
        printf("%d holding\n", 1);
        break;
    default:
        break;
    }
}
void btshort2(enum BUTTON_ACTION action)
{
    switch (action)
    {
    case push:
        printf("%d push\n", 2);
        break;
    case release:
        printf("%d release\n", 2);
        break;
    case holding:
        printf("%d holding\n", 2);
        break;
    default:
        break;
    }
}

int main()
{
    timer_hw->dbgpause = 0x2;
    stdio_init_all();

    setButtonHandler(0, btshort);
    setButtonHandler(1, btshort2);
    
    xTaskCreate(buttonTask, "buttonTask", BUTTON_TASK_STACK_SIZE, NULL, BUTTON_TASK_PRIORITY, NULL);

    vTaskStartScheduler();
    while (1)
    {
    }
}