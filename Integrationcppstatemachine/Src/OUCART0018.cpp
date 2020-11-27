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

OUCART0018::OUCART0018() {
	// TODO Auto-generated constructor stub

}

OUCART0018::OUCART0018(uint8_t _i2cadress) {
	this->i2cadress = _i2cadress;
}

void OUCART0018::setI2cAdress(uint8_t adr){
	this->i2cadress = adr;
}

OUCART0018::~OUCART0018() {
	// TODO Auto-generated destructor stub
}

std::string OUCART0018::getJsonString(){
	std::string s;
	this->mem1.readfrommemory(s);
	return s;
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
	j = this->getJsonString();

}


