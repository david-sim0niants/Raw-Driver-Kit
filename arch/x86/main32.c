#include <x86/intr/idt.h>
#include <x86/intr/pic.h>
#include <x86/ps2_keyboard.h>
#include <x86/system.h>

char *const vga_text_buffer = (char *)0xB8000;

int main32(void)
{
    setup_idt32();
    pic_remap(0x20, 0x28);
    ps2_keyboard_enable();
    enable_interrupts();

    // char c = 0;
    // while (1) {
    //     ++c;
    //     for (int i = 0; i < 80 * 25 * 2; ++i)
    //         vga_text_buffer[i] = 'X' + c;
    // }

    while (1)
        halt();
    return 0;
}
