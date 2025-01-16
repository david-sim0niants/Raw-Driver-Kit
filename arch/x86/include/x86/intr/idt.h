#pragma once

#include <stdint.h>

struct IDT32Entry {
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

extern uint32_t intr32_entries[256];

void intr32_trap_handler(uint32_t error_code, uint32_t vector);
void intr32_irq_handler(uint32_t vector);
