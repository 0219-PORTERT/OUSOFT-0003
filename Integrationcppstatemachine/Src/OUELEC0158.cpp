/*
 * OUELEC0158.cpp
 *
 *  Created on: 23 nov. 2020
 *      Author: PARIS
 */

#include "OUELEC0158.h"
#include <string>
#include <iostream>
#include "json.hpp"
#include "i2c.h"

OUELEC_0158::OUELEC_0158() {
	// TODO Auto-generated constructor stub

}

/**
 * @brief  Constructeur pour ouelec-0158
 * @param  _adressrack: adresse du rack
 * @retval None
 */
OUELEC_0158::OUELEC_0158(uint8_t _adressrack) {
	this->adressrack = _adressrack<<1;//shift de 1 pour ajouter le bit /RW à la fin de l'adresse i2c
	this->jsonstruct = {
				{"IDN", {
						{"PART_NB","PARTXXXX"},
						{"SERIAL_NB","SERXXXX"},
						{"AFFAIRE","XXXX"},
						{"REV","XXXX"}
				}},
				{"MCO", {
						{"MCO_N_DATE","10/12/20"},
						{"CAL_N_DATE","10/12/20"},
				}},
				{"CAL", {
						{"CFA",{0,0,0,0,0}},
						{"CFB",{0,0,0,0,0}},
				}},
		};// structure json


	this->carteEIC1.setI2cAdress(this->adressrack);//configure l'adresse i2c de la oucart-0018 du rack
	this->carteLEM1.setI2cAdress(ADCDAC_I2CADD);//configure l'adresse i2c de la oucart-0020 du rack

	for(int i = 0; i<6;i++){// ini des coef de calibration
		this->tabCfa[i] = 0;
		this->tabCfb[i] = 0;
	}
	this->partNb.assign("null");
	this->serialNb.assign("null");
	this->affaire.assign("null");
	this->calDate.assign("null");
	this->mcoDate.assign("null");
}



OUELEC_0158::~OUELEC_0158() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief  initialise le rack
 * @retval None
 */
void OUELEC_0158::init(){

	carteEIC1.switchToi2c(1); //switch to lem
	carteLEM1.enableInternalRef();//enable ref

	carteLEM1.setconfigADC(0x1f); //00011111
	carteLEM1.setconfigDAC(0xe0); //11100000

	carteEIC1.switchToi2c(6); //switchto eic
}

/**
 * @brief  configure l'adresse du rack
 * @param  adr: adresse du rack
 * @retval None
 */
void OUELEC_0158::setRackadress(uint8_t adr){
	this->adressrack = adr;
}

/**
 * @brief  renvoi l'adresse du rack
 * @retval adresse rack
 */
uint8_t OUELEC_0158::getRackadress(void){
	return this->adressrack;
}

/**
 * @brief  lire le courant avec l'adc de oucart-0020 avec calibration
 * @param  channel: channel à lire
 * @retval courant lu
 */
float OUELEC_0158::readCurrent(uint8_t channel){

	float value;
	value = (((carteLEM1.readADC(channel) - 2047.0f)*(5.0f/4095.0f))/(0.04167))*this->tabCfa[channel]+this->tabCfb[channel];//centrage, conversion en volt, conversion en courant, coef calibration
	return value;
}

/**
 * @brief  lire le code de l'adc de oucart-0020
 * @param  channel: channel à lire
 * @retval code adc lu
 */
uint16_t OUELEC_0158::readADC(uint8_t channel){
	return carteLEM1.readADC(channel);
}

/**
 * @brief  configure la postion pour le dac
 * @param  channel: channel à lire
 * @param  value: Valeur à écrire dans le dac
 * @retval None
 */
uint8_t OUELEC_0158:: setPosition(uint8_t channel, int value){

	carteEIC1.switchToi2c(1);
	carteLEM1.setDAC( channel, value);
	carteEIC1.switchToi2c(0);

	return 0;
}

/**
 * @brief  charge le json dans le µC
 * @retval retourne 0 si ok
 */
uint8_t OUELEC_0158::loadJson(){

	std::string s;
	s.reserve(256);
	s.assign("\0");
	uint8_t error =0;
	carteEIC1.getJsonStringfromMemory(s);// lecture de la chaine json de la mémoire

	try{

	this->jsonstruct = json::parse(s);//conversion chaine en json

	tabCfa[0] = this->jsonstruct.at("/CAL/CFA/0"_json_pointer);//chargement des tableaux de calibration
	tabCfa[1] = this->jsonstruct.at("/CAL/CFA/1"_json_pointer);
	tabCfa[2] = this->jsonstruct.at("/CAL/CFA/2"_json_pointer);
	tabCfa[3] = this->jsonstruct.at("/CAL/CFA/3"_json_pointer);
	tabCfa[4] = this->jsonstruct.at("/CAL/CFA/4"_json_pointer);

	tabCfb[0] = this->jsonstruct.at("/CAL/CFB/0"_json_pointer);
	tabCfb[1] = this->jsonstruct.at("/CAL/CFB/1"_json_pointer);
	tabCfb[2] = this->jsonstruct.at("/CAL/CFB/2"_json_pointer);
	tabCfb[3] = this->jsonstruct.at("/CAL/CFB/3"_json_pointer);
	tabCfb[4] = this->jsonstruct.at("/CAL/CFB/4"_json_pointer);

	this->partNb.assign(this->jsonstruct.at("/IDN/PART_NB"_json_pointer));//chargement des infos des rack
	this->serialNb.assign(this->jsonstruct.at("/IDN/SERIAL_NB"_json_pointer));
	this->affaire.assign(this->jsonstruct.at("/IDN/AFFAIRE"_json_pointer));
	this->calDate.assign(this->jsonstruct.at("/MCO/CAL_N_DATE"_json_pointer));
	this->mcoDate.assign(this->jsonstruct.at("/MCO/MCO_N_DATE"_json_pointer));


	}catch(json::parse_error& e){

		tabCfa[0] = 1;//valeur par defauts si problème pendant le chargement de la chaine
		tabCfa[1] = 1;
		tabCfa[2] = 1;
		tabCfa[3] = 1;
		tabCfa[4] = 1;

		tabCfb[0] = 0;
		tabCfb[1] = 0;
		tabCfb[2] = 0;
		tabCfb[3] = 0;
		tabCfb[4] = 0;

		this->partNb.assign("UNKNOW PART NB");
		this->serialNb.assign("UNKNOW SERIAL NB");
		this->affaire.assign("UNKNOW AFFAIR NB");
		this->calDate.assign("UNKNOW LAST CAL");
		this->mcoDate.assign("UNKNOW LAST MCO");

		error = 1;
	}
	catch (json::out_of_range& e)
	{
		error = 2;
	}
return error;
}

std::string OUELEC_0158::getPartnb(){
	return this->partNb;
}
std::string OUELEC_0158::getSerialnb(){
	return this->serialNb;
}
std::string OUELEC_0158::getAffaire(){
	return this->affaire;
}
std::string OUELEC_0158::getLastcal(){
	return this->calDate;
}
std::string OUELEC_0158::getLastmco(){
	return this->mcoDate;
}
