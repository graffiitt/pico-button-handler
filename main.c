#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"

#include "button.h"
#include <stdio.h>
#include "pico/stdlib.h"

void btshort()
{
}

int main()
{
    timer_hw->dbgpause = 0x2;
   //stdio_init_all();
    
    buttonHandlerInit();
    setButtonHandlerShort(0, &btshort);

    vTaskStartScheduler();
    while (1)
    {
    }
}  