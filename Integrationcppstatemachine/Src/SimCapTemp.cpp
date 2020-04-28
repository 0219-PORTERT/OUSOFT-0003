/*
 * SimCapTemp.cpp
 *
 *  Created on: 28 avr. 2020
 *      Author: PARIS
 */

#include "SimCapTemp.h"

SimCapTemp::SimCapTemp() {
	// TODO Auto-generated constructor stub
	this->capteur = TEMP1;
	this->tmpValue = 0;

}

SimCapTemp::SimCapTemp(std::string _name, uint8_t _capteur): ScpiClientServer(_name), capteur(_capteur) {
	// TODO Auto-generated constructor stub

}

SimCapTemp::~SimCapTemp() {
	// TODO Auto-generated destructor stub
}

short int SimCapTemp::ExecuteCmde(std::string& _cmde, std::string& _rep) {
	//_rep.assign("Je suis le execute de la classe SIMCAPTEMP");

	switch (decodeInstruct(_cmde)) {

	case REQ_RST:
		//RESET ?
		break;
	case REQ_IDN:
		_rep.assign("je suis le client HARDWARE " + this->getHeader() +" et je suis le capteur " + std::to_string(this->capteur));
		break;
	case REQ_x:
		//_rep.assign(_cmde +" : "+std::to_string(readADC())+"\n\r");
		break;
	case REQ_QST:
		//_rep.assign(_cmde +" : "+std::to_string(readADCImoy(NB_MOYENNE))+"\n\r");
		break;
	default:
		//throw something;
		break;
	}

	return 0;
}

int SimCapTemp::decodeInstruct(std::string& _cmde) {

	int sel = 0;

	if (_cmde.compare("*RST") == 0) {
		sel = REQ_RST;
	} else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	} else if(_cmde.compare("TMP ?") == 0){
		sel = REQ_QST;
	} else if(_cmde.compare(0, 4, "TMP ") == 0){
		int value = 0;
		value = stoi(_cmde.substr(4), nullptr, 10);

		if ((value < -40) || (value > 200)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			//this->modValue = value;
			sel = REQ_x;
		}
	}else {
		//throw something
	}
	return sel;
}
