#include<stm32f4xx.h>

#define  GPIODEN		(1U<<3)
#define  PIN13			(1U<<13)
#define ORANGE_LED		(PIN13)


int main (void){


	RCC->AHB1ENR |= GPIODEN;

	GPIOD->MODER |=(1U<<26);
	GPIOD->MODER &=~(1U<<27);
	while(1){
		GPIOD->BSRR = ORANGE_LED;
		for (int i = 0; i < 100000; i++) {}
		GPIOD->BSRR = (1U<<29);
		for (int i = 0; i < 100000; i++) {}
	}
}
