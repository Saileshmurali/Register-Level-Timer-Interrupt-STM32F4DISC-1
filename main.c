#include "stm32f4xx.h"
void start_timer(void);
void gpio_config(void);
int main(void)
{
	start_timer();
	gpio_config();
	NVIC_EnableIRQ(TIM2_IRQn);//Enable the timer 2 global interrupt
	TIM2->CR1 |= 1UL;//Start the timer
	TIM2->EGR|=1UL;//Reinitialise counter with auto reload value
	while(1)
	{

	}
}
void gpio_config(void)
{
	RCC->AHB1ENR |=(1UL<<3);//Enable clock for port D
	GPIOD->MODER &= ~(0xFFUL<<12*2);
	GPIOD->MODER |= (0x55UL<<12*2);//Set PD12-PD15 as output mode
}
void start_timer(void) {
  RCC->APB1ENR |= (1UL <<0);  	//Enable TIM2 clock
	TIM2->DIER|=(0x0041UL);//Enable the interrupt
	TIM2->CR1 |= (0x0084UL);    		//Set the mode to Count up
	TIM2->PSC = 16000-1;					//Set the Pre-scalar
	TIM2->ARR = 1000; 						//Set period (Auto reload) to 1000
	TIM2->SR &= ~(0x0001UL);				//Clear Update interrupt flag
}
void TIM2_IRQHandler(void) {
  // Handle a timer 'update' interrupt event
	GPIOD->ODR ^= (0xFUL<<12);
	TIM2->SR &= ~(0x0001UL);
  }
