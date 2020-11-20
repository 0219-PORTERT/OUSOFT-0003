/*
 * SCPIclientserveurADDO.cpp
 *
 *  Created on: 7 oct. 2020
 *      Author: PARIS
 */

#include "SCPIclientserveurADDO.h"
#include "EXPADDO24.h"
#include <String>
#include <iostream>

SCPIclientserveurADDO::SCPIclientserveurADDO() {
	// TODO Auto-generated constructor stub

}

SCPIclientserveurADDO::SCPIclientserveurADDO(std::string _name): ScpiClientServer(_name) {
	this->staterelay = 0;
	this->writevalue = 0;
	this->dir = -1;

	ExpADDOa.setSide(0);
	ExpADDOb.setSide(1);
	ExpADDOc.setSide(2);

	this->reltochange = 0;
	this->statereltochange = 0;
}

SCPIclientserveurADDO::~SCPIclientserveurADDO() {
	// TODO Auto-generated destructor stub
}

short int SCPIclientserveurADDO::ExecuteCmde (std::string& _cmde,std::string& _rep){
	switch (decodeInstruct(_cmde)) {

		case REQ_RST:
			//reset
			break;
		case REQ_IDN:
			_rep.assign(this->getHeader());
			break;
		case REQ_DIOARD:
			_rep.assign(std::to_string(ExpADDOa.readPort()));
			break;
		case REQ_DIOBRD:
			_rep.assign(std::to_string(ExpADDOb.readPort()));
			break;
		case REQ_DIOCRD:
			_rep.assign(std::to_string(ExpADDOc.readPort()));
			break;
		case REQ_DIOAWR:
			ExpADDOa.writePort(this->writevalue);
			break;
		case REQ_DIOBWR:
			ExpADDOb.writePort(this->writevalue);
			break;
		case REQ_DIOCWR:
			ExpADDOc.writePort(this->writevalue);
			break;
		case REQ_DIOAQSTDIR:
			_rep.assign(std::to_string(ExpADDOa.getDir()));
			break;
		case REQ_DIOBQSTDIR:
			_rep.assign(std::to_string(ExpADDOb.getDir()));
			break;
		case REQ_DIOCQSTDIR:
			_rep.assign(std::to_string(ExpADDOc.getDir()));
			break;
		case REQ_DIOASETDIR:
			ExpADDOa.setDir(this->dir);
			break;
		case REQ_DIOBSETDIR:
			ExpADDOb.setDir(this->dir);
			break;
		case REQ_DIOCSETDIR:
			ExpADDOc.setDir(this->dir);
			break;
		case REQ_RELAY:
			configRelay(this->statereltochange, this->reltochange);
			break;
		case REQ_TSTAB:
			_rep.assign(ExpADDOa.testAB(0xAA) + "\n\r" +ExpADDOb.testAB(0x55) +"\n\r");
			break;
		case REQ_TSTAC:
			_rep.assign(ExpADDOa.testAC(0xAA) + "\n\r" +ExpADDOc.testAC(0x55) +"\n\r");
			break;
		default:
			//throw something;
			break;
		}
	this->reltochange = 0;
	this->statereltochange = 0;
	return 0;
}

int SCPIclientserveurADDO::decodeInstruct(std::string& _cmde){
	int sel = 0;

	if (_cmde.compare("*CLR") == 0) {
		sel = REQ_RST;
	}else if (_cmde.compare("*IDN ?") == 0) {
		sel = REQ_IDN;
	}else if(_cmde.compare("DIOARD ?") == 0){
		sel = REQ_DIOARD;
	}else if(_cmde.compare("DIOBRD ?") == 0){
		sel = REQ_DIOBRD;
	}else if(_cmde.compare("DIOCRD ?") == 0){
		sel = REQ_DIOCRD;
	}else if(_cmde.compare(0, 7, "DIOAWR ") == 0){
		int value = 0;

		value = stoi(_cmde.substr(7), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->writevalue = value;
			sel = REQ_DIOAWR;
		}
	}else if(_cmde.compare(0, 7, "DIOBWR ") == 0){
		int value = 0;

		value = stoi(_cmde.substr(7), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->writevalue = value;
			sel = REQ_DIOBWR;
		}
	}else if(_cmde.compare(0, 7, "DIOCWR ") == 0){
		int value = 0;

		value = stoi(_cmde.substr(7), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->writevalue = value;
			sel = REQ_DIOCWR;
		}
	}else if(_cmde.compare("DIOADIR ?") == 0){
		sel = REQ_DIOAQSTDIR;
	}else if(_cmde.compare("DIOBDIR ?") == 0){
		sel = REQ_DIOBQSTDIR;
	}else if(_cmde.compare("DIOCDIR ?") == 0){
		sel = REQ_DIOCQSTDIR;
	}
	else if(_cmde.compare(0, 11, "DIOASETDIR ") == 0){
		int value = 0;
		value = stoi(_cmde.substr(11), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->dir = value;
			sel = REQ_DIOASETDIR;
		}
	}else if(_cmde.compare(0, 11, "DIOBSETDIR ") == 0){
		int value = 0;
		value = stoi(_cmde.substr(11), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->dir = value;
			sel = REQ_DIOBSETDIR;
		}
	}else if(_cmde.compare(0, 11, "DIOCSETDIR ") == 0){
		int value = 0;
		value = stoi(_cmde.substr(11), nullptr, 10);
		if ((value < 0) || (value > 255)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->dir = value;
			sel = REQ_DIOCSETDIR;
		}
	}else if(_cmde.compare(0, 5, "REL K") == 0){
		int value = 0;
		std::size_t pos = -1;

		value = stoi(_cmde.substr(5), nullptr, 10);
		if ((value < 0) || (value > 17)) {
			sel = -1; //bonne commande mais mauvaise valeur car mal convertie ou autre
		} else {
			this->reltochange = value-1;
		}


		pos = _cmde.find_last_of(" ");
		if(pos == -1){
			sel = -1;
		}else{
			if(_cmde.substr(pos+1).compare("ON") == 0){
				this->statereltochange =1;
				sel = REQ_RELAY;
			}if(_cmde.substr(pos+1).compare("OFF") == 0){
				this->statereltochange =0;
				sel = REQ_RELAY;
			}
		}


	}else if(_cmde.compare(0, 4, "LEV ") == 0){
		if(_cmde.substr(4).compare("ON") == 0){
			this->reltochange = K11;
			this->statereltochange =1;
			sel = REQ_RELAY;
		}else if(_cmde.substr(4).compare("OFF") == 0){
			this->reltochange = K11;
			this->statereltochange =0;
			sel = REQ_RELAY;
		}else{
			sel = -1;
		}
	}else if(_cmde.compare(0, 4, "ROT ") == 0){
		if(_cmde.substr(4).compare("ON") == 0){
			this->reltochange = K12;
			this->statereltochange =1;
			sel = REQ_RELAY;
		}else if(_cmde.substr(4).compare("OFF") == 0){
			this->reltochange = K12;
			this->statereltochange =0;
			sel = REQ_RELAY;
		}else{
			sel = -1;
		}
	}else if(_cmde.compare(0, 4, "CLR ") == 0){
		if(_cmde.substr(4).compare("ON") == 0){
			this->reltochange = K13;
			this->statereltochange =1;
			sel = REQ_RELAY;
		}else if(_cmde.substr(4).compare("OFF") == 0){
			this->reltochange = K13;
			this->statereltochange =0;
			sel = REQ_RELAY;
		}else{
			sel = -1;
		}
	}else if(_cmde.compare(0, 4, "SPA ") == 0){
		if(_cmde.substr(4).compare("ON") == 0){
			this->reltochange = K14;
			this->statereltochange =1;
			sel = REQ_RELAY;
		}else if(_cmde.substr(4).compare("OFF") == 0){
			this->reltochange = K14;
			this->statereltochange =0;
			sel = REQ_RELAY;
		}else{
			sel = -1;
		}
	}else if(_cmde.compare("TSTAB ?") == 0){
		sel = REQ_TSTAB;
	}else if(_cmde.compare("TSTAC ?") == 0){
		sel = REQ_TSTAC;
	}else {
		//throw something
	}
	return sel;
}



uint8_t SCPIclientserveurADDO::configRelay(uint8_t newstate, uint16_t relayTochange){

	uint8_t sidea = 0;
	uint8_t sideb = 0;


	if(this->staterelay & (1u << relayTochange )){// = etat actuel du relais 1
		if(newstate == 1){
			this->staterelay = (this->staterelay | (1u<<relayTochange)); // mise a 1 meme si deja a 1
		}else{
			this->staterelay = (this->staterelay & ~(1u<<relayTochange)); //mise a 0 car a 1 avant
		}
	}else{// = etat actuel du relais 0
		if(newstate == 0){
			this->staterelay = (this->staterelay & ~(1u<<relayTochange)); //mise a 0 meme si déja a 0
		}else{
			this->staterelay = (this->staterelay | (1u<<relayTochange)); //mise a 1 car 0 avant
		}
	}



	sidea = this->staterelay & 0x00ff;
	sideb = ((this->staterelay & 0xff00)>>8);



	ExpADDOa.writePort(sidea);
	ExpADDOb.writePort(sideb);

	ExpADDOc.writePort(RelayboardAddress);

	ExpADDOc.writePort(0);
	ExpADDOa.writePort(0);
	ExpADDOb.writePort(0);

	return 0;
}
