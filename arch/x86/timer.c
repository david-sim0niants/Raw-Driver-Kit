#include <x86/timer.h>
#include <x86/intr/defs.h>
#include <x86/intr/pic.h>
#include <x86/intr/handlers.h>

#define TIMER_INTR32_VECTOR 32

void timer_intr32_handler(uint32_t vector)
{
    // static char c = 10;
    // char *screen = (char *)(0xB8000);
    // ++c;
    // screen[0] = 'T';
    // screen[1] = c;
    // screen[2] = 'I';
    // screen[3] = c;
    // screen[4] = 'M';
    // screen[5] = c;
    // screen[6] = 'E';
    // screen[7] = c;
    pic_send_eoi(TIMER_INTR32_VECTOR - INTR32_NR_TRAPS);
}

void timer_enable()
{
    set_intr32_irq_handler(TIMER_INTR32_VECTOR, timer_intr32_handler);
}

void timer_disable()
{
    reset_intr32_irq_handler(TIMER_INTR32_VECTOR);
}
