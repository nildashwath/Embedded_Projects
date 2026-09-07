#include "stm32f4xx.h"

#define  GPIODEN		(1U<<3)
#define  PIN13			(1U<<13)
#define ORANGE_LED		(PIN13)


int main (void){

	RCC->AHB1ENR |= GPIODEN; //Enable clock at port D.
	//set bits as Output
	GPIOD->MODER |=(1U<<26);
	GPIOD->MODER &=~(1U<<27);
	while(1){
		//output data register.
		GPIOD->ODR ^=ORANGE_LED;
		for (int i = 0; i < 100000; i++) {

		}
	}
}
