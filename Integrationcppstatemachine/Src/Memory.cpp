/*
 * Memory.cpp
 *
 *  Created on: 20 nov. 2020
 *      Author: PARIS
 */

#include "Memory.h"

#include <sys/_stdint.h>
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>
#include "json.hpp"
#include "FonctionsAutotest.h"

using json = nlohmann::json;

Memory::Memory() {
	// TODO Auto-generated constructor stub

}

Memory::Memory(uint8_t _i2cadress): i2cadress(_i2cadress) {



}

Memory::~Memory() {
	// TODO Auto-generated destructor stub
}


void Memory::setI2cAdress(uint8_t adr){
	this->i2cadress = adr;
}



uint8_t Memory::readfrommemory(std::string &_toread){

	uint8_t dummy[2] = {};
	uint8_t dataread[256]= {};
	uint8_t test = 0;

	test = (uint8_t)TM_I2C_IsDeviceConnected(I2C4, this->i2cadress);


	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, dummy, sizeof(dummy));//dummy write
	TM_I2C_ReadMultiNoRegister(I2C1, (this->i2cadress | (1u<<0)), dataread, 256);


	std::string buffer((char*)dataread);

	_toread.assign(buffer);


	return test;
}


uint8_t Memory::writetomemory(std::string &_towrite){


	int a = _towrite.length()+3;
	uint8_t test = 0;

	uint8_t data[a] = {};

	data[0] = 0;
	data[1] = 0;

	for(int i =0; i<sizeof(data); i++){
		data[i+2] = _towrite[i];
	}

	//data[a-1] = '\0';



	test = (uint8_t)TM_I2C_IsDeviceConnected(I2C1, this->i2cadress);

	//this->eraseAll();
	//I2Cscanner(I2C1);
	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));

	return test;
}



void Memory::eraseAll(){
	uint8_t data2[255];

	for(int i =0; i<sizeof(data2);i++){
		data2[i] = '\0';
	}
	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data2, sizeof(data2));
}



std::string Memory::serialize(){
	std::string s;
	return s.assign(this->jsonstruct.dump());
}

void Memory::deserialize(std::string s){
	this->jsonstruct = s;
}

nlohmann::json Memory::getjsonstruct(){
	return this->jsonstruct;
}

void  Memory::getjsonstructref(json& j){
	j = this->jsonstruct;
}

