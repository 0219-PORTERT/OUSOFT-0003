/*
 * EXPADDO24.cpp
 *
 *  Created on: 7 sept. 2020
 *      Author: PARIS
 */

#include "EXPADDO24.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>


/**
 * @brief  Constructeur expaddo pour utilisation de l'expander 24bits
 * @param  _side: Nom à donner au client
 * @retval None
 */
EXPADDO24::EXPADDO24(uint8_t _side) {
	// TODO Auto-generated constructor stub
	this->direction = 0xff; //entrée
	this->side = _side;
}

EXPADDO24::EXPADDO24(){
	// TODO Auto-generated constructor stub



}

EXPADDO24::~EXPADDO24() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief  lit le port de l'expander
 * @retval valeur lu sur le port de l'expander
 */
uint8_t EXPADDO24::readPort(){
	uint8_t data = -1;

	if(this->direction != 0xFF){
		this->setDir(0xFF);//config input
	}

	if(this->side == SIDEC){
		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x00); //write input port 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 0
	}if(this->side == SIDEA){
		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x01); //write input port 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 1
	}if(this->side == SIDEB){
		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x02); //write input port 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 1
	}
	return data;
}

/**
 * @brief  ecrit sur le port de l'expander
 * @param  _writevalue: valeur à écrire
 * @retval None
 */
uint8_t EXPADDO24::writePort(uint8_t _writevalue){
	this->writevalue = _writevalue;

	//if(this->direction != 0x00){
		this->setDir(0x00);//config output
	//}

	if(this->side == SIDEC){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x04, this->writevalue);
	}if(this->side == SIDEA){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x05, this->writevalue);
	}if(this->side == SIDEB){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x06, this->writevalue);
	}
	return 0;
}

/**
 * @brief  configure le port de l'expander
 * @param  _dir: indique quels pins seront en entrée ou sortie
 * @retval None
 */
uint8_t EXPADDO24::setDir(uint8_t _dir){
	this->direction = _dir;

	if(this->side == SIDEC){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, this->direction);
	}if(this->side == SIDEA)
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0D, this->direction);
	if(this->side == SIDEB){
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0E, this->direction);
	}
	return 0;
}


std::string EXPADDO24::testAB(uint8_t bytetotest){
	uint8_t data = -1;
	std::string error = "unknow error";

	if(this->side == SIDEA){

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0D, 0xFF); //port B lecture
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, 0x00); //port A ecriture

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x04, bytetotest);//ecriture port A


		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x01); //write input portB 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input portB 1

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}

	}if(this->side == SIDEB){

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0D, 0x00); //port B ecriture
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, 0xFF); //port A lecture

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x05, bytetotest);//ecriture port B


		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x00); //write input port 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 0

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}


	}
	return error;
}
std::string EXPADDO24::testAC(uint8_t bytetotest){
	uint8_t data = -1;
	std::string error = "unknow error";

	if(this->side == SIDEA){

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0E, 0xFF); //port C lecture
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, 0x00); //port A ecriture

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x04, bytetotest);//ecriture port A


		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x02); //write input portC 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input portB 1

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}

	}if(this->side == SIDEC){

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0E, 0x00); //port C ecriture
		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x0C, 0xFF); //port A lecture

		TM_I2C_Write(I2C4, EXP_DATA_ADRESS_I2CADD, 0x06, bytetotest);//ecriture port C


		TM_I2C_WriteNoRegister(I2C4, EXP_DATA_ADRESS_I2CADD, 0x00); //write input portA 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DATA_ADRESS_I2CADD)|(1u<<0), &data); //read from input port 0

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}


	}
	return error;
}

/**
 * @brief  configure le port de l'expander
 * @param  _side: port a b ou c
 * @retval None
 */
void EXPADDO24::setSide(uint8_t _side){
	this->side = _side;
}


uint8_t EXPADDO24::getDir(){
	if(this->side == SIDEC){
		return this->direction;
	}if(this->side == SIDEA){
		return this->direction;
	}if(this->side == SIDEB){
		return this->direction;
	}
	return -1;
}
