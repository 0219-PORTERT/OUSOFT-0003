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
	this->jsonstruct = {
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
		};

	this->carteEIC1.setI2cAdress(_adressrack);
	this->carteLEM1.setI2cAdress(0x20);

	for(int i = 0; i<6;i++){
		this->tabCfa[i] = 0;
		this->tabCfb[i] = 0;
	}


	carteEIC1.switchToi2c(0); //switchto eic
	this->loadJson();

	carteEIC1.switchToi2c(1); //switch to lem
	carteLEM1.enableInternalRef();//enable ref

	carteLEM1.setconfigADC(0x1f); //00011111
	carteLEM1.setconfigDAC(0xe0); //11100000

	carteEIC1.switchToi2c(0); //switchto eic

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

float OUELEC_0158::readCurrent(uint8_t channel){

	float value;

	carteEIC1.switchToi2c(1);
	value = (carteLEM1.readADC(channel)*this->tabCfa[channel]+this->tabCfb[channel])*(3.3/4095.0);
	carteEIC1.switchToi2c(0);

	return value;

}

uint8_t OUELEC_0158:: setPosition(uint8_t channel, uint16_t value){


	carteEIC1.switchToi2c(1);
	carteLEM1.setDAC( channel, value);
	carteEIC1.switchToi2c(0);
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




