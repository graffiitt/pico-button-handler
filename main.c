#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "button.h"

void btshort()
{
    printf("bt short handler %d\n", time_us_32());
}

int main()
{
    timer_hw->dbgpause = 0x2;
    stdio_init_all();

    buttonHandlerInit();
    setButtonHandlerShort(0, &btshort);

    vTaskStartScheduler();
    while (1)
    {
    }
}  