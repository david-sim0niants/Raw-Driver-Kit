#include <x86/ps2_keyboard.h>

#include <x86/intr/pic.h>
#include <x86/io.h>
#include <x86/intr/idt.h>

void ps2_keyboard_irq_handler(void)
{
}

void ps2_keyboard_enable()
{
    outb(0x64, 0xAE); // Enable the keyboard interface
    uint8_t mask = inb(0x21);  // Read the current interrupt mask (master PIC)
    mask &= ~(1 << 1);         // Clear bit 1 to unmask IRQ 1
    outb(0x21, mask);          // Write the new mask back
}
