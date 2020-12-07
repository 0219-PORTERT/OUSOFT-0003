/*
 * OUCART0020.cpp
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#include "OUCART0020.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"

OUCART0020::OUCART0020() {
	// TODO Auto-generated constructor stub

}

OUCART0020::~OUCART0020() {
	// TODO Auto-generated destructor stub
}

void OUCART0020::setI2cAdress(uint8_t adr){
	this->i2cadress = adr;
}

uint16_t OUCART0020::readADC( uint8_t channel){

	uint16_t value = 0;
	uint8_t dataadc[2];
	uint8_t data[3];


	data[0] = 0x04;
	data[1] = 0x00;
	data[2] = 0 | (1u<<channel);

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));

	TM_I2C_ReadMulti(I2C1, this->i2cadress, 0x40 , dataadc, sizeof(dataadc));

	value = dataadc[1] << 8;
	value = value |  dataadc[0];
	return value;
}

uint16_t OUCART0020::setDAC(uint8_t channel, uint16_t value){
	uint8_t data[3];

	data[0] = (0x10 | channel) ;


	data[1] = 0x00;
	//data[2] = pins;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));

}

uint8_t OUCART0020::setconfigADC(uint8_t pins){

	uint8_t data[3];

	data[0] = 0x04;
	data[1] = 0x00;
	data[2] = pins;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));
}

uint8_t OUCART0020::setconfigDAC( uint8_t pins){

	uint8_t data[3];

	data[0] = 0x05;
	data[1] = 0x00;
	data[2] = pins;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));
}

uint8_t OUCART0020::enableInternalRef(){

	uint8_t data[3];

	data[0] = 0x0b;
	data[1] = 0x02;
	data[2] = 0x00;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));
}
uint8_t OUCART0020::disableInternalRef(){
	uint8_t data[3];

	data[0] = 0x0b;
	data[1] = 0x00;
	data[2] = 0x00;

	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));
}
