#pragma once

#include <stdint.h>

struct IDTEntry32 {
    uint16_t isr_addr_low;
    uint16_t cs;
    uint8_t reserved;
    uint8_t attributes;
    uint16_t isr_addr_high;
} __attribute__((packed));

struct IDTR32 {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

void setup_idt32(void);

static inline void enable_idt(void)
{
    asm volatile ("sti");
}

static inline void clear_idt(void)
{
    asm volatile ("cli");
}
