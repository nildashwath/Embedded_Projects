 //Where is the led connected?
//Port: D
//Pins: 13(Orange), 12(Green), 14(Red), 15(Blue)

#define PERIPH_BASE				(0x40000000UL) //unsinged Long
#define AHB1PERIPH_OFFSET		(0x00020000UL)
#define AHB1PERIPH_BASE			(PERIPH_BASE + AHB1PERIPH_OFFSET)
#define GPIOD_OFFSET			(0x0C00UL)

#define GPIOD_BASE				(AHB1PERIPH_BASE + GPIOD_OFFSET)

#define RCC_OFFSET				(0x3800UL)
#define RCC_BASE				(AHB1PERIPH_BASE + RCC_OFFSET)

#define AHB1ENR_OFFSET			(0x30UL)
#define RCC_AHB1EN_R			(*(volatile unsigned int *)(RCC_BASE + AHB1ENR_OFFSET))

#define MODER_OFFSET			(0x00UL)
#define GPIOD_MODE_R			(*(volatile unsigned int *)(GPIOD_BASE + MODER_OFFSET))

#define ODR_OFFSET				(0x14UL)
#define GPIOD_OD_R				(*(volatile unsigned int *)(GPIOD_BASE + ODR_OFFSET))

#define GPIODEN					(1U<<3)
#define PIN13					(1U<<13)
#define ORANGE_LED				(PIN13)
/*
 *
 * (1U<<26)  //set the 26 bit.
 * &=~(1U<<27) //set the 27 bit to 0.
 *
 * */



int main (void){
	/*1.Enable the clock access to GPIOD.*/
	RCC_AHB1EN_R |= GPIODEN; // '|' is used to set bit number 3 to 1, only '=' will sign new bits

	/*2.Set PD13 as the output pin.*/
	GPIOD_MODE_R |= (1U<<26); //set 26 bit to 1
	GPIOD_MODE_R &= ~(1U<<27); //set 27 bit to 0

	while(1){//Infinite loop
		/*3. PD13 as high*/
		//GPIOD_OD_R |= ORANGE_LED;

		/*4. Experiment */
		GPIOD_OD_R ^= ORANGE_LED;
		for ( int i = 0; i < 100000; i++) {

		}
	}
}
