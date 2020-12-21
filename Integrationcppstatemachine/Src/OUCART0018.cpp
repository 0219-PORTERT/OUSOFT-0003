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
	this->i2cadress = SWITCHI2C | adr;
}

OUCART0018::~OUCART0018() {
	// TODO Auto-generated destructor stub
}




uint8_t OUCART0018::switchToi2c(uint8_t i2cchannel){

	uint8_t data[1];
	data[0] = 0;
	switch(i2cchannel){
		case 0:
			TM_I2C_WriteNoRegister(I2C1, this->i2cadress, 0x01);/*problème adresse*/
			TM_I2C_ReadNoRegister(I2C1, (this->i2cadress | (1u<<0)), data);
			break;
		case 1:
			TM_I2C_WriteNoRegister(I2C1, this->i2cadress, 0x02);
			TM_I2C_ReadNoRegister(I2C1, (this->i2cadress | (1u<<0)), data);
			break;
		case 2:
			TM_I2C_WriteNoRegister(I2C1, this->i2cadress, 0x04);
			break;
		case 3:
			TM_I2C_WriteNoRegister(I2C1, this->i2cadress, 0x08);
			break;
		default:
			TM_I2C_WriteNoRegister(I2C1, this->i2cadress, 0x00);
			break;
	}

	return 0;
}

uint8_t OUCART0018::getJsonStringfromMemory(std::string &_toread){
	uint8_t test =0;

	this->switchToi2c(0);
	this->mem1.readfrommemory(_toread);
	this->switchToi2c(6);
	return test;
}

uint8_t OUCART0018::storeJsonStringtoMemory(std::string &_towrite){
	uint8_t test =0;

	this->switchToi2c(0);
	this->mem1.writetomemory(_towrite);
	this->switchToi2c(6);
	return test;

}


std::string OUCART0018::serialize(nlohmann::json j){
	std::string s;
	return s.assign(j.dump());
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

void OUCART0018::setTemp(uint8_t rGcode,uint8_t rPcode, uint8_t capteur ){
	this->switchToi2c(0); //switch to i2c channel 0 carte 0018
	//settings
	TM_I2C_Write(I2C1,POT_I2CADD, capteur, rPcode);
	//HAL_Delay(10);
	TM_I2C_Write(I2C1, POT_I2CADD, capteur, rGcode);
	this->switchToi2c(6);
}

void OUCART0018::setDir(uint8_t side, uint8_t dir){
	this->switchToi2c(0); //switch to i2c channel 0 carte 0018
	TM_I2C_Write(I2C1, EXPSECU_I2CADD, side, dir);
	this->switchToi2c(6);
}
void OUCART0018::writePort(uint8_t side, uint8_t writeBits){
	this->switchToi2c(0); //switch to i2c channel 0 carte 0018
	TM_I2C_Write(I2C1, EXPSECU_I2CADD, side, writeBits);
	this->switchToi2c(6);
}
void OUCART0018::readPort(uint8_t side, uint8_t *data){
	this->switchToi2c(0); //switch to i2c channel 0 carte 0018

/*	uint8_t test = 0;

	test = (uint8_t)TM_I2C_IsDeviceConnected(I2C1, EXPSECU_I2CADD);*/

	TM_I2C_WriteNoRegister(I2C1, EXPSECU_I2CADD, side); //write input port 1
	TM_I2C_ReadNoRegister(I2C1, (EXPSECU_I2CADD)|(1u<<0), data); //read from input port 1
	this->switchToi2c(6);
}

uint8_t OUCART0018::isConnected(){
	return (uint8_t)TM_I2C_IsDeviceConnected(I2C1, this->i2cadress);
}



