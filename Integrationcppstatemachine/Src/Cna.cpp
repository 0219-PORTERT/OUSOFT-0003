/*
 * Cna.cpp
 *
 *  Created on: 22 avr. 2020
 *      Author: PARIS
 */

#include "Cna.h"
#include "ScpiClientServer.h"
#include <string>
#include <iostream>
#include "dac.h"

Cna::Cna() {
	// TODO Auto-generated constructor stub
	modValue = 0;

}
Cna::Cna(std::string _name): ScpiClientServer(_name), modValue(0) {
	// TODO Auto-generated constructor stub
	this->rack.setRackadress(NULL);
}

Cna::Cna(std::string _name,OUELEC_0158 _rack, uint8_t _channel): ScpiClientServer(_name), rack(_rack), channel(_channel),modValue(0) {

}

Cna::~Cna() {
	// TODO Auto-generated destructor stub
}

short int Cna::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe CNA");

	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		this->modValue = 0;
		//Set_Dac_Value(DAC_CHANNEL_1, 0); // reset
		//Set_Dac_Value(DAC_CHANNEL_2, 0);

		setModulation();

		break;
	case REQ_IDN:
		//_rep.assign("je suis le client HARDWARE " + this->getHeader());
		_rep.assign(this->getHeader());
		break;
	case REQ_x:
		//Set_Dac_Value(DAC_CHANNEL_1, this->modValue);
		//Set_Dac_Value(DAC_CHANNEL_2, this->modValue);
		setModulation();

		break;
	case REQ_QST:
		//_rep.assign("MOD: " + std::to_string(this->modValue) + "\n\r"); //request
		_rep.assign(std::to_string(this->modValue)); //request
		break;

	default:
		throw ERROR_CMD_BAD_ARG;
		break;
	}

	return 0;
}

int Cna::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
		this->modValue = 0;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if (_cmde.compare("MOD ?") == 0) {
		sel = REQ_QST;
	} else if (_cmde.compare(0, 4, "MOD ") == 0) {
		int value = 0;
		value = stoi(_cmde.substr(4), nullptr, 10);

		if ((value < -100) || (value > 100)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->modValue = value;
			sel = REQ_x;
		}
	} else {
		throw ERROR_CMD_SCPIHARD_SYNTHAX_ERROR;
	}
	return sel;
}


void Cna::setModulation(){
	if(this->rack.getRackadress() == NULL){
		if(this->channel == 1){
			Set_Dac_Value(DAC_CHANNEL_1, this->modValue);
		}else if(this->channel == 2){
			Set_Dac_Value(DAC_CHANNEL_2, this->modValue);
		}else{
			//mauvaise channel
		}
	}else{
		rack.setPosition(this->channel, this->modValue);
	}
}
