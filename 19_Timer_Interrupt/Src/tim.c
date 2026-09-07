#include "stm32f4xx.h"

#define TIM2EN			(1U<<0)
#define CR1_CEN			(1U<<0)
#define DIER_UIE		(1U<<0)

void tim2_1hz_init(void){
	//Enable the clock access to timer 2
	RCC->APB1ENR |= TIM2EN;
	//Set prescaler value
	TIM2->PSC = 1600-1; // 16MHz (16000 000 / 1 600 = 10 000)
	//Set auto-reload value
	TIM2->ARR = 10000-1; //10000/10000 = 1.
	//clear counter
	TIM2->CNT = 0;
	//Enable the timer
	TIM2->CR1 = CR1_CEN;
}


void tim2_1hz_interrupt(void){
	//Enable the clock access to timer 2
	RCC->APB1ENR |= TIM2EN;
	//Set prescaler value
	TIM2->PSC = 1600-1; // 16MHz (16000 000 / 1 600 = 10 000)
	//Set auto-reload value
	TIM2->ARR = 10000-1; //10000/10000 = 1.
	//clear counter
	TIM2->CNT = 0;
	//Enable the timer
	TIM2->CR1 = CR1_CEN;
	//Enable the timer interrupt
	TIM2->DIER |= DIER_UIE;
	//Enable the timer in NVIC
	NVIC_EnableIRQ(TIM2_IRQn);

}
