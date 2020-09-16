/*
 * EXPSEC.cpp
 *
 *  Created on: 3 juin 2020
 *      Author: PARIS
 */

#include "EXPSEC.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>
#include "usart.h"
#include "FonctionsAutotest.h"

EXPSEC::EXPSEC() {
	// TODO Auto-generated constructor stub

}
EXPSEC::EXPSEC(std::string _name): ScpiClientServer(_name) {
	// TODO Auto-generated constructor stub
	this->staterelaysecu = 0;
}
EXPSEC::~EXPSEC() {
	// TODO Auto-generated destructor stub
}

short int EXPSEC::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe EXPSECu");


	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//reset
		break;
	case REQ_IDN:
		//_rep.assign("je suis le client HARDWARE " + this->getHeader());
		_rep.assign(this->getHeader());
		break;
	case REQ_QST:
		//_rep.assign(this->getHeader()+ " : "+ std::to_string(readPort()) + "\n\r");
		_rep.assign(std::to_string(readPort()) + "\n\r");
		break;
	case REQ_RTST:
		if(this->staterelaysecu == 1){
			HAL_GPIO_WritePin(GPIOG,EXT_IT_SECU_Pin , GPIO_PIN_SET); //PIN RELAY IT SECU
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13 , GPIO_PIN_SET); //PIN RELAY IT SECU
		}else{
			HAL_GPIO_WritePin(GPIOG,EXT_IT_SECU_Pin , GPIO_PIN_RESET); //PIN RELAY IT SECU
			HAL_GPIO_WritePin(GPIOF,GPIO_PIN_13 , GPIO_PIN_RESET); //PIN RELAY IT SECU
		}
		break;

	case REQ_I2CEXT1TST:
		//_rep.assign(testI2CEXT1() + "\n\r");
		I2Cscanner(I2C2);
		break;
	case REQ_I2CEXT2TST:
		//_rep.assign(testI2CEXT2() + "\n\r");
		I2Cscanner(I2C1);
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int EXPSEC::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("DATA ?") == 0){
		sel = REQ_QST;
	}else if(_cmde.compare(0, 5, "RTST ") == 0){
		int value = 0;

		value = stoi(_cmde.substr(5), nullptr, 10);
		if (value == 0 ){
			sel = REQ_RTST;
			this->staterelaysecu = value;
		}else if(value == 1){
			sel = REQ_RTST;
			this->staterelaysecu = value;
		}else{
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
			//throw
		}
	}else if(_cmde.compare("I2CEXT1 ?") == 0){
		sel = REQ_I2CEXT1TST;
	}else if(_cmde.compare("I2CEXT2 ?") == 0){
		sel = REQ_I2CEXT2TST;
	}else {
		//throw something
	}
	return sel;
}

uint16_t EXPSEC::readPort(){
	uint8_t data = 0;
	uint16_t value = 0;

	uint16_t value2 = 0x0000;

	TM_I2C_WriteNoRegister(I2C3, EXPSECU_I2CADD, 0x00); //write input port 0
	TM_I2C_ReadNoRegister(I2C3, (EXPSECU_I2CADD)|(1u<<0), &data); //read from input port 0

	value = data;
	value2 = data;

	TM_I2C_WriteNoRegister(I2C3, EXPSECU_I2CADD, 0x01); //write input port 1
	TM_I2C_ReadNoRegister(I2C3, (EXPSECU_I2CADD)|(1u<<0), &data); //read from input port 1

	value = value + data;
	value2 = value2 + (data<<8);

	TM_I2C_IsDeviceConnected(I2C3, EXPSECU_I2CADD);

	return value2;
}


std::string EXPSEC::testI2CEXT1(){
	UART_transmit("Test I2C2 EXT1");
	enableI2C_EXT1();
	while(1){CheckI2C2();}
	disableI2C_EXT1();

	if(CheckI2C2() == 0){
		disableI2C_EXT1();
		return "I2C2 EXT1 OK";
	}else{
		disableI2C_EXT1();
		return "I2C2 EXT1 NOK";
	}

}

std::string EXPSEC::testI2CEXT2(){
	UART_transmit("Test I2C1 EXT2");
	enableI2C_EXT2();
	while(1){CheckI2C1();}
	disableI2C_EXT2();

	if(CheckI2C1() == 0){
		disableI2C_EXT2();
		return "I2C1 EXT2 OK";
	}else{
		disableI2C_EXT2();
		return "I2C1 EXT2 NOK";
	}
}

int EXPSEC::configseq(){


	return 0;
}
