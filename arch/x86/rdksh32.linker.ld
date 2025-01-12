ENTRY(_start)

SECTIONS
{
    . = 1M;

    .multiboot2 :
    {
        KEEP(*(.multiboot2))
    }

    .text :
    {
        . = ALIGN(4K);
        *(.text)
    }

    .rodata :
    {
        . = ALIGN(4K);
        *(.rodata)
    }

    .data :
    {
        . = ALIGN(4K);
        *(.data)
    }

    .bss :
    {
        . = ALIGN(4K);
        *(.bss)
        *(COMMON)
    }

    .stack (NOLOAD): {
        . = ALIGN(4K);
        *(.stack)
        main_stack_top = .;
    }

	/* /DISCARD/ : */
	/* { */
	/* 	*(.note.gnu.property) */
	/* 	*(.comment) */
	/* 	*(.eh_frame) */
	/* } */
}
