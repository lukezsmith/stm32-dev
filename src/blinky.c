#include "stm32f407xx.h"

// LED delay duration
#define LEDDELAY    1000000

int main(void);
void delay(volatile uint32_t);

int main(void)
{
    // Enable GPIOD clock (AHB1ENR: bit 3)
    RCC->AHB1ENR |= (1U << 3);

    // reset bits 25 and 24 (pin 12)
    GPIOD->MODER &= ~(1U << 24);
    // set 25 and 24 bits
    GPIOD->MODER |=  (1U << 24);
    // Set pin 12 to turn on LED
    GPIOD->ODR |= (1U << 12);

    while(1)
    {
        delay(LEDDELAY);
        
        // Toggle LED
        GPIOD->ODR ^= (1U << 12);  
    }
    __asm("NOP");
    return 0;
}

// delay function
void delay(volatile uint32_t s)
{
    for(; s>0; s--);
}
