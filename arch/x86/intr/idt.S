.altmacro

.macro intr32_stub_enter nr
    intr32_stub_\nr:
        cli # disable interrupts
        pushal # push all GP registers
        pushl $\nr # push the interrupt vector number
.endm

.macro intr32_stub_exit
    popl (%esp) # pop the interrupt vector number
    popal # pop all GP registers
    sti # to enable interrupts
    iret
.endm

.macro intr32_trap_stub nr
    intr32_stub_enter %nr
    pushl $0 # push dummy zero error code
    call intr32_trap_handler
    popl (%esp)
    intr32_stub_exit
.endm

.macro intr32_trap_stub_with_ec nr
    intr32_stub_enter %nr
    pushl 36(%esp) # 9 32-bit registers pushed so far, get the error code following them
    call intr32_trap_handler
    popl (%esp)
    intr32_stub_exit
.endm

.macro intr32_irq_stub nr
    intr32_stub_enter %nr
    call intr32_irq_handler
    intr32_stub_exit
.endm

.macro intr32_stub nr
    .if \nr < 32
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
.rept 256
    intr32_stub %i
    .set i, i + 1
.endr

.globl intr32_trap_handler
.globl intr32_irq_handler

.section .data

.macro intr32_entry nr
    .long intr32_stub_\nr
.endm

.globl intr32_entries
intr32_entries:

.set i, 0
.rept 256
    intr32_entry %i
    .set i, i + 1
.endr

