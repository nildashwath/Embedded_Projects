#include "adxl345.h"


#define MULTI_BYTE_EN			0x40
#define READ_OPERATION			0x80


void adxl_read(uint8_t address, uint8_t * rxdata){

	//set read operation
	address |= READ_OPERATION;

	//Enable mutli-byte
	address |= MULTI_BYTE_EN;

	//pull cs line low to enable slave
	cs_enable();

	//send address
	spi1_transmit(&address, 1);

	//read 6 bytes
	spi1_receive(rxdata, 6);

	//pull cs line high to disable the slave
	cs_disable();
}

void adxl_write(uint8_t address, uint8_t value){
	uint8_t data [2];

	//Enable multi-byte, place address into buffer
	data[0] = address | MULTI_BYTE_EN;

	//place data into buffer
	data[1] = value;

	//pull the cs line low to enable slave
	cs_enable();

	//Transmit data and address
	spi1_transmit(data, 2);

	//pull cs line high to disable the slave
	cs_disable();


}




void adxl_init (void){

	//Enable SPI GPIO
	spi_gpio_init();

	//config SPI
	spi1_config();

	//set data format range to +-4g
	adxl_write(DATA_FORMAT_R, FOUR_G);

	//reset all bits
	adxl_write(POWER_CTL_R, RESET);

	//configure the power control measure bit
	adxl_write(POWER_CTL_R, SET_MEASURE_B);
}
