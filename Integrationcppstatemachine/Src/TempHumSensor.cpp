/*
 * TempHumSensor.cpp
 *
 *  Created on: 28 mai 2020
 *      Author: PARIS
 */

#include "TempHumSensor.h"
#include "ScpiClientServer.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <string>
#include <iostream>

TempHumSensor::TempHumSensor() {
	// TODO Auto-generated constructor stub
	this->temperature =0;
	this->huidity=0 ;
	this->i2csensoraddr = TEMP_HUM_SENS8_I2CADD;
}

TempHumSensor::TempHumSensor(std::string _name): ScpiClientServer(_name),temperature(0),huidity(0),i2csensoraddr(TEMP_HUM_SENS8_I2CADD){

}

TempHumSensor::~TempHumSensor() {
	// TODO Auto-generated destructor stub
}

short int TempHumSensor::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe TEMPHUM");
	int test =0;
	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//RESET ?
		break;
	case REQ_IDN:
		_rep.assign("je suis le client HARDWARE " + this->getHeader());
		break;
	case REQ_HUM:
		_rep.assign(_cmde +" : "+std::to_string(readTemp())+"\n\r");
		break;
	case REQ_TEMP:
		_rep.assign(_cmde +" : "+std::to_string(readTemp())+"\n\r");
		break;
	case REQ_TST:
		//_rep.assign(_cmde +" tem/hum: "+std::to_string(TM_I2C_IsDeviceConnected(I2C4, this->i2csensoraddr))+"\n\r"+" exp: "+std::to_string(TM_I2C_IsDeviceConnected(I2C4, 0x40))+"\n\r"+" potnum: "+std::to_string(TM_I2C_IsDeviceConnected(I2C4, 0x58
				//))+"\n\r");
		test = TM_I2C_IsDeviceConnected(I2C4, this->i2csensoraddr);//tem/hum
		test = TM_I2C_IsDeviceConnected(I2C4, 0x40);//exp
		test = TM_I2C_IsDeviceConnected(I2C4, 0x58); //pot
		test = TM_I2C_IsDeviceConnected(I2C4, 0xA0); //mem u3
		test = TM_I2C_IsDeviceConnected(I2C4, 0xA0); //mem u4 ?????
		test = TM_I2C_IsDeviceConnected(I2C4, 0xA4); //mem u5
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int TempHumSensor::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*RST") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("HUM ?") == 0){
		sel = REQ_HUM;
	} else if(_cmde.compare("TEMP ?") == 0){
		sel = REQ_TEMP;
	}else if(_cmde.compare("TST") == 0){
		sel = REQ_TST;
	} else {
		//throw something
	}
	return sel;
}

float TempHumSensor::readTemp(){
	uint8_t MSBLSB[2] = {0x2c,0x06}; //repeatability low, clock stretching enable
	uint8_t out[2] = {0x00,0x00};
	int test = 0;


	test = TM_I2C_WriteNoRegister(I2C4, this->i2csensoraddr, 0x00);
	test = TM_I2C_WriteNoRegister(I2C4, this->i2csensoraddr,  0x24);


	test = TM_I2C_WriteMultiNoRegister(I2C4, this->i2csensoraddr, MSBLSB, 2);
	test = TM_I2C_ReadMultiNoRegister(I2C4, this->i2csensoraddr, out, 2);

	return 0;
}
float TempHumSensor::readHum(){

	return 0;
}

