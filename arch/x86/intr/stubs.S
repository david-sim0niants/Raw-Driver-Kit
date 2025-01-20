#include <x86/intr/stubs.h>
#include <x86/intr/handlers.h>

.altmacro

.macro intr32_stub_enter nr
intr32_stub_\nr:
    cli # disable interrupts
    pushal # push all GP registers
    pushl $\nr # push the interrupt vector number
.endm

.macro intr32_stub_exit
    popal # pop all GP registers
    sti # to enable interrupts
    iret
.endm

.macro intr32_trap_stub nr
    intr32_stub_enter %nr
    pushl $0 # push dummy zero error code
    call *intr32_trap_handlers + 4 * \nr
    addl $8, %esp # pop the interrupt vector number and dummy zero error code
    intr32_stub_exit
.endm

.macro intr32_trap_stub_with_ec nr
    intr32_stub_enter %nr
    pushl 36(%esp) # 9 32-bit registers pushed so far, get the error code following them
    call *intr32_trap_handlers + 4 * \nr
    addl $8, %esp # pop the interrupt vector number and error code
    intr32_stub_exit
.endm

.macro intr32_irq_stub nr
    intr32_stub_enter %nr
    call *intr32_irq_handlers + 4 * \nr
    addl $4, %esp # pop the interrupt vector number
    intr32_stub_exit
.endm

.macro intr32_stub nr
    .if \nr < INTR32_NR_TRAPS
        .if \nr == 8 || (10 <= \nr && \nr <= 14) || \nr == 17 || \nr == 21
            intr32_trap_stub_with_ec %nr
        .else
            intr32_trap_stub %nr
        .endif
    .else
        intr32_irq_stub %nr
    .endif
.endm

.section .text

.set i, 0
.rept INTR32_NR_INTS
    intr32_stub %i
    .set i, i + 1
.endr

.section .data

.macro intr32_entry nr
    .long intr32_stub_\nr
.endm

.globl intr32_entries
intr32_entries:

.set i, 0
.rept INTR32_NR_INTS
    intr32_entry %i
    .set i, i + 1
.endr
