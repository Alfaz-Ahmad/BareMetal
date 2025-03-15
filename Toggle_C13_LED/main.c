#include <stdint.h>


int main(void)
{
	uint32_t *clkreg =  (uint32_t*) 0x40021018;
	uint32_t *modereg =  (uint32_t*) 0x40011004;
	uint32_t *outreg =  (uint32_t*)  0x4001100C;
	//Enable the clock for GPIOC peripheral in the APB2 bus
	*clkreg |= 0x00000010;
	 //Clear the Bit
	*modereg &= 0xff0fffff;
	//•	Set as Output
	*modereg |= 0x00200000;
	//Make 13th bit as High to turn on LED
    uint32_t i;
    while(1){
        for (i = 0; i <= 100000;i++){
            *outreg |= 0x00002000;
        }
        for (i = 0; i <= 100000;i++){
            *outreg &= ~0x00002000;
        }
    }
}