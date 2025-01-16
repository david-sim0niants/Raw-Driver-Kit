#pragma once

#include <stdint.h>

#include <x86/io.h>

#define PIC1_PORT    0x20
#define PIC2_PORT    0xA0
#define PIC1_COMMAND    PIC1_PORT
#define PIC1_DATA       (PIC1_PORT + 1)
#define PIC2_COMMAND    PIC2_PORT
#define PIC2_DATA       (PIC2_PORT + 1)

#define PIC_EOI 0x20

#define ICW1_ICW4   0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4  0x04
#define ICW1_LEVEL  0x08
#define ICW1_INIT   0x10

#define ICW4_8086   0x01
#define ICW4_AUTO   0x02
#define ICW4_BUF_SLAVE  0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM   0x10

#define PIC_READ_IRR    0x0A
#define PIC_READ_ISR    0x0B

void pic_remap(int offset1, int offset2);
void pic_disable(void);

static inline void pic_send_eoi(uint8_t irq)
{
    if (irq >= 8)
        outb(PIC2_PORT, PIC_EOI);
    outb(PIC1_PORT, PIC_EOI);
}

uint16_t pic_get_irr(void);
uint16_t pic_get_isr(void);
