#include <stdio.h>
#include<stdint.h>
#include "stm32f4xx.h"
#include "uart.h"
#include "adc.h"


uint32_t sensor_value;

static void adc_callblack(void);

int main (void){


	uart2_tx_init();
	pa1_adc_interrupt_init();
	start_conversion();

	while(1){


	}
}

static void adc_callblack(void){
	sensor_value = ADC1->DR;
			printf("Sensor value : %d\n\r",(int)sensor_value);
}

void ADC_IRQHandler (void){
	// check for EOC flag is raised
	if((ADC1->SR & ADC_SR_EOC) != 0){

		//Enable EOC
		ADC1->SR &= ~(ADC_SR_EOC);

		//Do something
		adc_callblack();
	}
}











