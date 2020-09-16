/*
 * EXPADDO24.cpp
 *
 *  Created on: 7 sept. 2020
 *      Author: PARIS
 */

#include "EXPADDO24.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>

EXPADDO24::EXPADDO24() {
	// TODO Auto-generated constructor stub

}

EXPADDO24::EXPADDO24(std::string _name, uint8_t _side): ScpiClientServer(_name), side(_side) {
	// TODO Auto-generated constructor stub

	this->direction = -1; //entrée

}

EXPADDO24::~EXPADDO24() {
	// TODO Auto-generated destructor stub
}


short int EXPADDO24::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	_rep.assign("Je suis le execute de la classe EXPaddo");


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
	case REQ_TSTAB:
		_rep.assign(testAB(0xAA) + "\n\r" +testAB(0x55) +"\n\r");
		break;
	case REQ_TSTAC:
		_rep.assign(testAC(0xAA) + "\n\r" +testAC(0x55) +"\n\r");
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int EXPADDO24::decodeInstruct(std::string& _cmde) {

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

	}else if(_cmde.compare("TSTAB ?") == 0){
		sel = REQ_TSTAB;
	}else if(_cmde.compare("TSTAC ?") == 0){
		sel = REQ_TSTAC;
	}else {
		//throw something
	}
	return sel;
}




uint8_t EXPADDO24::readPort(){
	uint8_t data = -1;

	if(this->direction != 0xFF){
		this->direction = 0xFF; //config input
		setDir();
	}

	if(this->side == SIDEA){
		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x00); //write input port 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 0
	}if(this->side == SIDEB){
		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x01); //write input port 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 1
	}if(this->side == SIDEC){
		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x02); //write input port 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 1
	}
	return data;
}
uint8_t EXPADDO24::writePort(){

	if(this->direction != 0x00){
		this->direction = 0x00; //config output
		setDir();
	}

	if(this->side == SIDEA){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x04, this->writevalue);
	}if(this->side == SIDEB){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x05, this->writevalue);
	}if(this->side == SIDEC){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x06, this->writevalue);
	}
	return 0;
}

uint8_t EXPADDO24::setDir(){
	if(this->side == SIDEA){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, this->direction);
	}if(this->side == SIDEB)
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0D, this->direction);
	if(this->side == SIDEC){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0E, this->direction);
	}
	return 0;
}


std::string EXPADDO24::testAB(uint8_t bytetotest){
	uint8_t data = -1;
	std::string error = "unknow error";

	if(this->side == SIDEA){

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0D, 0xFF); //port B lecture
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, 0x00); //port A ecriture

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x04, bytetotest);//ecriture port A


		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x01); //write input portB 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input portB 1

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}

	}if(this->side == SIDEB){

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0D, 0x00); //port B ecriture
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, 0xFF); //port A lecture

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x05, bytetotest);//ecriture port B


		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x00); //write input port 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 0

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}


	}
	return error;
}
std::string EXPADDO24::testAC(uint8_t bytetotest){
	uint8_t data = -1;
	std::string error = "unknow error";

	if(this->side == SIDEA){

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0E, 0xFF); //port C lecture
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, 0x00); //port A ecriture

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x04, bytetotest);//ecriture port A


		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x02); //write input portC 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input portB 1

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}

	}if(this->side == SIDEC){

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0E, 0x00); //port C ecriture
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, 0xFF); //port A lecture

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x06, bytetotest);//ecriture port C


		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x00); //write input portA 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 0

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}


	}
	return error;
}

uint16_t EXPADDO24::readPin(){
	return 0;
}
uint16_t EXPADDO24::writePin(){
	return 0;
}

