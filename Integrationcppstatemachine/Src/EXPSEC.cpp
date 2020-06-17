/*
 * EXPSEC.cpp
 *
 *  Created on: 3 juin 2020
 *      Author: PARIS
 */

#include "EXPSEC.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>

EXPSEC::EXPSEC() {
	// TODO Auto-generated constructor stub

}
EXPSEC::EXPSEC(std::string _name): ScpiClientServer(_name) {
	// TODO Auto-generated constructor stub

}
EXPSEC::~EXPSEC() {
	// TODO Auto-generated destructor stub
}

short int EXPSEC::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe EXPSECu");


	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//reset
		break;
	case REQ_IDN:
		//_rep.assign("je suis le client HARDWARE " + this->getHeader());
		_rep.assign(this->getHeader());
		break;
	case REQ_QST:
		//_rep.assign(this->getHeader()+ " : "+ std::to_string(readPort()) + "\n\r");
		_rep.assign(std::to_string(readPort()) + "\n\r");
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int EXPSEC::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*RST") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("DATA ?") == 0){
		sel = REQ_QST;
	}else {
		//throw something
	}
	return sel;
}

uint16_t EXPSEC::readPort(){
	uint8_t data = 0;
	uint16_t value = 0;

	uint16_t value2 = 0x0000;

	TM_I2C_WriteNoRegister(I2C4, EXPSECU_I2CADD, 0x00); //write input port 0
	TM_I2C_ReadNoRegister(I2C4, (EXPSECU_I2CADD)|(1u<<0), &data); //read from input port 0

	value = data;
	value2 = data;

	TM_I2C_WriteNoRegister(I2C4, EXPSECU_I2CADD, 0x01); //write input port 1
	TM_I2C_ReadNoRegister(I2C4, (EXPSECU_I2CADD)|(1u<<0), &data); //read from input port 1

	value = value + data;
	value2 = value2 + (data<<8);

	TM_I2C_IsDeviceConnected(I2C4, EXPSECU_I2CADD);

	return value2;
}

int EXPSEC::configseq(){


	return 0;
}
