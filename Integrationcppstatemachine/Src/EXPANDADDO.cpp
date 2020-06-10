/*
 * EXPANDADDO.cpp
 *
 *  Created on: 10 juin 2020
 *      Author: PARIS
 */

#include "EXPANDADDO.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>

EXPANDADDO::EXPANDADDO() {
	// TODO Auto-generated constructor stub
	this->expvalue = 0;
	this->expdir = 0;
}

EXPANDADDO::EXPANDADDO(std::string _name): ScpiClientServer(_name) {
	// TODO Auto-generated constructor stub
	this->expvalue = 0;
	this->expdir = 0;
}

EXPANDADDO::~EXPANDADDO() {
	// TODO Auto-generated destructor stub
}

short int EXPANDADDO::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe EXPADDO");


	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//reset
		break;
	case REQ_IDN:
		_rep.assign("je suis le client HARDWARE " + this->getHeader());
		break;
	case REQ_QST:
		_rep.assign(this->getHeader()+ " : "+ std::to_string(readPort()) + "\n\r");
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}
int EXPANDADDO::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*RST") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("DATA ?") == 0){
		sel = REQ_QST;
	}else {
		//throw something
	}
	return sel;
}

int EXPANDADDO::setDir(uint16_t pin, uint8_t dir){

	if(dir == 0){
		this->expdir = this->expdir & (1u<<pin);
	}else{
		this->expdir = this->expdir | (1u<<pin);
	}

	//write i2c4 this.expvalue

}

int EXPANDADDO::writepin(uint16_t pin, uint8_t state){


	if(state == 0){
		this->expvalue = this->expvalue & (1u<<pin);
	}else{
		this->expvalue = this->expvalue | (1u<<pin);
	}

	//write i2c4 this.expvalue
}


uint16_t EXPANDADDO::readPort(){
	uint8_t data = 0;
	uint16_t value = 0;

	uint16_t value2 = 0x0000;

	TM_I2C_WriteNoRegister(I2C4, EXPSECU_I2CADD, 0x00); //write input port 0
	TM_I2C_ReadNoRegister(I2C4, (EXPSECU_I2CADD)|(1u<<0), &data); //read from input port 0

	value = data;
	value2 = data;

	TM_I2C_WriteNoRegister(I2C4, EXPSECU_I2CADD, 0x01); //write input port 1
	TM_I2C_ReadNoRegister(I2C4, (EXPSECU_I2CADD)|(1u<<0), &data); //read from input port 1

	value = value + data;
	value2 = value2 + (data<<8);



	return value2;
}

int EXPANDADDO::configseq(){

	//configurer en écriture


	return 0;
}
