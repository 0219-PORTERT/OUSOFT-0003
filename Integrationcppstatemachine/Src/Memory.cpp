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

Memory::Memory() {
	// TODO Auto-generated constructor stub
	nlohmann::json j;
}

Memory::Memory(uint8_t _i2cadress): i2cadress(_i2cadress) {

}

Memory::~Memory() {
	// TODO Auto-generated destructor stub
}

uint8_t Memory::readfrommemory(std::string &_toread){
	this->i2cadress;
}


uint8_t Memory::writetomemory(std::string &_towrite){
	this->i2cadress;
}
