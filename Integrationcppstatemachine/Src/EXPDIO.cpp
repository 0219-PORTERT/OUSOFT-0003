/*
 * EXPDIO.cpp
 *
 *  Created on: 27 août 2020
 *      Author: PARIS
 */

#include "EXPDIO.h"
#include "tm_stm32_i2c.h"
#include "i2c.h"
#include <String>
#include <iostream>
#include "OUELEC0158.h"

EXPDIO::EXPDIO() {
	// TODO Auto-generated constructor stub

}

/**
 * @brief  Constructeur expdio pour utilisation de l'expander 16bits de oucart-0014
 * @param  _name: Nom à donner au client
 * @param  _side: coté a ou b
 * @retval None
 */
EXPDIO::EXPDIO(std::string _name, uint8_t _side): ScpiClientServer(_name), side(_side) {
	// TODO Auto-generated constructor stub

	this->direction = -1; //entrée
	this->rack.setRackadress(NULL);
}

/**
 * @brief  Constructeur expdio pour utilisation de l'expander 16bits de oucart-0018
 * @param  _name: Nom à donner au client
 * @param  _side: coté a ou b
 * @param  _rack: rack où se trouve la oucart-0018
 * @retval None
 */
EXPDIO::EXPDIO(std::string _name, uint8_t _side,OUELEC_0158 _rack): ScpiClientServer(_name), side(_side), rack(_rack) {
	// TODO Auto-generated constructor stub

	this->direction = -1; //entrée

}

EXPDIO::~EXPDIO() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief  client execute commande scpi
 * @param  & _cmde: référence à la commande scpi à executer
 * @param  & _rep: référence à la chaine de réponse scpi si le client en a besoin
 * @retval peut retourner une erreur
 */
short int EXPDIO::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe EXPDIO");


	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//reset
		break;
	case REQ_IDN:
		_rep.assign(this->getHeader());
		break;
	case REQ_QSTRD:
		_rep.assign(std::to_string(readPort()));
		break;
	case REQ_WR:
		writePort();
		break;
	case REQ_QSTDIR:
		_rep.assign(std::to_string(this->direction));
		break;
	case REQ_SETDIR:
		setDir();
		break;
	case REQ_TST:
		_rep.assign(testAB(0xAA) + "\n\r" +testAB(0x55) +"\n\r");
		break;
	case REQ_SDR:
		_rep.assign(std::to_string(getSDR()));
		break;
	case REQ_RTR:
		_rep.assign(std::to_string(getRTR()));
		break;
	case REQ_MBA:
		_rep.assign(std::to_string(getMBA()));
		break;
	case REQ_THO:
		_rep.assign(std::to_string(getTHO()));
		break;
	case REQ_THM:
		_rep.assign(std::to_string(getTHM()));
		break;
	case REQ_THN:
		_rep.assign(std::to_string(getTHN()));
		break;
	case REQ_WDSDR:
		_rep.assign(std::to_string(getWDSDR()));
		break;
	case REQ_RTA:
		_rep.assign(std::to_string(getRTA()));
		break;

	default:
		throw ERROR_CMD_BAD_ARG;
		break;
	}

	return 0;
}

/**
 * @brief  décode les instructions scpi
 * @param  & _cmde: référence à la commande scpi à executer
 * @retval None
 */
int EXPDIO::decodeInstruct(std::string& _cmde) {
	/*toutes les instructions scpi*/
	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	}else if(_cmde.compare("RD ?") == 0){
		sel = REQ_QSTRD;
	}else if(_cmde.compare(0, 3, "WR ") == 0){
		int value = 0;

		value = stoi(_cmde.substr(3), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->writevalue = value;
			sel = REQ_WR;
		}
	}else if(_cmde.compare("DIR ?") == 0){
		sel = REQ_QSTDIR;
	}else if(_cmde.compare(0, 7, "SETDIR ") == 0){
		int value = 0;
		value = stoi(_cmde.substr(7), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->direction = value;
			sel = REQ_SETDIR;
		}

	}else if(_cmde.compare("TST ?") == 0){
		sel = REQ_TST;
	}else if(_cmde.compare("SDR ?") == 0){
		sel = REQ_SDR;
	}else if(_cmde.compare("RTR ?") == 0){
		sel = REQ_RTR;
	}else if(_cmde.compare("MBA ?") == 0){
		sel = REQ_MBA;
	}else if(_cmde.compare("THO ?") == 0){
		sel = REQ_THO;
	}else if(_cmde.compare("THM ?") == 0){
		sel = REQ_THM;
	}else if(_cmde.compare("THN ?") == 0){
		sel = REQ_THN;
	}else if(_cmde.compare("WDSDR ?") == 0){
		sel = REQ_WDSDR;
	}else if(_cmde.compare("RTA ?") == 0){
		sel = REQ_RTA;
	}else {
		throw ERROR_CMD_SCPIHARD_SYNTHAX_ERROR;
	}
	return sel;
}



/**
 * @brief  lit le port de l'expander
 * @retval valeur lu sur le port de l'expander
 */
uint8_t EXPDIO::readPort(){
	uint8_t data = -1;

	if(this->direction != 0xFF){
		this->direction = 0xFF; //config input
		setDir();
	}

	if(this->rack.getRackadress() == NULL){//pour oucart-0014
		if(this->side == SIDEA){
			TM_I2C_WriteNoRegister(I2C4, EXP_DIO_I2CADD, 0x00); //write input port 0
			TM_I2C_ReadNoRegister(I2C4, (EXP_DIO_I2CADD)|(1u<<0), &data); //read from input port 0
		}else{
			TM_I2C_WriteNoRegister(I2C4, EXP_DIO_I2CADD, 0x01); //write input port 1
			TM_I2C_ReadNoRegister(I2C4, (EXP_DIO_I2CADD)|(1u<<0), &data); //read from input port 1
		}
	}else{//pour oucart-0018
		if(this->side == SIDEA){
			this->rack.carteEIC1.readPort(0x00, &data);
		}else{
			this->rack.carteEIC1.readPort(0x01, &data);
		}
	}
	return data;
}

/**
 * @brief  ecrit sur le port de l'expander
 * @retval None
 */
uint8_t EXPDIO::writePort(){

	if(this->direction != 0x00){
		this->direction = 0x00; //config output
		setDir();
	}

	if(this->rack.getRackadress() == NULL){
		if(this->side == SIDEA){
			TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x02, this->writevalue);
		}else{
			TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x03, this->writevalue);
		}
	}else{
		if(this->side == SIDEA){
			this->rack.carteEIC1.writePort(0x02, this->writevalue);
		}else{
			this->rack.carteEIC1.writePort(0x03, this->writevalue);
		}
	}
	return 0;
}

/**
 * @brief  configure le port de l'expander
 * @param  _dir: indique quels pins seront en entrée ou sortie
 * @retval None
 */
uint8_t EXPDIO::setDir(){

	if(this->rack.getRackadress() == NULL){
		if(this->side == SIDEA){
			TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x06, this->direction);
		}else{
			TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x07, this->direction);
		}
	}else{
		if(this->side == SIDEA){
			this->rack.carteEIC1.setDir(0x06, this->direction);
		}else{
			this->rack.carteEIC1.setDir(0x07, this->direction);
		}
	}
	return 0;
}


std::string EXPDIO::testAB(uint8_t bytetotest){

	uint8_t data = -1;
	std::string error = "unknow error";

	if(this->side == SIDEA){

		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x07, 0xFF); //port B lecture
		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x06, 0x00); //port A ecriture

		//this->writevalue = bytetotest;
		//this->writePort();

		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x02, bytetotest);//ecriture port A


		TM_I2C_WriteNoRegister(I2C4, EXP_DIO_I2CADD, 0x01); //write input portB 1
		TM_I2C_ReadNoRegister(I2C4, (EXP_DIO_I2CADD)|(1u<<0), &data); //read from input portB 1

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}

	}else{

		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x07, 0x00); //port B ecriture
		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x06, 0xFF); //port A lecture


		//this->writevalue = bytetotest;
		//this->writePort();

		TM_I2C_Write(I2C4, EXP_DIO_I2CADD, 0x03, bytetotest);//ecriture port B


		TM_I2C_WriteNoRegister(I2C4, EXP_DIO_I2CADD, 0x00); //write input port 0
		TM_I2C_ReadNoRegister(I2C4, (EXP_DIO_I2CADD)|(1u<<0), &data); //read from input port 0

		if(data == bytetotest){
			return error.assign("OK");
		}else{
			return error.assign("error at:" + std::to_string(data));
		}


	}
	return error;
}


/**
 * @brief  recupère le bits sdr spécifiquement
 * @retval 1 ou 0 en fonction de l'etat de sdr
 */
uint8_t EXPDIO::getSDR(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 0)){//bits 0
		return 1;
	}else{
		return 0;
	}
}

/**
 * @brief  recupère le bits rtr spécifiquement
 * @retval 1 ou 0 en fonction de l'etat de rtr
 */
uint8_t EXPDIO::getRTR(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 1)){//bits 1
		return 1;
	}else{
		return 0;
	}
	return 0;
}

/**
 * @brief  recupère le bits mba spécifiquement
 * @retval 1 ou 0 en fonction de l'etat de mba
 */
uint8_t EXPDIO::getMBA(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 2)){//bits 2
		return 1;
	}else{
		return 0;
	}
	return 0;
}

/**
 * @brief  recupère le bits tho spécifiquement
 * @retval 1 ou 0 en fonction de l'etat de tho
 */
uint8_t EXPDIO::getTHO(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 3)){//bits 3
		return 1;
	}else{
		return 0;
	}
	return 0;
}

/**
 * @brief  recupère le bits thm spécifiquement
 * @retval 1 ou 0 en fonction de l'etat de thm
 */
uint8_t EXPDIO::getTHM(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 4)){//bits 4
		return 1;
	}else{
		return 0;
	}
	return 0;
}

/**
 * @brief  recupère le bits thn spécifiquement
 * @retval 1 ou 0 en fonction de l'etat de thn
 */
uint8_t EXPDIO::getTHN(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 5)){//bits 5
		return 1;
	}else{
		return 0;
	}
	return 0;
}

/**
 * @brief  recupère le bits wdsdr spécifiquement
 * @retval 1 ou 0 en fonction de l'etat de wdsdr
 */
uint8_t EXPDIO::getWDSDR(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 6)){//bits 6
		return 1;
	}else{
		return 0;
	}
	return 0;
}

/**
 * @brief  recupère le bits rta spécifiquement
 * @retval 1 ou 0 en fonction de l'etat de rta
 */
uint8_t EXPDIO::getRTA(void){
	uint8_t value = -1;
	value = this->readPort();

	if(value & (1u << 7)){//bits 7
		return 1;
	}else{
		return 0;
	}
	return 0;
}

