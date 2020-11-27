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

uint16_t OUCART0020::readADC(uint8_t i2cadress, uint8_t channel){

}

uint16_t OUCART0020::setDAC(uint8_t i2cadress, uint8_t channel, uint16_t value){

}

uint8_t OUCART0020::setconfigADCDAC(uint8_t i2cadress, uint8_t channel, uint8_t mode){

}

uint8_t OUCART0020::enableInternalRef(uint8_t i2cadress){

}
uint8_t OUCART0020::disableInternalRef(uint8_t i2cadress){

}
