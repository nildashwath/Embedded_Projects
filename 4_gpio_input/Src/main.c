#include<stm32f4xx.h>





#define  GPIODEN		(1U<<3)
#define  PIN13			(1U<<13)
#define ORANGE_LED		(PIN13)

#define GPIOAEN			(1U<<0)
#define  PIN0			(1U<<0)
#define PUSH_BUTTON		(PIN0)

int main (void){
	//Enable the clock on both port A and D
	RCC->AHB1ENR |= GPIOAEN;
	RCC->AHB1ENR |= GPIODEN;

	//set PD13 as output
	GPIOD->MODER |=(1U<<26);
	GPIOD->MODER &=~(1U<<27);

	//set PA0 as input
	GPIOA->MODER &=~(1U<<0);
	GPIOA->MODER &=~(1U<<1);

	while(1){

		//Check the Button(active Low Button) is pressed
		if(!(GPIOA->IDR & PUSH_BUTTON))

		{
				//Turn on the LED
			GPIOD->BSRR = ORANGE_LED;
		}

		else
		{
			//Turn OFF the LED
			GPIOD->BSRR = (1U<<29);
		}
	}
}
