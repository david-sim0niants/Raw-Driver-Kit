#include <x86/intr/idt.h>
#include <x86/intr/pic.h>

#define IDT_SIZE 256
#define IDT_NR_EXCEPTIONS 32

#define INTR_GATE 0x8E
#define TRAP_GATE 0x8F

__attribute__((aligned(0x10)))
static struct IDT32Entry idt32_entries[IDT_SIZE] = {};
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
    for (int i = 0; i < IDT_NR_EXCEPTIONS; ++i)
        init_idt32_handler(cs, TRAP_GATE, intr32_entries[i], &idt32_entries[i]);

    for (int i = IDT_NR_EXCEPTIONS; i < IDT_SIZE; ++i)
        init_idt32_handler(cs, INTR_GATE, intr32_entries[i], &idt32_entries[i]);

    idtr32.base = (uint32_t)&idt32_entries[0];
    idtr32.limit = (uint16_t)(IDT_SIZE * sizeof(struct IDT32Entry) - 1);

    asm volatile ("lidt %0" :: "m"(idtr32));
}

void intr32_trap_handler(uint32_t error_code, uint32_t vector)
{
    static char c = 10;
    char *screen = (char *)(0xB8000);
    ++c;
    screen[0] = 'T';
    screen[1] = c;
    screen[2] = 'R';
    screen[3] = c;
    screen[4] = 'P';
    screen[5] = c;
    pic_send_eoi(vector);
}

void intr32_irq_handler(uint32_t vector)
{
    static char c = 10;
    char *screen = (char *)(0xB8000);
    ++c;
    screen[0] = 'I';
    screen[1] = c;
    screen[2] = 'R';
    screen[3] = c;
    screen[4] = 'Q';
    screen[5] = vector;
    pic_send_eoi(vector);
}
