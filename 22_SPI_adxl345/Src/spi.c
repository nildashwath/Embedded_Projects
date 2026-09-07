#include "stm32f4xx.h"


#define SPI1ENR			(1U<<12)
#define GPIOAEN			(1U<<0)

#define	CR1_CPHA		(1U<<0)
#define CR1_CPOL		(1U<<1)
#define	CR1_RXONLY		(1U<<10)
#define	CR1_LSBFIRST	(1U<<7)
#define	CR1_MSTR		(1U<<2)
#define CR1_DFF			(1U<<11)
#define CR1_SSI			(1U<<8)
#define CR1_SSM			(1U<<9)
#define	CR1_SPE			(1U<<6)
#define SR_TXE			(1U<<1)
#define	SR_BSY			(1U<<7)
#define	SR_RXNE			(1U<<0)
//PA5 -> CLK
//PA6 -> MISO
//PA7 -> MOSI
//PA9 -> SS

void spi_gpio_init(void){
	//Enable the clock to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	//Set the PA5 as AF
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |= (1U<<11);

	//Set the PA6 as AF
	GPIOA->MODER &=~(1U<<12);
	GPIOA->MODER |= (1U<<13);

	//Set the PA7 as AF
	GPIOA->MODER &=~(1U<<14);
	GPIOA->MODER |= (1U<<15);

	//Set the PA9 as AF
	GPIOA->MODER |= (1U<<18);
	GPIOA->MODER &=~(1U<<19);

	//set PA5, PA6, PA7 to alternating function
	GPIOA->AFR[0] |= (1U<<20);
	GPIOA->AFR[0] &=~(1U<<21);
	GPIOA->AFR[0] |= (1U<<22);
	GPIOA->AFR[0] &=~(1U<<23);

	GPIOA->AFR[0] |= (1U<<24);
	GPIOA->AFR[0] &=~(1U<<25);
	GPIOA->AFR[0] |= (1U<<26);
	GPIOA->AFR[0] &=~(1U<<27);

	GPIOA->AFR[0] |= (1U<<28);
	GPIOA->AFR[0] &=~(1U<<29);
	GPIOA->AFR[0] |= (1U<<30);
	GPIOA->AFR[0] &=~(1U<<31);
}

void spi1_config(void){
	//Enable the clock to SPI
	RCC->APB2ENR |= SPI1ENR;

	//Set the Baud rate to fpclk/4
	SPI1->CR1 |= (1U<<3);
	SPI1->CR1 &=~(1U<<4);
	SPI1->CR1 &=~(1U<<5);

	//configure the CPOL and CPHA
	SPI1->CR1 |= CR1_CPHA;
	SPI1->CR1 |= CR1_CPOL;

	//configure it to Full duplex mode
	SPI1->CR1 &= ~(CR1_RXONLY);

	//set MSB to be 1st
	SPI1->CR1 &= ~(CR1_LSBFIRST);

	//set mode to master
	SPI1->CR1 |= CR1_MSTR;

	//set the data size
	SPI1->CR1 &= ~(CR1_DFF);

	//SPI work in software slave management
	SPI1->CR1 |= CR1_SSI;
	SPI1->CR1 |= CR1_SSM;

	//Enable SPI module
	SPI1->CR1 |= CR1_SPE;

}
void spi1_transmit(uint8_t *data, uint32_t size){

	uint32_t i = 0;
	uint8_t temp;

	while(i < size){
		//wait until the TXE is set
		while (!(SPI1->SR & (SR_TXE))){}

		//write the data to data register
		SPI1->DR = data[i];
		i++;
	}
	//wait till TXE is set
	while (!(SPI1->SR & (SR_TXE))){}


	//wait for busy flag to be reset
	while((SPI1->SR & (SR_BSY))){}


	//Clear overrun flag
	temp = SPI1->DR;
	temp = SPI1->SR;

}

void spi1_receive(uint8_t *data, uint32_t size){

	while(size){
		//send dummy data
		SPI1->DR = 0;

		//wait for RXNE is set
		while(!(SPI1->SR & (SR_RXNE))){}

		//Read the data from the data register
		*data++ = SPI1->DR;
		size--;

	}
}

void cs_enable(void){
	//set PA9 to low for enable
	GPIOA->ODR &= ~ (1U<<9);
}

void cs_disable(void){
	//set PA9 to high for disable
	GPIOA->ODR |= (1U<<9);
}





