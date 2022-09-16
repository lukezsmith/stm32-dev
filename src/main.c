#include "stm32f4xx.h"
#include "simple_module.h"
#include "stm32f4xx_hal_gpio.h"

// LED delay duration
#define LEDDELAY    200000

int main(){
	
	GPIO_InitTypeDef GPIOD_Params; // Initilisation structure for GPIOD Settings
	
	__HAL_RCC_GPIOD_CLK_ENABLE(); // Turn on Clock of GPIOD
	
	// Configure the GPIO Pins 12, 13, 14 and 15 used for LEDs
	GPIOD_Params.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15; // Select pins 12 to 15
	GPIOD_Params.Mode = GPIO_MODE_OUTPUT_PP; // Set pins to push pull output mode
	GPIOD_Params.Speed = GPIO_SPEED_LOW; // Set low output speed
	HAL_GPIO_Init(GPIOD, &GPIOD_Params); // Initialise GPIOD according to parameters on GPIOD_Params
	
	while(1){
		delay(LEDDELAY); // Delay
		HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15); // Toggle LEDs
	}
}