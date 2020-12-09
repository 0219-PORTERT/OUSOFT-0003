/*
 * OUCART0018.cpp
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#include "OUCART0018.h"
#include <string>
#include <iostream>
#include "json.hpp"
#include "i2c.h"
#include "tm_stm32_i2c.h"

OUCART0018::OUCART0018() {
	// TODO Auto-generated constructor stub
	this->mem1.setI2cAdress(EEPROM1_I2CADD);
}

OUCART0018::OUCART0018(uint8_t _i2cadress) {
	this->i2cadress = _i2cadress;
	this->mem1.setI2cAdress(EEPROM1_I2CADD);
}

void OUCART0018::setI2cAdress(uint8_t adr){
	this->i2cadress = adr;
}

OUCART0018::~OUCART0018() {
	// TODO Auto-generated destructor stub
}




uint8_t OUCART0018::switchToi2c(uint8_t i2cchannel){

	uint8_t data[1];
	data[0] = 0;
	switch(i2cchannel){
		case 0:
			TM_I2C_WriteNoRegister(I2C1, SWITCHI2C, 0x01);
			TM_I2C_ReadNoRegister(I2C1, (SWITCHI2C | (1u<<0)), data);
			break;
		case 1:
			TM_I2C_WriteNoRegister(I2C1, SWITCHI2C, 0x02);
			TM_I2C_ReadNoRegister(I2C1, (SWITCHI2C | (1u<<0)), data);
			break;
		case 2:
			TM_I2C_WriteNoRegister(I2C1, SWITCHI2C, 0x04);
			break;
		case 3:
			TM_I2C_WriteNoRegister(I2C1, SWITCHI2C, 0x08);
			break;
		default:
			TM_I2C_WriteNoRegister(I2C1, SWITCHI2C, 0x00);
			break;
	}

	return 0;
}

uint8_t OUCART0018::getJsonStringfromMemory(std::string &_toread){
	uint8_t test =0;

	this->switchToi2c(0);
	this->mem1.readfrommemory(_toread);

	return test;
}

uint8_t OUCART0018::storeJsonStringtoMemory(std::string &_towrite){
	uint8_t test =0;

	this->switchToi2c(0);
	this->mem1.writetomemory(_towrite);

	return test;

}


std::string OUCART0018::serialize(){
	//std::string s;
	//return s.assign(this->jsonstruct.dump());
}

void OUCART0018::deserialize(std::string s){
	//this->jsonstruct = s;
}

nlohmann::json OUCART0018::getjsonstruct(){
	//return this->jsonstruct;
}

void  OUCART0018::getjsonwithref(json& j){
	std::string s;

	this->getJsonStringfromMemory(s);

	j = s;

}


