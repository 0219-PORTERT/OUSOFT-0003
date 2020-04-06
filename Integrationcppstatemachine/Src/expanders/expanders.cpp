/*
 * expanders.cpp
 *
 *  Created on: 27 sept. 2019
 *      Author: RENAULT_E
 */

#include "expanders.h"

expanders::expanders() {
	// TODO Auto-generated constructor stub
}

expanders::~expanders() {
	// TODO Auto-generated destructor stub
}

void expanders::Add(int p_value) {
	this->value += p_value;
}

int expanders::GetValue() {
	return value;
}

char* expanders::GetType(){
	return this->name;
}
