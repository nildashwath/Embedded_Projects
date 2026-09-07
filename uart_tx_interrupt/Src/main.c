#include <stdio.h>
#include<stdint.h>
#include "stm32f4xx.h"
#include "uart.h"



static void uart_callback(void);

int main (void){

	uart2_tx_interrupt_init();

	while(1){

	}
}

static void uart_callback(void){
	uart2_write('Y');
}
void USART2_IRQHandler(void){
	//Check if TXE is set
	if (USART2->SR & SR_TXE){
		//Do something
		uart_callback();
	}
}










