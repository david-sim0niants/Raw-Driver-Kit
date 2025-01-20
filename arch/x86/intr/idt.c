#include <x86/intr/idt.h>
#include <x86/intr/stubs.h>

#define IDT32_SIZE INTR32_NR_INTS

#define INTR_GATE 0x8E
#define TRAP_GATE 0x8F

__attribute__((aligned(0x10)))
static struct IDT32Entry idt32_entries[IDT32_SIZE] = {};
static struct IDTR32 idtr32 = {};

static void init_idt32_handler(uint16_t cs, uint8_t attributes,
        uint32_t handler, struct IDT32Entry *entry)
{
    entry->isr_addr_low = (uint16_t)handler;
    entry->cs = cs;
    entry->reserved = 0;
    entry->attributes = attributes;
    entry->isr_addr_high = (uint16_t)(handler >> 16);
}

void setup_idt32()
{
    uint16_t cs = 0;
    asm volatile ("mov %%cs, %0" : "=r"(cs));
    for (int i = 0; i < INTR32_NR_TRAPS; ++i)
        init_idt32_handler(cs, TRAP_GATE, intr32_entries[i], &idt32_entries[i]);

    for (int i = INTR32_NR_TRAPS; i < IDT32_SIZE; ++i)
        init_idt32_handler(cs, INTR_GATE, intr32_entries[i], &idt32_entries[i]);

    idtr32.base = (uint32_t)&idt32_entries[0];
    idtr32.limit = (uint16_t)(IDT32_SIZE * sizeof(struct IDT32Entry) - 1);

    asm volatile ("lidt %0" :: "m"(idtr32));
}
