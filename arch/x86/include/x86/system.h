static inline void halt(void)
{
    asm volatile ("hlt" ::: "memory");
}

static inline void enable_interrupts(void)
{
    asm volatile ("sti");
}

static inline void disable_interrupts(void)
{
    asm volatile ("cli");
}
