#include <stdio.h>
#include<stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIODEN					(1U<<3)

#define PIN13					(1U<<13)
#define ORANGE_LED				(PIN13)

char key;

int main (void){
	//Enable clock access to GPIOD
	RCC->AHB1ENR |= GPIODEN;

	//Direction of GPIOD-13
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &=~(1U<<27);

	uart2_rxtx_init();

	while(1){
		key = uart2_read();
		if(key == '1'){
			GPIOD->ODR |= ORANGE_LED;
		}
		else
			GPIOD->ODR &= ~(ORANGE_LED);
	}
}













