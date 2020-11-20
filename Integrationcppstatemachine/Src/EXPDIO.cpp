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

	this->direction = -1; //entrée

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
	case REQ_TST:
		_rep.assign(testAB(0xAA) + "\n\r" +testAB(0x55) +"\n\r");
		break;
	case REQ_SDR:
		_rep.assign(getSDR()+"\n\r");
		break;
	case REQ_RTR:
		_rep.assign(getRTR()+"\n\r");
		break;
	case REQ_MBA:
		_rep.assign(getMBA()+"\n\r");
		break;
	case REQ_THO:
		_rep.assign(getTHO()+"\n\r");
		break;
	case REQ_THM:
		_rep.assign(getTHM()+"\n\r");
		break;
	case REQ_THN:
		_rep.assign(getTHN()+"\n\r");
		break;
	case REQ_WDSDR:
		_rep.assign(getWDSDR()+"\n\r");
		break;
	case REQ_RTA:
		_rep.assign(getRTA()+"\n\r");
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

	}else if(_cmde.compare("TST ?") == 0){
		sel = REQ_TST;
	}else if(_cmde.compare("SDR ?") == 0){
		sel = REQ_SDR;
	}else if(_cmde.compare("RTR ?") == 0){
		sel = REQ_RTR;
	}else if(_cmde.compare("MBA ?") == 0){
		sel = REQ_MBA;
	}else if(_cmde.compare("THO ?") == 0){
		sel = REQ_THO;
	}else if(_cmde.compare("THM ?") == 0){
		sel = REQ_THM;
	}else if(_cmde.compare("THN ?") == 0){
		sel = REQ_THN;
	}else if(_cmde.compare("WDSDR ?") == 0){
		sel = REQ_WDSDR;
	}else if(_cmde.compare("RTA ?") == 0){
		sel = REQ_RTA;
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
		TM_I2C_WriteNoRegister(I2C4, EXP_DIO_I2CADD, 0x00); //write input port 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DIO_I2CADD)|(1u<<0), &data); //read from input port 0
	}else{
		TM_I2C_WriteNoRegister(I2C4, EXP_DIO_I2CADD, 0x01); //write input port 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DIO_I2CADD)|(1u<<0), &data); //read from input port 1
	}
	return data;
}
uint8_t EXPDIO::writePort(){

	if(this->direction != 0x00){
		this->direction = 0x00; //config output
		setDir();
	}
	if(this->side == SIDEA){
		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x02, this->writevalue);
	}else{
		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x03, this->writevalue);
	}
	return 0;
}

uint8_t EXPDIO::setDir(){
	if(this->side == SIDEA){
		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x06, this->direction);
	}else{
		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x07, this->direction);
	}
	return 0;
}


std::string EXPDIO::testAB(uint8_t bytetotest){

	uint8_t data = -1;
	std::string error = "unknow error";

	if(this->side == SIDEA){

		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x07, 0xFF); //port B lecture
		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x06, 0x00); //port A ecriture

		//this->writevalue = bytetotest;
		//this->writePort();

		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x02, bytetotest);//ecriture port A


		TM_I2C_WriteNoRegister(I2C4, EXP_DIO_I2CADD, 0x01); //write input portB 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DIO_I2CADD)|(1u<<0), &data); //read from input portB 1

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}

	}else{

		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x07, 0x00); //port B ecriture
		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x06, 0xFF); //port A lecture


		//this->writevalue = bytetotest;
		//this->writePort();

		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x03, bytetotest);//ecriture port B


		TM_I2C_WriteNoRegister(I2C4, EXP_DIO_I2CADD, 0x00); //write input port 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DIO_I2CADD)|(1u<<0), &data); //read from input port 0

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}


	}
	return error;
}

uint8_t EXPDIO::getSDR(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 0)){
		return 1;
	}else{
		return 0;
	}
}

uint8_t EXPDIO::getRTR(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 1)){
		return 1;
	}else{
		return 0;
	}
	return 0;
}

uint8_t EXPDIO::getMBA(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 2)){
		return 1;
	}else{
		return 0;
	}
	return 0;
}

uint8_t EXPDIO::getTHO(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 3)){
		return 1;
	}else{
		return 0;
	}
	return 0;
}

uint8_t EXPDIO::getTHM(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 4)){
		return 1;
	}else{
		return 0;
	}
	return 0;
}

uint8_t EXPDIO::getTHN(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 5)){
		return 1;
	}else{
		return 0;
	}
	return 0;
}

uint8_t EXPDIO::getWDSDR(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 6)){
		return 1;
	}else{
		return 0;
	}
	return 0;
}

uint8_t EXPDIO::getRTA(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 7)){
		return 1;
	}else{
		return 0;
	}
	return 0;
}
uint16_t EXPDIO::readPin(){
	return 0;
}
uint16_t EXPDIO::writePin(){
	return 0;
}
