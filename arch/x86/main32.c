#include "x86/idt.h"

char *const vga_text_buffer = (char *)0xB8000;

int main32(void)
{
    setup_idt32();
    enable_idt();

    char c = 0;
    while (1) {
        ++c;
        for (int i = 0; i < 80 * 25 * 2; ++i)
            vga_text_buffer[i] = 'X' + c;
    }

    asm volatile ("hlt" ::: "memory");
    return 0;
}
