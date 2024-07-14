#include "button_handler/button.h"

void btshort()
{
    printf("bt short handler\n");
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