/*
 * Pwm.cpp
 *
 *  Created on: 15 avr. 2020
 *      Author: PARIS
 */

#include "Pwm.h"
#include "ScpiClientServer.h"
#include <string>
#include <iostream>
#include "tim.h"

Pwm::Pwm() {
	// TODO Auto-generated constructor stub
	rpmValue = 0;

}

Pwm::Pwm(std::string _name) :
		ScpiClientServer(_name), rpmValue(0) {
	// TODO Auto-generated constructor stub
}

Pwm::~Pwm() {
	// TODO Auto-generated destructor stub
}

short int Pwm::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe pwm");

	///////////////
	while(1){;}/*Simulation du client qui bosse*/
	///////////////
	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		this->rpmValue = 0;
		startPwm(0);
		break;
	case REQ_IDN:
		_rep.assign("je suis le client HARDWARE " + this->getHeader());
		break;
	case REQ_x:
		startPwm(this->rpmValue);
		break;
	case REQ_QST:
		_rep.assign("RPM: " + std::to_string(this->rpmValue) + "\n\r");
		break;

	default:
		//throw something;
		break;
	}

	return 0;
}

int Pwm::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*RST") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if (_cmde.compare("RPM ?") == 0) {
		sel = REQ_QST;
	} else if (_cmde.compare(0, 4, "RPM ") == 0) {
		int value = 0;
		value = stoi(_cmde.substr(4), nullptr, 10);
		if ((value < 0) || (value > MAX_FREQ_VALUE)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->rpmValue = value;
			sel = REQ_x;
		}
	} else {
		//throw something;
	}
	return sel;
}
