/*
 * Pwm.cpp
 *
 *  Created on: 15 avr. 2020
 *      Author: PARIS
 */

#include "Pwm.h"
#include <string>

Pwm::Pwm() {
	// TODO Auto-generated constructor stub
	rpmValue = 0;

}

Pwm::Pwm(std::string _name) {
	// TODO Auto-generated constructor stub
	this->rpmValue = 0;
	this->Name = _name;
}

Pwm::~Pwm() {
	// TODO Auto-generated destructor stub
}

short int Pwm::ExecuteCmde (std::string& _cmde, std::string &_rep){

	//switch(){
	//}

	return 0;
}
