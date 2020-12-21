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
						{"PART_NB","PARTXXXX"},
						{"SERIAL_NB","SERXXXX"},
						{"AFFAIRE","XXXX"},
						{"REV","XXXX"}
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
	this->partNb.assign("null");
	this->serialNb.assign("null");
	this->affaire.assign("null");
	this->calDate.assign("null");
	this->mcoDate.assign("null");
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

	//carteEIC1.switchToi2c(1);
	//value = (carteLEM1.readADC(channel)*(5.0/4095.0))*this->tabCfa[channel]+this->tabCfb[channel];
	value = (((carteLEM1.readADC(channel) - 2047.0f)*(5.0f/4095.0f))/(0.04167))*this->tabCfa[channel]+this->tabCfb[channel];
			//*(5.0/4095.0))*1+0;
	//carteEIC1.switchToi2c(0);


	//0.0195 -> b0


	return value;

}

uint8_t OUELEC_0158:: setPosition(uint8_t channel, int value){

	carteEIC1.switchToi2c(1);
	carteLEM1.setDAC( channel, value);
	carteEIC1.switchToi2c(0);
}


uint8_t OUELEC_0158::loadJson(){

	std::string s;
	uint8_t error =0;
	carteEIC1.getJsonStringfromMemory(s);
	//std::string test;

	//test.assign(this->jsonstruct.dump());

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

	this->partNb.assign(this->jsonstruct.at("/IDN/PART_NB"_json_pointer));
	this->serialNb.assign(this->jsonstruct.at("/IDN/SERIAL_NB"_json_pointer));
	this->affaire.assign(this->jsonstruct.at("/IDN/AFFAIRE"_json_pointer));
	this->calDate.assign(this->jsonstruct.at("/MCO/CAL_N_DATE"_json_pointer));
	this->mcoDate.assign(this->jsonstruct.at("/MCO/MCO_N_DATE"_json_pointer));


	}catch(json::parse_error& e){

		tabCfa[0] = 1;
		tabCfa[1] = 1;
		tabCfa[2] = 1;
		tabCfa[3] = 1;
		tabCfa[4] = 1;

		tabCfb[0] = 0;
		tabCfb[1] = 0;
		tabCfb[2] = 0;
		tabCfb[3] = 0;
		tabCfb[4] = 0;

		this->partNb.assign("UNKNOW PART NB");
		this->serialNb.assign("UNKNOW SERIAL NB");
		this->affaire.assign("UNKNOW AFFAIR NB");
		this->calDate.assign("UNKNOW LAST CAL");
		this->mcoDate.assign("UNKNOW LAST MCO");

		error = 1;
	}
	catch (json::out_of_range& e)
	{
		error = 2;
	}
return error;
}

std::string OUELEC_0158::getPartnb(){
	return this->partNb;
}
std::string OUELEC_0158::getSerialnb(){
	return this->serialNb;
}
std::string OUELEC_0158::getAffaire(){
	return this->affaire;
}
std::string OUELEC_0158::getLastcal(){
	return this->calDate;
}
std::string OUELEC_0158::getLastmco(){
	return this->mcoDate;
}
