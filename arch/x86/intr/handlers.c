#include <x86/intr/handlers.h>
#include <x86/intr/defs.h>

static void default_handler()
{
    asm volatile ("ud2");
}

intr32_trap_handler_t intr32_trap_handlers[INTR32_NR_TRAPS] = {default_handler};
intr32_irq_handler_t intr32_irq_handlers[INTR32_NR_IRQS] = {default_handler};

void set_intr32_trap_handler(uint32_t vector, intr32_trap_handler_t trap_handler)
{
    // TODO: come up with some way to assert valid vector number
    intr32_trap_handlers[vector] = trap_handler;
}

void set_intr32_irq_handler(uint32_t vector, intr32_irq_handler_t irq_handler)
{
    // TODO: come up with some way to assert valid vector number
    intr32_irq_handlers[vector] = irq_handler;
}

void reset_intr32_trap_handler(uint32_t vector)
{
    intr32_trap_handlers[vector] = default_handler;
}

void reset_intr32_irq_handler(uint32_t vector)
{
    intr32_irq_handlers[vector] = default_handler;
}
