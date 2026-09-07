//Where is the led connected?
//Port: D
//Pins: 13(Orange), 12(Green), 14(Red), 15(Blue)
#include <stdint.h>

#define PERIPH_BASE				(0x40000000UL) //unsinged Long
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOD_OFFSET			(0x0C00UL)

#define GPIOD_BASE				(AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)


#define GPIODEN					(1U<<3)

#define PIN13					(1U<<13)
#define ORANGE_LED				(PIN13)
/*
 *
 * (1U<<26)  //set the 26 bit.
 * &=~(1U<<27) //set the 27 bit to 0.
 *
 * */

#define __IO volatile

typedef struct{
	volatile uint32_t	  DUMMY[12];
	volatile uint32_t AHB1ENR;
}RCC_TypeDef;


typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
}GPIO_TypeDef;

#define RCC 	((RCC_TypeDef*)RCC_BASE)
#define GPIOD 	((GPIO_TypeDef*)GPIOD_BASE)


int main (void){
	/*1.Enable the clock access to GPIOD.*/
		RCC->AHB1ENR |= GPIODEN;
	/*2.Set PD13 as the output pin.*/
		GPIOD->MODER |= (1U<<26);
		GPIOD->MODER &= ~(1U<<27);

	while(1){//Infinite loop

		GPIOD->ODR ^= ORANGE_LED;
		for ( int i = 0; i < 100000; i++) {

		}
	}
}
