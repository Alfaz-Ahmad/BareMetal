#include <stdint.h>
#include <stdio.h>

int main(){
    //Clock Register RCC to enable the AHB bus.
    uint32_t *RCC_BASE = (uint32_t*)  0x40021000;
    uint32_t RCC_APB2ENR_OFFSET = 0x18;
    uint32_t *clkreg = (uint32_t*) ((uint32_t)RCC_BASE + RCC_APB2ENR_OFFSET);


    //Enable the RCC clock.
    *clkreg |= (1 << 2) | (1 << 4);
    //GPIOPA -> 0X00000004
    //GPIOPC -> 0X00000010

    //Enable the GPIO pins
    uint32_t *GPIOPA_BASE = (uint32_t *)0x40010800;
    uint32_t GPIOPA_CRL = 0x00;
    uint32_t *GPIOPC_BASE = (uint32_t *)0x40011000;
    uint32_t GPIOPC_CRH = 0x04;
    uint32_t *GPIOPA_MODEREG = (uint32_t *)((uint32_t)GPIOPA_BASE + GPIOPA_CRL);
    uint32_t *GPIOPC_MODEREG = (uint32_t *)((uint32_t)GPIOPC_BASE + GPIOPC_CRH);

    //Seting Output

    //GPIOPA
    //Clear Bit
    *GPIOPA_MODEREG &= 0xff0fffff;
    //Set Bit
    *GPIOPA_MODEREG |= 0x00200000;

    //GPIOPC
    //Clear Bit
    *GPIOPC_MODEREG &= 0xff0fffff;
    //Set Bit
    *GPIOPC_MODEREG |= 0x00200000;

    //Oupput Register GPIOP
    uint32_t GPIOPx_ODR_OFFSET = 0x0C;
    uint32_t *GPIOPA_ODR = (uint32_t *)((uint32_t)GPIOPA_BASE + GPIOPx_ODR_OFFSET);
    uint32_t *GPIOPC_ODR = (uint32_t *)((uint32_t)GPIOPC_BASE + GPIOPx_ODR_OFFSET);

    uint32_t i;
    while(1){
        *GPIOPA_ODR |= 0x00000020;
        *GPIOPC_ODR &= ~0x00002000;
        for (i = 0; i <= 200000;i++);   //DELAY

        
        *GPIOPA_ODR &= ~0x00000020;
        *GPIOPC_ODR |= 0x00002000;
        for (i = 0; i <= 200000;i++);   //DELAY

    }

}
