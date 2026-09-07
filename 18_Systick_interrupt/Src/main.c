#include <stdio.h>
#include<stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"


#define GPIODEN		(1U<<3)
#define GPIOD_13	(1U<<13)

#define ORANGE_LED	(GPIOD_13)

static void systick_callback(void);

int main (void){

	//Enable the clock access to GPIO
	RCC->AHB1ENR |= GPIODEN;

	//set PD13 as Output pin
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &= ~(1U<<27);

	uart2_tx_init();
	systick_1hz_interrupt();

	while(1){


	}
}

static void systick_callback(void){
	printf("A second passed !!\n \r");
	GPIOD->ODR ^= ORANGE_LED;
}

void SysTick_Handler(void){

	//Do something
	systick_callback();
}












