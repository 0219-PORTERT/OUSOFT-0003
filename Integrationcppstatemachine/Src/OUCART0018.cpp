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
#include "FonctionsAutotest.h"


/**
 * @brief  Constructeur pour OUCART-0018 avec rack (le rack se charge de l'ini dans le constructeur de OUELEC-0158)
 * @retval None
 */
OUCART0018::OUCART0018() {
	// TODO Auto-generated constructor stub
	this->mem1.setI2cAdress(EEPROM1_I2CADD);
}

/**
 * @brief  Constructeur pour OUCART-0018 seule
 * @param  _i2cadress: adresse i2c
 * @retval None
 */
OUCART0018::OUCART0018(uint8_t _i2cadress) {
	this->i2cadress = _i2cadress;//ini adresse i2c oucart-0018
	this->mem1.setI2cAdress(EEPROM1_I2CADD);//donne à l'objet mémoire contenu dans oucart-0018 son adress
}

/**
 * @brief  config l'adresse i2c de oucart-0018 (fait par le rack ouelec-0158)
 * @param  _adr: adresse du rack ( les microswitch sur oucart-0020)
 * @retval None
 */
void OUCART0018::setI2cAdress(uint8_t adr){
	this->i2cadress = SWITCHI2C | adr; //OU logique entre l'adresse fixe du switch i2c avec l'adresse du rack ( les microswitch sur oucart-0020)
}

OUCART0018::~OUCART0018() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief  selectionne la channel du switch i2c de oucart-0018
 * @param  i2cchannel: channel à selectionner
 * @retval None
 */
uint8_t OUCART0018::switchToi2c(uint8_t i2cchannel){

	uint8_t data[1];
	data[0] = 0;
	switch(i2cchannel){
		case 0://channel 0 -> i2c interne à oucart-0018
			TM_I2C_WriteNoRegister(I2C1, this->i2cadress, 0x01);
			TM_I2C_ReadNoRegister(I2C1, (this->i2cadress | (1u<<0)), data);
			break;
		case 1://channel 1 -> i2c extern 1 de oucart-0018, ici oucart-0020
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
			TM_I2C_WriteNoRegister(I2C1, this->i2cadress, 0x00);//desactive toutes les channel
			break;
	}

	return 0;
}

/**
 * @brief  recupère la chaine json de la mémoire
 * @param  &_toread: buffer de lecture
 * @retval None
 */
uint8_t OUCART0018::getJsonStringfromMemory(std::string &_toread){
	uint8_t test =0;

	this->switchToi2c(0);//switch to oucart-0018
	this->mem1.readfrommemory(_toread);//lecture
	this->switchToi2c(6);//desactive le switch
	return test;
}

/**
 * @brief  enregistre la chaine json dans la mémoire
 * @param  &_towrite: buffer d'écriture
 * @retval None
 */
uint8_t OUCART0018::storeJsonStringtoMemory(std::string &_towrite){
	uint8_t test =0;

	this->switchToi2c(0);
	this->mem1.writetomemory(_towrite);
	this->switchToi2c(6);
	return test;

}

/**
 * @brief  envoie la commande de température au potentiomètre numérique
 * @param  code: code décimal
 * @param  capteur: voie du potentiomètre
 * @retval None
 */
void OUCART0018::setTemp(uint8_t code, uint8_t capteur ){
	this->switchToi2c(0); //switch to i2c channel 0 carte 0018
	TM_I2C_Write(I2C1,POT_I2CADD, capteur, code);
	this->switchToi2c(6);
}

/**
 * @brief  configure la direction de l'exp
 * @param  side: coté de l'exp
 * @param  dir: direction des pins à configurer
 * @retval None
 */
void OUCART0018::setDir(uint8_t side, uint8_t dir){
	this->switchToi2c(0); //switch to i2c channel 0 carte 0018
	TM_I2C_Write(I2C1, EXPSECU_I2CADD, side, dir);
	this->switchToi2c(6);
}

/**
 * @brief  ecrit sur l'expander
 * @param  side: coté de l'exp
 * @param  dir: pins à écrire
 * @retval None
 */
void OUCART0018::writePort(uint8_t side, uint8_t writeBits){
	this->switchToi2c(0); //switch to i2c channel 0 carte 0018
	TM_I2C_Write(I2C1, EXPSECU_I2CADD, side, writeBits);
	this->switchToi2c(6);
}

/**
 * @brief  lit la valeur de l'expander
 * @param  side: coté de l'exp
 * @param  *data: valeur lue sur l'expander
 * @retval None
 */
void OUCART0018::readPort(uint8_t side, uint8_t *data){
	this->switchToi2c(0); //switch to i2c channel 0 carte 0018

/*	uint8_t test = 0;

	test = (uint8_t)TM_I2C_IsDeviceConnected(I2C1, EXPSECU_I2CADD);*/

	TM_I2C_WriteNoRegister(I2C1, EXPSECU_I2CADD, side); //write input port 1
	TM_I2C_ReadNoRegister(I2C1, (EXPSECU_I2CADD)|(1u<<0), data); //read from input port 1
	this->switchToi2c(6);
}

/**
 * @brief  test si la oucart-0018 est connectée
 * @retval 0 si la carte est bien connectée
 */
uint8_t OUCART0018::isConnected(){
	return (uint8_t)TM_I2C_IsDeviceConnected(I2C1, this->i2cadress);
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
