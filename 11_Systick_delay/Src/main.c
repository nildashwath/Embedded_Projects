#include <stdio.h>
#include<stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"


#define GPIODEN		(1U<<3)
#define GPIOD_13	(1U<<13)

#define ORANGE_LED	(GPIOD_13)

int main (void){

	//Enable the clock access to GPIO
	RCC->AHB1ENR |= GPIODEN;

	//set PD13 as Output pin
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &= ~(1U<<27);

	uart2_tx_init();

	while(1){


		printf("A second passed !!\n \r");
		GPIOD->ODR ^= ORANGE_LED;
		systickDelayMs(1000);
	}
}













