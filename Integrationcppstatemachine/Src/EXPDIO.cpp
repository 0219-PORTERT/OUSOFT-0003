/*
 * EXPDIO.cpp
 *
 *  Created on: 27 août 2020
 *      Author: PARIS
 */

#include "EXPDIO.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>

EXPDIO::EXPDIO() {
	// TODO Auto-generated constructor stub

}

EXPDIO::EXPDIO(std::string _name, uint8_t _side): ScpiClientServer(_name), side(_side) {
	// TODO Auto-generated constructor stub

}

EXPDIO::~EXPDIO() {
	// TODO Auto-generated destructor stub
}


short int EXPDIO::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	_rep.assign("Je suis le execute de la classe EXPDIO");


	/*switch (decodeInstruct(_cmde)) {

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

	return 0;*/
}

int EXPDIO::decodeInstruct(std::string& _cmde) {

	/*int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("DATA ?") == 0){
		sel = REQ_QST;
	}else {
		//throw something
	}
	return sel;*/
}

uint16_t EXPDIO::readPort(){



}
