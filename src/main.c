#include <string.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_uart.h"

/*Function prototype for delay and UART2 configuration functions */
void UART2_Configuration(void);
void Delay_ms(volatile int time_ms);

UART_HandleTypeDef UART_Handler; /*Create UART_HandleTypeDef struct instance */
char Message[] = "Write anything on Serial Terminal\r\n"; /* Message to be transmitted through UART */

int main(void)
{
	HAL_Init(); /* HAL library initialization */
	UART2_Configuration(); /* Call UART2 initialization define below */
	HAL_UART_Transmit(&UART_Handler, (uint8_t *)Message, strlen(Message), 10);
	while(1)
	{
		 uint8_t buffer[4];
     HAL_UART_Receive(&UART_Handler, buffer, sizeof(buffer), HAL_MAX_DELAY);
     HAL_UART_Transmit(&UART_Handler, buffer, sizeof(buffer), HAL_MAX_DELAY);
	}
}

void UART2_Configuration(void)
{
	__HAL_RCC_GPIOA_CLK_ENABLE(); /* Enable clock to PORTA - UART2 pins PA2 and PA3 */
	__HAL_RCC_USART2_CLK_ENABLE(); /* Enable clock to UART2 module */
	
	GPIO_InitTypeDef UART2_GPIO_Handler; /*Create GPIO_InitTypeDef struct instance */
	UART2_GPIO_Handler.Pin = GPIO_PIN_2 | GPIO_PIN_3; 
	UART2_GPIO_Handler.Mode = GPIO_MODE_AF_PP;
	UART2_GPIO_Handler.Pull = GPIO_PULLUP;
	UART2_GPIO_Handler.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	UART2_GPIO_Handler.Alternate = GPIO_AF7_USART2;
	HAL_GPIO_Init(GPIOA, &UART2_GPIO_Handler);
	//UART Configuration
	UART_Handler.Instance = USART2;
	UART_Handler.Init.BaudRate = 115200;
	UART_Handler.Init.Mode = UART_MODE_TX_RX;
	UART_Handler.Init.WordLength = UART_WORDLENGTH_8B;
	UART_Handler.Init.StopBits = UART_STOPBITS_1;
	UART_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
	HAL_UART_Init(&UART_Handler);	
}

void SysTick_Handler(void)
{
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
}
/*Generate ms */
void Delay_ms(volatile int time_ms)
{
	      int j;
        for(j = 0; j < time_ms*4000; j++)
            {}  /* excute NOP for 1ms */
}