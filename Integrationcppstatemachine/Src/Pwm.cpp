/*
 * Pwm.cpp
 *
 *  Created on: 15 avr. 2020
 *      Author: PARIS
 */

#include "Pwm.h"
#include "ScpiClientServer.h"
#include <string>

Pwm::Pwm() {
	// TODO Auto-generated constructor stub
	rpmValue = 0;

}

Pwm::Pwm(std::string _name) : ScpiClientServer(_name), rpmValue(0) {
	// TODO Auto-generated constructor stub
}

Pwm::~Pwm() {
	// TODO Auto-generated destructor stub
}

short int Pwm::ExecuteCmde (std::string& _cmde, std::string& _rep){
	_rep.assign("Je suis le execute de la classe pwm");

	/*if(_cmde.compare("*RST") == 0){

	}else if(_cmde.compare("RPM ?") == 0){

	}else if(_cmde.compare("RPM ") == 0){

	}else{
		//throw something
	}*/



	return 0;
}
