/*
 * OUELEC0158.cpp
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#include "OUELEC0158.h"
#include <string>
#include <iostream>
#include "json.hpp"

OUELEC_0158::OUELEC_0158() {
	// TODO Auto-generated constructor stub

}

OUELEC_0158::OUELEC_0158(uint8_t _adressrack) {
	this->adressrack = _adressrack;
	this->jsonstruct ;
	/*= {
				{"IDN", {
						{"part_nb",0},
						{"serial_nb",0},
						{"affaire",0}
				}},
				{"MCO", {
						{"part_nb",0},
						{"serial_nb",0},
						{"affaire",0}
				}},
				{"CAL", {
						{"CFa",{0,0,0,0,0}},
						{"CFb",{0,0,0,0,0}},
				}},
		};*/

	this->carteEIC1.setI2cAdress(_adressrack);
	this->carteLEM1.setI2cAdress(_adressrack);

	for(int i = 0; i<6;i++){
		this->tabCfa[i] = 0;
		this->tabCfb[i] = 0;
	}
	//this->loadJson();

}


OUELEC_0158::~OUELEC_0158() {
	// TODO Auto-generated destructor stub
}

void OUELEC_0158::setRackadress(uint8_t adr){
	this->adressrack = adr;
}

uint8_t OUELEC_0158::getRackadress(void){
	return this->adressrack;
}

uint16_t OUELEC_0158::readCurrent(uint8_t channel){


	return carteLEM1.readADC(this->adressrack, channel)*this->tabCfa[channel]+this->tabCfb[channel];

}



void OUELEC_0158::loadJson(){

	this->jsonstruct = carteEIC1.getJsonString();

	tabCfa[0] = this->jsonstruct.at("/CAL/CFa/0"_json_pointer);
	tabCfa[1] = this->jsonstruct.at("/CAL/CFa/1"_json_pointer);
	tabCfa[2] = this->jsonstruct.at("/CAL/CFa/2"_json_pointer);
	tabCfa[3] = this->jsonstruct.at("/CAL/CFa/3"_json_pointer);
	tabCfa[4] = this->jsonstruct.at("/CAL/CFa/4"_json_pointer);

	tabCfb[0] = this->jsonstruct.at("/CAL/CFb/0"_json_pointer);
	tabCfb[1] = this->jsonstruct.at("/CAL/CFb/1"_json_pointer);
	tabCfb[2] = this->jsonstruct.at("/CAL/CFb/2"_json_pointer);
	tabCfb[3] = this->jsonstruct.at("/CAL/CFb/3"_json_pointer);
	tabCfb[4] = this->jsonstruct.at("/CAL/CFb/4"_json_pointer);
}




