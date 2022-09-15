#include <simple_module.h>

uint8_t add(uint8_t a, uint8_t b);

uint8_t SomethingSimple(uint8_t a, uint8_t b) {
    return a+b + add(1, 2);
}

uint8_t AnotherSimpleThing() {
    return 2;
}

// delay function
void delay(volatile uint32_t s)
{
    for(; s>0; s--);
}