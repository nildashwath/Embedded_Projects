#include "stm32f4xx.h"

#define GPIOBEN				(1U<<1)
#define I2C1EN				(1U<<21)
#define OT8					(1U<<8)
#define OT9					(1U<<9)

#define	I2C_100KHZ				80 //0b 0101 0000 = Decimal = 80
#define	SD_MODE_MAX_RISE_TIME	17
#define CR1_PE				(1U<<0)

#define SR2_BUSY			(1U<<1)
#define CR1_START			(1U<<8)
#define	SR1_SB				(1U<<0)
#define	SR1_ADDR			(1U<<1)
#define	SR1_TxE				(1U<<7)
#define	CR1_ACK				(1U<<10)
#define CR1_STOP			(1U<<9)
#define	SR1_RxNE			(1U<<6)
#define SR1_BTF				(1U<<2)

//Pinout
//PB8 ---->SCL
//PB9 ---->SDA

void I2C1_inti(void){
	//Enable the clock access to GPIOB
	RCC->AHB1ENR|=GPIOBEN;
	//set PB8 and PB9 to alternate function
	GPIOB->MODER &= ~(1U<<16);
	GPIOB->MODER |= (1U<<17);

	GPIOB->MODER &=~(1U<<18);
	GPIOB->MODER |= (1U<<19);

	//set PB8 and PB9 to output type to open drain
	GPIOB->OTYPER|= OT8;
	GPIOB->OTYPER|= OT9;

	//Enable Pullup for PB8 and PB9
	GPIOB->PUPDR |= (1U<<16);
	GPIOB->PUPDR &= ~(1U<<17);

	GPIOB->PUPDR |= (1U<<18);
	GPIOB->PUPDR &= ~(1U<<19);

	//Set PB8 and PB9 alternate function type to I2C(AF4)
	GPIOB->AFR[1] &=~(1U<<0);
	GPIOB->AFR[1] &=~(1U<<1);
	GPIOB->AFR[1] |= (1U<<2);
	GPIOB->AFR[1] &= (1U<<3);

	GPIOB->AFR[1] &=~(1U<<4);
	GPIOB->AFR[1] &=~(1U<<5);
	GPIOB->AFR[1] |= (1U<<6);
	GPIOB->AFR[1] &=~(1U<<7);
	//Enable the clock access to I2C1
	RCC->APB1ENR |= I2C1EN;

	//Enter reset mode
	I2C1->CR1 |= (1U<<15);

	//Enter out of reset mode
	I2C1->CR1 &= ~(1U<<15);

	//Set Peripheral Clock Frequency
	I2C1->CR2 = (1U<<4); //16 Mhz

	//Set I2C to Standard mode, 100KHZ Clock
	I2C1->CCR = I2C_100KHZ;

	//Set Rise Time
	I2C1->TRISE = SD_MODE_MAX_RISE_TIME;

	//Enable I2C1 module
	I2C1->CR1 |= CR1_PE;

}

void I2C1_byteRead(char saddr, char maddr, char* data){

	volatile int temp;

	//wait until bus not busy
	while (I2C1->SR2 & (SR2_BUSY)){}

	//Generate start
	I2C1->CR1 |= CR1_START;

	//Wait for Start flag is set
	while(!(I2C1->SR1 & (SR1_SB))){}

	//Transmit slave address + write
	I2C1->DR = saddr << 1;

	//wait until addr flag is set
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	//Clear address Flag
	temp = I2C1->SR2;

	//Send memory address
	I2C1->DR = maddr;

	//wait until transmitter empty
	while(!(I2C1->SR1 & SR1_TxE)){}

	//Generate restart
	I2C1->CR1 |= CR1_START;

	//Wait for Start flag is set
	while(!(I2C1->SR1 & (SR1_SB))){}

	//Transmit slave address + Read
	I2C1->DR = saddr << 1 | 1;

	//wait until addr flag is set
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	//Diable the acknowledge
	I2C1->CR1 &= ~CR1_ACK;

	//Clear addr flag
	temp = I2C1->SR2;

	//Generate Stop
	I2C1->CR1 |= CR1_STOP;

	//wait until Receiver empty
	while(!(I2C1->SR1 & SR1_RxNE)){}

	//Read the data from DR
	*data++ = I2C1->DR;

}

void I2C1_burstRead(char saddr, char maddr, int n, char* data){

	volatile int temp;

	//wait until bus not busy
	while (I2C1->SR2 & (SR2_BUSY)){}

	//Generate start
	I2C1->CR1 |= CR1_START;

	//Wait for Start flag is set
	while(!(I2C1->SR1 & (SR1_SB))){}

	//Transmit slave address + write
	I2C1->DR = saddr << 1;

	//wait until addr flag is set
	while(!(I2C1->SR1 & (SR1_ADDR))){}

	//Clear address Flag
	temp = I2C1->SR2;

	//wait until transmitter empty
	while(!(I2C1->SR1 & SR1_TxE)){}

	//Send memory address
	I2C1->DR = maddr;

	//wait until transmitter empty
	while(!(I2C1->SR1 & SR1_TxE)){}

	//Generate restart
	I2C1->CR1 |= CR1_START;

	//Wait for Start flag is set
	while(!(I2C1->SR1 & (SR1_SB))){}

	//Transmit slave address + Read
	I2C1->DR = saddr << 1 | 1;

	//Clear addr flag
	temp = I2C1->SR2;

	//Enable the acknowledge
	I2C1->CR1 |= CR1_ACK;

	while(n > 0U){
		//if one byte is left
		if(n == 1U){
			//Diable the acknowledge
			I2C1->CR1 &= ~CR1_ACK;

			//Generate Stop
			I2C1->CR1 |= CR1_STOP;

			//wait until Receiver empty
			while(!(I2C1->SR1 & SR1_RxNE)){}

			//Read the data from DR
			*data++ = I2C1->DR;

			break;
		}
		else{
			//wait until Receiver empty
			while(!(I2C1->SR1 & SR1_RxNE)){}

			//Read the data from DR
			(*data++) = I2C1->DR;

			n--;
		}

	}
}

void I2C1_burstWrite(char saddr, char maddr, int n, char* data){

		volatile int temp;

		//wait until bus not busy
		while (I2C1->SR2 & (SR2_BUSY)){}

		//Generate start
		I2C1->CR1 |= CR1_START;

		//Wait for Start flag is set
		while(!(I2C1->SR1 & (SR1_SB))){}

		//Transmit slave address + write
		I2C1->DR = saddr << 1;

		//wait until addr flag is set
		while(!(I2C1->SR1 & (SR1_ADDR))){}

		//Clear address Flag
		temp = I2C1->SR2;

		//wait until transmitter empty
		while(!(I2C1->SR1 & SR1_TxE)){}

		//Send memory address
		I2C1->DR = maddr;

		for (int i = 0; i < n; ++i) {

			//wait until data register is empty
			while (!(I2C1->SR1 & (SR1_TxE))){}

			//Transmit memory address
			I2C1->DR = *data++;
		}

		//wait until transfer finished
		while(!(I2C1->SR1 & (SR1_BTF))){}

		//Generate Stop
		I2C1->CR1 |= CR1_STOP;
}








