/*
 * Memory.cpp
 *
 *  Created on: 20 nov. 2020
 *      Author: PARIS
 */

#include "Memory.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>
#include "json.hpp"

using json = nlohmann::json;

Memory::Memory() {
	// TODO Auto-generated constructor stub

}

Memory::Memory(uint8_t _i2cadress): i2cadress(_i2cadress) {

	/*this->jsonstruct = {
			{"IDN", {
					{"part_nb",0},
					{"serial_nb",0},
					{"affaire",0}
			}},
			{"MCO", {
					{"part_nb",0},
					{"serial_nb",0},
					{"affaire",0}
			}},
			{"CAL", {
					{"CFa",{0,0,0,0,0}},
					{"CFb",{0,0,0,0,0}},
			}},
	};*/
	this->i2cadress = 0xa4;

}

Memory::~Memory() {
	// TODO Auto-generated destructor stub
}






uint8_t Memory::readfrommemory(std::string &_toread){

	uint8_t dummy[2] = {};
	uint8_t dataread[256]= {};


	TM_I2C_IsDeviceConnected(I2C4, this->i2cadress);


	TM_I2C_WriteMultiNoRegister(I2C4, this->i2cadress, dummy, sizeof(dummy));//dummy write
	TM_I2C_ReadMultiNoRegister(I2C4, (this->i2cadress | (1u<<0)), dataread, 256);


	std::string buffer((char*)dataread);

	_toread.assign(buffer);


	return 0;
}


uint8_t Memory::writetomemory(std::string &_towrite){


	int a = _towrite.length()+2;


	uint8_t data[a] = {};

	data[0] = 0;
	data[1] = 0;

	for(int i =2; i<sizeof(data); i++){
		data[i] = _towrite[i];
	}

	data[0];

	TM_I2C_IsDeviceConnected(I2C4, this->i2cadress);
	TM_I2C_WriteMultiNoRegister(I2C4, this->i2cadress, data, sizeof(data));




	return 0;
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
