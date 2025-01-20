#include <x86/ps2_keyboard.h>

#include <x86/intr/defs.h>
#include <x86/intr/pic.h>
#include <x86/intr/handlers.h>
#include <x86/io.h>

#include <stdbool.h>

#define PS2_KEYBOARD_INTR32_VECTOR 33

#define VGA_TEXT_BUFFER ((char *)(0xB8000))
#define VGA_TEXT_BUFFER_SIZE (80 * 25 * 2)

// TODO: obviously this is all temporary
static bool ps2_key_extended = false;
static unsigned int cursor = 0;

// TODO: this mapping is very little
static char ps2_to_ascii_map[] = {
    0x0, 0x1B,
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b',
    '\t', 'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[', ']', '\n',
    0x0,
    'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`',
    0x0, '\\', 'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', 0x0,
    '*', 0x0, ' '
};

char ps2_map_to_ascii(unsigned char scan_code)
{
    if (scan_code >= sizeof(ps2_to_ascii_map) / sizeof(ps2_to_ascii_map[0]))
        return 0;
    else
        return ps2_to_ascii_map[scan_code];
}

void ps2_keyboard_irq_handler(uint32_t vector)
{
    pic_send_eoi(PS2_KEYBOARD_INTR32_VECTOR - INTR32_NR_TRAPS);
    unsigned char scan_code = inb(0x60);
    if (scan_code == 0xE0) {
        ps2_key_extended = true;
    } else if (scan_code > 0 && scan_code <= 128) {
        if (cursor >= VGA_TEXT_BUFFER_SIZE)
            return;

        char key = ps2_map_to_ascii(scan_code);
        switch (key) {
        case '\b':
            if (cursor < 2)
                break;
            cursor -= 2;
            VGA_TEXT_BUFFER[cursor] = ' ';
            // VGA_TEXT_BUFFER[cursor + 1] = 0;
            break;
        case '\n':
            cursor = (cursor / (80 * 2) + 1) * (80 * 2);
            if (cursor >= VGA_TEXT_BUFFER_SIZE)
                cursor -= 80 * 2;
            break;
        case '\t':
        case 0x1B:
        case 0x0:
            break;
        default:
            VGA_TEXT_BUFFER[cursor] = key;
            cursor = (cursor + 2) % VGA_TEXT_BUFFER_SIZE;
            break;
        }
    } else {
        // TODO: support this case too
    }
}

void ps2_keyboard_enable()
{
    outb(0x64, 0xAE); // Enable the keyboard interface
    uint8_t mask = inb(0x21);  // Read the current interrupt mask (master PIC)
    mask &= ~(1 << 1);         // Clear bit 1 to unmask IRQ 1
    outb(0x21, mask);          // Write the new mask back
    set_intr32_irq_handler(PS2_KEYBOARD_INTR32_VECTOR, ps2_keyboard_irq_handler);
}
