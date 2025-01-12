#include "x86/idt.h"

#define IDT_SIZE 256
#define IDT_NR_EXCEPTIONS 32

#define INTR_GATE 0x8E
#define TRAP_GATE 0x8F

__attribute__((aligned(0x10)))
static struct IDTEntry32 idt_entries_32[IDT_SIZE] = {};
static struct IDTR32 idtr32 = {};

static void default_handler(void)
{
    asm volatile ("cli; hlt");
    __builtin_unreachable();
}

static void set_idt_defualt_handler(uint16_t cs, uint8_t attributes, struct IDTEntry32 *entry)
{
    entry->isr_addr_low = (uint16_t)(uint32_t)default_handler;
    entry->cs = cs;
    entry->reserved = 0;
    entry->attributes = attributes;
    entry->isr_addr_high = (uint16_t)((uint32_t)(default_handler) >> 16);
}

void setup_idt32()
{
    uint16_t cs = 0;
    asm volatile ("mov %%cs, %0" : "=r"(cs));
    for (int i = 0; i < IDT_NR_EXCEPTIONS; ++i)
        set_idt_defualt_handler(cs, TRAP_GATE, &idt_entries_32[i]);

    for (int i = IDT_NR_EXCEPTIONS; i < IDT_SIZE; ++i)
        set_idt_defualt_handler(cs, INTR_GATE, &idt_entries_32[i]);

    idtr32.base = (uint32_t)&idt_entries_32[0];
    idtr32.limit = (uint16_t)(IDT_SIZE * sizeof(struct IDTEntry32) - 1);

    asm volatile ("lidt %0" :: "m"(idtr32));
}
