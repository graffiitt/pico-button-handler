#include "button.h"

void alarmIrq()
{
    hw_clear_bits(&timer_hw->intr, 1u << ALARM_NUM);
    printf("Alarm IRQ  pin state: %d\n", gpio_get(6));
    timer_hw->alarm[ALARM_NUM] = timer_hw->timerawl + TIMER_DELAY;
}

void buttonHandlerInit()
{
    gpio_init(6);
    gpio_set_dir(6, GPIO_IN);
    gpio_pull_up(6);

    hw_set_bits(&timer_hw->inte, 1u << ALARM_NUM);
    irq_set_exclusive_handler(ALARM_IRQ, alarmIrq);
    irq_set_enabled(ALARM_IRQ, true);
    timer_hw->alarm[ALARM_NUM] = timer_hw->timerawl + TIMER_DELAY;
}
