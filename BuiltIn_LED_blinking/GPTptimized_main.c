#include <stdint.h>

int main(){
    // Base Address Definitions
    uint32_t RCC_BASE = 0x40021000;
    uint32_t GPIOA_BASE = 0x40010800;
    uint32_t GPIOC_BASE = 0x40011000;

    // Register Offsets
    uint32_t RCC_APB2ENR_OFFSET = 0x18;
    uint32_t GPIO_CRL_OFFSET = 0x00;
    uint32_t GPIO_CRH_OFFSET = 0x04;
    uint32_t GPIO_ODR_OFFSET = 0x0C;

    // Create Register Pointers
    uint32_t *RCC_APB2ENR = (uint32_t *)(RCC_BASE + RCC_APB2ENR_OFFSET);
    uint32_t *GPIOA_CRL = (uint32_t *)(GPIOA_BASE + GPIO_CRL_OFFSET);
    uint32_t *GPIOC_CRH = (uint32_t *)(GPIOC_BASE + GPIO_CRH_OFFSET);
    uint32_t *GPIOA_ODR = (uint32_t *)(GPIOA_BASE + GPIO_ODR_OFFSET);
    uint32_t *GPIOC_ODR = (uint32_t *)(GPIOC_BASE + GPIO_ODR_OFFSET);

    // Enable Clocks for GPIOA and GPIOC
    *RCC_APB2ENR |= (1 << 2) | (1 << 4);  // GPIOA (Bit 2) and GPIOC (Bit 4)

    // Configure PA5 as Output (Push-Pull, 2MHz)
    *GPIOA_CRL &= ~(0xF << 20);  // Clear bits for PA5
    *GPIOA_CRL |= (0x2 << 20);   // MODE5 = 10 (Output 2MHz), CNF5 = 00 (Push-Pull)

    // Configure PC13 as Output (Push-Pull, 2MHz)
    *GPIOC_CRH &= ~(0xF << 20);  // Clear bits for PC13
    *GPIOC_CRH |= (0x2 << 20);   // MODE13 = 10 (Output 2MHz), CNF13 = 00 (Push-Pull)

    // Blink PA5 and PC13
    while (1)
    {
        *GPIOA_ODR |= (1 << 5);  // Set PA5 HIGH
        *GPIOC_ODR |= (1 << 13); // Set PC13 HIGH
        for (volatile int i = 0; i < 100000; i++); // Delay

        *GPIOA_ODR &= ~(1 << 5);  // Set PA5 LOW
        *GPIOC_ODR &= ~(1 << 13); // Set PC13 LOW
        for (volatile int i = 0; i < 100000; i++); // Delay
    }

    return 0;
}