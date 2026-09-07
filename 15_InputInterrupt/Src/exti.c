#include "exti.h"

#define GPIOAEN			(1U<<0)
#define SYSCFGEN		(1U<<14)

void pa0_exti_init(void){
	//Disable  global interrupt
	__disable_irq();

	//Enable the GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//Set GPIOA as input
	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER &=~(1U<<1);
	//Enable the SYSCFG
	RCC->APB1ENR|=SYSCFGEN;

	//select PORTA for EXTI0
	SYSCFG->EXTICR[0] &= ~(1U<<0);
	SYSCFG->EXTICR[0] &= ~(1U<<1);
	SYSCFG->EXTICR[0] &= ~(1U<<2);
	SYSCFG->EXTICR[0] &= ~(1U<<3);
	//unmasked EXTI0
	EXTI->IMR |= (1U<<0);
	//select falling edge trigger
	EXTI->FTSR |= (1U<<0);
	//Enable the EXTI0 line in NVIC
	NVIC_EnableIRQ(EXTI0_IRQn);
	//Enable  global interrupt
	__enable_irq();

}
