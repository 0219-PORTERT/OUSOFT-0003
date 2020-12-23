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

/**
 * @brief  Constructeur pour mémoire
 * @param  _i2cadress: adresse i2c
 * @retval None
 */
Memory::Memory(uint8_t _i2cadress): i2cadress(_i2cadress) {

}

Memory::~Memory() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief  fixe l'adresse i2c
 * @param  adr: adresse i2c
 * @retval None
 */
void Memory::setI2cAdress(uint8_t adr){
	this->i2cadress = adr;
}


/**
 * @brief  lecture du contenu de la mémoire
 * @param  &_toread: reférence du buffer de lecture
 * @retval retourne 0 si la lecture à fonctionné
 */
uint8_t Memory::readfrommemory(std::string &_toread){

	uint8_t dummy[2] = {};
	uint8_t dataread[256]= {};
	uint8_t test = 0;

	test = (uint8_t)TM_I2C_IsDeviceConnected(I2C4, this->i2cadress);//test si la mémoire est connecté


	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, dummy, sizeof(dummy));//dummy write
	TM_I2C_ReadMultiNoRegister(I2C1, (this->i2cadress | (1u<<0)), dataread, 256);//reception


	std::string buffer((char*)dataread);//conversion en std::string

	_toread.assign(buffer);//ajout au buffer


	return test;
}

/**
 * @brief  ecrit dans la mémoire
 * @param  &_towrite: reférence du buffer d'ecriture
 * @retval retourne 0 si l'écriture à fonctionné
 */
uint8_t Memory::writetomemory(std::string &_towrite){


	int a = _towrite.length()+3;//+2 car les 2 1er caractère servent à definir la page, +1 pour ajouter la fin de trame '\0'
	uint8_t test = 0;

	uint8_t data[a] = {};

	data[0] = 0;//page 0
	data[1] = 0;//page 0

	for(int i =0; i<sizeof(data); i++){//copie de la chaine en tableau de caractère
		data[i+2] = _towrite[i];
	}

	//data[a-1] = '\0';



	test = (uint8_t)TM_I2C_IsDeviceConnected(I2C1, this->i2cadress);//test si la mémoire est connectée

	//this->eraseAll();
	//I2Cscanner(I2C1);
	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data, sizeof(data));//ecriture

	return test;
}



void Memory::eraseAll(){
	uint8_t data2[255];

	for(int i =0; i<sizeof(data2);i++){
		data2[i] = '\0';
	}
	TM_I2C_WriteMultiNoRegister(I2C1, this->i2cadress, data2, sizeof(data2));
}


/**
 * @brief  transforme la structure json en chaine
 * @retval retourne la chaine json
 */
std::string Memory::serialize(){
	std::string s;
	return s.assign(this->jsonstruct.dump());
}

/**
 * @brief  transforme une chaine formatée en structure json
 * @retval None
 */
void Memory::deserialize(std::string s){
	this->jsonstruct = s;
}

/**
 * @brief  renvoie la structure json
 * @retval retourne la structure json
 */
nlohmann::json Memory::getjsonstruct(){
	return this->jsonstruct;
}

/**
 * @brief  renvoie une référence de la structure json
 * @param  & j: Référence json
 * @retval None
 */
void  Memory::getjsonstructref(json& j){
	j = this->jsonstruct;
}

