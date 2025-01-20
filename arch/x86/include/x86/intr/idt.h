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
