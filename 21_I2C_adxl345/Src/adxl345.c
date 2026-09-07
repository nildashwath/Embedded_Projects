#include "adxl345.h"




char data;

uint8_t data_rec[6];

void adxl_read_address(uint8_t reg){

	I2C1_byteRead(DEVICE_ADDR, reg, &data);

}

void adxl_write(uint8_t reg, char value){

	//local buffer called as data
	char data[1];
	data[0] = value;

	I2C1_burstRead(DEVICE_ADDR, reg, 1,data);
}

//This function is used to read data register of ADXL345
void adxl_read_values(uint8_t reg){

	I2C1_burstRead(DEVICE_ADDR, reg, 6,(char *)data_rec);
}

void adxl_init (void){

	//Enable I2C module
	I2C1_inti();
	//read Device ID, this should return 0xE5
	adxl_read_address(DEVID_R);

	//set data format range to +-4g
	adxl_write(DATA_FORMAT_R, FOUR_G);

	//reset all bits
	adxl_write(POWER_CTL_R, RESET);

	//configure the power control measure bit
	adxl_write(POWER_CTL_R, SET_MEASURE_B);
}
