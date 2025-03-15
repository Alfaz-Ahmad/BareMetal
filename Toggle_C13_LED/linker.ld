/* Define memory regions */
MEMORY
{
    FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 64K
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Stack pointer */
__stack_top = ORIGIN(RAM) + LENGTH(RAM);

SECTIONS
{
    /* Vector Table */
    .isr_vector :
    {
        . = ALIGN(4);
        LONG(__stack_top);  /* Initial Stack Pointer */
        LONG(_start | 1);   /* Reset Handler */
        . = 0x000000D4;      /* Align to 0xD4 (332 bytes for vectors) */
    } > FLASH

    /* Code and Read-Only Data */
    .text :
    {
        . = ALIGN(4);
        *(.text*)     /* All .text sections */
        *(.rodata*)   /* Read-only data */
        . = ALIGN(4);
    } > FLASH

    /* Read-Write Data (in RAM) */
    .data :
    {
        . = ALIGN(4);
        *(.data*)     /* Initialized global/static variables */
        . = ALIGN(4);
    } > RAM AT > FLASH

    /* Uninitialized Data (in RAM) */
    .bss :
    {
        . = ALIGN(4);
        *(.bss*)      /* Uninitialized global/static variables */
        *(COMMON)
        . = ALIGN(4);
    } > RAM
}
