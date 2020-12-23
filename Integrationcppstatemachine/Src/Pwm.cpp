/*
 * Pwm.cpp
 *
 *  Created on: 15 avr. 2020
 *      Author: PARIS
 */

#include "Pwm.h"
#include "ScpiClientServer.h"
#include <string>
#include <iostream>
#include <math.h>
#include "tim.h"

/**
 * @brief  Constructeur pour pwm
 * @retval None
 */
Pwm::Pwm() {
	// TODO Auto-generated constructor stub
	rpmValue = 0; //ini les pwm à 0;

}
/**
 * @brief  Constructeur pour pwm
 * @param  _name: nom du client
 * @retval None
 */
Pwm::Pwm(std::string _name) :
		ScpiClientServer(_name), rpmValue(0) {
	// TODO Auto-generated constructor stub
}

Pwm::~Pwm() {
	// TODO Auto-generated destructor stub
}

/**
 * @brief  client execute commande scpi
 * @param  & _cmde: référence à la commande scpi à executer
 * @param  & _rep: référence à la chaine de réponse scpi si le client en a besoin
 * @retval peut retourner une erreur
 */
short int Pwm::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe pwm");


	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		this->rpmValue = 0;
		startPwm(0);
		break;
	case REQ_IDN:
		//_rep.assign("je suis le client HARDWARE " + this->getHeader());
		_rep.assign(this->getHeader());
		break;
	case REQ_x:
		startPwm(this->rpmValue);
		break;
	case REQ_QST:
		_rep.assign(std::to_string(this->rpmValue) + "\n\r");
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
int Pwm::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if (_cmde.compare("RPM ?") == 0) {
		sel = REQ_QST;
	} else if (_cmde.compare(0, 4, "RPM ") == 0) {
		int value = 0;
		value = stoi(_cmde.substr(4), nullptr, 10);
		if ((value < 0) || (value > MAX_FREQ_VALUE)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			float floatFreq = value/60.0;
			this->rpmValue = round(floatFreq);
			sel = REQ_x;
		}
	} else {
		throw ERROR_CMD_SCPIHARD_SYNTHAX_ERROR;
	}
	return sel;
}
