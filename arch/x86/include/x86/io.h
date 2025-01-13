#pragma once

static inline unsigned char inb(unsigned short port)
{
    unsigned char value;
    asm volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

static inline void outb(unsigned short port, unsigned char value)
{
    asm volatile ("outb %0, %1" :: "a"(value), "Nd"(port));
}

static inline void io_wait()
{
    outb(0x80, 0);
}
