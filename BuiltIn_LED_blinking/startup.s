.section .text
.global _start

_start:
    /* Load stack pointer (sp) from a memory location */
    ldr r0, =__stack_top
    mov sp, r0

    /* Call main function */
    bl main

    /* Infinite loop to prevent unexpected execution */
    b .
