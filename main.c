#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "button.h"

void btshort(TimerHandle_t *pxTimer)
{
    printf("bt short handler %d\n", time_us_32());
}

int main()
{
    timer_hw->dbgpause = 0x2;
    stdio_init_all();
    TimerHandle_t timerHandler;
    timerHandler = xTimerCreate("buttonTimer", 1000, pdTRUE, (void *)timerHandler, (TimerCallbackFunction_t)btshort);
    xTimerStart(timerHandler, 1000);
    // buttonHandlerInit();
    // setButtonHandlerShort(0, &btshort);

    vTaskStartScheduler();
    while (1)
    {
    }
}