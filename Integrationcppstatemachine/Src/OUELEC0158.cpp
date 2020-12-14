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
#include "i2c.h"

OUELEC_0158::OUELEC_0158() {
	// TODO Auto-generated constructor stub

}

OUELEC_0158::OUELEC_0158(uint8_t _adressrack) {
	this->adressrack = _adressrack<<1;//shift de 1 pour ajouter le bit /RW à la fin de l'adresse i2c
	this->jsonstruct = {
				{"IDN", {
						{"PART_NB",0},
						{"SERIAL_NB",0},
						{"AFFAIRE",0}
				}},
				{"MCO", {
						{"MCO_N_DATE","10/12/20"},
						{"CAL_N_DATE","10/12/20"},
				}},
				{"CAL", {
						{"CFA",{0,0,0,0,0}},
						{"CFB",{0,0,0,0,0}},
				}},
		};


	this->carteEIC1.setI2cAdress(this->adressrack);
	this->carteLEM1.setI2cAdress(ADCDAC_I2CADD);

	for(int i = 0; i<6;i++){
		this->tabCfa[i] = 0;
		this->tabCfb[i] = 0;
	}

}



OUELEC_0158::~OUELEC_0158() {
	// TODO Auto-generated destructor stub
}

void OUELEC_0158::init(){
	//carteEIC1.switchToi2c(0); //switchto eic
	//this->loadJson();

	carteEIC1.switchToi2c(1); //switch to lem

	carteLEM1.enableInternalRef();//enable ref



	//carteLEM1.setconfigADC(0xff);
	//carteLEM1.setconfigDAC(0xff);

	carteLEM1.setconfigADC(0x1f); //00011111
	carteLEM1.setconfigDAC(0xe0); //11100000

	carteEIC1.switchToi2c(0); //switchto eic
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


uint8_t OUELEC_0158::loadJson(){

	std::string s;
	uint8_t error =0;
	carteEIC1.getJsonStringfromMemory(s);


	try{

	this->jsonstruct = json::parse(s);

	tabCfa[0] = this->jsonstruct.at("/CAL/CFA/0"_json_pointer);
	tabCfa[1] = this->jsonstruct.at("/CAL/CFA/1"_json_pointer);
	tabCfa[2] = this->jsonstruct.at("/CAL/CFA/2"_json_pointer);
	tabCfa[3] = this->jsonstruct.at("/CAL/CFA/3"_json_pointer);
	tabCfa[4] = this->jsonstruct.at("/CAL/CFA/4"_json_pointer);

	tabCfb[0] = this->jsonstruct.at("/CAL/CFB/0"_json_pointer);
	tabCfb[1] = this->jsonstruct.at("/CAL/CFB/1"_json_pointer);
	tabCfb[2] = this->jsonstruct.at("/CAL/CFB/2"_json_pointer);
	tabCfb[3] = this->jsonstruct.at("/CAL/CFB/3"_json_pointer);
	tabCfb[4] = this->jsonstruct.at("/CAL/CFB/4"_json_pointer);


	}catch(json::parse_error& e){
		error = 1;
	}
	catch (json::out_of_range& e)
	{
		error = 2;
	}

return error;
}




