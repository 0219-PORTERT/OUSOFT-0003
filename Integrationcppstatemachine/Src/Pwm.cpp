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
	_rep.assign("Je suis le execute de la classe pwm");
	//testPWM();

	if (_cmde.compare("*RST") == 0) {
		this->rpmValue = 0;
		startPwm(0);
	}/*else if(_cmde.compare("*IDN ?") == 0){
	 _rep.assign("je suis le client " + this->getHeader());
	 }*/
	/*else if (_cmde.compare("?") == 0) {
		_rep.assign("RPM: " + std::to_string(this->rpmValue) + "\n\r");
	} else {
		int value = 0;
		value = stoi(_cmde, nullptr, 10);
		this->rpmValue = value;
		startPwm(value);
	}*/

	return 0;
}
