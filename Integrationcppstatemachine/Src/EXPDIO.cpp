/*
 * EXPDIO.cpp
 *
 *  Created on: 27 août 2020
 *      Author: PARIS
 */

#include "EXPDIO.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>

EXPDIO::EXPDIO() {
	// TODO Auto-generated constructor stub

}

EXPDIO::EXPDIO(std::string _name, uint8_t _side): ScpiClientServer(_name), side(_side) {
	// TODO Auto-generated constructor stub

	this->direction = 0; //entrée

}

EXPDIO::~EXPDIO() {
	// TODO Auto-generated destructor stub
}


short int EXPDIO::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe EXPDIO");


	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//reset
		break;
	case REQ_IDN:
		_rep.assign(this->getHeader());
		break;
	case REQ_QSTRD:
		_rep.assign(std::to_string(readPort()) + "\n\r");
		break;
	case REQ_WR:
		writePort();
		break;
	case REQ_QSTDIR:
		_rep.assign(std::to_string(this->direction) + "\n\r");
		break;
	case REQ_SETDIR:
		setDir();
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int EXPDIO::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	}else if(_cmde.compare("RD ?") == 0){
		sel = REQ_QSTRD;
	}else if(_cmde.compare(0, 3, "WR ") == 0){
		int value = 0;

		value = stoi(_cmde.substr(3), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->writevalue = value;
			sel = REQ_WR;
		}
	}else if(_cmde.compare("DIR ?") == 0){
		sel = REQ_QSTDIR;
	}else if(_cmde.compare(0, 7, "SETDIR ") == 0){
		int value = 0;
		value = stoi(_cmde.substr(7), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->direction = value;
			sel = REQ_SETDIR;
		}

	}else {
		//throw something
	}
	return sel;
}




uint8_t EXPDIO::readPort(){
	uint8_t data = -1;

	if(this->direction != 0xFF){
		this->direction = 0xFF; //config input
		setDir();
	}
	if(this->side == SIDEA){
		TM_I2C_WriteNoRegister(I2C4, EXPSECU_I2CADD, 0x00); //write input port 0
		TM_I2C_ReadNoRegister(I2C4, (EXPSECU_I2CADD)|(1u<<0), &data); //read from input port 0
	}else{
		TM_I2C_WriteNoRegister(I2C4, EXPSECU_I2CADD, 0x01); //write input port 1
		TM_I2C_ReadNoRegister(I2C4, (EXPSECU_I2CADD)|(1u<<0), &data); //read from input port 1
	}
	return data;
}
uint8_t EXPDIO::writePort(){

	if(this->direction != 0x00){
		this->direction = 0x00; //config output
		setDir();
	}
	if(this->side == SIDEA){
		TM_I2C_Write(I2C4, EXPSECU_I2CADD, 0x02, this->writevalue);
	}else{
		TM_I2C_Write(I2C4, EXPSECU_I2CADD, 0x03, this->writevalue);
	}
	return 0;
}

uint8_t EXPDIO::setDir(){
	if(this->side == SIDEA){
		TM_I2C_Write(I2C4, EXPSECU_I2CADD, 0x06, this->direction);
	}else{
		TM_I2C_Write(I2C4, EXPSECU_I2CADD, 0x07, this->direction);
	}
	return 0;
}


uint16_t EXPDIO::readPin(){
	return 0;
}
uint16_t EXPDIO::writePin(){
	return 0;
}
