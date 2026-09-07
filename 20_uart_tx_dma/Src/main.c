#include <stdio.h>
#include<stdint.h>
#include "stm32f4xx.h"
#include "uart.h"

#define GPIODEN					(1U<<3)

#define PIN13					(1U<<13)
#define ORANGE_LED				(PIN13)

char key;

static void dma_callback(void);

int main (void){

	char message[31] = "Hello from STM32 DMA transfer\n\r";
	//Enable clock access to GPIOD
	RCC->AHB1ENR |= GPIODEN;

	//Direction of GPIOD-13
	GPIOD->MODER |= (1U<<26);
	GPIOD->MODER &=~(1U<<27);

	uart2_tx_init();
	dma1_stream6_init((uint32_t) message, (uint32_t)&USART2->DR, 31);

	while(1){

	}
}

static void dma_callback(void){
	GPIOD->ODR ^= ORANGE_LED;
}

void DMA1_Stream6_IRQHandler(void){
	//check for transfer complete interrupt
	if(DMA1->HISR & TCIF6){
		//clear the flag
		DMA1->HIFCR |= HIFCR_CTCIF6;
		//do something
		dma_callback();
	}
}
