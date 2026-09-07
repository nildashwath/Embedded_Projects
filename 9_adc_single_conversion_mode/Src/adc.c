
#include "stm32f4xx.h"
#include "adc.h"

#define GPIOAEN				(1U<<0)
#define ADC1EN				(1U<<8)
#define ADC_CH1				(1U<<0)
#define ADC_SEQ_LEN_1		(0x00)
#define ADC_CR2_ADON		(1U<<0)
#define ADC_CR2_SWSTART		(1U<<30)
#define ADC_SR_EOC			(1U<<1)


void pa1_adc_init(void){
	/******************configure the ADC GPIO pin******************/

	/*Enable clock access to GPIOA */
	RCC->AHB1ENR |= GPIOAEN;
	//set the mode of PA1
	GPIOA->MODER |= (1U<<2);
	GPIOA->MODER |= (1U<<3);

	/******************configure the ADC module******************/

	//Enable clock access to ADC
	RCC->APB2ENR |= ADC1EN;

	/******************Configure adc parameters******************/

	//Conversion sequence start
	ADC1->SQR3 = ADC_CH1;
	//Conversion sequence length
	ADC1->SQR1 = ADC_SEQ_LEN_1;
	//Enable the ADC module
	ADC1->CR2 |= ADC_CR2_ADON;

}


void start_conversion(void){

	//start conversions
	ADC1->CR2 |=  ADC_CR2_SWSTART;
}

uint32_t adc_read(void){
//wait for the conversion to be complete.
while (!(ADC1->SR & ADC_SR_EOC)){

}
//Read the converted result.
return (ADC1->DR);
}
