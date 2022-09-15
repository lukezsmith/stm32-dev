#include <stdint.h>

void delay(volatile uint32_t s);

/**
 * @brief   Add two 8 bit integers and add 3 to it
 *
 * @param a first uint8_t
 * @param b second uint8_t
 *
 * @retval  a+b
 */
uint8_t SomethingSimple(uint8_t a, uint8_t b);

/**
 * @brief   Return the value 2
 *
 * @retval  2 constant value 2
 */
uint8_t AnotherSimpleThing(void);