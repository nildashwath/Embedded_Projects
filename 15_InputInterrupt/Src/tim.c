#include "stm32f4xx.h"

#define TIM2EN			(1U<<0)
#define TIM3EN			(1U<<1)
#define CR1_CEN			(1U<<0)
#define OC_TOGGLE		((1U<<4) | (1U<<5))
#define CCER_CC1E		(1U<<0)
#define	GPIOAEN			(1U<<0)
#define AFR5_TIM		(1U<<20)
#define AFR6_TIM		(1U<<25)
#define CCMR1_CC1S		(1U<<0)

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

void tim2_pa5_output_compare(void){
	//Configure the PA5
	RCC->AHB1ENR |= GPIOAEN;

	//PA5 to alternating function mode
	GPIOA->MODER &= ~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	//Set PA5 alternate function type to TIM2_CH1(AF1)
	GPIOA->AFR[0]|= AFR5_TIM;

	//Enable the clock access to timer 2
	RCC->APB1ENR |= TIM2EN;
	//Set prescaler value
	TIM2->PSC = 1600-1; // 16MHz (16000 000 / 1 600 = 10 000)
	//Set auto-reload value
	TIM2->ARR = 10000-1; //10000/10000 = 1.

	//set output compare toggle mode
	TIM2->CCMR1 = OC_TOGGLE;

	//Enable tim2 ch1 in compare mode
	TIM2->CCER |= CCER_CC1E;


	//clear counter
	TIM2->CNT = 0;
	//Enable the timer
	TIM2->CR1 = CR1_CEN;
}

void tim3_pa6_input_capture(void){
	//Enable the clock access GPIOA
	RCC->AHB1ENR |= GPIOAEN;
	//Set the Mode to Alternating function
	GPIOA->MODER &= ~(1U<<12);
	GPIOA->MODER |= (1U<<13);
	//Set the Alternate function type to TIM3_CH1(AF2)
	GPIOA->AFR[0]|= AFR6_TIM;
	//Enable the clock access to timer 3
	RCC->APB1ENR |= TIM3EN;
	//Set prescaler value
	TIM3->PSC = 16000 -1; //16000000/16000
	//set CH1 to Input capture
	TIM3->CCMR1|= CCMR1_CC1S;
	//Set CH1 to capture at rising edge
	TIM3->CCER |= CCER_CC1E;
	//Enable TIM3
	TIM3->CR1 = CR1_CEN;
}
