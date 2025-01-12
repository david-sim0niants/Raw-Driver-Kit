char *const vga_text_buffer = (char *)0xB8000;

int main32()
{
    for (int i = 0; i < 80 * 25 * 2; ++i)
        vga_text_buffer[i] = 'X';
    asm volatile ("hlt" ::: "memory");
    return 0;
}
