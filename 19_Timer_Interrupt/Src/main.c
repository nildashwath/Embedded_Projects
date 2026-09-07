#include <stdio.h>
#include<stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"
#include "systick.h"
#include "tim.h"



#define GPIODEN		(1U<<3)
#define GPIOD_13	(1U<<13)

#define ORANGE_LED	(GPIOD_13)

static void tim2_callback(void);

int main (void){

	//Enable the clock access to GPIO
	RCC->AHB1ENR |= GPIODEN;

	//set PD13 as Output pin
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &= ~(1U<<27);

	uart2_tx_init();
	tim2_1hz_interrupt();

	while(1){

	}
}
static void tim2_callback(void){
	printf("A second passed !!\n \r");
	GPIOD->ODR ^= ORANGE_LED;
}

void TIM2_IRQHandler(void){

	//clear update interrupt flag
	TIM2-> SR &= ~(SR_UIF);
	//Do something
	tim2_callback();

}










