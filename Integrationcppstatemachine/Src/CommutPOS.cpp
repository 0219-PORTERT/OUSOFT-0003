/*
 * CommutPOS.cpp
 *
 *  Created on: 11 juin 2020
 *      Author: PARIS
 */

#include "CommutPOS.h"
#include <String>
#include <iostream>

CommutPOS::CommutPOS() {
	// TODO Auto-generated constructor stub

}

CommutPOS::CommutPOS(std::string _name) : ScpiClientServer(_name) {
	// TODO Auto-generated constructor stub

}

CommutPOS::~CommutPOS() {
	// TODO Auto-generated destructor stub
}

short int CommutPOS::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe commut pos");


	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//reset
		break;
	case REQ_IDN:
		_rep.assign("je suis le client HARDWARE " + this->getHeader());
		break;
	case REQ_QST:
		//_rep.assign(this->getHeader()+ " : "+ std::to_string(readPort()) + "\n\r");
		break;
	case REQ_x:
		//_rep.assign(this->getHeader()+ " : "+ std::to_string(readPort()) + "\n\r");
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int CommutPOS::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*RST") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("POS ?") == 0){
		sel = REQ_QST;
	}else if(_cmde.compare("POS ") == 0){
		sel = REQ_x;
	}else {
		//throw something
	}
	return sel;
}

uint16_t CommutPOS::getStateRelay(){
	return this->relaystate;
}


uint16_t CommutPOS::Commut1Relay(uint16_t relay){

	uint8_t portC;
	uint16_t portAB;





}

