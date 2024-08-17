#include "FreeRTOS.h"
#include "task.h"

#include "button.h"

void btshort()
{
    printf("bt short handler 0\n");
}

int main()
{
    stdio_init_all();

    buttonHandlerInit();
    setButtonHandlerShort(0, &btshort);

    // printf("while 1");

    while (1)
    {
    }
}