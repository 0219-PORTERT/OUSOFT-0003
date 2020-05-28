/*
 * TempHumSensor.cpp
 *
 *  Created on: 28 mai 2020
 *      Author: PARIS
 */

#include "TempHumSensor.h"
#include "ScpiClientServer.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <string>
#include <iostream>

TempHumSensor::TempHumSensor() {
	// TODO Auto-generated constructor stub
	this->temperature =0;
	this->huidity=0 ;
	this->i2csensoraddr = TEMP_HUM_SENS8_I2CADD;
}

TempHumSensor::TempHumSensor(std::string _name): ScpiClientServer(_name),temperature(0),huidity(0),i2csensoraddr(TEMP_HUM_SENS8_I2CADD){

}

TempHumSensor::~TempHumSensor() {
	// TODO Auto-generated destructor stub
}

short int TempHumSensor::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe TEMPHUM");

	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//RESET ?
		break;
	case REQ_IDN:
		_rep.assign("je suis le client HARDWARE " + this->getHeader());
		break;
	case REQ_HUM:
		_rep.assign(_cmde +" : "+std::to_string(readTemp())+"\n\r");
		break;
	case REQ_TEMP:
		_rep.assign(_cmde +" : "+std::to_string(readTemp())+"\n\r");
		break;
	case REQ_TST:
		//_rep.assign(_cmde +" : "+std::to_string()+"\n\r");
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int TempHumSensor::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*RST") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("HUM ?") == 0){
		sel = REQ_HUM;
	} else if(_cmde.compare("TEMP ?") == 0){
		sel = REQ_TEMP;
	}else if(_cmde.compare("TST") == 0){
		sel = REQ_TST;
	} else {
		//throw something
	}
	return sel;
}

float TempHumSensor::readTemp(){

	return 0;
}
float TempHumSensor::readHum(){

	return 0;
}

