#pragma once

#ifdef __ASSEMBLER__
.globl intr32_trap_handlers
.globl intr32_irq_handlers
#else

#include <stdint.h>

typedef void (*intr32_trap_handler_t)(uint32_t error_code, uint32_t vector);
typedef void (*intr32_irq_handler_t)(uint32_t vector);

void set_intr32_trap_handler(uint32_t vector, intr32_trap_handler_t trap_handler);
void set_intr32_irq_handler(uint32_t vector, intr32_irq_handler_t irq_handler);

void reset_intr32_trap_handler(uint32_t vector);
void reset_intr32_irq_handler(uint32_t vector);

#endif
