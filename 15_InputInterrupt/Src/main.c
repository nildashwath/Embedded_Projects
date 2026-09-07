#include <stdio.h>
#include<stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"
#include "exti.h"

#define GPIODEN		(1U<<3)
#define GPIOD_13	(1U<<13)

#define ORANGE_LED	(GPIOD_13)

static void exti_callback(void);

int main (void){

	//Enable the clock access to GPIO
	RCC->AHB1ENR |= GPIODEN;

	//set PD13 as Output pin
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &= ~(1U<<27);

	pa0_exti_init();
	uart2_tx_init();

	while(1){

	}
}

static void exti_callback(void){
	printf("Button Pressed...\n\r");
}

void EXTI0_IRQHandler(void){
	if((EXTI->PR & LINE0) != 0){
	//Clear PR Flag
	EXTI->PR |= LINE0;

	exti_callback();
	}
}










